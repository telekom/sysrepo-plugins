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

#include "plugin.hpp"
#include "plugin/context.hpp"

#include <sysrepo-cpp/Session.hpp>
#include <sysrepo-cpp/utils/utils.hpp>

#include <srpcpp.hpp>
#include <array>
#include <string>

#include "plugin/modules/bridging.hpp"

#include "sysrepo.h"

namespace sr = sysrepo;

/**
 * @brief Initial system data fill.
 *
 * @param session Plugin session.
 */
inline void fillInitialDatastoreFromSystem(sysrepo::Session& session);

/**
 * @brief Plugin init callback.
 *
 * @param session Plugin session.
 * @param priv Private data.
 *
 * @return Error code (SR_ERR_OK on success).
 */
int sr_plugin_init_cb(sr_session_ctx_t* session, void** priv)
{
    sr::ErrorCode error = sysrepo::ErrorCode::Ok;
    auto sess = sysrepo::wrapUnmanagedSession(session);
    auto& registry(srpc::ModuleRegistry<ieee::br::PluginContext>::getInstance());
    auto ctx = new ieee::br::PluginContext(sess);

    *priv = static_cast<void*>(ctx);

    // create session subscriptions
    SRPLG_LOG_INF(ctx->getPluginName(), "Creating plugin subscriptions");

    registry.registerModule<BridgingModule>(*ctx);

    auto& modules = registry.getRegisteredModules();

    // fill initial ds from system
    // first check if datastore is empty

    fillInitialDatastoreFromSystem(sess);


    // get registered modules and create subscriptions
    for (auto& mod : modules) {
        SRPLG_LOG_INF(ctx->getPluginName(), "Registering operational callbacks for module %s", mod->getName());
        srpc::registerOperationalSubscriptions(sess, *ctx, mod);
        SRPLG_LOG_INF(ctx->getPluginName(), "Registering module change callbacks for module %s", mod->getName());
        srpc::registerModuleChangeSubscriptions(sess, *ctx, mod);
        SRPLG_LOG_INF(ctx->getPluginName(), "Registering RPC callbacks for module %s", mod->getName());
        srpc::registerRpcSubscriptions(sess, *ctx, mod);
        SRPLG_LOG_INF(ctx->getPluginName(), "Registered module %s", mod->getName());
    }

    SRPLG_LOG_INF("ietf-system-plugin", "Created plugin subscriptions");

    return static_cast<int>(error);
}

/**
 * @brief Plugin cleanup callback.
 *
 * @param session Plugin session.
 * @param priv Private data.
 *
 */
void sr_plugin_cleanup_cb(sr_session_ctx_t* session, void* priv)
{
    auto& registry(srpc::ModuleRegistry<ieee::br::PluginContext>::getInstance());
    auto ctx = static_cast<ieee::br::PluginContext*>(priv);
    const auto plugin_name = ctx->getPluginName();

    SRPLG_LOG_INF(plugin_name, "Plugin cleanup called");

    auto& modules = registry.getRegisteredModules();
    for (auto& mod : modules) {
        SRPLG_LOG_INF(ctx->getPluginName(), "Cleaning up module: %s", mod->getName());
    }

    // cleanup context manually
    delete ctx;

    SRPLG_LOG_INF(plugin_name, "Plugin cleanup finished");
}

inline void fillInitialDatastoreFromSystem(sysrepo::Session& session)
{
    sr::Datastore current_ds = session.activeDatastore();
    session.switchDatastore(sr::Datastore::Running);

    //delete running ds for data consistancy
    session.deleteItem("/ieee802-dot1q-bridge:bridges");

    // fill system data here
    auto& nl_ctx = NlContext::getInstance();

    // lets go hierarchicly, first fill bridges, then go to lower levels
    for (auto&& bridge : nl_ctx.getBridgeInterfaces()) {
        std::string format_addr = bridge.getMacAddr();
        std::replace(format_addr.begin(), format_addr.end(), ':', '-');
        std::string bridge_name = bridge.getName();

        session.setItem("/ieee802-dot1q-bridge:bridges/bridge[name='" + bridge_name + "']/bridge-type", "customer-vlan-bridge");
        session.setItem("/ieee802-dot1q-bridge:bridges/bridge[name='" + bridge_name + "']/address", format_addr);
        session.setItem("/ieee802-dot1q-bridge:bridges/bridge[name='" + bridge_name + "']/component[name='" + bridge_name + "']/type", "c-vlan-component");
        session.setItem("/ieee802-dot1q-bridge:bridges/bridge[name='" + bridge_name + "']/component[name='" + bridge_name + "']/address", format_addr);

        auto slave_interfaces = bridge.getSlaveInterfaces();

        if (!slave_interfaces.empty()) {
            // we have slave interfaces so we will fill the vlan registration entry

            for (auto&& slave : slave_interfaces) {
                const auto& vlans = slave.getVlanList();
                const auto& fdb = slave.getFilteringVids();

                auto vlan_map = BridgeRef::parseVlanIDSToString(vlans);

                std::string tagged = vlan_map[BridgeRef::BridgeVidParse::TAGGED];
                std::string untagged = vlan_map[BridgeRef::BridgeVidParse::UNTAGGED];

                if (!tagged.empty()) {
                    session.setItem("/ieee802-dot1q-bridge:bridges/bridge[name='" + bridge_name + "']/component[name='" + bridge_name + "']/filtering-database/vlan-registration-entry[vids='" + tagged + "'][database-id='0']/port-map[port-ref='" + std::to_string(slave.getIfindex()) + "']/static-vlan-registration-entries/vlan-transmitted", "tagged");
                }

                if (!untagged.empty()) {
                    session.setItem("/ieee802-dot1q-bridge:bridges/bridge[name='" + bridge_name + "']/component[name='" + bridge_name + "']/filtering-database/vlan-registration-entry[vids='" + untagged + "'][database-id='0']/port-map[port-ref='" + std::to_string(slave.getIfindex()) + "']/static-vlan-registration-entries/vlan-transmitted", "untagged");
                }

                if (!fdb.empty()) {

                    std::unordered_map<std::string, std::vector<uint16_t>> parsed_by_mac;

                    // group them by mac addr
                    for (auto i : fdb) {

                        if (i.isFiltered()) {
                            std::string formatted_mac_string = i.getStringMAC();
                            std::replace(formatted_mac_string.begin(), formatted_mac_string.end(), ':', '-');
                            parsed_by_mac[formatted_mac_string].push_back(i.getVID());
                        }
                    }

                    for (auto&& fdb_mac_ftd : parsed_by_mac) {

                        const auto& mac_string = fdb_mac_ftd.first;
                        const auto& filtered_vids = BridgeRef::rawNumParser(fdb_mac_ftd.second);
                        session.setItem("/ieee802-dot1q-bridge:bridges/bridge[name='" + bridge_name + "']/component[name='" + bridge_name + "']/filtering-database/filtering-entry[vids='" + filtered_vids + "'][database-id='0'][address='" + mac_string + "']/port-map[port-ref='" + std::to_string(slave.getIfindex()) + "']/static-filtering-entries/control-element", "forward");
                        session.setItem("/ieee802-dot1q-bridge:bridges/bridge[name='" + bridge_name + "']/component[name='" + bridge_name + "']/filtering-database/filtering-entry[vids='" + filtered_vids + "'][database-id='0'][address='" + mac_string + "']/entry-type", "static");
                    }
                }
            }
        }
    }

    session.applyChanges();

    session.switchDatastore(current_ds);
}
