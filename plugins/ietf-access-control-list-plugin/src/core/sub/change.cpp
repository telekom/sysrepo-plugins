//
// telekom / sysrepo-plugins
//
// This program is made available under the terms of the
// BSD 3-Clause license which is available at
// https://opensource.org/licenses/BSD-3-Clause
//
// SPDX-FileCopyrightText: 2024 Deutsche Telekom AG
// SPDX-FileContributor: Sartura d.d.
//
// SPDX-License-Identifier: BSD-3-Clause
//

#include "change.hpp"

namespace ietf::acl {
namespace sub::change {
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    AclModuleChangeCb::AclModuleChangeCb(std::shared_ptr<ietf::acl::ModuleChangeContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ietf-access-control-list:acls/acl[name='%s'].
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
    sr::ErrorCode AclModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
    {
        sr::ErrorCode error = sr::ErrorCode::Ok;
        return error;
    }

    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    InterfaceModuleChangeCb::InterfaceModuleChangeCb(std::shared_ptr<ietf::acl::ModuleChangeContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s'].
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
    sr::ErrorCode InterfaceModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
    {
        sr::ErrorCode error = sr::ErrorCode::Ok;
        return error;
    }

}
}