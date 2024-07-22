#pragma once

#include <srpcpp.hpp>

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