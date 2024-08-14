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

#include "nexthop.hpp"
#include "address.hpp"

#include <netlink/route/nexthop.h>

/**
 * @brief Private constructor accessible only to netlink context. Stores a reference to a next-hop for later access of members.
 */
NextHopRef::NextHopRef(struct rtnl_nexthop* nh, struct nl_sock* socket)
    : m_nh(RtnlNextHopPtr(nh, NlEmptyDeleter<RtnlNextHop>))
    , m_socket(NlSocketPtr(socket, NlEmptyDeleter<NlSocket>))
{
}

/**
 * @brief Private constructor accessible only to netlink context. Stores a reference to a next-hop for later access of members.
 */
NextHopRef::NextHopRef(struct nl_object* nh, struct nl_sock* socket)
    : m_nh(RtnlNextHopPtr(reinterpret_cast<RtnlNextHop*>(nh), NlEmptyDeleter<RtnlNextHop>))
    , m_socket(NlSocketPtr(socket, NlEmptyDeleter<NlSocket>))
{
}

/**
 * @brief Returns the weight of the next hop.
 */
std::uint8_t NextHopRef::getWeight() const { return rtnl_route_nh_get_weight(m_nh.get()); }

/**
 * @brief Sets the weight of the next hop.
 */
void NextHopRef::setWeight(std::uint8_t weight) { rtnl_route_nh_set_weight(m_nh.get(), weight); }

/**
 * @brief Returns the weight of the next hop.
 */
std::int32_t NextHopRef::getInterfaceIndex() const { return rtnl_route_nh_get_ifindex(m_nh.get()); }

/**
 * @brief Sets the ifindex of the next hop.
 */
void NextHopRef::setInterfaceIndex(std::int32_t ifindex) { rtnl_route_nh_set_ifindex(m_nh.get(), ifindex); }

/**
 * @brief Returns the weight of the next hop.
 */
AddressRef NextHopRef::getGateway() const { return AddressRef(rtnl_route_nh_get_gateway(m_nh.get()), m_socket.get()); }

/**
 * @brief Sets the gateway of the next hop.
 */
void NextHopRef::setGateway(AddressRef addr)
{
    rtnl_route_nh_set_gateway(m_nh.get(), addr.m_addr.get());
}

/**
 * @brief Returns the weight of the next hop.
 */
std::uint32_t NextHopRef::getFlags() const { return rtnl_route_nh_get_flags(m_nh.get()); }

/**
 * @brief Sets the flags of the next hop.
 */
void NextHopRef::setFlags(std::uint32_t flags) { rtnl_route_nh_set_flags(m_nh.get(), flags); }

/**
 * @brief Unsets the flags of the next hop.
 */
void NextHopRef::unsetFlags(std::int32_t flags) { rtnl_route_nh_unset_flags(m_nh.get(), flags); }

/**
 * @brief Returns the weight of the next hop.
 */
std::uint32_t NextHopRef::getRealms() const { return rtnl_route_nh_get_realms(m_nh.get()); }

/**
 * @brief Sets the realms of the next hop.
 */
void NextHopRef::setRealms(std::uint32_t realms) { rtnl_route_nh_set_realms(m_nh.get(), realms); }
