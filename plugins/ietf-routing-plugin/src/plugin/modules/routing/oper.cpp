#include "oper.hpp"
#include "plugin/modules/routing/api/nexthop.hpp"
#include "plugin/modules/routing/api/rib.hpp"
#include "srpcpp/netlink/address.hpp"
#include "srpcpp/netlink/route.hpp"
#include "sysrepo.h"
#include "common.hpp"
#include <optional>
#include <sstream>
#include <stdexcept>
#include <variant>

namespace ietf::rt::sub::oper {

static std::optional<std::string> getUnicastModuleForAddressFamily(AddressFamily af)
{
    switch (af) {
    case AddressFamily::V4:
        return "ietf-ipv4-unicast-routing";
    case AddressFamily::V6:
        return "ietf-ipv6-unicast-routing";
    case AddressFamily::Other:
        break;
    }
    return std::nullopt;
}

/**
 * sysrepo-plugin-generator: Generated default constructor.
 *
 * @param ctx Plugin operational context.
 *
 */
RoutingOperGetCb::RoutingOperGetCb(std::shared_ptr<RoutingOperationalContext> ctx) { m_ctx = ctx; }

/**
 * sysrepo-plugin-generator: Generated operator() for path /ietf-routing:routing.
 *
 * @param session An implicit session for the callback.
 * @param subscriptionId ID the subscription associated with the callback.
 * @param moduleName The module name used for subscribing.
 * @param subXPath The optional xpath used at the time of subscription.
 * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
 * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
 *
 * @return Error code.
 *
 */
sr::ErrorCode RoutingOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
    std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
    std::optional<ly::DataNode>& output)
{
    sr::ErrorCode error = sr::ErrorCode::Ok;
    return error;
}

/**
 * sysrepo-plugin-generator: Generated default constructor.
 *
 * @param ctx Plugin operational context.
 *
 */
RoutingInterfacesOperGetCb::RoutingInterfacesOperGetCb(std::shared_ptr<RoutingOperationalContext> ctx)
    : m_ctx(ctx)
{
}

/**
 * sysrepo-plugin-generator: Generated operational get operator() for path /ietf-routing:routing.
 *
 * @param session An implicit session for the callback.
 * @param subscriptionId ID the subscription associated with the callback.
 * @param moduleName The module name used for subscribing.
 * @param subXPath The optional xpath used at the time of subscription.
 * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
 * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
 *
 * @return Error code.
 *
 */
sr::ErrorCode RoutingInterfacesOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath,
    std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
{
    sr::ErrorCode error = sr::ErrorCode::Ok;

    try {
        auto& nl_ctx = NlContext::getInstance();
        auto link_cache = nl_ctx.getLinkCache();

        for (auto& link : link_cache) {
            output->newPath("interface", link.getName());
        }

    } catch (std::runtime_error& ex) {
        SRPLG_LOG_ERR(getModuleLogPrefix(), "Error getting network-layer interfaces used for routing: %s", ex.what());
    }

    return error;
}

/**
 * sysrepo-plugin-generator: Generated default constructor.
 *
 * @param ctx Plugin operational context.
 *
 */
RoutingRibOperGetCb::RoutingRibOperGetCb(std::shared_ptr<RoutingOperationalContext> ctx)
    : m_ctx(ctx)
{
}

/**
 * sysrepo-plugin-generator: Generated operational get operator() for path /ietf-routing:routing.
 *
 * @param session An implicit session for the callback.
 * @param subscriptionId ID the subscription associated with the callback.
 * @param moduleName The module name used for subscribing.
 * @param subXPath The optional xpath used at the time of subscription.
 * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
 * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
 *
 * @return Error code.
 *
 */
sr::ErrorCode RoutingRibOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath,
    std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
{
    sr::ErrorCode error = sr::ErrorCode::Ok;

    auto& nl_ctx = NlContext::getInstance();

    auto route_map = nl_ctx.getRoutingMap();

    auto ribs_node = output->newPath("ribs");

    for (auto&& rib : route_map) {

        std::string table_family_name = RouteRef::tableToString(rib.first);
        auto rib_node = ribs_node->newPath("rib[name='" + (table_family_name + "-ipv4") + "']");
        auto routes_node = rib_node->newPath("routes");

        // ipv4 routes
        for (auto&& ipv4_routes : rib.second[RouteFamily::RT_INET]) {
            auto route_node = routes_node->newPath("route");
            route_node->newPath("ietf-ipv4-unicast-routing:destination-prefix", ipv4_routes.getDestinationString());
            auto next_hop_node = route_node->newPath("next-hop");
            auto next_hop_list_node = next_hop_node->newPath("next-hop-list");
            for (auto&& nhs : ipv4_routes.getNextHops()) {

                auto next_hop_inside_node = next_hop_list_node->newPath("next-hop");
                next_hop_inside_node->newPath("outgoing-interface", nl_ctx.ifindexToName(nhs.getInterfaceIndex()));
                next_hop_inside_node->newPath("ietf-ipv4-unicast-routing:address", nhs.getGateway().toString());
            }
        }

        // // ipv6 routes
        // for (auto&& ipv4_routes : rib.second[RouteFamily::RT_INET6]) {
        // }
    }

    return error;
}

}
