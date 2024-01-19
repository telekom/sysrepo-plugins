#include "plugin.hpp"
#include "plugin/context.hpp"

#include <sysrepo-cpp/Session.hpp>
#include <sysrepo-cpp/utils/utils.hpp>

#include <srpcpp.hpp>

#include "plugin/modules/routing.hpp"

#include "sysrepo.h"
#include "sysrepo-cpp/utils/exception.hpp"

namespace sr = sysrepo;

inline void fillInitialRunninDS(sysrepo::Session& sess);

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
    auto& registry(srpc::ModuleRegistry<ietf::rt::PluginContext>::getInstance());
    auto ctx = new ietf::rt::PluginContext(sess);

    *priv = static_cast<void*>(ctx);

    // create session subscriptions
    SRPLG_LOG_INF(ctx->getPluginName(), "Creating plugin subscriptions");

    registry.registerModule<RoutingModule>(*ctx);

    auto& modules = registry.getRegisteredModules();

    sess.switchDatastore(sysrepo::Datastore::Running);

    // this is the check where we check if running is full or empty
    auto data_cp_opt = sess.getData("/ietf-routing:routing/control-plane-protocols")->child()->child();
    auto data_ribs_opt = sess.getData("/ietf-routing:routing/ribs")->child()->child();

    if (!data_cp_opt && !data_ribs_opt) {
        try {

            fillInitialRunninDS(sess);
        } catch (sysrepo::ErrorWithCode& e) {
            SRPLG_LOG_ERR(ctx->getPluginName(), "Unable to fill running Datastore, Possible error is matching interfaces in interfaces plugin, Err: %s", e.what());
        }
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
    auto& registry(srpc::ModuleRegistry<ietf::rt::PluginContext>::getInstance());
    auto ctx = static_cast<ietf::rt::PluginContext*>(priv);
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

inline void fillInitialRunninDS(sysrepo::Session& m_sess)
{
    auto& nl_ctx = NlContext::getInstance();

    m_sess.switchDatastore(sr::Datastore::Running);

    auto route_map = nl_ctx.getRoutingMap();

    // m_sess.setItem("/ietf-routing:routing/control-plane-protocols/control-plane-protocol[type='ietf-routing:static'][name='unspec']/static-routes/ietf-ipv4-unicast-routing:ipv4/route[destination-prefix='10.10.10.0/24']/next-hop/next-hop-list/next-hop[index='test5']/next-hop-address", "192.168.0.1");
    // m_sess.setItem("/ietf-routing:routing/control-plane-protocols/control-plane-protocol[type='ietf-routing:static'][name='unspec']/static-routes/ietf-ipv4-unicast-routing:ipv4/route[destination-prefix='10.10.10.0/24']/next-hop/next-hop-list/next-hop[index='test5']/outgoing-interface", "enp0s3");

    for (auto&& main_table_ipv4_route : route_map[254][RouteFamily::RT_INET]) {
        int idx_count = 0;
        for (auto&& nhs : main_table_ipv4_route.getNextHops()) {
            m_sess.setItem("/ietf-routing:routing/control-plane-protocols/control-plane-protocol[type='ietf-routing:static'][name='unspec']/static-routes/ietf-ipv4-unicast-routing:ipv4/route[destination-prefix='" + main_table_ipv4_route.getDestinationString() + "']/next-hop/next-hop-list/next-hop[index='index-" + std::to_string(idx_count) + "']/next-hop-address", nhs.getGateway().toString());
            m_sess.setItem("/ietf-routing:routing/control-plane-protocols/control-plane-protocol[type='ietf-routing:static'][name='unspec']/static-routes/ietf-ipv4-unicast-routing:ipv4/route[destination-prefix='" + main_table_ipv4_route.getDestinationString() + "']/next-hop/next-hop-list/next-hop[index='index-" + std::to_string(idx_count) + "']/outgoing-interface", nl_ctx.ifindexToName(nhs.getInterfaceIndex()));

            idx_count++;
        }

        idx_count = 0;
    }

    m_sess.applyChanges();
}