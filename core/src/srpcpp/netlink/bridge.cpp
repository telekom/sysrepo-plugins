#include "bridge.hpp"

/**
 * @brief Private constructor accessible only to netlink context. Stores a reference to a link for later access of link members.
 */
BridgeRef::BridgeRef(struct rtnl_link* link, struct nl_sock* socket)
{
    m_link = BridgeLinkPtr(link, NlEmptyDeleter<RtnlLink>), m_socket = NlSocketPtr(socket, NlEmptyDeleter<struct nl_sock>);
}

/**
 * @brief Private constructor accessible only to netlink context. Stores a reference to a link for later access of link members.
 */
BridgeRef::BridgeRef(struct nl_object* link, struct nl_sock* socket)
{
    m_link = BridgeLinkPtr(reinterpret_cast<RtnlLink*>(link), NlEmptyDeleter<RtnlLink>),
    m_socket = NlSocketPtr(reinterpret_cast<struct nl_sock*>(socket), NlEmptyDeleter<struct nl_sock>);
}

std::string BridgeRef::getName(void)
{
    return std::string(rtnl_link_get_name(this->m_link.get()));
}

std::string BridgeRef::getMacAddr(void)
{
    nl_addr* addr = NULL;
    char addr_buffer[50] = { 0 };

    addr = rtnl_link_get_addr(this->m_link.get());

    if (addr == NULL)
        throw std::runtime_error("NULL Address error");

    nl_addr2str(addr, addr_buffer, sizeof(addr_buffer));
    nl_addr_put(addr);

    return std::string(addr_buffer);
}

std::map<int, std::string> BridgeRef::getSlaveInterfaces()
{
    nl_cache* link_cache = NULL;
    rtnl_link* iter = NULL;
    int error = 0;
    std::map<int, std::string> bridge_slaves;

    int current_ifindex = rtnl_link_get_ifindex(this->m_link.get());
    if (current_ifindex <= 0)
        throw std::runtime_error("Failed to obtain ifindex");

    // allocate new cache since no access to the default one
    error = rtnl_link_alloc_cache(m_socket.get(), AF_UNSPEC, &link_cache);

    if (error < 0) {
        nl_cache_put(link_cache);
        throw std::runtime_error("Failed to allocate link cache");
    }

    iter = (rtnl_link*)nl_cache_get_first(link_cache);
    int iter_ifindex = 0;

    while (iter != nullptr) {

        iter_ifindex = rtnl_link_get_master(iter);

        if (current_ifindex == iter_ifindex) {
            bridge_slaves.insert(std::make_pair(rtnl_link_get_ifindex(iter), std::string(rtnl_link_get_name(iter))));
        };

        iter = (rtnl_link*)nl_cache_get_next((nl_object*)iter);
    }

    nl_cache_put(link_cache);

    return bridge_slaves;
}
