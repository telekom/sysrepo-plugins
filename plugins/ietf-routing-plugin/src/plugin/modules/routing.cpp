#include "routing.hpp"

#include "plugin/modules/routing/change.hpp"
#include "plugin/modules/routing/context.hpp"
#include "routing/oper.hpp"

/**
 * Routing module constructor. Allocates each context.
 */
RoutingModule::RoutingModule(ietf::rt::PluginContext& plugin_ctx)
    : srpc::IModule<ietf::rt::PluginContext>(plugin_ctx)
{
    m_operContext = std::make_shared<RoutingOperationalContext>();
    m_changeContext = std::make_shared<RoutingModuleChangesContext>();
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
            .XPath = "/ietf-routing:routing/ribs",
            .Callback = ietf::rt::sub::oper::RoutingRibOperGetCb(m_operContext),
        },
    };
}

/**
 * Get all module change callbacks which the module should use.
 */
std::list<srpc::ModuleChangeCallback> RoutingModule::getModuleChangeCallbacks()
{
    return {
        srpc::ModuleChangeCallback {
            .Module = "ietf-routing",
            .XPath = "/ietf-routing:routing/control-plane-protocols/control-plane-protocol/description",
            .Callback = ietf::rt::sub::change::ControlPlaneProtocolDescriptionModuleChangeCb(m_changeContext),
        },
        srpc::ModuleChangeCallback {
            .Module = "ietf-routing",
            .XPath = "/ietf-routing:routing/control-plane-protocols/control-plane-protocol/static-routes/ietf-ipv4-unicast-routing:ipv4/route",
            .Callback = ietf::rt::sub::change::V4RouteModuleChangeCb(m_changeContext),
        },
        srpc::ModuleChangeCallback {
            .Module = "ietf-routing",
            .XPath = "/ietf-routing:routing/control-plane-protocols/control-plane-protocol/static-routes/ipv4/route/next-hop/next-hop-list/next-hop",
            .Callback = ietf::rt::sub::change::V4RouteNextHopNextHopListNextHopModuleChangeCb(m_changeContext),
        },
        srpc::ModuleChangeCallback {
            .Module = "ietf-routing",
            .XPath = "/ietf-routing:routing/control-plane-protocols/control-plane-protocol/static-routes/ipv4/route/next-hop/next-hop-list/next-hop/next-hop-address",
            .Callback = ietf::rt::sub::change::V4RouteNextHopNextHopListNextHopNextHopAddressModuleChangeCb(m_changeContext),
        },
        srpc::ModuleChangeCallback {
            .Module = "ietf-routing",
            .XPath = "/ietf-routing:routing/control-plane-protocols/control-plane-protocol/static-routes/ipv4/route/next-hop/next-hop-list/next-hop/outgoing-interface",
            .Callback = ietf::rt::sub::change::V4RouteNextHopNextHopListNextHopOutgoingInterfaceModuleChangeCb(m_changeContext),
        },

    };
}

/**
 * Get all RPC callbacks which the module should use.
 */
std::list<srpc::RpcCallback> RoutingModule::getRpcCallbacks() { return {}; }

/**
 * Get module name.
 */
constexpr const char* RoutingModule::getName() { return "Routing"; }
