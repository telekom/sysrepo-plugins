#pragma once

#include "nl.hpp"
#include "cache.hpp"

class AddressRef;

class RouteRef {
public:
    friend class NlContext; ///< Allow NlContext to use the private constructor.
    friend class CacheRef<RouteRef>; ///< Allow Cache to use the private constructor.

    /**
     * @brief Returns the table ID of the route.
     */
    std::uint32_t getTable() const;

    /**
     * @brief Returns the scope of the route.
     */
    std::uint8_t getScope() const;

    /**
     * @brief Returns the TOS of the route.
     */
    std::uint8_t getTOS() const;

    /**
     * @brief Returns the protocol of the route.
     */
    std::uint8_t getProtocol() const;

    /**
     * @brief Returns the priority of the route.
     */
    std::uint32_t getPriority() const;

    /**
     * @brief Returns the family of the route.
     */
    std::uint8_t getFamily() const;

    /**
     * @brief Returns the type of the route.
     */
    std::uint8_t getType() const;

    /**
     * @brief Returns the flags of the route.
     */
    std::uint32_t getFlags() const;

    /**
     * @brief Returns the destination address of the route.
     */
    AddressRef getDestination() const;

    /**
     * @brief Returns the source address of the route.
     */
    AddressRef getSource() const;

private:
    using RtnlRoute = struct rtnl_route; ///< Route type alias.
    using RtnlRouteDeleter = NlDeleter<RtnlRoute>; ///< Deleter type alias.
    using RtnlRoutePtr = std::unique_ptr<RtnlRoute, RtnlRouteDeleter>; ///< Unique pointer type alias.
    using NlSocket = struct nl_sock; ///< Socket type alias.
    using NlSocketDeleter = NlDeleter<NlSocket>; ///< Socket deleter alias.
    using NlSocketPtr = std::unique_ptr<NlSocket, NlSocketDeleter>; ///< Socket unique pointer type alias.

    /**
     * @brief Private constructor accessible only to netlink context. Stores a reference to a route for later access of members.
     */
    RouteRef(struct rtnl_route* route, struct nl_sock* socket);

    /**
     * @brief Private constructor accessible only to netlink context. Stores a reference to a route for later access of members.
     */
    RouteRef(struct nl_object* route, struct nl_sock* socket);

    RtnlRoutePtr m_route; ///< Route reference.
    NlSocketPtr m_socket; /// socket reference.
};
