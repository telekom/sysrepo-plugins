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
