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

#include "core/context.hpp"

#include <optional>
#include <string_view>

#include <sysrepo-cpp/Session.hpp>
#include <libyang-cpp/Context.hpp>

namespace sr = sysrepo;
namespace ly = libyang;

namespace ieee::br {
namespace sub::rpc {
}
}