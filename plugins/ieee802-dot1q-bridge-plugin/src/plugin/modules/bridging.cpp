#include "bridging.hpp"
#include "bridging/change.hpp"
#include "bridging/oper.hpp"

#include <memory>

/**
 * Bridging module constructor. Allocates each context.
 */
BridgingModule::BridgingModule(ieee::br::PluginContext& plugin_ctx)
    : srpc::IModule<ieee::br::PluginContext>(plugin_ctx)
{
    m_operContext = std::make_shared<BridgingOperationalContext>();
    m_changeContext = std::make_shared<BridgingModuleChangesContext>();
    m_rpcContext = std::make_shared<BridgingRpcContext>();
}

/**
 * Return the operational context from the module.
 */
std::shared_ptr<srpc::IModuleContext> BridgingModule::getOperationalContext() { return m_operContext; }

/**
 * Return the module changes context from the module.
 */
std::shared_ptr<srpc::IModuleContext> BridgingModule::getModuleChangesContext() { return m_changeContext; }

/**
 * Return the RPC context from the module.
 */
std::shared_ptr<srpc::IModuleContext> BridgingModule::getRpcContext() { return m_rpcContext; }

/**
 * Get all operational callbacks which the module should use.
 */
std::list<srpc::OperationalCallback> BridgingModule::getOperationalCallbacks()
{
    return {
        
        srpc::OperationalCallback {
            "ieee802-dot1q-bridge",
            "/ieee802-dot1q-bridge:bridges/bridge",
            ieee::br::sub::oper::BridgeOperGetCb(this->m_operContext)
        },
        srpc::OperationalCallback {
            "ieee802-dot1q-bridge",
            "/ieee802-dot1q-bridge:bridges/bridge/address",
            ieee::br::sub::oper::BridgeAddressOperGetCb(this->m_operContext)
        },
        srpc::OperationalCallback {
            "ieee802-dot1q-bridge",
            "/ieee802-dot1q-bridge:bridges/bridge/ports",
            ieee::br::sub::oper::BridgePortsOperGetCb(this->m_operContext)
        },
        srpc::OperationalCallback {
            "ieee802-dot1q-bridge",
            "/ieee802-dot1q-bridge:bridges/bridge/component",
            ieee::br::sub::oper::BridgeComponentOperGetCb(this->m_operContext)
        },
        srpc::OperationalCallback {
            "ieee802-dot1q-bridge",
            "/ieee802-dot1q-bridge:bridges/bridge/component/type",
            ieee::br::sub::oper::BridgeComponentTypeOperGetCb(this->m_operContext)
        },
        srpc::OperationalCallback {
            "ieee802-dot1q-bridge",
            "/ieee802-dot1q-bridge:bridges/bridge/component/bridge-vlan",
            ieee::br::sub::oper::BridgeComponentBridgeVlanOperGetCb(this->m_operContext)
        },
        srpc::OperationalCallback {
            "ieee802-dot1q-bridge",
            "/ieee802-dot1q-bridge:bridges/bridge/component/filtering-database",
            ieee::br::sub::oper::BridgeComponentFilteringDatabaseOperGetCb(this->m_operContext)
        }

    };
}

/**
 * Get all module change callbacks which the module should use.
 */
std::list<srpc::ModuleChangeCallback> BridgingModule::getModuleChangeCallbacks()
{
    return {
        srpc::ModuleChangeCallback {
            "ieee802-dot1q-bridge",
            "/ieee802-dot1q-bridge:bridges/bridge/name",
            ieee::br::sub::change::BridgeNameModuleChangeCb(this->m_changeContext),
        },

        srpc::ModuleChangeCallback {
            "ieee802-dot1q-bridge",
            "/ieee802-dot1q-bridge:bridges/bridge/address",
            ieee::br::sub::change::BridgeAddressModuleChangeCb(this->m_changeContext),
        },

        srpc::ModuleChangeCallback {
            "ieee802-dot1q-bridge",
            "/ieee802-dot1q-bridge:bridges/bridge/component/name",
            ieee::br::sub::change::BridgeComponentNameModuleChangeCb(this->m_changeContext),
        },

        srpc::ModuleChangeCallback {
            "ieee802-dot1q-bridge",
            "/ieee802-dot1q-bridge:bridges/bridge/component/address",
            ieee::br::sub::change::BridgeComponentAddressModuleChangeCb(this->m_changeContext),
        },

        srpc::ModuleChangeCallback {
            "ietf-interfaces",
            "/ietf-interfaces:interfaces/interface/bridge-port/component-name",
            ieee::br::sub::change::InterfaceBridgePortComponentNameModuleChangeCb(this->m_changeContext),
        },

        srpc::ModuleChangeCallback {
            "ieee802-dot1q-bridge",
            "/ieee802-dot1q-bridge:bridges/bridge/component/filtering-database/vlan-registration-entry/database-id",
            ieee::br::sub::change::BridgeComponentFilteringDatabaseVlanRegistrationEntryDatabaseIdModuleChangeCb(this->m_changeContext),
        },

        srpc::ModuleChangeCallback {
            "ieee802-dot1q-bridge",
            "/ieee802-dot1q-bridge:bridges/bridge/component/filtering-database/vlan-registration-entry/port-map/port-ref",
            ieee::br::sub::change::BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapPortRefModuleChangeCb(this->m_changeContext),
        },
        srpc::ModuleChangeCallback {
            "ieee802-dot1q-bridge",
            "/ieee802-dot1q-bridge:bridges/bridge/component/filtering-database/vlan-registration-entry/port-map/static-vlan-registration-entries/vlan-transmitted",
            ieee::br::sub::change::BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticVlanRegistrationEntriesVlanTransmittedModuleChangeCb(this->m_changeContext),
        },

        srpc::ModuleChangeCallback {
            "ieee802-dot1q-bridge",
            "/ieee802-dot1q-bridge:bridges/bridge/component/filtering-database",
            ieee::br::sub::change::BridgeComponentFilteringDatabaseAgingTimeModuleChangeCb(this->m_changeContext),
        },

        srpc::ModuleChangeCallback {
            "ieee802-dot1q-bridge",
            "/ieee802-dot1q-bridge:bridges/bridge/component/filtering-database/filtering-entry/port-map/port-ref",
            ieee::br::sub::change::BridgeComponentFilteringDatabaseFilteringEntryPortMapPortRefModuleChangeCb(this->m_changeContext),
        },

    };
}

/**
 * Get all RPC callbacks which the module should use.
 */
std::list<srpc::RpcCallback> BridgingModule::getRpcCallbacks() { return {}; }

/**
 * Get module name.
 */
constexpr const char* BridgingModule::getName() { return "Bridging"; }
