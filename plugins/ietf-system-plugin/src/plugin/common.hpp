//
// telekom / sysrepo-plugins
//
// This program is made available under the terms of the
// BSD 3-Clause license which is available at
// https://opensource.org/licenses/BSD-3-Clause
//
// SPDX-FileCopyrightText: 2024 Deutsche Telekom AG
// SPDX-FileContributor: Sartura d.d.
//
// SPDX-License-Identifier: BSD-3-Clause
//

#pragma once

#include <string>

#include <libyang-cpp/Context.hpp>

namespace ietf::sys {

constexpr auto PLUGIN_NAME = "ietf-system-plugin";
constexpr auto HOSTNAME_MAX_LEN = 253;
constexpr auto TIMEZONE_FILE_PATH = "/etc/localtime";
constexpr auto TIMEZONE_DIR_PATH = "/usr/share/zoneinfo";

namespace auth {
    constexpr auto DEFAULT_GECOS = "ietf-system user";
    constexpr auto SKEL_DIR = "/etc/skel";
    constexpr auto PASSWD_PATH = "/etc/passwd";
    constexpr auto DEFAULT_SHELL = "/bin/bash";
} // namespace auth

} // namespace ietf::sys
