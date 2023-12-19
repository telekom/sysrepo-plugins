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

    if (!sess.getData("/ieee802-dot1q-bridge:bridges")->child().has_value()) {
        fillInitialDatastoreFromSystem(sess);
    }

    // for all registered modules - apply startup datastore values
    // startup datastore values are coppied into the running datastore when the first connection with sysrepo is made
    for (auto& mod : modules) {
        SRPLG_LOG_INF(ctx->getPluginName(), "Applying startup values for module %s", mod->getName());
        for (auto& applier : mod->getValueAppliers()) {
            try {
                applier->applyDatastoreValues(sess);
            } catch (const std::runtime_error& err) {
                SRPLG_LOG_INF(ctx->getPluginName(), "Failed to apply datastore values for the following paths:");
                for (const auto& path : applier->getPaths()) {
                    SRPLG_LOG_INF(ctx->getPluginName(), "\t%s", path.c_str());
                }
            }
        }
    }

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
                auto vlan_map = BridgeRef::parseVlanIDSToString(vlans);

                std::string tagged = vlan_map[BridgeRef::BridgeVidParse::TAGGED];
                std::string untagged = vlan_map[BridgeRef::BridgeVidParse::UNTAGGED];

                if (!tagged.empty()) {
                    session.setItem("/ieee802-dot1q-bridge:bridges/bridge[name='" + bridge_name + "']/component[name='" + bridge_name + "']/filtering-database/vlan-registration-entry[vids='" + tagged + "'][database-id='0']/port-map[port-ref='" + std::to_string(slave.getIfindex()) + "']/static-vlan-registration-entries/vlan-transmitted", "tagged");
                }

                if (!untagged.empty()) {
                    session.setItem("/ieee802-dot1q-bridge:bridges/bridge[name='" + bridge_name + "']/component[name='" + bridge_name + "']/filtering-database/vlan-registration-entry[vids='" + untagged + "'][database-id='0']/port-map[port-ref='" + std::to_string(slave.getIfindex()) + "']/static-vlan-registration-entries/vlan-transmitted", "untagged");
                }
            }
        }
    }

    session.applyChanges();
}
