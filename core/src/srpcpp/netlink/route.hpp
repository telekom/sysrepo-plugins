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

#pragma once

#include "nl.hpp"
#include "cache.hpp"

#include <list>

class AddressRef;
class NextHopRef;

class NextHopHelper {
private:
    int m_ifindex;
    std::string m_address;

public:
    NextHopHelper(const std::string& address, int ifindex);

    int getIfindex();

    std::string getAddress();
};

class RouteRef {
public:
    friend class NlContext; ///< Allow NlContext to use the private constructor.
    friend class CacheRef<RouteRef>; ///< Allow Cache to use the private constructor.

    /**
     * @brief Returns the table ID of the route.
     */
    std::uint32_t getTable() const;

    /**
     * @brief Returns the table name of the route.
     */
    std::string getTableName() const;

    /**
     * @brief Sets the table ID of the route.
     */
    void setTable(std::uint32_t table);

    /**
     * @brief Returns the scope of the route.
     */
    std::uint8_t getScope() const;

    /**
     * @brief Sets the scope of the route.
     */
    void setScope(std::uint8_t scope);

    /**
     * @brief Returns the TOS of the route.
     */
    std::uint8_t getTOS() const;

    /**
     * @brief Sets the TOS of the route.
     */
    void setTOS(std::uint8_t tos);

    /**
     * @brief Returns the protocol of the route.
     */
    std::uint8_t getProtocol() const;

    /**
     * @brief Sets the protocol of the route.
     */
    void setProtocol(std::uint8_t protocol);

    /**
     * @brief Returns the priority of the route.
     */
    std::uint32_t getPriority() const;

    /**
     * @brief Sets the priority of the route.
     */
    void setPriority(std::uint32_t priority);

    /**
     * @brief Returns the family of the route.
     */
    std::uint8_t getFamily() const;

    /**
     * @brief Sets the family of the route.
     */
    void setFamily(std::uint8_t family);

    /**
     * @brief Returns the type of the route.
     */
    std::uint8_t getType() const;

    /**
     * @brief Sets the type of the route.
     */
    void setType(std::uint8_t type);

    /**
     * @brief Returns the flags of the route.
     */
    std::uint32_t getFlags() const;

    /**
     * @brief Sets the flags of the route.
     */
    void setFlags(std::uint32_t flags);

    /**
     * @brief Unsets the flags of the route.
     */
    void unsetFlags(std::uint32_t flags);

    /**
     * @brief Returns the destination address of the route.
     */
    AddressRef getDestination() const;

    /**
     * @brief Sets the destination address of the route.
     */
    void setDestination(AddressRef addr);

    /**
     * @brief Returns the source address of the route.
     */
    AddressRef getSource() const;

    /**
     * @brief Sets the source address of the route.
     */
    void setSource(AddressRef addr);

    /**
     * @brief Returns the list of next-hops for the given route.
     */
    std::list<NextHopRef> getNextHops();

    /**
     * @brief Remove selected next-hop.
     * @deprecated Better use is addAndRemoveNextHops() with an empty std::vectot<NextHopHelper> = {} for addition
     */
    void removeNextHop(NextHopHelper& nh_obj);

    /**
     * @brief Add and remove next-hops to existing route.
     * @details Method is structured like this so if it gives an error, it will not add one or more routes, so its all or none
     */
    void addAndRemoveNextHops(const std::vector<NextHopHelper>& nhs_add, const std::vector<NextHopHelper>& nhs_delete);

    /**
     * @brief get the name of the table.
     */
    static std::string tableToString(const uint32_t& table);

    /**
     * @brief get the Address in a string format.
     */
    std::string getDestinationString();

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
