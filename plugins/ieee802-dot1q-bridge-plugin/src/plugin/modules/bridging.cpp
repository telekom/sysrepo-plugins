#include "bridging.hpp"
#include "bridging/change.hpp"
#include "bridging/oper.hpp"

#include <memory>

/**
 * Bridging module constructor. Allocates each context.
 */
BridgingModule::BridgingModule(ieee::br::PluginContext& plugin_ctx)
    : srpc::IModule<ieee::br::PluginContext>(plugin_ctx)
{
    m_operContext = std::make_shared<BridgingOperationalContext>();
    m_changeContext = std::make_shared<BridgingModuleChangesContext>();
    m_rpcContext = std::make_shared<BridgingRpcContext>();
}

/**
 * Return the operational context from the module.
 */
std::shared_ptr<srpc::IModuleContext> BridgingModule::getOperationalContext() { return m_operContext; }

/**
 * Return the module changes context from the module.
 */
std::shared_ptr<srpc::IModuleContext> BridgingModule::getModuleChangesContext() { return m_changeContext; }

/**
 * Return the RPC context from the module.
 */
std::shared_ptr<srpc::IModuleContext> BridgingModule::getRpcContext() { return m_rpcContext; }

/**
 * Get all operational callbacks which the module should use.
 */
std::list<srpc::OperationalCallback> BridgingModule::getOperationalCallbacks()
{
    return {};
}

/**
 * Get all module change callbacks which the module should use.
 */
std::list<srpc::ModuleChangeCallback> BridgingModule::getModuleChangeCallbacks()
{
    return
    {
        srpc::ModuleChangeCallback {
            "ieee802-dot1q-bridge",
            "/ieee802-dot1q-bridge:bridges/bridge/name",
            ieee::br::sub::change::BridgeNameModuleChangeCb(this->m_changeContext),  
        },
        
    };
}
/**
 * Get all RPC callbacks which the module should use.
 */
std::list<srpc::RpcCallback> BridgingModule::getRpcCallbacks() { return {}; }

/**
 * Get module name.
 */
constexpr const char* BridgingModule::getName() { return "Bridging"; }
