#include "oper.hpp"
#include "plugin/modules/routing/api/nexthop.hpp"
#include "plugin/modules/routing/api/rib.hpp"
#include "sysrepo.h"
#include "common.hpp"
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

    auto ipv4_module = session.getContext().getModule("ietf-ipv4-unicast-routing", "2018-03-13");
    auto ipv6_module = session.getContext().getModule("ietf-ipv6-unicast-routing", "2018-03-13");

    auto base = RoutingInformationBase(route_cache);

    for (auto& rib_iter : base) {
        auto& rib_name = rib_iter.first;
        auto& rib_object = rib_iter.second;
        auto& routes = rib_object.getRoutes();

        std::stringstream rib_path_buffer;

        rib_path_buffer << "rib[name=\'" << rib_name << "\']";
        auto rib_node = output->newPath(rib_path_buffer.str());
        auto routes_node = rib_node->newPath("routes");

        SRPLG_LOG_INF(getModuleLogPrefix(), "RIB: %s", rib_name.c_str());

        // configure rib

        // default
        rib_node->newPath("default-rib", rib_object.isDefault() ? "true" : "false");

        // address family
        rib_node->newPath("address-family", rib_object.getFamily() == AddressFamily::V4 ? "ipv4" : "ipv6");

        for (auto& route : routes) {
            std::stringstream pref_buffer, ifname_buffer, ip_buffer;
            auto route_node = routes_node->newPath("route");
            auto nh_node = route_node->newPath("next-hop");

            pref_buffer << route.getPreference();

            // route-preference
            route_node->newPath("route-preference", pref_buffer.str());

            // route-metadata
            route_node->newPath("source-protocol", route.getMetadata().source_protocol);

            SRPLG_LOG_INF(getModuleLogPrefix(), "Route: %d, %s", route.getPreference(), route.getMetadata().source_protocol.c_str());
        }
    }

    return error;
}

}
