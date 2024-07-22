<<<<<<< HEAD
//
// telekom / sysrepo-plugins
//
// This program is made available under the terms of the
// BSD 3-Clause license which is available at
// https://opensource.org/licenses/BSD-3-Clause
//
// SPDX-FileCopyrightText: 2025 Deutsche Telekom AG
// SPDX-FileContributor: Sartura d.d.
//
// SPDX-License-Identifier: BSD-3-Clause
//

#include "srpcpp/module.hpp"

#pragma once

#include <srpcpp.hpp>

#include "core/context.hpp"
#include "core/sub/change.hpp"
#include "core/sub/context.hpp"

/**
 * @brief ACL container module.
 * @brief Provides callbacks for acl list element.
 */
class AclModule : public srpc::IModule<ietf::acl::PluginContext> {
public:
    /**
     * Aclentication module constructor. Allocates each context.
     */
    AclModule(ietf::acl::PluginContext &ctx);

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
    constexpr const char* getName() override;

    /**
     * Acl module destructor.
     */
    ~AclModule() { }

private:
    std::shared_ptr<AclOperationalContext> m_operContext;
    std::shared_ptr<AclModuleChangesContext> m_changeContext;
    std::shared_ptr<AclRpcContext> m_rpcContext;
};
