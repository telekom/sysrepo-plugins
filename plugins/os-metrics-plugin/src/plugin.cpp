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

#include "plugin/modules/metrics.hpp"
#include "plugin/threshold_manager.hpp"

#include <sysrepo.h>

namespace sr = sysrepo;

int sr_plugin_init_cb(sr_session_ctx_t* session, void** priv)
{
    sr::ErrorCode error = sr::ErrorCode::Ok;
    auto sess = sysrepo::wrapUnmanagedSession(session);
    auto& registry(srpc::ModuleRegistry<metrics::PluginContext>::getInstance());
    auto ctx = new metrics::PluginContext(sess);

    *priv = static_cast<void*>(ctx);

    SRPLG_LOG_INF(ctx->getPluginName(), "Creating plugin subscriptions");

    try {
        auto conn = ctx->getConnection();
        metrics::MemoryMonitoring::getInstance().injectConnection(conn, "os-metrics");
        metrics::FilesystemMonitoring::getInstance().injectConnection(conn, "os-metrics");

        registry.registerModule<MetricsModule>(*ctx);

        auto& modules = registry.getRegisteredModules();

        for (auto& mod : modules) {
            SRPLG_LOG_INF(ctx->getPluginName(), "Registering operational callbacks for module %s", mod->getName());
            srpc::registerOperationalSubscriptions(sess, *ctx, mod);
            SRPLG_LOG_INF(ctx->getPluginName(), "Registering module change callbacks for module %s", mod->getName());
            srpc::registerModuleChangeSubscriptions(sess, *ctx, mod);
            SRPLG_LOG_INF(ctx->getPluginName(), "Registering RPC callbacks for module %s", mod->getName());
            srpc::registerRpcSubscriptions(sess, *ctx, mod);
            SRPLG_LOG_INF(ctx->getPluginName(), "Registered module %s", mod->getName());
        }
    } catch (std::exception const& e) {
        SRPLG_LOG_ERR(ctx->getPluginName(), "sr_plugin_init_cb: %s", e.what());
        delete ctx;
        return SR_ERR_OPERATION_FAILED;
    }

    SRPLG_LOG_INF(ctx->getPluginName(), "Created plugin subscriptions");

    return static_cast<int>(error);
}

void sr_plugin_cleanup_cb(sr_session_ctx_t* session, void* priv)
{
    auto& registry(srpc::ModuleRegistry<metrics::PluginContext>::getInstance());
    auto ctx = static_cast<metrics::PluginContext*>(priv);
    const auto plugin_name = ctx->getPluginName();

    SRPLG_LOG_INF(plugin_name, "Plugin cleanup called");

    auto& modules = registry.getRegisteredModules();
    for (auto& mod : modules) {
        SRPLG_LOG_INF(plugin_name, "Cleaning up module: %s", mod->getName());
    }

    delete ctx;

    SRPLG_LOG_INF(plugin_name, "Plugin cleanup finished");
}
