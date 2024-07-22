#include "plugin.hpp"
#include "core/context.hpp"
#include "core/common.hpp"

#include <sysrepo-cpp/Session.hpp>
#include <sysrepo-cpp/utils/utils.hpp>
#include <srpcpp.hpp>

#include "modules/acl.hpp"

namespace sr = sysrepo;

/**
 * TODO
 * Register all operational plugin subscriptions.
 *
 * @param sess Session to use for creating subscriptions.
 * @param ctx Plugin context.
 * @param mod Module to use.
 *
 */
void registerOperationalSubscriptions(sr::Session& sess, ietf::acl::PluginContext& ctx, std::unique_ptr<srpc::IModule<ietf::acl::PluginContext>>& mod){
    const auto oper_callbacks = mod->getOperationalCallbacks();

    auto& sub_handle = ctx.getSubscriptionHandle();

    for (auto& cb : oper_callbacks) {
        SRPLG_LOG_INF(ietf::acl::PLUGIN_NAME, "Creating operational subscription for xpath %s", cb.XPath.c_str());
        if (sub_handle.has_value()) {
            sub_handle->onOperGet("ietf-access-control-list", cb.Callback, cb.XPath);
        } else {
            sub_handle = sess.onOperGet("ietf-access-control-list", cb.Callback, cb.XPath);
        }
    }
};

/**
 * TODO
 * Register all module change plugin subscriptions.
 *
 * @param sess Session to use for creating subscriptions.
 * @param ctx Plugin context.
 * @param mod Module to use.
 *
 */
void registerModuleChangeSubscriptions(sr::Session& sess, ietf::acl::PluginContext& ctx, std::unique_ptr<srpc::IModule<ietf::acl::PluginContext>>& mod){
    
    const auto change_callbacks = mod->getModuleChangeCallbacks();

    auto& sub_handle = ctx.getSubscriptionHandle();

    for (auto& cb : change_callbacks) {
        SRPLG_LOG_INF(ietf::acl::PLUGIN_NAME, "Creating module change subscription for xpath %s", cb.XPath.c_str());
        if (sub_handle.has_value()) {
            sub_handle->onModuleChange("ietf-access-control-list", cb.Callback, cb.XPath);
        } else {
            sub_handle = sess.onModuleChange("ietf-access-control-list", cb.Callback, cb.XPath);
        }
    }
};

/**
 * TODO
 * Register all RPC plugin subscriptions.
 *
 * @param sess Session to use for creating subscriptions.
 * @param ctx Plugin context.
 * @param mod Module to use.
 *
 */
void registerRpcSubscriptions(sr::Session& sess, ietf::acl::PluginContext& ctx, std::unique_ptr<srpc::IModule<ietf::acl::PluginContext>>& mod){
    const auto rpc_callbacks = mod->getRpcCallbacks();

    auto& sub_handle = ctx.getSubscriptionHandle();

    for (auto& cb : rpc_callbacks) {
        SRPLG_LOG_INF(ietf::acl::PLUGIN_NAME, "Creating RPC subscription for xpath %s", cb.XPath.c_str());
        if (sub_handle.has_value()) {
            sub_handle->onRPCAction(cb.XPath, cb.Callback);
        } else {
            sub_handle = sess.onRPCAction(cb.XPath, cb.Callback);
        }
    }
};

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
    auto plugin_ctx = new ietf::acl::PluginContext(sess);
    auto& registry(srpc::ModuleRegistry<ietf::acl::PluginContext>::getInstance());
    *priv = static_cast<void*>(plugin_ctx);

    SRPLG_LOG_INF(ietf::acl::PLUGIN_NAME, "Creating plugin subscriptions");

    registry.registerModule<AclModule>(*plugin_ctx);

    // get registered modules and create subscriptions
    auto& modules = registry.getRegisteredModules();
    for (auto& mod : modules) {
        SRPLG_LOG_INF(ietf::acl::PLUGIN_NAME, "Registering operational callbacks for module %s", mod->getName());
        registerOperationalSubscriptions(sess, *plugin_ctx, mod);
        SRPLG_LOG_INF(ietf::acl::PLUGIN_NAME, "Registering module change callbacks for module %s", mod->getName());
        registerModuleChangeSubscriptions(sess, *plugin_ctx, mod);
        SRPLG_LOG_INF(ietf::acl::PLUGIN_NAME, "Registering RPC callbacks for module %s", mod->getName());
        registerRpcSubscriptions(sess, *plugin_ctx, mod);
        SRPLG_LOG_INF(ietf::acl::PLUGIN_NAME, "Registered module %s", mod->getName());
    }

    SRPLG_LOG_INF(ietf::acl::PLUGIN_NAME, "Created plugin subscriptions");

    return static_cast<int>(error);
}

void sr_plugin_cleanup_cb(sr_session_ctx_t* session, void* priv)
{
    SRPLG_LOG_INF(ietf::acl::PLUGIN_NAME, "Plugin cleanup called");

    auto& registry(srpc::ModuleRegistry<ietf::acl::PluginContext>::getInstance());
    auto plugin_ctx = static_cast<ietf::acl::PluginContext*>(priv);

    auto& modules = registry.getRegisteredModules();
    for (auto& mod : modules) {
        SRPLG_LOG_INF(ietf::acl::PLUGIN_NAME, "Cleaning up module: %s", mod->getName());
    }

    delete plugin_ctx;

    SRPLG_LOG_INF(ietf::acl::PLUGIN_NAME, "Plugin cleanup finished");
}
