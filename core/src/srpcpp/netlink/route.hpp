#pragma once

#include "nl.hpp"
#include "cache.hpp"

class RouteRef {
public:
    friend class NlContext; ///< Allow NlContext to use the private constructor.
    friend class CacheRef<RouteRef>; ///< Allow Cache to use the private constructor.

private:
    using RtnlRoute = struct rtnl_route; ///< Route type alias.
    using RtnlRouteDeleter = NlDeleter<RtnlRoute>; ///< Deleter type alias.
    using RtnlRoutePtr = std::unique_ptr<RtnlRoute, RtnlRouteDeleter>; ///< Unique pointer type alias.
    using NlSocket = struct nl_sock; ///< Socket type alias.
    using NlSocketDeleter = NlDeleter<NlSocket>; ///< Socket deleter alias.
    using NlSocketPtr = std::unique_ptr<NlSocket, NlSocketDeleter>; ///< Socket unique pointer type alias.

    /**
     * @brief Private constructor accessible only to netlink context. Stores a reference to a route for later access of link members.
     */
    RouteRef(struct rtnl_route* route, struct nl_sock* socket);

    /**
     * @brief Private constructor accessible only to netlink context. Stores a reference to a route for later access of link members.
     */
    RouteRef(struct nl_object* route, struct nl_sock* socket);

    RtnlRoutePtr m_route; ///< Route reference.
    NlSocketPtr m_socket; /// socket reference.
};
