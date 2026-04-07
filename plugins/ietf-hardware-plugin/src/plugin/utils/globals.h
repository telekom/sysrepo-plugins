// telekom / sysrepo-plugin-hardware
//
// This program is made available under the terms of the
// BSD 3-Clause license which is available at
// https://opensource.org/licenses/BSD-3-Clause
//
// SPDX-FileCopyrightText: 2026 Deutsche Telekom AG
// SPDX-FileContributor: Sartura d.d.
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef GLOBALS_H
#define GLOBALS_H

#include <sysrepo-cpp/Session.hpp>
#include <sysrepo.h>

#define PLUGIN_NAME "IETF-Hardware"
#define COMPONENTS_LOCATION "/tmp/hardware_components.json"
#define DEFAULT_POLL_INTERVAL 60 // seconds

struct SensorsInitFail : public std::exception {
    const char* what() const throw() override
    {
        return "sensor_init() failure";
    }
};

static bool setXpath(sysrepo::Session& session,
    std::optional<libyang::DataNode>& parent,
    std::string const& node_xpath,
    std::string const& value)
{
    try {
        if (parent) {
            parent.value().newPath(node_xpath, value);
        } else {
            parent = session.getContext().newPath(node_xpath, value);
        }
    } catch (std::runtime_error const& e) {
        SRPLG_LOG_WRN(PLUGIN_NAME, "%s", ("At path " + node_xpath + ", value " + value + " " + ", error: " + e.what()).c_str());
        return false;
    }
    return true;
}

#endif // GLOBALS_H
