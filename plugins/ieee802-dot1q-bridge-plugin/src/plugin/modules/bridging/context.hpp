#pragma once

#include <srpcpp/netlink.hpp>
#include <srpcpp.hpp>

/**
 * Operational context for the interfaces module.
 */
class BridgingOperationalContext : public srpc::IModuleContext {
// public:
//     NlContext& getNetlinkContext() { return m_nlContext; }

// private:
//     NlContext m_nlContext;
};

/**
 * Module changes context for the interfaces module.
 */
class BridgingModuleChangesContext : public srpc::IModuleContext {
// public:
//     NlContext& getNetlinkContext() { return m_nlContext; }

// private:
//     NlContext m_nlContext;
};

/**
 * RPC context for the interfaces module.
 */
class BridgingRpcContext : public srpc::IModuleContext { };
