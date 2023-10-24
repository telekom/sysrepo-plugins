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

/**
 * @brief Private constructor accessible only to netlink context. Stores a reference to a link for later access of link members.
 */
BridgeSlaveRef::BridgeSlaveRef(struct rtnl_link* link, struct nl_sock* socket)
{
    m_link = BridgeLinkPtr(link, NlEmptyDeleter<RtnlLink>), m_socket = NlSocketPtr(socket, NlEmptyDeleter<struct nl_sock>);
}

/**
 * @brief Private constructor accessible only to netlink context. Stores a reference to a link for later access of link members.
 */
BridgeSlaveRef::BridgeSlaveRef(struct nl_object* link, struct nl_sock* socket)
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

std::map<int, std::string> BridgeRef::getSlaveInterfacesIfindexName()
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
};

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

    std::string new_addr = address;

    int err = -1;

    auto clean = [&]() {
        if (change_link != NULL)
            rtnl_link_put(change_link);
        if (addr != NULL)
            nl_addr_put(addr);
    };

    std::replace(new_addr.begin(), new_addr.end(), '-', ':');

    change_link = rtnl_link_alloc();

    if (change_link == NULL)
        throw std::runtime_error("Cannot allocate link!");

    err = nl_addr_parse(new_addr.c_str(), 0, &addr);

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

void BridgeRef::setAgeingTime(uint32_t ageing_time)
{
    struct nl_msg* msg = NULL;
    struct nlattr* link_info = NULL;
    struct nlattr* info_data = NULL;
    nl_sock* socket = m_socket.get();
    int error = 0;

    msg = nlmsg_alloc_simple(RTM_NEWLINK, NLM_F_REQUEST | NLM_F_ACK);
    if (msg == NULL) {
        throw std::runtime_error("nlmsg_alloc_simple() failed");
    }

    // fill RTM_NEWLINK message header
    struct ifinfomsg ifinfo = {
        .ifi_family = AF_BRIDGE,
        .ifi_type = ARPHRD_NETROM,
        .ifi_index = rtnl_link_get_ifindex(m_link.get()),
        .ifi_flags = 0,
        .ifi_change = 0
    };

    error = nlmsg_append(msg, &ifinfo, sizeof(ifinfo), nlmsg_padlen(sizeof(ifinfo)));
    if (error) {
        throw std::runtime_error(nl_geterror(error));
    }
    // open nested attributes IFLA_LINKINFO->IFLA_INFO_DATA
    link_info = nla_nest_start(msg, IFLA_LINKINFO);
    if (link_info == NULL) {
        throw std::runtime_error("nla_nest_start() failed");
    }

    error = nla_put_string(msg, IFLA_INFO_KIND, "bridge");
    if (error) {
        throw std::runtime_error("nla_put_string() failed: " + std::string(nl_geterror(error)));
    }

    info_data = nla_nest_start(msg, IFLA_INFO_DATA);

    if (info_data == NULL) {
        throw std::runtime_error("nla_nest_start() failed");
    }
    // add bridge vlan attributes
    error = nla_put_u32(msg, IFLA_BR_AGEING_TIME, ageing_time);
    if (error) {
        throw std::runtime_error("nla_put_u32() failed: " + std::string(nl_geterror(error)));
    }

    // close nested attributes
    error = nla_nest_end(msg, info_data);
    if (error) {
        throw std::runtime_error("nla_nest_end() failed: " + std::string(nl_geterror(error)));
    }

    error = nla_nest_end(msg, link_info);
    if (error) {
        throw std::runtime_error("nla_nest_end() failed: " + std::string(nl_geterror(error)));
    }
    error = nl_send_sync(socket, msg);
    if (error) {
        throw std::runtime_error("nl_send() failed: " + std::string(nl_geterror(error)));
    }
}

void BridgeSlaveRef::add_or_remove_bridge_vlan_ids(std::vector<bridge_vlan_info> vlan_ids, uint8_t oper)
{

    nl_msg* msg = NULL;
    nl_sock* socket = m_socket.get();
    struct nlattr* afspec = NULL;
    int err = -1;

    if (socket == NULL) {
        throw std::runtime_error("Failed to allocate socket for nl_msg");
    }

    nl_socket_disable_seq_check(socket);
    // operation can be RTM_SETLINK for create, and RTM_DELLINK for deletion
    msg = nlmsg_alloc_simple(oper, NLM_F_REQUEST | NLM_F_ACK);

    if (msg == NULL) {
        throw std::runtime_error("nlmsg_alloc_simple() failed!");
    }

    struct ifinfomsg ifinfo = {
        .ifi_family = AF_BRIDGE,
        .ifi_type = ARPHRD_NETROM,
        .ifi_index = rtnl_link_get_ifindex(m_link.get()),
        .ifi_flags = 0,
        .ifi_change = 0
    };

    err = nlmsg_append(msg, &ifinfo, sizeof(ifinfo), nlmsg_padlen(sizeof(ifinfo)));

    if (err < 0) {
        throw std::runtime_error(nl_geterror(err));
    }

    uint16_t cmd_flags = 0;

    if (rtnl_link_is_bridge(m_link.get())) {
        cmd_flags = BRIDGE_FLAGS_SELF;
    } else
        cmd_flags = BRIDGE_FLAGS_MASTER; // send command to bridge master

    err = nla_put_u16(msg, IFLA_BRIDGE_FLAGS, cmd_flags);

    if (err < 0) {
        throw std::runtime_error(nl_geterror(err));
    }

    afspec = nla_nest_start(msg, IFLA_AF_SPEC);

    if (afspec == NULL) {
        throw std::runtime_error("nla_nest_start() failed");
    }

    for (auto id : vlan_ids) {
        if ((nla_put(msg, IFLA_BRIDGE_VLAN_INFO, sizeof(id), &id)) < 0) {
            // break  the loop for bad msg so it can go to nest_end
            break;
        }
    }

    err = nla_nest_end(msg, afspec);
    if (err < 0) {
        throw std::runtime_error(nl_geterror(err));
    }

    err = nl_send_sync(socket, msg);
    if (err < 0) {
        throw std::runtime_error("send failed! " + std::string(nl_geterror(err)));
    }
}

std::vector<uint16_t> BridgeRef::parseStringToVlanIDS(const std::string& vlan_str)
{
    // the string value can be formulated in 3 ways:
    // 1. just a single num (3)
    // 2. range of nums (3-20)
    // 3. selection of nums by delimiter (3,5,6,9,10)
    // probably no need for regex since it will be validated on libyang side

    std::vector<uint16_t> vids;

    std::istringstream chunkStream(vlan_str);
    std::string chunk;

    while (std::getline(chunkStream, chunk, ',')) {

        int pos = chunk.find('-');
        if (pos != std::string::npos) {

            std::string min_range = std::string(chunk.begin(), chunk.begin() + pos);
            std::string max_range = std::string(chunk.begin() + (++pos), chunk.end());

            for (int i = std::stoi(min_range); i <= std::stoi(max_range); i++) {
                vids.push_back(i);
            }

            continue;
        }

        vids.push_back(std::stoi(chunk));
    }

    return vids;
}

void BridgeSlaveRef::addVlanIDS(const std::vector<uint16_t>& vlan_ids, uint16_t flags)
{

    std::vector<bridge_vlan_info> vec;
    bridge_vlan_info inf = { 0 };
    for (auto i : vlan_ids) {
        inf.vid = i;
        inf.flags = flags;
        vec.push_back(inf);
    }

    add_or_remove_bridge_vlan_ids(vec, RTM_SETLINK);
}

void BridgeSlaveRef::removeVlanIDS(const std::vector<uint16_t>& vlan_ids)
{

    std::vector<bridge_vlan_info> vec;
    bridge_vlan_info inf = { 0 };
    for (auto i : vlan_ids) {
        inf.vid = i;
        inf.flags = 0;
        vec.push_back(inf);
    }

    add_or_remove_bridge_vlan_ids(vec, RTM_DELLINK);
}

std::string BridgeSlaveRef::getName()
{
    return std::string(rtnl_link_get_name(this->m_link.get()));
}

std::vector<BridgeSlaveRef> BridgeRef::getSlaveInterfaces()
{
    std::vector<BridgeSlaveRef> slaves;

    rtnl_link* iter = NULL;
    nl_cache* cache = NULL;
    int err = -1;

    auto clean = [&]() {
        if (cache != NULL)
            nl_cache_free(cache);
    };

    err = rtnl_link_alloc_cache(m_socket.get(), AF_BRIDGE, &cache);

    if (err < 0) {
        throw std::runtime_error(nl_geterror(err));
    }

    iter = (rtnl_link*)nl_cache_get_first(cache);

    int master_ifindex = rtnl_link_get_ifindex(m_link.get());

    while (iter != nullptr) {

        if (master_ifindex == rtnl_link_get_master(iter)) {
            slaves.push_back(BridgeSlaveRef(iter, m_socket.get()));
        }

        iter = (rtnl_link*)nl_cache_get_next((nl_object*)iter);
    }

    return slaves;
}

int BridgeSlaveRef::getIfindex()
{
    return rtnl_link_get_ifindex(this->m_link.get());
}

std::optional<BridgeSlaveRef> BridgeRef::getSlaveByIfindex(int ifindex)
{
    for (auto&& i : this->getSlaveInterfaces()) {
        if (i.getIfindex() == ifindex) {
            return std::move(i);
        }
    }

    return std::nullopt;
}

void BridgeSlaveRef::removeAllVlanIDS()
{
    //[TODO]: Removing all vlan ids with one function.
}