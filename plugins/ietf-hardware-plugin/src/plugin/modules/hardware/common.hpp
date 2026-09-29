//
// telekom / sysrepo-plugins
//
// This program is made available under the terms of the
// BSD 3-Clause license which is available at
// https://opensource.org/licenses/BSD-3-Clause
//
// SPDX-FileCopyrightText: 2026 Deutsche Telekom AG
// SPDX-FileContributor: Sartura d.d.
//
// SPDX-License-Identifier: BSD-3-Clause
//

#pragma once

#include <cstdint>

/**
 * @brief Return the logging prefix of the current module.
 */
constexpr const char* getModuleLogPrefix(void) { return "module(Hardware)"; }

namespace ietf::hw {

constexpr auto COMPONENTS_LOCATION = "/tmp/hardware_components.json"; ///< File to which lshw output is written.
constexpr uint32_t DEFAULT_POLL_INTERVAL = 60; ///< Default sensor poll interval in seconds.

} // namespace ietf::hw
