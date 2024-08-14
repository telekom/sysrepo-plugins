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

#include <srpcpp/context.hpp>
#include <sysrepo-cpp/Session.hpp>

namespace ietf::ifc {
/**
 * @brief Plugin context.
 */
class PluginContext : public srpc::BasePluginContext {
public:
    /**
     * Default constructor.
     *
     * @param sess Plugin session from the plugin init callback.
     *
     */
    PluginContext(sysrepo::Session sess);

    /**
     * @brief Get the name of the plugin which uses this context.
     *
     * @return Plugin name string.
     */
    virtual constexpr const char* getPluginName() override { return "ietf-interfaces-plugin"; }

    /**
     * @brief Default destructor.
     */
    ~PluginContext();
};
}
