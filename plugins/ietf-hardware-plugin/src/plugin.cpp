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
#include "plugin/callback.hpp"

#include <sysrepo-cpp/Connection.hpp>
#include <sysrepo-cpp/Subscription.hpp>

struct HardwareModel {
    std::shared_ptr<sysrepo::Subscription> sub;
    static std::string const moduleName;
};

static HardwareModel theModel;

std::string const HardwareModel::moduleName = "ietf-hardware";

int sr_plugin_init_cb(sr_session_ctx_t* session, void** /*private_data*/)
{
    sysrepo::Connection conn;
    sysrepo::Session ses = conn.sessionStart();
    std::string const oper_xpath("/" + HardwareModel::moduleName + ":" + "hardware");
    try {
        hardware::HardwareSensors::getInstance().injectConnection(conn);
        sysrepo::Subscription sub = ses.onModuleChange(
            HardwareModel::moduleName, &hardware::Callback::configurationCallback, std::nullopt, 0,
            sysrepo::SubscribeOptions::Enabled | sysrepo::SubscribeOptions::DoneOnly);
        sub.onOperGet(HardwareModel::moduleName, &hardware::Callback::operationalCallback,
            oper_xpath);
        theModel.sub = std::make_shared<sysrepo::Subscription>(std::move(sub));
    } catch (std::exception const& e) {
        SRPLG_LOG_ERR(PLUGIN_NAME, "%s", (std::string("sr_plugin_init_cb: ") + e.what()).c_str());
        theModel.sub.reset();
        return SR_ERR_OPERATION_FAILED;
    }

    return SR_ERR_OK;
}

void sr_plugin_cleanup_cb(sr_session_ctx_t* /*session*/, void* /*private_data*/)
{
    theModel.sub.reset();
    SRPLG_LOG_DBG(PLUGIN_NAME, "plugin cleanup finished.");
}
