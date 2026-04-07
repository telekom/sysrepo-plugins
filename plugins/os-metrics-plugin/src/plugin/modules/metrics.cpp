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

#include "metrics.hpp"

#include "plugin/cpu_stats.hpp"
#include "plugin/filesystem_stats.hpp"
#include "plugin/memory_stats.hpp"
#include "plugin/process_stats.hpp"
#include "plugin/threshold_manager.hpp"

#include <format>
#include <sysrepo.h>

static constexpr const char* MODULE_NAME = "os-metrics";

MetricsModule::MetricsModule(metrics::PluginContext& plugin_ctx)
    : srpc::IModule<metrics::PluginContext>(plugin_ctx)
{
    m_operContext = std::make_shared<MetricsOperationalContext>();
    m_changeContext = std::make_shared<MetricsModuleChangesContext>();
    m_rpcContext = std::make_shared<MetricsRpcContext>();
}

std::shared_ptr<srpc::IModuleContext> MetricsModule::getOperationalContext() { return m_operContext; }
std::shared_ptr<srpc::IModuleContext> MetricsModule::getModuleChangesContext() { return m_changeContext; }
std::shared_ptr<srpc::IModuleContext> MetricsModule::getRpcContext() { return m_rpcContext; }

std::list<srpc::OperationalCallback> MetricsModule::getOperationalCallbacks()
{
    return {
        srpc::OperationalCallback {
            MODULE_NAME,
            "/os-metrics:system-metrics/cpu-statistics",
            [](sysrepo::Session session, uint32_t, std::string_view moduleName,
                std::optional<std::string_view>, std::optional<std::string_view>,
                uint32_t, std::optional<libyang::DataNode>& parent) -> sysrepo::ErrorCode {
                metrics::CpuStats stats;
                stats.readCpuTimes();
                stats.setXpathValues(parent, moduleName);
                double loadavg[3];
                if (getloadavg(loadavg, 3) != -1) {
                    parent->newPath(
                        "/" + std::string(moduleName) + ":system-metrics/cpu-statistics/average-load/avg-1min-load",
                        std::format("{:.2f}", loadavg[0]));
                    parent->newPath(
                        "/" + std::string(moduleName) + ":system-metrics/cpu-statistics/average-load/avg-5min-load",
                        std::format("{:.2f}", loadavg[1]));
                    parent->newPath(
                        "/" + std::string(moduleName) + ":system-metrics/cpu-statistics/average-load/avg-15min-load",
                        std::format("{:.2f}", loadavg[2]));
                } else {
                    SRPLG_LOG_ERR(PLUGIN_NAME, "getloadavg call failed");
                }
                return sysrepo::ErrorCode::Ok;
            } },

        srpc::OperationalCallback {
            MODULE_NAME,
            "/os-metrics:system-metrics/memory/statistics",
            [](sysrepo::Session session, uint32_t, std::string_view moduleName,
                std::optional<std::string_view>, std::optional<std::string_view>,
                uint32_t, std::optional<libyang::DataNode>& parent) -> sysrepo::ErrorCode {
                auto modules = session.getContext().modules();
                auto mod = std::find_if(modules.begin(), modules.end(),
                    [&moduleName](libyang::Module const& m) { return moduleName == m.name(); });
                if (mod != modules.end() && mod->featureEnabled("usage-notifications")) {
                    metrics::MemoryMonitoring::getInstance().setXpaths(parent, moduleName);
                }
                metrics::MemoryStats::getInstance().readMemoryStats();
                metrics::MemoryStats::getInstance().setXpathValues(parent, moduleName);
                return sysrepo::ErrorCode::Ok;
            } },

        srpc::OperationalCallback {
            MODULE_NAME,
            "/os-metrics:system-metrics/filesystems",
            [](sysrepo::Session session, uint32_t, std::string_view moduleName,
                std::optional<std::string_view>, std::optional<std::string_view>,
                uint32_t, std::optional<libyang::DataNode>& parent) -> sysrepo::ErrorCode {
                auto modules = session.getContext().modules();
                auto mod = std::find_if(modules.begin(), modules.end(),
                    [&moduleName](libyang::Module const& m) { return moduleName == m.name(); });
                if (mod != modules.end() && mod->featureEnabled("usage-notifications")) {
                    metrics::FilesystemMonitoring::getInstance().setXpaths(parent, moduleName);
                }
                metrics::FilesystemStats::getInstance().readFilesystemStats();
                metrics::FilesystemStats::getInstance().setXpathValues(parent, moduleName);
                return sysrepo::ErrorCode::Ok;
            } },

        srpc::OperationalCallback {
            MODULE_NAME,
            "/os-metrics:system-metrics/processes",
            [](sysrepo::Session, uint32_t, std::string_view moduleName,
                std::optional<std::string_view>, std::optional<std::string_view>,
                uint32_t, std::optional<libyang::DataNode>& parent) -> sysrepo::ErrorCode {
                metrics::ProcessStats::getInstance().readAndSetAll(parent, moduleName);
                return sysrepo::ErrorCode::Ok;
            } },
    };
}

std::list<srpc::ModuleChangeCallback> MetricsModule::getModuleChangeCallbacks()
{
    return {
        srpc::ModuleChangeCallback {
            MODULE_NAME,
            "/os-metrics:system-metrics/memory",
            [](sysrepo::Session session, uint32_t, std::string_view moduleName,
                std::optional<std::string_view>, sysrepo::Event,
                uint32_t) -> sysrepo::ErrorCode {
                auto modules = session.getContext().modules();
                auto mod = std::find_if(modules.begin(), modules.end(),
                    [&moduleName](libyang::Module const& m) { return moduleName == m.name(); });
                if (mod != modules.end() && mod->featureEnabled("usage-notifications")) {
                    metrics::MemoryMonitoring::getInstance().notifyAndJoin();
                    metrics::MemoryMonitoring::getInstance().populateConfigData(session, moduleName);
                    metrics::MemoryMonitoring::getInstance().startThread();
                } else {
                    SRPLG_LOG_WRN(PLUGIN_NAME, "Feature not enabled: usage-notifications");
                }
                return sysrepo::ErrorCode::Ok;
            },
            sysrepo::SubscribeOptions::Enabled | sysrepo::SubscribeOptions::DoneOnly },

        srpc::ModuleChangeCallback {
            MODULE_NAME,
            "/os-metrics:system-metrics/filesystems",
            [](sysrepo::Session session, uint32_t, std::string_view moduleName,
                std::optional<std::string_view>, sysrepo::Event,
                uint32_t) -> sysrepo::ErrorCode {
                auto modules = session.getContext().modules();
                auto mod = std::find_if(modules.begin(), modules.end(),
                    [&moduleName](libyang::Module const& m) { return moduleName == m.name(); });
                if (mod != modules.end() && mod->featureEnabled("usage-notifications")) {
                    metrics::FilesystemMonitoring::getInstance().notifyAndJoin();
                    metrics::FilesystemMonitoring::getInstance().populateConfigData(session, moduleName);
                    metrics::FilesystemMonitoring::getInstance().startThreads();
                } else {
                    SRPLG_LOG_WRN(PLUGIN_NAME, "Feature not enabled: usage-notifications");
                }
                return sysrepo::ErrorCode::Ok;
            },
            sysrepo::SubscribeOptions::Enabled | sysrepo::SubscribeOptions::DoneOnly },
    };
}

std::list<srpc::RpcCallback> MetricsModule::getRpcCallbacks() { return {}; }

constexpr const char* MetricsModule::getName() { return "Metrics"; }
