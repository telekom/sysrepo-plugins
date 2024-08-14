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
#include "plugin/modules/routing/common.hpp"
#include "sysrepo-cpp/Enum.hpp"
#include "plugin/modules/routing/api/nexthop.hpp"
#include "plugin/modules/routing/api/rib.hpp"

#include <stdexcept>
#include <sysrepo.h>

namespace ietf::rt {
namespace sub::change {
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    RouterIdModuleChangeCb::RouterIdModuleChangeCb(std::shared_ptr<RoutingModuleChangesContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ietf-routing:routing/router-id.
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
    sr::ErrorCode RouterIdModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    TypeModuleChangeCb::TypeModuleChangeCb(std::shared_ptr<RoutingModuleChangesContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-routing:routing/control-plane-protocols/control-plane-protocol[name='%s'][type='%s']/type.
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
    sr::ErrorCode TypeModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    ControlPlaneProtocolNameModuleChangeCb::ControlPlaneProtocolNameModuleChangeCb(std::shared_ptr<RoutingModuleChangesContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-routing:routing/control-plane-protocols/control-plane-protocol[name='%s'][type='%s']/name.
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
    sr::ErrorCode ControlPlaneProtocolNameModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    ControlPlaneProtocolDescriptionModuleChangeCb::ControlPlaneProtocolDescriptionModuleChangeCb(std::shared_ptr<RoutingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-routing:routing/control-plane-protocols/control-plane-protocol[name='%s'][type='%s']/description.
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
    sr::ErrorCode ControlPlaneProtocolDescriptionModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
    {
        sr::ErrorCode error = sr::ErrorCode::Ok;

        switch (event) {
        case sysrepo::Event::Change:
            for (auto& change : session.getChanges(subXPath->data())) {
                switch (change.operation) {
                case sysrepo::ChangeOperation::Created:
                case sysrepo::ChangeOperation::Modified: {
                    SRPLG_LOG_DBG(getModuleLogPrefix(), "Value of %s modified.", change.node.path().c_str());
                    SRPLG_LOG_DBG(getModuleLogPrefix(), "Value of %s modified.", change.node.schema().name().data());

                    break;
                }
                case sysrepo::ChangeOperation::Deleted:
                    break;
                case sysrepo::ChangeOperation::Moved:
                    break;
                }
            }
            break;
        default:
            break;
        }

        return error;
    }

    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    V4RouteDestinationPrefixModuleChangeCb::V4RouteDestinationPrefixModuleChangeCb(std::shared_ptr<RoutingModuleChangesContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-routing:routing/control-plane-protocols/control-plane-protocol[name='%s'][type='%s']/static-routes/ietf-ipv4-unicast-routing:ipv4/route[destination-prefix='%s']/destination-prefix.
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
    sr::ErrorCode V4RouteDestinationPrefixModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
    {
        sr::ErrorCode error = sr::ErrorCode::Ok;

        switch (event) {
        case sysrepo::Event::Change:
            for (auto& change : session.getChanges(subXPath->data())) {
                switch (change.operation) {
                case sysrepo::ChangeOperation::Created:
                case sysrepo::ChangeOperation::Modified: {

                    break;
                }
                case sysrepo::ChangeOperation::Deleted:
                    break;
                case sysrepo::ChangeOperation::Moved:
                    break;
                }
            }
            break;
        default:
            break;
        }

        return error;
    }

    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    V4RouteDescriptionModuleChangeCb::V4RouteDescriptionModuleChangeCb(std::shared_ptr<RoutingModuleChangesContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-routing:routing/control-plane-protocols/control-plane-protocol[name='%s'][type='%s']/static-routes/ietf-ipv4-unicast-routing:ipv4/route[destination-prefix='%s']/description.
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
    sr::ErrorCode V4RouteDescriptionModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    V4RouteNextHopOutgoingInterfaceModuleChangeCb::V4RouteNextHopOutgoingInterfaceModuleChangeCb(std::shared_ptr<RoutingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-routing:routing/control-plane-protocols/control-plane-protocol[name='%s'][type='%s']/static-routes/ietf-ipv4-unicast-routing:ipv4/route[destination-prefix='%s']/next-hop/outgoing-interface.
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
    sr::ErrorCode V4RouteNextHopOutgoingInterfaceModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    V4RouteNextHopNextHopAddressModuleChangeCb::V4RouteNextHopNextHopAddressModuleChangeCb(std::shared_ptr<RoutingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-routing:routing/control-plane-protocols/control-plane-protocol[name='%s'][type='%s']/static-routes/ietf-ipv4-unicast-routing:ipv4/route[destination-prefix='%s']/next-hop/next-hop-address.
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
    sr::ErrorCode V4RouteNextHopNextHopAddressModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    V4RouteNextHopSpecialNextHopModuleChangeCb::V4RouteNextHopSpecialNextHopModuleChangeCb(std::shared_ptr<RoutingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-routing:routing/control-plane-protocols/control-plane-protocol[name='%s'][type='%s']/static-routes/ietf-ipv4-unicast-routing:ipv4/route[destination-prefix='%s']/next-hop/special-next-hop.
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
    sr::ErrorCode V4RouteNextHopSpecialNextHopModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    V4RouteNextHopNextHopListNextHopIndexModuleChangeCb::V4RouteNextHopNextHopListNextHopIndexModuleChangeCb(
        std::shared_ptr<RoutingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-routing:routing/control-plane-protocols/control-plane-protocol[name='%s'][type='%s']/static-routes/ietf-ipv4-unicast-routing:ipv4/route[destination-prefix='%s']/next-hop/next-hop-list/next-hop[index='%s']/index.
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
    sr::ErrorCode V4RouteNextHopNextHopListNextHopIndexModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId,
        std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    V4RouteNextHopNextHopListNextHopOutgoingInterfaceModuleChangeCb::V4RouteNextHopNextHopListNextHopOutgoingInterfaceModuleChangeCb(
        std::shared_ptr<RoutingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-routing:routing/control-plane-protocols/control-plane-protocol[name='%s'][type='%s']/static-routes/ietf-ipv4-unicast-routing:ipv4/route[destination-prefix='%s']/next-hop/next-hop-list/next-hop[index='%s']/outgoing-interface.
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
    sr::ErrorCode V4RouteNextHopNextHopListNextHopOutgoingInterfaceModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId,
        std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
    {
        sr::ErrorCode error = sr::ErrorCode::Ok;

        switch (event) {
        case sr::Event::Change: {

            for (sysrepo::Change change : session.getChanges(subXPath->data())) {

                std::string destination_prefix = srpc::extractListKeysFromXpath("route", change.node.path())["destination-prefix"];
                std::string path = "/ietf-routing:routing/control-plane-protocols/control-plane-protocol/static-routes/ietf-ipv4-unicast-routing:ipv4/route[destination-prefix='" + destination_prefix + "']";
                auto changes = session.getChanges(path);

                if (!(changes.begin() == changes.end())) {
                    continue;
                }

                std::string index = srpc::extractListKeysFromXpath("next-hop", change.node.path())["index"];

                path.append("/next-hop/next-hop-list/next-hop[index='" + index + "']");

                changes = session.getChanges(path);

                if (!(changes.begin() == changes.end())) {
                    continue;
                }

                // you cannot modify the interface that you are on
                error = sr::ErrorCode::Unsupported;
            }

            break;
        }
        default:
            break;
        }

        return error;
    }

    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    V4RouteNextHopNextHopListNextHopNextHopAddressModuleChangeCb::V4RouteNextHopNextHopListNextHopNextHopAddressModuleChangeCb(
        std::shared_ptr<RoutingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-routing:routing/control-plane-protocols/control-plane-protocol[name='%s'][type='%s']/static-routes/ietf-ipv4-unicast-routing:ipv4/route[destination-prefix='%s']/next-hop/next-hop-list/next-hop[index='%s']/next-hop-address.
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
    sr::ErrorCode V4RouteNextHopNextHopListNextHopNextHopAddressModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId,
        std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
    {
        sr::ErrorCode error = sr::ErrorCode::Ok;
        switch (event) {
        case sr::Event::Change:

            for (sysrepo::Change change : session.getChanges(subXPath->data())) {

                // handle upper callbacks

                // 1. check if destination-prefix has change
                // 2. check if route cb has change

                std::string destination_prefix = srpc::extractListKeysFromXpath("route", change.node.path())["destination-prefix"];
                std::string path = "/ietf-routing:routing/control-plane-protocols/control-plane-protocol/static-routes/ietf-ipv4-unicast-routing:ipv4/route[destination-prefix='" + destination_prefix + "']";

                auto changes = session.getChanges(path);

                if (!(changes.begin() == changes.end())) {
                    continue;
                }

                std::string index = srpc::extractListKeysFromXpath("next-hop", change.node.path())["index"];

                path.append("/next-hop/next-hop-list/next-hop[index='" + index + "']");

                changes = session.getChanges(path);

                if (!(changes.begin() == changes.end())) {
                    continue;
                }

                switch (change.operation) {

                case sr::ChangeOperation::Modified: {
                    auto& nl_ctx = NlContext::getInstance();
                    // cannot modify nh, just delete and create new

                    // first we need the interface, that is the first sibiling of the tree
                    std::string xpath = change.node.parent()->path();
                    xpath.append("/outgoing-interface");

                    auto if_name_node = session.getOneNode(xpath);

                    std::string if_name = if_name_node.asTerm().valueStr().data();

                    std::string new_value = change.node.asTerm().valueStr().data();
                    std::string old_value = change.previousValue->data();

                    try {
                        int ifindex = nl_ctx.nameToIfindex(if_name);

                        auto route = nl_ctx.findRoute(destination_prefix);

                        route->addAndRemoveNextHops(
                            {
                                NextHopHelper(new_value, ifindex),
                            },
                            {
                                NextHopHelper(old_value, ifindex),
                            });

                    } catch (std::exception& e) {
                        SRPLG_LOG_ERR(getModuleLogPrefix(), e.what());
                        error = sr::ErrorCode::CallbackFailed;
                    }

                    break;
                }
                case sr::ChangeOperation::Deleted:
                    // delete address should be unsupported
                    return sr::ErrorCode::Unsupported;
                    break;
                }
            }

            break;

        default:
            break;
        }

        return error;
    }

    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    V4RouteNextHopNextHopListNextHopModuleChangeCb::V4RouteNextHopNextHopListNextHopModuleChangeCb(std::shared_ptr<RoutingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-routing:routing/control-plane-protocols/control-plane-protocol[name='%s'][type='%s']/static-routes/ietf-ipv4-unicast-routing:ipv4/route[destination-prefix='%s']/next-hop/next-hop-list/next-hop[index='%s'].
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
    sr::ErrorCode V4RouteNextHopNextHopListNextHopModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId,
        std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
    {
        sr::ErrorCode error = sr::ErrorCode::Ok;

        enum class NextHopOperations {
            TO_DELETE,
            TO_CREATE
        };

        switch (event) {
        case sysrepo::Event::Change: {

            auto& nl_ctx = NlContext::getInstance();

            std::string outgoing_interface;
            std::string next_hop_address;

            // this handles the case of multiple destination prefixes at once

            std::unordered_map<std::string, std::map<NextHopOperations, std::vector<NextHopHelper>>> route_map;

            for (sysrepo::Change change : session.getChanges(subXPath->data())) {

                outgoing_interface.clear();
                next_hop_address.clear();
                int ifindex = 0;

                std::string destination_prefix = srpc::extractListKeysFromXpath("route", change.node.path())["destination-prefix"];
                const std::string path = "/ietf-routing:routing/control-plane-protocols/control-plane-protocol/static-routes/ietf-ipv4-unicast-routing:ipv4/route[destination-prefix='" + destination_prefix + "']";

                auto changes = session.getChanges(path);

                if (!(changes.begin() == changes.end())) {
                    // it means that container is not empty
                    // there are changes there, so break the loop
                    // that node will create the whole route with nh's
                    continue;
                };

                // get the route
                auto route_opt = nl_ctx.findRoute(destination_prefix);

                if (!route_opt) {
                    SRPLG_LOG_ERR(getModuleLogPrefix(), "Failed to find route!");
                    return sr::ErrorCode::CallbackFailed;
                }

                for (libyang::DataNode&& i : change.node.childrenDfs()) {
                    if (i.schema().name().compare("outgoing-interface") == 0) {
                        outgoing_interface = i.asTerm().valueStr();
                    } else if (i.schema().name().compare("next-hop-address") == 0) {
                        next_hop_address = i.asTerm().valueStr();
                    }
                }

                // check if values are there
                if (outgoing_interface.empty() || next_hop_address.empty()) {
                    SRPLG_LOG_ERR(getModuleLogPrefix(), "Next-Hop values missing!");
                    return sr::ErrorCode::CallbackFailed;
                };

                try {
                    ifindex = nl_ctx.nameToIfindex(outgoing_interface);
                } catch (std::exception& e) {
                    SRPLG_LOG_ERR(getModuleLogPrefix(), e.what());
                    return sr::ErrorCode::CallbackFailed;
                }

                switch (change.operation) {
                case sysrepo::ChangeOperation::Created: {
                    route_map[destination_prefix][NextHopOperations::TO_CREATE].push_back(NextHopHelper(next_hop_address, ifindex));
                    break;
                }

                case sysrepo::ChangeOperation::Deleted:
                    route_map[destination_prefix][NextHopOperations::TO_DELETE].push_back(NextHopHelper(next_hop_address, ifindex));
                    break;
                }
            }

            for (auto&& route : route_map) {

                std::string dest_pref = route.first;

                try {
                    auto route_opt = nl_ctx.findRoute(dest_pref);

                    if (!route_opt) {
                        throw std::runtime_error("Failed to find route!");
                    }

                    route_opt->addAndRemoveNextHops(route.second[NextHopOperations::TO_CREATE], route.second[NextHopOperations::TO_DELETE]);

                } catch (std::exception& e) {
                    SRPLG_LOG_ERR(getModuleLogPrefix(), e.what());
                    error = sr::ErrorCode::CallbackFailed;
                }
            };

            break;
        }
        default:
            break;
        }
        return error;
    }

    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    V4RouteNextHopNextHopListModuleChangeCb::V4RouteNextHopNextHopListModuleChangeCb(std::shared_ptr<RoutingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-routing:routing/control-plane-protocols/control-plane-protocol[name='%s'][type='%s']/static-routes/ietf-ipv4-unicast-routing:ipv4/route[destination-prefix='%s']/next-hop/next-hop-list.
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
    sr::ErrorCode V4RouteNextHopNextHopListModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    V4RouteNextHopModuleChangeCb::V4RouteNextHopModuleChangeCb(std::shared_ptr<RoutingModuleChangesContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-routing:routing/control-plane-protocols/control-plane-protocol[name='%s'][type='%s']/static-routes/ietf-ipv4-unicast-routing:ipv4/route[destination-prefix='%s']/next-hop.
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
    sr::ErrorCode V4RouteNextHopModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    V4RouteModuleChangeCb::V4RouteModuleChangeCb(std::shared_ptr<RoutingModuleChangesContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-routing:routing/control-plane-protocols/control-plane-protocol[name='%s'][type='%s']/static-routes/ietf-ipv4-unicast-routing:ipv4/route[destination-prefix='%s'].
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
    sr::ErrorCode V4RouteModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
    {
        sr::ErrorCode error = sr::ErrorCode::Ok;

        switch (event) {
        case sysrepo::Event::Change: {
            auto& nl_ctx = NlContext::getInstance();
            for (sysrepo::Change route_change : session.getChanges(subXPath->data())) {
                switch (route_change.operation) {
                case sysrepo::ChangeOperation::Created: {
                    std::vector<NextHopHelper> create_nh;

                    std::string route = srpc::extractListKeysFromXpath("route", route_change.node.path())["destination-prefix"];

                    for (sysrepo::Change change : session.getChanges(route_change.node.path() + "/next-hop/next-hop-list/next-hop")) {
                        switch (change.operation) {
                        case sysrepo::ChangeOperation::Created: {

                            std::string interface_name;
                            std::string nh_addr;
                            int ifindex;

                            for (auto&& i : change.node.childrenDfs()) {
                                if (i.schema().name().compare("outgoing-interface") == 0) {
                                    interface_name = i.asTerm().valueStr();
                                } else if (i.schema().name().compare("next-hop-address") == 0) {
                                    nh_addr = i.asTerm().valueStr();
                                }
                            }

                            // first check if ifindex is valid
                            try {
                                ifindex = nl_ctx.nameToIfindex(interface_name);
                            } catch (std::exception& e) {
                                SRPLG_LOG_ERR(getModuleLogPrefix(), e.what());
                                return sr::ErrorCode::CallbackFailed;
                            }

                            create_nh.push_back(NextHopHelper(nh_addr, ifindex));

                            break;
                        }
                        case sysrepo::ChangeOperation::Deleted:
                            /*
                            this case will never be used since on creating new route,
                            there is nothing to delete
                            */
                            break;

                        default:
                            break;
                        }
                    }

                    try {
                        nl_ctx.createRoute(route, create_nh);
                    } catch (std::exception& e) {
                        SRPLG_LOG_ERR(getModuleLogPrefix(), "Error creating route! reason %s", e.what());
                        error = sr::ErrorCode::CallbackFailed;
                    };

                    break;
                }

                case sysrepo::ChangeOperation::Deleted: {
                    // just delete the route, the nhs will automaticaly delete
                    std::string del_route = srpc::extractListKeysFromXpath("route", route_change.node.path())["destination-prefix"];
                    // try catch here!!
                    nl_ctx.deleteRoute(del_route);
                    break;
                }
                case sysrepo::ChangeOperation::Moved:
                    break;
                }
            }
        }
        default:
            break;
        }

        return error;
    }

    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    V4ModuleChangeCb::V4ModuleChangeCb(std::shared_ptr<RoutingModuleChangesContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-routing:routing/control-plane-protocols/control-plane-protocol[name='%s'][type='%s']/static-routes/ietf-ipv4-unicast-routing:ipv4.
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
    sr::ErrorCode V4ModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    V6RouteDestinationPrefixModuleChangeCb::V6RouteDestinationPrefixModuleChangeCb(std::shared_ptr<RoutingModuleChangesContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-routing:routing/control-plane-protocols/control-plane-protocol[name='%s'][type='%s']/static-routes/ietf-ipv6-unicast-routing:ipv6/route[destination-prefix='%s']/destination-prefix.
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
    sr::ErrorCode V6RouteDestinationPrefixModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    V6RouteDescriptionModuleChangeCb::V6RouteDescriptionModuleChangeCb(std::shared_ptr<RoutingModuleChangesContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-routing:routing/control-plane-protocols/control-plane-protocol[name='%s'][type='%s']/static-routes/ietf-ipv6-unicast-routing:ipv6/route[destination-prefix='%s']/description.
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
    sr::ErrorCode V6RouteDescriptionModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    V6RouteNextHopOutgoingInterfaceModuleChangeCb::V6RouteNextHopOutgoingInterfaceModuleChangeCb(std::shared_ptr<RoutingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-routing:routing/control-plane-protocols/control-plane-protocol[name='%s'][type='%s']/static-routes/ietf-ipv6-unicast-routing:ipv6/route[destination-prefix='%s']/next-hop/outgoing-interface.
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
    sr::ErrorCode V6RouteNextHopOutgoingInterfaceModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    V6RouteNextHopNextHopAddressModuleChangeCb::V6RouteNextHopNextHopAddressModuleChangeCb(std::shared_ptr<RoutingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-routing:routing/control-plane-protocols/control-plane-protocol[name='%s'][type='%s']/static-routes/ietf-ipv6-unicast-routing:ipv6/route[destination-prefix='%s']/next-hop/next-hop-address.
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
    sr::ErrorCode V6RouteNextHopNextHopAddressModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    V6RouteNextHopSpecialNextHopModuleChangeCb::V6RouteNextHopSpecialNextHopModuleChangeCb(std::shared_ptr<RoutingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-routing:routing/control-plane-protocols/control-plane-protocol[name='%s'][type='%s']/static-routes/ietf-ipv6-unicast-routing:ipv6/route[destination-prefix='%s']/next-hop/special-next-hop.
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
    sr::ErrorCode V6RouteNextHopSpecialNextHopModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    V6RouteNextHopNextHopListNextHopIndexModuleChangeCb::V6RouteNextHopNextHopListNextHopIndexModuleChangeCb(
        std::shared_ptr<RoutingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-routing:routing/control-plane-protocols/control-plane-protocol[name='%s'][type='%s']/static-routes/ietf-ipv6-unicast-routing:ipv6/route[destination-prefix='%s']/next-hop/next-hop-list/next-hop[index='%s']/index.
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
    sr::ErrorCode V6RouteNextHopNextHopListNextHopIndexModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId,
        std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    V6RouteNextHopNextHopListNextHopOutgoingInterfaceModuleChangeCb::V6RouteNextHopNextHopListNextHopOutgoingInterfaceModuleChangeCb(
        std::shared_ptr<RoutingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-routing:routing/control-plane-protocols/control-plane-protocol[name='%s'][type='%s']/static-routes/ietf-ipv6-unicast-routing:ipv6/route[destination-prefix='%s']/next-hop/next-hop-list/next-hop[index='%s']/outgoing-interface.
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
    sr::ErrorCode V6RouteNextHopNextHopListNextHopOutgoingInterfaceModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId,
        std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    V6RouteNextHopNextHopListNextHopNextHopAddressModuleChangeCb::V6RouteNextHopNextHopListNextHopNextHopAddressModuleChangeCb(
        std::shared_ptr<RoutingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-routing:routing/control-plane-protocols/control-plane-protocol[name='%s'][type='%s']/static-routes/ietf-ipv6-unicast-routing:ipv6/route[destination-prefix='%s']/next-hop/next-hop-list/next-hop[index='%s']/next-hop-address.
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
    sr::ErrorCode V6RouteNextHopNextHopListNextHopNextHopAddressModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId,
        std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    V6RouteNextHopNextHopListNextHopModuleChangeCb::V6RouteNextHopNextHopListNextHopModuleChangeCb(std::shared_ptr<RoutingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-routing:routing/control-plane-protocols/control-plane-protocol[name='%s'][type='%s']/static-routes/ietf-ipv6-unicast-routing:ipv6/route[destination-prefix='%s']/next-hop/next-hop-list/next-hop[index='%s'].
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
    sr::ErrorCode V6RouteNextHopNextHopListNextHopModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId,
        std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    V6RouteNextHopNextHopListModuleChangeCb::V6RouteNextHopNextHopListModuleChangeCb(std::shared_ptr<RoutingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-routing:routing/control-plane-protocols/control-plane-protocol[name='%s'][type='%s']/static-routes/ietf-ipv6-unicast-routing:ipv6/route[destination-prefix='%s']/next-hop/next-hop-list.
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
    sr::ErrorCode V6RouteNextHopNextHopListModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    V6RouteNextHopModuleChangeCb::V6RouteNextHopModuleChangeCb(std::shared_ptr<RoutingModuleChangesContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-routing:routing/control-plane-protocols/control-plane-protocol[name='%s'][type='%s']/static-routes/ietf-ipv6-unicast-routing:ipv6/route[destination-prefix='%s']/next-hop.
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
    sr::ErrorCode V6RouteNextHopModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    V6RouteModuleChangeCb::V6RouteModuleChangeCb(std::shared_ptr<RoutingModuleChangesContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-routing:routing/control-plane-protocols/control-plane-protocol[name='%s'][type='%s']/static-routes/ietf-ipv6-unicast-routing:ipv6/route[destination-prefix='%s'].
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
    sr::ErrorCode V6RouteModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    V6ModuleChangeCb::V6ModuleChangeCb(std::shared_ptr<RoutingModuleChangesContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-routing:routing/control-plane-protocols/control-plane-protocol[name='%s'][type='%s']/static-routes/ietf-ipv6-unicast-routing:ipv6.
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
    sr::ErrorCode V6ModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    StaticRoutesModuleChangeCb::StaticRoutesModuleChangeCb(std::shared_ptr<RoutingModuleChangesContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-routing:routing/control-plane-protocols/control-plane-protocol[name='%s'][type='%s']/static-routes.
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
    sr::ErrorCode StaticRoutesModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    ControlPlaneProtocolModuleChangeCb::ControlPlaneProtocolModuleChangeCb(std::shared_ptr<RoutingModuleChangesContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-routing:routing/control-plane-protocols/control-plane-protocol[name='%s'][type='%s'].
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
    sr::ErrorCode ControlPlaneProtocolModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    ControlPlaneProtocolsModuleChangeCb::ControlPlaneProtocolsModuleChangeCb(std::shared_ptr<RoutingModuleChangesContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ietf-routing:routing/control-plane-protocols.
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
    sr::ErrorCode ControlPlaneProtocolsModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    RibNameModuleChangeCb::RibNameModuleChangeCb(std::shared_ptr<RoutingModuleChangesContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ietf-routing:routing/ribs/rib[name='%s']/name.
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
    sr::ErrorCode RibNameModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    AddressFamilyModuleChangeCb::AddressFamilyModuleChangeCb(std::shared_ptr<RoutingModuleChangesContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ietf-routing:routing/ribs/rib[name='%s']/address-family.
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
    sr::ErrorCode AddressFamilyModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    RibDescriptionModuleChangeCb::RibDescriptionModuleChangeCb(std::shared_ptr<RoutingModuleChangesContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ietf-routing:routing/ribs/rib[name='%s']/description.
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
    sr::ErrorCode RibDescriptionModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    RibModuleChangeCb::RibModuleChangeCb(std::shared_ptr<RoutingModuleChangesContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ietf-routing:routing/ribs/rib[name='%s'].
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
    sr::ErrorCode RibModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    RibsModuleChangeCb::RibsModuleChangeCb(std::shared_ptr<RoutingModuleChangesContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ietf-routing:routing/ribs.
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
    sr::ErrorCode RibsModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    RoutingModuleChangeCb::RoutingModuleChangeCb(std::shared_ptr<RoutingModuleChangesContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ietf-routing:routing.
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
    sr::ErrorCode RoutingModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
    {
        sr::ErrorCode error = sr::ErrorCode::Ok;
        return error;
    }
}
}
