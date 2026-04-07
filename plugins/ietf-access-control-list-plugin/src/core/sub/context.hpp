//
// telekom / sysrepo-plugins
//
// This program is made available under the terms of the
// BSD 3-Clause license which is available at
// https://opensource.org/licenses/BSD-3-Clause
//
// SPDX-FileCopyrightText: 2026 Deutsche Telekom AG
// SPDX-FileContributor: Sartura d.d.
//
// SPDX-License-Identifier: BSD-3-Clause
//

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