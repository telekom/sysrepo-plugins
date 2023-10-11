#pragma once

#include "nl.hpp"
#include <netlink/route/link/bridge.h>

class BridgeRef {
public:
    friend class NlContext;

    std::string getName(void);

    std::string getMacAddr(void);


private:
    using RtnlLink = struct rtnl_link; ///< Route link type alias.
    using RtnlLinkDeleter = NlDeleter<RtnlLink>; ///< Deleter type alias.
    using BridgeLinkPtr = std::unique_ptr<RtnlLink, RtnlLinkDeleter>; ///< Unique pointer type alias.
    using NlSocketPtr = std::unique_ptr<struct nl_sock, NlDeleter<struct nl_sock>>; // Socket type alias.

    /**
     * @brief Private constructor accessible only to netlink context. Stores a reference to a link for later access of link members.
     */
    BridgeRef(struct rtnl_link* link, struct nl_sock* socket);

    /**
     * @brief Private constructor accessible only to netlink context. Stores a reference to a link for later access of link members.
     */
    BridgeRef(struct nl_object* link, struct nl_sock* socket);

    BridgeLinkPtr m_link; ///< Link reference.
    NlSocketPtr m_socket; /// socket reference.
};