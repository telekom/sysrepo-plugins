#include "nexthop.hpp"

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
