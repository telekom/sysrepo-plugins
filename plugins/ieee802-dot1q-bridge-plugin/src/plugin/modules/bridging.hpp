#pragma once

#include <srpcpp.hpp>

#include "plugin/context.hpp"

// module context
#include "bridging/context.hpp"

/**
 * @brief Bridging module.
 */
class BridgingModule : public srpc::IModule<ieee::br::PluginContext> {
public:
    /**
     * Bridging module constructor. Allocates each context.
     */
    BridgingModule(ieee::br::PluginContext& plugin_ctx);

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
    ~BridgingModule() { }

private:
    std::shared_ptr<BridgingOperationalContext> m_operContext;
    std::shared_ptr<BridgingModuleChangesContext> m_changeContext;
    std::shared_ptr<BridgingRpcContext> m_rpcContext;
};
