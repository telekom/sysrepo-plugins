#include "oper.hpp"
#include "plugin/modules/routing/api/nexthop.hpp"
#include "plugin/modules/routing/api/rib.hpp"
#include "srpcpp/netlink/address.hpp"
#include "sysrepo.h"
#include "common.hpp"
#include <optional>
#include <sstream>
#include <stdexcept>
#include <variant>

namespace ietf::rt::sub::oper {
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
        auto& nl_ctx = m_ctx->getNetlinkContext();
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

    auto& nl_ctx = m_ctx->getNetlinkContext();

    auto route_cache = nl_ctx.getRouteCache();

    auto ipv4_module = session.getContext().loadModule("ietf-ipv4-unicast-routing");
    auto ipv6_module = session.getContext().loadModule("ietf-ipv6-unicast-routing");

    auto base = RoutingInformationBase(route_cache);

    for (auto& rib_iter : base) {
        auto& rib_name = rib_iter.first;
        auto& rib_object = rib_iter.second;
        auto& routes = rib_object.getRoutes();

        std::stringstream rib_path_buffer;

        rib_path_buffer << "rib[name=\'" << rib_name << "\']";
        auto rib_node = output->newPath(rib_path_buffer.str());
        auto routes_node = rib_node->newPath("routes");

        // default
        rib_node->newPath("default-rib", rib_object.isDefault() ? "true" : "false");

        // address family
        rib_node->newPath("address-family", rib_object.getFamily() == AddressFamily::V4 ? "ietf-ipv4-unicast-routing:ipv4-unicast" : "ietf-ipv6-unicast-routing:ipv6-unicast");

        for (auto& route : routes) {
            std::stringstream pref_buffer, ifname_buffer, ip_buffer;
            auto route_node = routes_node->newPath("route");
            auto nh_node = route_node->newPath("next-hop");

            pref_buffer << route.getPreference();

            // route-preference
            route_node->newPath("route-preference", pref_buffer.str());

            // route-metadata
            route_node->newPath("source-protocol", route.getMetadata().source_protocol);

            // next-hop data
            auto& next_hop = route.getNextHop();
            if (std::holds_alternative<NextHopSimple>(next_hop)) {
                auto next_hop_simple = std::get<NextHopSimple>(next_hop);

                auto if_index = next_hop_simple.getInterfaceIndex();
                auto gateway = next_hop_simple.getGateway();
                auto interface = nl_ctx.getInterfaceByIndex((uint32_t)if_index);

                nh_node->newPath("outgoing-interface", interface->getName());

                std::optional<std::string> addr_module = std::nullopt;

                switch (rib_object.getFamily()) {
                case AddressFamily::V4:
                    addr_module = "ipv4";
                    break;
                case AddressFamily::V6:
                    addr_module = "ipv6";
                    break;
                default:
                    // return an error
                    break;
                }

                // add gateway
                if (gateway != "none" && addr_module.has_value()) {
                    auto ss = std::stringstream();
                    ss << "ietf-" << addr_module.value() << "-unicast-routing:next-hop-address";
                    nh_node->newPath(ss.str(), gateway);
                }
            } else if (std::holds_alternative<NextHopList>(next_hop)) {
                auto next_hop_list = std::get<NextHopList>(next_hop);
            } else if (std::holds_alternative<NextHopSpecial>(next_hop)) {
                auto next_hop_spec = std::get<NextHopSpecial>(next_hop);
            } else {
                // invalid next-hop
            }

            // SRPLG_LOG_INF(getModuleLogPrefix(), "Route: %d, %s", route.getPreference(), route.getMetadata().source_protocol.c_str());
        }
    }

    return error;
}

}
