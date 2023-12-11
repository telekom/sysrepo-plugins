#pragma once

#include "srpcpp/netlink/nl.hpp"
#include <srpcpp.hpp>
#include <srpcpp/netlink.hpp>

/**
 * Operational context for the routing module.
 */
class RoutingOperationalContext : public srpc::IModuleContext {
public:
    RoutingOperationalContext(NlContext& nl_ctx)
        : m_nlContext(nl_ctx)
    {
    }

    NlContext& getNetlinkContext() { return m_nlContext; }

private:
    NlContext& m_nlContext;
};

/**
 * Module changes context for the routing module.
 */
class RoutingModuleChangesContext : public srpc::IModuleContext {
public:
    RoutingModuleChangesContext(NlContext& nl_ctx)
        : m_nlContext(nl_ctx)
    {
    }

    NlContext& getNetlinkContext() { return m_nlContext; }

private:
    NlContext& m_nlContext;
};

/**
 * RPC context for the routing module.
 */
class RoutingRpcContext : public srpc::IModuleContext { };
