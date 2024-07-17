#include "plugin.hpp"
#include "plugin/context.hpp"

#include <sysrepo-cpp/Session.hpp>
#include <sysrepo-cpp/utils/utils.hpp>

#include <srpcpp.hpp>

#include "plugin/modules/interfaces.hpp"
#include "sysrepo.h"

namespace sr = sysrepo;

void fillInitialRunningDs(sysrepo::Session& s);


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
    auto& registry(srpc::ModuleRegistry<ietf::ifc::PluginContext>::getInstance());
    auto ctx = new ietf::ifc::PluginContext(sess);

    *priv = static_cast<void*>(ctx);

    // create session subscriptions
    SRPLG_LOG_INF(ctx->getPluginName(), "Creating plugin subscriptions");

    registry.registerModule<InterfacesModule>(*ctx);

    auto& modules = registry.getRegisteredModules();

    fillInitialRunningDs(sess);

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
    auto& registry(srpc::ModuleRegistry<ietf::ifc::PluginContext>::getInstance());
    auto ctx = static_cast<ietf::ifc::PluginContext*>(priv);
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

void fillInitialRunningDs(sysrepo::Session& s) {

    sysrepo::Datastore current_ds = s.activeDatastore();
    s.switchDatastore(sysrepo::Datastore::Running);

    // on startup, we delete interfaces node so it allways starts clean
    s.deleteItem("/ietf-interfaces:interfaces");

    auto& nl_ctx = NlContext::getInstance();
    nl_ctx.refillCache();

    auto interfaces = nl_ctx.getLinkCache();
    auto addr_cache = nl_ctx.getAddressCache();
    auto neigh_cache = nl_ctx.getNeighborCache();

    //here we loop through the interfaces
    for (auto& interface : interfaces) {
        std::string if_name = interface.getName();

        // how we handle mtu? 
        // ipv4 mtu is in range 68 - 65565 
        // ipv6 is in range 1280 - 64000
        // so if it is in range for both, we display both
        // we make an intersection of the value for both interfaces
        uint32_t mtu = interface.getMTU();

        s.setItem("/ietf-interfaces:interfaces/interface[name='" + if_name + "']/type", interface.getIanaType());
        //fix the type from rtnl_link_get_arptype(); <linux/if_arp.h>
        s.setItem("/ietf-interfaces:interfaces/interface[name='" + if_name + "']/enabled", (interface.getOperationalStatus() == IF_OPER_UP ? "true" : "false"));

        //map ipv4 with interfaces
        int ifindex = interface.getIndex();

        //ipv4 interface related nodes
        s.setItem("/ietf-interfaces:interfaces/interface[name='" + if_name + "']/ietf-ip:ipv4/forwarding", (interface.getForwarding(AddressFamily::V4) ? "true" : "false"));
        s.setItem("/ietf-interfaces:interfaces/interface[name='" + if_name + "']/ietf-ip:ipv4/enabled", (interface.isIPVEnabled(AddressFamily::V4, addr_cache) ? "true" : "false"));
        // ipv6 mtu minimal packet is 68
        if (mtu >= 68 && mtu <= 0xFFFF)
            s.setItem("/ietf-interfaces:interfaces/interface[name='" + if_name + "']/ietf-ip:ipv4/mtu", std::to_string(mtu));
        //ipv6 interface related nodes
        s.setItem("/ietf-interfaces:interfaces/interface[name='" + if_name + "']/ietf-ip:ipv6/forwarding", (interface.getForwarding(AddressFamily::V6) ? "true" : "false"));
        s.setItem("/ietf-interfaces:interfaces/interface[name='" + if_name + "']/ietf-ip:ipv6/enabled", (interface.isIPVEnabled(AddressFamily::V6, addr_cache) ? "true" : "false"));
        // ipv6 mtu minimal packet is 1280
        if (mtu >= 1280)
            s.setItem("/ietf-interfaces:interfaces/interface[name='" + if_name + "']/ietf-ip:ipv6/mtu", std::to_string(mtu));

        //address handling
        for (auto& addr : addr_cache) {
            if (addr.getInterfaceIndex() == ifindex && addr.getFamily() == AddressFamily::V4) {
                //handle ipv4
                s.setItem("/ietf-interfaces:interfaces/interface[name='" + if_name + "']/ietf-ip:ipv4/address[ip='" + addr.getIPAddress() + "']/prefix-length", std::to_string(addr.getPrefix()));

            }
            else if (addr.getInterfaceIndex() == ifindex && addr.getFamily() == AddressFamily::V6) {
                //handle ipv6
                s.setItem("/ietf-interfaces:interfaces/interface[name='" + if_name + "']/ietf-ip:ipv6/address[ip='" + addr.getIPAddress() + "']/prefix-length", std::to_string(addr.getPrefix()));
            }
        }

        //neighbor handling
        for (auto& neigh : neigh_cache) {
            if (neigh.getInterfaceIndex() == ifindex && neigh.getAddressFamily() == AddressFamily::V4) {
                //handle ipv4
                s.setItem("/ietf-interfaces:interfaces/interface[name='" + if_name + "']/ietf-ip:ipv4/neighbor[ip='" + neigh.getDestinationIP() + "']/link-layer-address", neigh.getLinkLayerAddress());

            }
            else if (neigh.getInterfaceIndex() == ifindex && neigh.getAddressFamily() == AddressFamily::V6) {
                //handle ipv6
                s.setItem("/ietf-interfaces:interfaces/interface[name='" + if_name + "']/ietf-ip:ipv6/neighbor[ip='" + neigh.getDestinationIP() + "']/link-layer-address", neigh.getLinkLayerAddress());
            }
        }

        //bridge port ref handling
        if (interface.isBridge()) {

            auto bridge = nl_ctx.getBridgeByName(if_name);
            if (bridge.has_value()) {

                for (auto&& slave_if : bridge->getSlaveInterfaces()) {
                    s.setItem("/ietf-interfaces:interfaces/interface[name='"+slave_if.getName()+"']/ieee802-dot1q-bridge:bridge-port/component-name", if_name );
                }

            }
        }
    }

    s.applyChanges();

    //revert previous ds
    s.switchDatastore(current_ds);
}

