#include "srpcpp/module.hpp"
#include "core/context.hpp"

/**
 * Operational context for the authentication module.
 */
class AclOperationalContext : public srpc::IModuleContext { };

/**
 * Module changes context for the authentication module.
 */
class AclModuleChangesContext : public srpc::IModuleContext { };

/**
 * RPC context for the authentication module.
 */
class AclRpcContext : public srpc::IModuleContext { };

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
//     AclModule(ietf::acl::PluginContext &ctx) : srpc::IModule<ietf::acl::PluginContext>(ctx) {}

    /**
     * Return the operational context from the module.
     */
    virtual std::shared_ptr<srpc::IModuleContext> getOperationalContext() override;

    /**
     * Return the module changes context from the module.
     */
    std::shared_ptr<srpc::IModuleContext> getModuleChangesContext() override;

    /**
     * Return the RPC context from the module.
     */
    std::shared_ptr<srpc::IModuleContext> getRpcContext() override;

    /**
     * Get all operational callbacks which the module should use.
     */
    std::list<srpc::OperationalCallback> getOperationalCallbacks() override;

    /**
     * Get all module change callbacks which the module should use.
     */
    std::list<srpc::ModuleChangeCallback> getModuleChangeCallbacks() override;

    /**
     * Get all RPC callbacks which the module should use.
     */
    std::list<srpc::RpcCallback> getRpcCallbacks() override;

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
