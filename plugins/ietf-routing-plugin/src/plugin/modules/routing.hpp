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

#include <srpcpp.hpp>

#include "plugin/context.hpp"

// module context
#include "routing/context.hpp"

// netlink context
#include <srpcpp/netlink.hpp>

/**
 * @brief Routing module.
 */
class RoutingModule : public srpc::IModule<ietf::rt::PluginContext> {
public:
    /**
     * Routing module constructor. Allocates each context.
     */
    RoutingModule(ietf::rt::PluginContext& plugin_ctx);

    /**
     * Return the operational context from the module.
     */
    virtual std::shared_ptr<srpc::IModuleContext> getOperationalContext() override;

    /**
     * Return the module changes context from the module.
     */
    virtual std::shared_ptr<srpc::IModuleContext> getModuleChangesContext() override;

    /**
     * Return the RPC context from the module.
     */
    virtual std::shared_ptr<srpc::IModuleContext> getRpcContext() override;

    /**
     * Get all operational callbacks which the module should use.
     */
    virtual std::list<srpc::OperationalCallback> getOperationalCallbacks() override;

    /**
     * Get all module change callbacks which the module should use.
     */
    virtual std::list<srpc::ModuleChangeCallback> getModuleChangeCallbacks() override;

    /**
     * Get all RPC callbacks which the module should use.
     */
    virtual std::list<srpc::RpcCallback> getRpcCallbacks() override;

    /**
     * Get module name.
     */
    virtual constexpr const char* getName() override;

    /**
     * System module destructor.
     */
    ~RoutingModule() { }

private:
    std::shared_ptr<RoutingOperationalContext> m_operContext;
    std::shared_ptr<RoutingModuleChangesContext> m_changeContext;
    std::shared_ptr<RoutingRpcContext> m_rpcContext;
};
