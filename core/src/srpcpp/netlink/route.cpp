#include "route.hpp"
#include "srpcpp/netlink/nl.hpp"

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
