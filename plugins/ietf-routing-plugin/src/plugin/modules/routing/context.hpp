#pragma once

#include <srpcpp.hpp>
#include <srpcpp/netlink.hpp>

/**
 * Operational context for the routing module.
 */
class RoutingOperationalContext : public srpc::IModuleContext {
public:
    NlContext& getNetlinkContext() { return m_nlContext; }

private:
    NlContext m_nlContext;
};

/**
 * Module changes context for the routing module.
 */
class RoutingModuleChangesContext : public srpc::IModuleContext {
};

/**
 * RPC context for the routing module.
 */
class RoutingRpcContext : public srpc::IModuleContext { };
