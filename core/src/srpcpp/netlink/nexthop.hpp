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

class AddressRef;
class RouteRef;

class NextHopRef {
public:
    friend class NlContext; ///< Allow NlContext to use the private constructor.
    friend class CacheRef<NextHopRef>; ///< Allow Cache to use the private constructor.
    friend class RouteRef;

    /**
     * @brief Returns the weight of the next hop.
     */
    std::uint8_t getWeight() const;

    /**
     * @brief Sets the weight of the next hop.
     */
    void setWeight(std::uint8_t weight);

    /**
     * @brief Returns the weight of the next hop.
     */
    std::int32_t getInterfaceIndex() const;

    /**
     * @brief Sets the ifindex of the next hop.
     */
    void setInterfaceIndex(std::int32_t ifindex);

    /**
     * @brief Returns the weight of the next hop.
     */
    AddressRef getGateway() const;

    /**
     * @brief Sets the gateway of the next hop.
     */
    void setGateway(AddressRef addr);

    /**
     * @brief Returns the weight of the next hop.
     */
    std::uint32_t getFlags() const;

    /**
     * @brief Sets the flags of the next hop.
     */
    void setFlags(std::uint32_t flags);

    /**
     * @brief Unsets the flags of the next hop.
     */
    void unsetFlags(std::int32_t flags);

    /**
     * @brief Returns the weight of the next hop.
     */
    std::uint32_t getRealms() const;

    /**
     * @brief Sets the realms of the next hop.
     */
    void setRealms(std::uint32_t realms);

private:
    using RtnlNextHop = struct rtnl_nexthop; ///< NextHop type alias.
    using RtnlNextHopDeleter = NlDeleter<RtnlNextHop>; ///< Deleter type alias.
    using RtnlNextHopPtr = std::unique_ptr<RtnlNextHop, RtnlNextHopDeleter>; ///< Unique pointer type alias.
    using NlSocket = struct nl_sock; ///< Socket type alias.
    using NlSocketDeleter = NlDeleter<NlSocket>; ///< Socket deleter alias.
    using NlSocketPtr = std::unique_ptr<NlSocket, NlSocketDeleter>; ///< Socket unique pointer type alias.

    /**
     * @brief Private constructor accessible only to netlink context. Stores a reference to a next-hop for later access of members.
     */
    NextHopRef(struct rtnl_nexthop* nh, struct nl_sock* socket);

    /**
     * @brief Private constructor accessible only to netlink context. Stores a reference to a next-hop for later access of members.
     */
    NextHopRef(struct nl_object* nh, struct nl_sock* socket);

    RtnlNextHopPtr m_nh; ///< NextHop reference.
    NlSocketPtr m_socket; ///< Socket reference.
};
