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

void BridgeRef::addInterfaceToBridge(std::string interface_name)
{
    add_or_remove_interface_to_bridge(0, interface_name.c_str(), BRIDGE_ADD);
}

void BridgeRef::addInterfaceToBridge(int ifindex)
{
    add_or_remove_interface_to_bridge(ifindex, NULL, BRIDGE_ADD);
};

void BridgeRef::removeInterfaceFromBridge(std::string interface_name)
{
    add_or_remove_interface_to_bridge(0, interface_name.c_str(), BRIDGE_REMOVE);
}

void BridgeRef::removeInterfaceFromBridge(int ifindex)
{
    add_or_remove_interface_to_bridge(ifindex, NULL, BRIDGE_REMOVE);
};

void BridgeRef::add_or_remove_interface_to_bridge(int ifindex, const char* interface_name, BridgeOperation op)
{
    rtnl_link* slave_link = NULL;
    int error = 0;

    auto clean = [&]() {
        if (slave_link != NULL)
            rtnl_link_put(slave_link);
    };

    error = rtnl_link_get_kernel(m_socket.get(), ifindex, interface_name, &slave_link);

    if (error < 0)
        throw std::runtime_error("error rtnl_link_get_kernel, reason: " + std::string(nl_geterror(error)));

    // check if interface is allready bridged
    int master_if = rtnl_link_get_master(slave_link);

    switch (op) {
    case BRIDGE_ADD:

        if (master_if == 0) {
            // no bridge is associated, can enslave
            error = rtnl_link_enslave(m_socket.get(), m_link.get(), slave_link);
        } else {
            clean();
            throw std::runtime_error("Cannot enslave link, associated with index: " + std::to_string(master_if));
        };

        break;
    case BRIDGE_REMOVE:

        // it has bridge associated on `master_if` ifindex
        if (master_if > 0) {
            error = rtnl_link_release(m_socket.get(), slave_link);
        } else {
            clean();
            throw std::runtime_error("Link allready released!");
        }

        break;
    default:
        break;
    }

    if (error < 0) {
        clean();
        throw std::runtime_error("error rtnl_link_enslave, reason: " + std::string(nl_geterror(error)));
    }

    clean();
}

void BridgeRef::setMacAddr(std::string address)
{
    nl_addr* addr = NULL;
    rtnl_link* change_link = NULL;
    rtnl_link* current_link = m_link.get();

    int err = -1;

    auto clean = [&]() {
        if (change_link != NULL)
            rtnl_link_put(change_link);
        if (addr != NULL)
            nl_addr_put(addr);
    };

    std::replace(address.begin(), address.end(), '-', ':');

    change_link = rtnl_link_alloc();

    if (change_link == NULL)
        throw std::runtime_error("Cannot allocate link!");

    err = nl_addr_parse(address.c_str(), AF_LLC, &addr);

    if (err < 0) {
        clean();
        throw std::runtime_error(nl_geterror(err));
    }

    rtnl_link_set_addr(change_link, addr);

    err = rtnl_link_change(m_socket.get(), current_link, change_link, 0);

    if (err < 0) {
        clean();
        throw std::runtime_error(nl_geterror(err));
    }

    clean();
}
