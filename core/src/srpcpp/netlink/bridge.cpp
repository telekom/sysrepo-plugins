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
    nl_addr* mac_addr = NULL;
    char addr_buffer[100] = { 0 };

    mac_addr = rtnl_link_get_addr(this->m_link.get());

    if (mac_addr == NULL)
        throw std::runtime_error("NULL Address error");

    nl_addr2str(mac_addr, addr_buffer, sizeof(addr_buffer));
    nl_addr_put(mac_addr);

    return std::string(addr_buffer);
}
