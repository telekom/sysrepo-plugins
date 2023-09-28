#include "routing.hpp"

#include "routing/oper.hpp"

/**
 * Routing module constructor. Allocates each context.
 */
RoutingModule::RoutingModule(ietf::rt::PluginContext& plugin_ctx)
    : srpc::IModule<ietf::rt::PluginContext>(plugin_ctx)
{
    m_operContext = std::make_shared<RoutingOperationalContext>();
}

/**
 * Return the operational context from the module.
 */
std::shared_ptr<srpc::IModuleContext> RoutingModule::getOperationalContext() { return m_operContext; }

/**
 * Return the module changes context from the module.
 */
std::shared_ptr<srpc::IModuleContext> RoutingModule::getModuleChangesContext() { return m_changeContext; }

/**
 * Return the RPC context from the module.
 */
std::shared_ptr<srpc::IModuleContext> RoutingModule::getRpcContext() { return m_rpcContext; }

/**
 * Get all operational callbacks which the module should use.
 */
std::list<srpc::OperationalCallback> RoutingModule::getOperationalCallbacks()
{
    return {
        srpc::OperationalCallback {
            .Module = "ietf-routing",
            .XPath = "/ietf-routing:routing/interfaces/interface",
            .Callback = ietf::rt::sub::oper::RoutingInterfacesOperGetCb(m_operContext),
        },
        srpc::OperationalCallback {
            .Module = "ietf-routing",
            .XPath = "/ietf-routing:routing/ribs/rib",
            .Callback = ietf::rt::sub::oper::RoutingRibOperGetCb(m_operContext),
        },
    };
}

/**
 * Get all module change callbacks which the module should use.
 */
std::list<srpc::ModuleChangeCallback> RoutingModule::getModuleChangeCallbacks() { return {}; }

/**
 * Get all RPC callbacks which the module should use.
 */
std::list<srpc::RpcCallback> RoutingModule::getRpcCallbacks() { return {}; }

/**
 * Get module name.
 */
constexpr const char* RoutingModule::getName() { return "Routing"; }
