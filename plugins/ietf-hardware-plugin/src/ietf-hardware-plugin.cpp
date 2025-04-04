// telekom / sysrepo-plugin-hardware
//
// This program is made available under the terms of the
// BSD 3-Clause license which is available at
// https://opensource.org/licenses/BSD-3-Clause
//
// SPDX-FileCopyrightText: 2021 Deutsche Telekom AG
//
// SPDX-License-Identifier: BSD-3-Clause

#include <callback.h>
#include <stdio.h>
#include <sysrepo-cpp/Connection.hpp>

extern "C" {
void sr_plugin_cleanup_cb(sr_session_ctx_t* session, void* private_data);
int sr_plugin_init_cb(sr_session_ctx_t* session, void** private_data);
}

struct HardwareModel {
    std::shared_ptr<sysrepo::Subscription> sub;
    static std::string const moduleName;
};

static HardwareModel theModel;

std::string const HardwareModel::moduleName = "ietf-hardware";

int sr_plugin_init_cb(sr_session_ctx_t* session, void** /*private_data*/) {
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
        logMessage(SR_LL_ERR, std::string("sr_plugin_init_cb: ") + e.what());
        theModel.sub.reset();
        return SR_ERR_OPERATION_FAILED;
    }

    return SR_ERR_OK;
}

void sr_plugin_cleanup_cb(sr_session_ctx_t* /*session*/, void* /*private_data*/) {
    theModel.sub.reset();
    logMessage(SR_LL_DBG, "plugin cleanup finished.");
}
