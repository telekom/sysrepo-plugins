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

#endif // GLOBALS_H
