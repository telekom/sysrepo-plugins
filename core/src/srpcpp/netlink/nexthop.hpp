#pragma once

#include "nl.hpp"
#include "cache.hpp"

class AddressRef;

class NextHopRef {
public:
    friend class NlContext; ///< Allow NlContext to use the private constructor.
    friend class CacheRef<NextHopRef>; ///< Allow Cache to use the private constructor.

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
