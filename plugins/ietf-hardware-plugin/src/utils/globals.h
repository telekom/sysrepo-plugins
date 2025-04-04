// telekom / sysrepo-plugin-hardware
//
// This program is made available under the terms of the
// BSD 3-Clause license which is available at
// https://opensource.org/licenses/BSD-3-Clause
//
// SPDX-FileCopyrightText: 2021 Deutsche Telekom AG
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef GLOBALS_H
#define GLOBALS_H

#include <sysrepo-cpp/Session.hpp>
#include <sysrepo.h>

#define COMPONENTS_LOCATION "/tmp/hardware_components.json"
#define DEFAULT_POLL_INTERVAL 60  // seconds

struct SensorsInitFail : public std::exception {
    const char* what() const throw() override {
        return "sensor_init() failure";
    }
};

static void logMessage(sr_log_level_t log, std::string const& msg) {
    std::string const _("IETF-Hardware");
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

#endif  // GLOBALS_H
