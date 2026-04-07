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

#pragma once

#include <srpcpp.hpp>

#include "plugin/context.hpp"
#include "metrics/context.hpp"

class MetricsModule : public srpc::IModule<metrics::PluginContext> {
public:
    MetricsModule(metrics::PluginContext& plugin_ctx);

    virtual std::shared_ptr<srpc::IModuleContext> getOperationalContext() override;
    virtual std::shared_ptr<srpc::IModuleContext> getModuleChangesContext() override;
    virtual std::shared_ptr<srpc::IModuleContext> getRpcContext() override;

    virtual std::list<srpc::OperationalCallback> getOperationalCallbacks() override;
    virtual std::list<srpc::ModuleChangeCallback> getModuleChangeCallbacks() override;
    virtual std::list<srpc::RpcCallback> getRpcCallbacks() override;

    virtual constexpr const char* getName() override;

    ~MetricsModule() { }

private:
    std::shared_ptr<MetricsOperationalContext> m_operContext;
    std::shared_ptr<MetricsModuleChangesContext> m_changeContext;
    std::shared_ptr<MetricsRpcContext> m_rpcContext;
};
