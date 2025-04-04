// telekom / sysrepo-plugin-os-metrics
//
// This program is made available under the terms of the
// BSD 3-Clause license which is available at
// https://opensource.org/licenses/BSD-3-Clause
//
// SPDX-FileCopyrightText: 2022 Deutsche Telekom AG
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef GLOBALS_H
#define GLOBALS_H

#define FILESYSTEM_STATS_LOCATION "/tmp/df_output1.tmp"
#define FILESYSTEM_STATS_LOCATION2 "/tmp/df_output2.tmp"

#include <sysrepo-cpp/Session.hpp>
#include <sysrepo.h>

static void logMessage(sr_log_level_t log, std::string const& msg) {
    static std::string const _("OS-Metrics");
    switch (log) {
    case SR_LL_ERR:
        SRPLG_LOG_ERR(_.c_str(), msg.c_str());
        break;
    case SR_LL_WRN:
        SRPLG_LOG_WRN(_.c_str(), msg.c_str());
        break;
    case SR_LL_INF:
        SRPLG_LOG_INF(_.c_str(), msg.c_str());
        break;
    case SR_LL_DBG:
    default:
        SRPLG_LOG_DBG(_.c_str(), msg.c_str());
    }
}

static bool setXpath(sysrepo::Session& session,
                     std::optional<libyang::DataNode>& parent,
                     std::string const& node_xpath,
                     std::string const& value) {
    try {
        if (parent) {
            parent.value().newPath(node_xpath, value);
        } else {
            parent = session.getContext().newPath(node_xpath, value);
        }
    } catch (std::runtime_error const& e) {
        logMessage(SR_LL_WRN,
                   "At path " + node_xpath + ", value " + value + " " + ", error: " + e.what());
        return false;
    }
    return true;
}

[[maybe_unused]] static std::optional<libyang::Module> findModule(sysrepo::Session session,
                                                                  std::string_view moduleName) {
    auto const& modules = session.getContext().modules();
    auto module =
        std::find_if(modules.begin(), modules.end(), [moduleName](libyang::Module const& module) {
            return moduleName == module.name();
        });
    if (module == std::end(modules)) {
        return std::nullopt;
    }
    return *module;
}

static void printCurrentConfig(sysrepo::Session& session,
                               std::string_view module_name,
                               std::string const& node) {
    try {
        std::string xpath(std::string("/") + std::string(module_name) + std::string(":") + node);
        auto values = session.getData(xpath);
        if (!values)
            return;

        std::string const toPrint(
            values.value()
                .printStr(libyang::DataFormat::JSON, libyang::PrintFlags::WithSiblings)
                .value());
        logMessage(SR_LL_DBG, toPrint);
    } catch (const std::exception& e) {
        logMessage(SR_LL_WRN, e.what());
    }
}

#endif  // GLOBALS_H
