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

#include "change.hpp"
#include "common.hpp"
#include "api/component_data.hpp"
#include "api/hardware_sensors.hpp"

#include <string>

#include <sysrepo.h>

namespace ietf::hw::sub::change {

using ErrorCode = sr::ErrorCode;

/**
 * @brief Log the current module configuration (debug).
 */
static void printCurrentConfig(sr::Session& session, std::string_view module_name)
{
    try {
        std::string xpath(std::string("/") + std::string(module_name) + std::string(":*//*"));
        auto values = session.getData(xpath);
        if (!values)
            return;

        std::string const toPrint(
            values.value()
                .printStr(libyang::DataFormat::JSON, libyang::PrintFlags::Siblings)
                .value());
        SRPLG_LOG_DBG(getModuleLogPrefix(), "%s", toPrint.c_str());
    } catch (const std::exception& e) {
        SRPLG_LOG_WRN(getModuleLogPrefix(), "%s", e.what());
    }
}

/**
 * Default constructor.
 *
 * @param ctx Plugin module change context.
 *
 */
HardwareModuleChangeCb::HardwareModuleChangeCb(std::shared_ptr<HardwareModuleChangesContext> ctx) { m_ctx = ctx; }

/**
 * Module change operator() for path /ietf-hardware:hardware.
 *
 * @param session An implicit session for the callback.
 * @param subscriptionId ID the subscription associated with the callback.
 * @param moduleName The module name used for subscribing.
 * @param subXPath The optional xpath used at the time of subscription.
 * @param event Type of the event that has occured.
 * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
 * SR_EV_DONE, for example) have the same request ID.
 *
 * @return Error code.
 *
 */
sr::ErrorCode HardwareModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath,
    sr::Event event, uint32_t requestId)
{
    printCurrentConfig(session, moduleName);
    SRPLG_LOG_DBG(getModuleLogPrefix(), "Processing received configuration.");
    HardwareSensors::getInstance().notifyAndJoin();
    ComponentData::populateConfigData(session, moduleName);
    HardwareSensors::getInstance().startThreads();
    return ErrorCode::Ok;
}

} // namespace ietf::hw::sub::change
