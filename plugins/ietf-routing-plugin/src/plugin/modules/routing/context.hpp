//
// telekom / sysrepo-plugins
//
// This program is made available under the terms of the
// BSD 3-Clause license which is available at
// https://opensource.org/licenses/BSD-3-Clause
//
// SPDX-FileCopyrightText: 2024 Deutsche Telekom AG
// SPDX-FileContributor: Sartura d.d.
//
// SPDX-License-Identifier: BSD-3-Clause
//

#pragma once

#include <srpcpp.hpp>
#include <srpcpp/netlink.hpp>

/**
 * Operational context for the routing module.
 */
class RoutingOperationalContext : public srpc::IModuleContext {
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
