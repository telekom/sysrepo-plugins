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

#include "context.hpp"

namespace ieee::br {
/**
 * @brief Default constructor.
 *
 * @param sess Plugin session from the plugin init callback.
 *
 */
PluginContext::PluginContext(sysrepo::Session sess)
    : srpc::BasePluginContext(sess)
{
}

/**
 * @brief Default destructor.
 */
PluginContext::~PluginContext() { }
}
