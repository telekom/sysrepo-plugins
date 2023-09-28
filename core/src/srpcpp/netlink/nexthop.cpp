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
 * @brief Returns the weight of the next hop.
 */
std::int32_t NextHopRef::getInterfaceIndex() const { return rtnl_route_nh_get_ifindex(m_nh.get()); }

/**
 * @brief Returns the weight of the next hop.
 */
AddressRef NextHopRef::getGateway() const { return AddressRef(rtnl_route_nh_get_gateway(m_nh.get()), m_socket.get()); }

/**
 * @brief Returns the weight of the next hop.
 */
std::uint32_t NextHopRef::getFlags() const { return rtnl_route_nh_get_flags(m_nh.get()); }

/**
 * @brief Returns the weight of the next hop.
 */
std::uint32_t NextHopRef::getRealms() const { return rtnl_route_nh_get_realms(m_nh.get()); }
