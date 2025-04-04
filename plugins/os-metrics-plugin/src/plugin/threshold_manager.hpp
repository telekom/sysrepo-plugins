// telekom / sysrepo-plugin-os-metrics
//
// This program is made available under the terms of the
// BSD 3-Clause license which is available at
// https://opensource.org/licenses/BSD-3-Clause
//
// SPDX-FileCopyrightText: 2022 Deutsche Telekom AG
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef THRESHOLD_MANAGER_H
#define THRESHOLD_MANAGER_H

#include "filesystem_stats.hpp"
#include "memory_stats.hpp"
#include "utils/globals.h"

#include <chrono>
#include <condition_variable>
#include <map>
#include <math.h>
#include <mutex>
#include <sysrepo-cpp/Connection.hpp>
#include <thread>

namespace metrics {
using libyang::Context;
using libyang::DataNode;
using sysrepo::Connection;

struct Threshold {
    Threshold(long double val = 0.0) : value(val), rising(false), falling(false){};
    long double value;
    bool rising;
    bool falling;
};

struct UsageMonitoring {
    using thresholdMap_t = std::unordered_map<std::string, Threshold>;
    using fsThresholdTuple_t = std::tuple<uint32_t, thresholdMap_t>;

    void notify() {
        mCV.notify_all();
    }

    void injectConnection(Connection conn, std::string const& moduleName) {
        mConn = std::make_shared<Connection>(conn);
        mModuleName = moduleName;
    }

    void checkAndTriggerNotification(std::string const& sensName,
                                     Threshold const& thr,
                                     long double value,
                                     std::string const& type,
                                     std::string mountPoint = std::string()) {
        std::string notifPath("/" + mModuleName + ":" + type + "-threshold-crossed");

        /* start session */
        if (!mConn) {
            return;
        }
        auto sess = mConn->sessionStart();

        auto input = sess.getContext().newPath((notifPath + "/name"), sensName);
        if (type == "filesystem") {
            input.newPath((notifPath + "/mount-point"), mountPoint);
        }
        if (value >= thr.value) {
            input.newPath((notifPath + "/rising"));
        } else {
            input.newPath((notifPath + "/falling"));
        }
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << value;
        input.newPath((notifPath + "/usage"), stream.str());

        sess.sendNotification(input, sysrepo::Wait::No);
    }

    std::shared_ptr<Connection> mConn;
    std::mutex mNotificationMtx;
    std::condition_variable mCV;
    std::string mModuleName;
};

struct MemoryMonitoring : public UsageMonitoring {

    static MemoryMonitoring& getInstance() {
        static MemoryMonitoring instance;
        return instance;
    }

    MemoryMonitoring(MemoryMonitoring const&) = delete;
    void operator=(MemoryMonitoring const&) = delete;

    ~MemoryMonitoring() {
        notifyAndJoin();
    }

    void notifyAndJoin() {
        mCV.notify_all();
        if (mThread.joinable()) {
            mThread.join();
        }
    }

    void startThread() {
        if (mMemoryThesholds.empty()) {
            return;
        }
        if (mThread.joinable()) {
            mThread.join();
        }
        logMessage(SR_LL_DBG, "Thread for memory thresholds started.");
        mThread = std::thread(&MemoryMonitoring::runFunc, this);
    }

    void runFunc() {
        std::unique_lock<std::mutex> lk(mNotificationMtx);
        while (mCV.wait_for(lk, std::chrono::seconds(mPollInterval)) == std::cv_status::timeout) {
            long double value = MemoryStats::getInstance().getUsage();
            for (auto const& [name, thrValue] : mMemoryThesholds) {
                logMessage(SR_LL_DBG, std::string("Trigger notification for: ") + name + ": " +
                                          std::to_string(value));
                checkAndTriggerNotification(name, thrValue, value, "memory");
            }
        }
        logMessage(SR_LL_DBG, "Thread for memory thresholds ended.");
    }

    void populateConfigData(sysrepo::Session& session, std::string_view moduleName) {
        std::string const data_xpath(std::string("/") + std::string(moduleName) +
                                     ":system-metrics/memory");
        auto const& data(session.getData(data_xpath));
        if (!data) {
            logMessage(SR_LL_ERR, "No data found for population.");
            return;
        }
        std::shared_ptr<std::pair<std::string, Threshold>> threshold;
        mMemoryThesholds.clear();

        for (libyang::DataNode const& node : data.value().childrenDfs()) {
            libyang::SchemaNode schema = node.schema();
            switch (schema.nodeType()) {
            case libyang::NodeType::List: {
                if (std::string(schema.name()) == "threshold" && threshold) {
                    mMemoryThesholds[threshold->first] = threshold->second;
                }
                break;
            }
            case libyang::NodeType::Leaf: {
                if (schema.asLeaf().isKey()) {
                    threshold = std::make_shared<std::pair<std::string, Threshold>>();
                    threshold->first = node.asTerm().valueStr();
                } else if (std::string(schema.name()) == "value") {
                    threshold->second.value =
                        std::get<libyang::Decimal64>(node.asTerm().value()).number /
                        std::pow(10, std::get<libyang::Decimal64>(node.asTerm().value()).digits);
                }

                if (std::string(schema.name()) == "poll-interval") {
                    mPollInterval = std::get<uint32_t>(node.asTerm().value());
                }
                break;
            }
            default:
                break;
            }
        }
        if (threshold) {
            mMemoryThesholds[threshold->first] = threshold->second;
        }
    }

    void setXpaths(sysrepo::Session session,
                   std::optional<libyang::DataNode>& parent,
                   std::string_view moduleName) const {
        std::string configPath("/" + std::string(moduleName) +
                               ":system-metrics/memory/usage-monitoring/");
        setXpath(session, parent, configPath + "poll-interval", std::to_string(mPollInterval));
        for (auto const& [name, thr] : mMemoryThesholds) {
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2) << thr.value;
            setXpath(session, parent, configPath + "threshold[name='" + name + "']/value",
                     stream.str());
        }
    }

private:
    MemoryMonitoring() : mPollInterval(60){};
    thresholdMap_t mMemoryThesholds;
    std::thread mThread;
    uint32_t mPollInterval;
};

struct FilesystemMonitoring : public UsageMonitoring {
    static FilesystemMonitoring& getInstance() {
        static FilesystemMonitoring instance;
        return instance;
    }

    FilesystemMonitoring(FilesystemMonitoring const&) = delete;
    void operator=(FilesystemMonitoring const&) = delete;

    ~FilesystemMonitoring() {
        notifyAndJoin();
    }

    void notifyAndJoin() {
        mCV.notify_all();
        stopThreads();
    }

    void stopThreads() {
        int32_t numThreadsStopped(0);
        for (auto& [_, thread] : mFsThreads) {
            if (thread.joinable()) {
                thread.join();
                numThreadsStopped++;
            }
        }
        logMessage(SR_LL_DBG, std::to_string(numThreadsStopped) +
                                  " filesystem threads stopped, out of: " +
                                  std::to_string(mFsThreads.size()) + " started.");
        mFsThreads.clear();
    }

    void startThreads() {
        if (mFsThresholds.empty()) {
            return;
        }
        for (auto const& [name, _] : mFsThresholds) {
            logMessage(SR_LL_DBG, "Starting thread for filesystem: " + name + ".");
            mFsThreads[name] = std::thread(&FilesystemMonitoring::runFunc, this, name);
        }
    }

    void runFunc(std::string const& name) {
        std::unique_lock<std::mutex> lk(mNotificationMtx);
        std::unordered_map<std::string, fsThresholdTuple_t>::iterator itr;
        if ((itr = mFsThresholds.find(name)) != mFsThresholds.end()) {
            while (mCV.wait_for(lk, std::chrono::seconds(std::get<0>(itr->second))) ==
                   std::cv_status::timeout) {
                std::optional<long double> usageValue =
                    FilesystemStats::getInstance().getUsage(name);
                if (!usageValue) {
                    logMessage(SR_LL_WRN, std::string("No filesystem found: ") + name);
                    break;
                }
                for (auto const& [thrName, thrValue] : std::get<1>(itr->second)) {
                    logMessage(SR_LL_DBG, std::string("Trigger notification for: ") + thrName +
                                              ": " + std::to_string(usageValue.value()));
                    checkAndTriggerNotification(thrName, thrValue, usageValue.value(), "filesystem",
                                                name);
                }
            }
        }
        logMessage(SR_LL_DBG, "Thread for filesystem: " + name + " ended.");
    }

    void populateConfigData(sysrepo::Session& session, std::string_view moduleName) {
        std::string const data_xpath(std::string("/") + std::string(moduleName) +
                                     ":system-metrics/filesystems");
        auto const& data(session.getData(data_xpath));
        if (!data) {
            logMessage(SR_LL_ERR, "No data found for population.");
            return;
        }

        thresholdMap_t thresholdMap;
        std::shared_ptr<std::pair<std::string, Threshold>> threshold;
        std::string mountPoint("");
        uint32_t poll(60);
        mFsThresholds.clear();
        for (libyang::DataNode const& node : data.value().childrenDfs()) {
            libyang::SchemaNode schema = node.schema();
            switch (schema.nodeType()) {
            case libyang::NodeType::List: {
                if (std::string(schema.name()) == "threshold" && threshold) {
                    thresholdMap[threshold->first] = threshold->second;
                }
                break;
            }
            case libyang::NodeType::Leaf: {
                if (schema.asLeaf().isKey() && std::string(schema.name()) == "mount-point") {
                    if (threshold) {
                        thresholdMap[threshold->first] = threshold->second;
                    }
                    if (!thresholdMap.empty()) {
                        mFsThresholds[mountPoint] = std::make_tuple(poll, thresholdMap);
                    }
                    thresholdMap.clear();
                    mountPoint = node.asTerm().valueStr();
                    threshold.reset();
                } else if (schema.asLeaf().isKey() && std::string(schema.name()) == "name") {
                    threshold = std::make_shared<std::pair<std::string, Threshold>>();
                    threshold->first = node.asTerm().valueStr();
                } else if (std::string(schema.name()) == "value") {
                    threshold->second.value =
                        std::get<libyang::Decimal64>(node.asTerm().value()).number /
                        std::pow(10, std::get<libyang::Decimal64>(node.asTerm().value()).digits);
                }

                if (std::string(schema.name()) == "poll-interval") {
                    poll = std::get<uint32_t>(node.asTerm().value());
                }
                break;
            }
            default:
                break;
            }
        }
        if (threshold) {
            thresholdMap[threshold->first] = threshold->second;
            mFsThresholds[mountPoint] = std::make_tuple(poll, thresholdMap);
        }
    }

    void printFsConfig() {
        for (auto const& [name, thresholds] : mFsThresholds) {
            std::cout << "name: " << name << "\t poll:" << std::get<0>(thresholds);
            for (auto const& [thrName, thrValue] : std::get<1>(thresholds)) {
                std::cout << "\t thr-name: " << thrName << " thr-value" << thrValue.value << " "
                          << thrValue.rising << " " << thrValue.falling << std::endl;
            }
        }
    }

    void setXpaths(sysrepo::Session session,
                   std::optional<libyang::DataNode>& parent,
                   std::string_view moduleName) const {
        for (auto const& [fsName, thresholdTuple] : mFsThresholds) {
            std::string const configPath("/" + std::string(moduleName) +
                                         ":system-metrics/filesystems/filesystem[mount-point='" +
                                         fsName + "']/usage-monitoring/");
            setXpath(session, parent, configPath + "poll-interval",
                     std::to_string(std::get<0>(thresholdTuple)));
            for (auto const& [name, thr] : std::get<1>(thresholdTuple)) {
                std::stringstream stream;
                stream << std::fixed << std::setprecision(2) << thr.value;
                setXpath(session, parent, configPath + "threshold[name='" + name + "']/value",
                         stream.str());
            }
        }
    }

private:
    FilesystemMonitoring() = default;
    std::unordered_map<std::string, fsThresholdTuple_t> mFsThresholds;
    std::unordered_map<std::string, std::thread> mFsThreads;
};

}  // namespace metrics

#endif  // THRESHOLD_MANAGER_H
