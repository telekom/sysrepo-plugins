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

#include "hardware.hpp"
#include "hardware/oper.hpp"
#include "hardware/change.hpp"
#include "hardware/api/hardware_sensors.hpp"

#include <memory>

/**
 * Hardware module constructor. Allocates each context.
 */
HardwareModule::HardwareModule(ietf::hw::PluginContext& plugin_ctx)
    : srpc::IModule<ietf::hw::PluginContext>(plugin_ctx)
{
    m_operContext = std::make_shared<HardwareOperationalContext>();
    m_changeContext = std::make_shared<HardwareModuleChangesContext>();
    m_rpcContext = std::make_shared<HardwareRpcContext>();

    // connection used by the sensor polling threads for sending threshold notifications
    ietf::hw::HardwareSensors::getInstance().injectConnection(plugin_ctx.getConnection());
}

/**
 * Return the operational context from the module.
 */
std::shared_ptr<srpc::IModuleContext> HardwareModule::getOperationalContext() { return m_operContext; }

/**
 * Return the module changes context from the module.
 */
std::shared_ptr<srpc::IModuleContext> HardwareModule::getModuleChangesContext() { return m_changeContext; }

/**
 * Return the RPC context from the module.
 */
std::shared_ptr<srpc::IModuleContext> HardwareModule::getRpcContext() { return m_rpcContext; }

/**
 * Get all operational callbacks which the module should use.
 */
std::list<srpc::OperationalCallback> HardwareModule::getOperationalCallbacks()
{
    return {
        srpc::OperationalCallback {
            "ietf-hardware",
            "/ietf-hardware:hardware",
            ietf::hw::sub::oper::HardwareOperGetCb(m_operContext),
        },
    };
}

/**
 * Get all module change callbacks which the module should use.
 */
std::list<srpc::ModuleChangeCallback> HardwareModule::getModuleChangeCallbacks()
{
    return {
        srpc::ModuleChangeCallback {
            "ietf-hardware",
            "/ietf-hardware:hardware",
            ietf::hw::sub::change::HardwareModuleChangeCb(m_changeContext),
            sysrepo::SubscribeOptions::Enabled | sysrepo::SubscribeOptions::DoneOnly,
        },
    };
}

/**
 * Get all RPC callbacks which the module should use.
 */
std::list<srpc::RpcCallback> HardwareModule::getRpcCallbacks() { return {}; }

/**
 * Get module name.
 */
constexpr const char* HardwareModule::getName() { return "Hardware"; }
