#include "route.hpp"
#include "address.hpp"
#include <netlink/route/route.h>

/**
 * @brief Private constructor accessible only to netlink context. Stores a reference to a route for later access of link members.
 */
RouteRef::RouteRef(struct rtnl_route* route, struct nl_sock* socket)
    : m_route(RtnlRoutePtr(route, NlEmptyDeleter<RtnlRoute>))
    , m_socket(NlSocketPtr(socket, NlEmptyDeleter<NlSocket>))
{
}

/**
 * @brief Private constructor accessible only to netlink context. Stores a reference to a route for later access of link members.
 */
RouteRef::RouteRef(struct nl_object* route, struct nl_sock* socket)
    : m_route(RtnlRoutePtr(reinterpret_cast<RtnlRoute*>(route), NlEmptyDeleter<RtnlRoute>))
    , m_socket(NlSocketPtr(socket, NlEmptyDeleter<NlSocket>))
{
}

/**
 * @brief Returns the table ID of the route.
 */
std::uint32_t RouteRef::getTable() const { return rtnl_route_get_table(m_route.get()); }

/**
 * @brief Returns the scope of the route.
 */
std::uint8_t RouteRef::getScope() const { return rtnl_route_get_scope(m_route.get()); }

/**
 * @brief Returns the TOS of the route.
 */
std::uint8_t RouteRef::getTOS() const { return rtnl_route_get_tos(m_route.get()); }

/**
 * @brief Returns the protocol of the route.
 */
std::uint8_t RouteRef::getProtocol() const { return rtnl_route_get_protocol(m_route.get()); }

/**
 * @brief Returns the priority of the route.
 */
std::uint32_t RouteRef::getPriority() const { return rtnl_route_get_priority(m_route.get()); }

/**
 * @brief Returns the family of the route.
 */
std::uint8_t RouteRef::getFamily() const { return rtnl_route_get_family(m_route.get()); }

/**
 * @brief Returns the type of the route.
 */
std::uint8_t RouteRef::getType() const { return rtnl_route_get_type(m_route.get()); }

/**
 * @brief Returns the flags of the route.
 */
std::uint32_t RouteRef::getFlags() const { return rtnl_route_get_flags(m_route.get()); }

/**
 * @brief Returns the destination address of the route.
 */
AddressRef RouteRef::getDestination() const
{
    return AddressRef(rtnl_route_get_dst(m_route.get()), m_socket.get());
}

/**
 * @brief Returns the source address of the route.
 */
AddressRef RouteRef::getSource() const
{
    return AddressRef(rtnl_route_get_src(m_route.get()), m_socket.get());
}
