// telekom / sysrepo-plugin-os-metrics
//
// This program is made available under the terms of the
// BSD 3-Clause license which is available at
// https://opensource.org/licenses/BSD-3-Clause
//
// SPDX-FileCopyrightText: 2026 Deutsche Telekom AG
// SPDX-FileContributor: Sartura d.d.
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef CALLBACK_H
#define CALLBACK_H

#include "cpu_stats.hpp"
#include "filesystem_stats.hpp"
#include "memory_stats.hpp"
#include "process_stats.hpp"
#include "threshold_manager.hpp"

namespace metrics {

struct Callback {
    using Session = sysrepo::Session;
    using ErrorCode = sysrepo::ErrorCode;
    using Event = sysrepo::Event;
    using DataNode = libyang::DataNode;

    static ErrorCode cpuStateCallback(Session session,
        uint32_t /* subscriptionId */,
        std::string_view moduleName,
        std::optional<std::string_view> /* subXPath */,
        std::optional<std::string_view> /* requestXPath */,
        uint32_t /* requestId */,
        std::optional<DataNode>& parent)
    {
        CpuStats stats;
        stats.readCpuTimes();
        stats.setXpathValues(parent, moduleName);
        double loadavg[3];
        if (getloadavg(loadavg, 3) != -1) {
            parent->newPath(
                "/" + std::string(moduleName) + ":system-metrics/cpu-statistics/average-load/avg-1min-load",
                std::format("{:.2f}", loadavg[0]));
            parent->newPath(
                "/" + std::string(moduleName) + ":system-metrics/cpu-statistics/average-load/avg-5min-load",
                std::format("{:.2f}", loadavg[1]));
            parent->newPath(
                "/" + std::string(moduleName) + ":system-metrics/cpu-statistics/average-load/avg-15min-load",
                std::format("{:.2f}", loadavg[2]));
        } else {
            SRPLG_LOG_ERR(PLUGIN_NAME, "getloadavg call failed");
        }
        return ErrorCode::Ok;
    }

    static ErrorCode memoryStateCallback(Session session,
        uint32_t /* subscriptionId */,
        std::string_view moduleName,
        std::optional<std::string_view> /* subXPath */,
        std::optional<std::string_view> /* requestXPath */,
        uint32_t /* requestId */,
        std::optional<DataNode>& parent)
    {
        auto module = findModule(session, moduleName);
        if (module && module.value().featureEnabled("usage-notifications")) {
            MemoryMonitoring::getInstance().setXpaths(parent, moduleName);
        }
        MemoryStats::getInstance().readMemoryStats();
        MemoryStats::getInstance().setXpathValues(parent, moduleName);
        return ErrorCode::Ok;
    }

    static ErrorCode filesystemStateCallback(Session session,
        uint32_t /* subscriptionId */,
        std::string_view moduleName,
        std::optional<std::string_view> /* subXPath */,
        std::optional<std::string_view> /* requestXPath */,
        uint32_t /* requestId */,
        std::optional<DataNode>& parent)
    {
        auto module = findModule(session, moduleName);
        if (module && module.value().featureEnabled("usage-notifications")) {
            FilesystemMonitoring::getInstance().setXpaths(parent, moduleName);
        }
        FilesystemStats::getInstance().readFilesystemStats();
        FilesystemStats::getInstance().setXpathValues(parent, moduleName);
        return ErrorCode::Ok;
    }

    static ErrorCode processesStateCallback(Session session,
        uint32_t /* subscriptionId */,
        std::string_view moduleName,
        std::optional<std::string_view> /* subXPath */,
        std::optional<std::string_view> /* requestXPath */,
        uint32_t /* requestId */,
        std::optional<DataNode>& parent)
    {
        ProcessStats::getInstance().readAndSetAll(parent, moduleName);
        return ErrorCode::Ok;
    }

    static ErrorCode memoryConfigCallback(Session session,
        uint32_t /* subscriptionId */,
        std::string_view moduleName,
        std::optional<std::string_view> /* subXPath */,
        Event /* event */,
        uint32_t /* request_id */)
    {
        printCurrentConfig(session, moduleName, "system-metrics/memory//*");
        auto module = findModule(session, moduleName);
        if (module && module.value().featureEnabled("usage-notifications")) {
            MemoryMonitoring::getInstance().notifyAndJoin();
            MemoryMonitoring::getInstance().populateConfigData(session, moduleName);
            MemoryMonitoring::getInstance().startThread();
        } else {
            SRPLG_LOG_WRN(PLUGIN_NAME, "Feature not enabled: usage-notifications");
        }
        return ErrorCode::Ok;
    }

    static ErrorCode filesystemsConfigCallback(Session session,
        uint32_t /* subscriptionId */,
        std::string_view moduleName,
        std::optional<std::string_view> /* subXPath */,
        Event /* event */,
        uint32_t /* request_id */)
    {
        printCurrentConfig(session, moduleName, "system-metrics/filesystems//*");
        auto module = findModule(session, moduleName);
        if (module && module.value().featureEnabled("usage-notifications")) {
            FilesystemMonitoring::getInstance().notifyAndJoin();
            FilesystemMonitoring::getInstance().populateConfigData(session, moduleName);
            FilesystemMonitoring::getInstance().startThreads();
        } else {
            SRPLG_LOG_WRN(PLUGIN_NAME, "Feature not enabled: usage-notifications");
        }
        return ErrorCode::Ok;
    }
};

} // namespace metrics

#endif // CALLBACK_H
