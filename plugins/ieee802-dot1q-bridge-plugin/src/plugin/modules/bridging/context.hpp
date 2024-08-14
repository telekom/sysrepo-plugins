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
