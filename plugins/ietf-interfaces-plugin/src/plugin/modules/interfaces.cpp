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

#include "interfaces.hpp"
#include "interfaces/change.hpp"
#include "interfaces/oper.hpp"

#include <memory>

/**
 * Interfaces module constructor. Allocates each context.
 */
InterfacesModule::InterfacesModule(ietf::ifc::PluginContext& plugin_ctx)
    : srpc::IModule<ietf::ifc::PluginContext>(plugin_ctx)
{
    m_operContext = std::make_shared<InterfacesOperationalContext>();
    m_changeContext = std::make_shared<InterfacesModuleChangesContext>();
    m_rpcContext = std::make_shared<InterfacesRpcContext>();
}

/**
 * Return the operational context from the module.
 */
std::shared_ptr<srpc::IModuleContext> InterfacesModule::getOperationalContext() { return m_operContext; }

/**
 * Return the module changes context from the module.
 */
std::shared_ptr<srpc::IModuleContext> InterfacesModule::getModuleChangesContext() { return m_changeContext; }

/**
 * Return the RPC context from the module.
 */
std::shared_ptr<srpc::IModuleContext> InterfacesModule::getRpcContext() { return m_rpcContext; }

/**
 * Get all operational callbacks which the module should use.
 */
std::list<srpc::OperationalCallback> InterfacesModule::getOperationalCallbacks()
{
    return {
        srpc::OperationalCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface",
            InterfaceOperGetCb(m_operContext),
        },
        srpc::OperationalCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface/admin-status",
            InterfaceAdminStatusOperGetCb(m_operContext),
        },
        srpc::OperationalCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface/oper-status",
            InterfaceOperStatusOperGetCb(m_operContext),
        },
        srpc::OperationalCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface/if-index",
            InterfaceIfIndexOperGetCb(m_operContext),
        },
        srpc::OperationalCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface/phys-address",
            InterfacePhysAddressOperGetCb(m_operContext),
        },
        srpc::OperationalCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface/higher-layer-if",
            InterfaceHigherLayerIfOperGetCb(m_operContext),
        },
        srpc::OperationalCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface/lower-layer-if",
            InterfaceLowerLayerIfOperGetCb(m_operContext),
        },
        srpc::OperationalCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface/speed",
            InterfaceSpeedOperGetCb(m_operContext),
        },
        srpc::OperationalCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface/statistics",
            InterfaceStatsOperGetCb(m_operContext),
        },
        srpc::OperationalCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface/ipv4/address",
            Ipv4AddrOperGetCb(m_operContext),
        },
        srpc::OperationalCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface/ipv4/neighbor",
            Ipv4NeighOperGetCb(m_operContext),
        },
        srpc::OperationalCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface/ipv6/address",
            Ipv6AddrOperGetCb(m_operContext),
        },
        srpc::OperationalCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface/ipv6/neighbor",
            Ipv6NeighOperGetCb(m_operContext),
        },
    };
}

/**
 * Get all module change callbacks which the module should use.
 */
std::list<srpc::ModuleChangeCallback> InterfacesModule::getModuleChangeCallbacks()
{
    return {
        srpc::ModuleChangeCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface/name",
            InterfaceNameModuleChangeCb(this->m_changeContext),
        },
        srpc::ModuleChangeCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface/enabled",
            InterfaceEnabledModuleChangeCb(this->m_changeContext),
        },
        srpc::ModuleChangeCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface/description",
            InterfaceDescriptionModuleChangeCb(this->m_changeContext),
        },
        srpc::ModuleChangeCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface/type",
            InterfaceTypeModuleChangeCb(this->m_changeContext),
        },
        srpc::ModuleChangeCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface/link-up-down-trap-enable",
            InterfaceLinkUpDownTrapEnableModuleChangeCb(this->m_changeContext),
        },
        srpc::ModuleChangeCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface/ipv4/enabled",
            Ipv4EnabledModuleChangeCb(this->m_changeContext),
        },
        srpc::ModuleChangeCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface/ipv4/forwarding",
            Ipv4ForwardingModuleChangeCb(this->m_changeContext),
        },
        srpc::ModuleChangeCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface/ipv4/mtu",
            Ipv4MtuModuleChangeCb(this->m_changeContext),
        },
        srpc::ModuleChangeCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface/ipv4/address/ip",
            Ipv4AddrIpModuleChangeCb(this->m_changeContext),
        },
        srpc::ModuleChangeCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface/ipv4/address/prefix-length",
            Ipv4AddrPrefixLengthModuleChangeCb(this->m_changeContext),
        },
        srpc::ModuleChangeCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface/ipv4/neighbor/ip",
            Ipv4NeighIpModuleChangeCb(this->m_changeContext),
        },
        srpc::ModuleChangeCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface/ipv4/neighbor/link-layer-address",
            Ipv4NeighLinkLayerAddressModuleChangeCb(this->m_changeContext),
        },
        srpc::ModuleChangeCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface/ipv6/enabled",
            Ipv6EnabledModuleChangeCb(this->m_changeContext),
        },
        srpc::ModuleChangeCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface/ipv6/forwarding",
            Ipv6ForwardingModuleChangeCb(this->m_changeContext),
        },
        srpc::ModuleChangeCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface/ipv6/mtu",
            Ipv6MtuModuleChangeCb(this->m_changeContext),
        },
        srpc::ModuleChangeCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface/ipv6/address/ip",
            Ipv6AddrIpModuleChangeCb(this->m_changeContext),
        },
        srpc::ModuleChangeCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface/ipv6/address/prefix-length",
            Ipv6AddrPrefixLengthModuleChangeCb(this->m_changeContext),
        },
        srpc::ModuleChangeCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface/ipv6/neighbor/ip",
            Ipv6NeighIpModuleChangeCb(this->m_changeContext),
        },
        srpc::ModuleChangeCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface/ipv6/neighbor/link-layer-address",
            Ipv6NeighLinkLayerAddressModuleChangeCb(this->m_changeContext),
        },
        srpc::ModuleChangeCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface/ipv6/dup-addr-detect-transmits",
            Ipv6DupAddrDetectTransmitsModuleChangeCb(this->m_changeContext),
        },
        srpc::ModuleChangeCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface/ipv6/autoconf/create-global-addresses",
            Ipv6AutoconfCreateGlobalAddressesModuleChangeCb(this->m_changeContext),
        },
        srpc::ModuleChangeCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface/bridge-port/component-name",
            InterfaceBridgePortChangeCb(this->m_changeContext),
        },
    };
}
/**
 * Get all RPC callbacks which the module should use.
 */
std::list<srpc::RpcCallback> InterfacesModule::getRpcCallbacks() { return {}; }

/**
 * Get module name.
 */
constexpr const char* InterfacesModule::getName() { return "Interfaces"; }
