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

#include "plugin.hpp"
#include "plugin/context.hpp"

#include <sysrepo-cpp/Session.hpp>
#include <sysrepo-cpp/utils/utils.hpp>

#include "plugin/modules/acl.hpp"

#include <sysrepo.h>

namespace sr = sysrepo;

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
    auto& registry(srpc::ModuleRegistry<ietf::acl::PluginContext>::getInstance());
    auto ctx = new ietf::acl::PluginContext(sess);

    *priv = static_cast<void*>(ctx);

    // create session subscriptions
    SRPLG_LOG_INF(ctx->getPluginName(), "Creating plugin subscriptions");

    try {
        registry.registerModule<AclModule>(*ctx);

        auto& modules = registry.getRegisteredModules();

        // for all registered modules - apply running datastore values to the system
        for (auto& mod : modules) {
            SRPLG_LOG_INF(ctx->getPluginName(), "Applying running datastore values for module %s", mod->getName());
            for (auto& applier : mod->getValueAppliers()) {
                try {
                    applier->applyDatastoreValues(sess);
                } catch (const std::exception& err) {
                    SRPLG_LOG_ERR(ctx->getPluginName(), "Failed to apply datastore values for the following paths:");
                    for (const auto& path : applier->getPaths()) {
                        SRPLG_LOG_ERR(ctx->getPluginName(), "\t%s", path.c_str());
                    }
                    SRPLG_LOG_ERR(ctx->getPluginName(), "Reason: %s", err.what());
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
    } catch (const std::exception& err) {
        SRPLG_LOG_ERR(ctx->getPluginName(), "Plugin initialization failed: %s", err.what());

        // sysrepo-plugind does not call the cleanup callback for a plugin whose init failed - drop the context (and
        // with it any subscriptions created so far) here and leave nothing behind for sr_plugin_cleanup_cb()
        delete ctx;
        *priv = nullptr;

        return static_cast<int>(sr::ErrorCode::OperationFailed);
    }

    SRPLG_LOG_INF(ctx->getPluginName(), "Created plugin subscriptions");

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
    auto& registry(srpc::ModuleRegistry<ietf::acl::PluginContext>::getInstance());
    auto ctx = static_cast<ietf::acl::PluginContext*>(priv);

    // init failed and already cleaned up after itself
    if (!ctx) {
        return;
    }

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
