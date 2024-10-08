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
    rtnl_link* lnk = this->m_link.get();
    char addr_buffer[50] = { 0 };

    addr = rtnl_link_get_addr(lnk);

    if (addr == NULL)
        throw std::runtime_error("NULL Address error");

    nl_addr2str(addr, addr_buffer, sizeof(addr_buffer));

    return std::string(addr_buffer);
}

std::map<int, std::string> BridgeRef::getSlaveInterfacesIfindexName()
{
    nl_cache* link_cache = NULL;
    rtnl_link* iter = NULL;
    rtnl_link* link = this->m_link.get();
    int error = 0;
    std::map<int, std::string> bridge_slaves;

    int current_ifindex = rtnl_link_get_ifindex(link);
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
    rtnl_link* link = this->m_link.get();
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
            error = rtnl_link_enslave(m_socket.get(), link, slave_link);
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
        nlmsg_free(msg);
        throw std::runtime_error(nl_geterror(error));
    }
    // open nested attributes IFLA_LINKINFO->IFLA_INFO_DATA
    link_info = nla_nest_start(msg, IFLA_LINKINFO);
    if (link_info == NULL) {
        nlmsg_free(msg);
        throw std::runtime_error("nla_nest_start() failed");
    }

    error = nla_put_string(msg, IFLA_INFO_KIND, "bridge");
    if (error) {
        nlmsg_free(msg);
        throw std::runtime_error("nla_put_string() failed: " + std::string(nl_geterror(error)));
    }

    info_data = nla_nest_start(msg, IFLA_INFO_DATA);

    if (info_data == NULL) {
        nlmsg_free(msg);
        throw std::runtime_error("nla_nest_start() failed");
    }
    // add bridge vlan attributes
    error = nla_put_u32(msg, IFLA_BR_AGEING_TIME, ageing_time);

    if (error) {
        nlmsg_free(msg);
        throw std::runtime_error("nla_put_u32() failed: " + std::string(nl_geterror(error)));
    }

    // close nested attributes
    error = nla_nest_end(msg, info_data);

    if (error) {
        nlmsg_free(msg);
        throw std::runtime_error("nla_nest_end() failed: " + std::string(nl_geterror(error)));
    }

    error = nla_nest_end(msg, link_info);
    if (error) {
        nlmsg_free(msg);
        throw std::runtime_error("nla_nest_end() failed: " + std::string(nl_geterror(error)));
    }
    error = nl_send_sync(socket, msg);
    if (error) {
        nlmsg_free(msg);
        throw std::runtime_error("nl_send() failed: " + std::string(nl_geterror(error)));
    }
}

uint32_t BridgeRef::getAgeingTime()
{
    struct nl_msg* msg = NULL;
    unsigned char* msg_buf = NULL;
    int error = 0;
    int len = 0;
    nl_sock* socket = m_socket.get();
    struct sockaddr_nl nla = { 0 };
    nlmsghdr* hdr = NULL;

    int if_index = rtnl_link_get_ifindex(m_link.get());
    const char* name = rtnl_link_get_name(m_link.get());

    auto clean = [&]() {
        if (msg)
            nlmsg_free(msg);
    };

    // send RTM_GETLINK message for the bridge
    error = rtnl_link_build_get_request(if_index, name, &msg);

    if (error) {
        clean();
        throw std::runtime_error("rtnl_link_build_get_request() failed!");
    }
    len = nl_send_auto(socket, msg);
    if (len < 0) {
        clean();
        throw std::runtime_error("getAgeingTime(), nl_send_auto() failed!");
    }

    // wait for kernel response and ack
    len = nl_recv(socket, &nla, &msg_buf, NULL);
    if (len <= 0) {
        clean();
        throw std::runtime_error("getAgeingTime(), nl_recv() failed!");
    }
    error = nl_wait_for_ack(socket);
    if (error) {
        clean();
        throw std::runtime_error("getAgeingTime(), nl_wait_for_ack() failed!");
    }

    // validate message type
    hdr = (struct nlmsghdr*)msg_buf;
    if (hdr->nlmsg_type != RTM_NEWLINK) {
        clean();
        throw std::runtime_error("getAgeingTime(), header validation failed!");
    }
    // RTM_NEWLINK messages contain an ifinfomsg structure
    // followed by a series of rtattr structures, see `man 7 rtnetlink`.
    int proto_header_len = sizeof(struct ifinfomsg);

    // Find IFLA_BR_VLAN_PROTOCOL and IFLA_BR_VLAN_FILTERING attributes,
    // which are nested in IFLA_LINKINFO->IFLA_INFO_DATA.
    struct nlattr* ifla_linkinfo = nlmsg_find_attr(hdr, proto_header_len, IFLA_LINKINFO);
    if (ifla_linkinfo == NULL) {
        clean();
        throw std::runtime_error("getAgeingTime(),IFLA_LINKINFO not found!");
    }
    struct nlattr* ifla_info_data = nla_find((nlattr*)nla_data(ifla_linkinfo), nla_len(ifla_linkinfo), IFLA_INFO_DATA);
    if (ifla_info_data == NULL) {
        clean();
        throw std::runtime_error("getAgeingTime(), IFLA_INFO_DATA not found!");
    }
    struct nlattr* br_vlan_filtering = nla_find((nlattr*)nla_data(ifla_info_data), nla_len(ifla_info_data), IFLA_BR_AGEING_TIME);
    if (br_vlan_filtering == NULL) {
        clean();
        throw std::runtime_error("getAgeingTime(), IFLA_BR_AGEING_TIME not found!");
    }

    int ageing_time = nla_get_u32(br_vlan_filtering);

    clean();

    return ageing_time;
}

void BridgeRef::setSTP(bool stp)
{
    nl_msg* msg = NULL;
    nlattr* link_info = NULL;
    nlattr* info_data = NULL;
    rtnl_link* link = m_link.get();
    int error = 0;
    int len = 0;

    auto clean = [&]() {
        if (msg)
            nlmsg_free(msg);
    };

    error = rtnl_link_build_add_request(link, 0, &msg);

    if (error) {
        clean();
        throw std::runtime_error("setSTP(), rtnl_link_build_add_request failed!");
    }

    link_info = nla_nest_start(msg, IFLA_LINKINFO);

    if (link_info == NULL) {
        clean();
        throw std::runtime_error("setSTP(), IFLA_LINKINFO failed!");
    }
    error = nla_put_string(msg, IFLA_INFO_KIND, "bridge");

    if (error) {
        clean();
        throw std::runtime_error("setSTP(), nla_put_string(msg, IFLA_INFO_KIND) failed!");
    }

    info_data = nla_nest_start(msg, IFLA_INFO_DATA);

    if (info_data == NULL) {
        clean();
        throw std::runtime_error("setSTP(), IFLA_INFO_DATA failed!");
    }

    error = nla_put_u32(msg, IFLA_BR_STP_STATE, stp);

    if (error) {
        clean();
        throw std::runtime_error("setSTP(), IFLA_BR_STP_STATE set failed!");
    }

    error = nla_nest_end(msg, info_data);

    if (error) {
        clean();
        throw std::runtime_error("setSTP(), IFLA_INFO_DATA nest_end failed!");
    }

    error = nla_nest_end(msg, link_info);

    if (error) {
        clean();
        throw std::runtime_error("setSTP(), LINK_INFO nest_end failed!");
    }

    len = nl_send(m_socket.get(), msg);

    if (len <= 0) {
        clean();
        throw std::runtime_error("setSTP(), nl_send_auto failed!");
    }

    clean();
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
        nlmsg_free(msg);
        throw std::runtime_error(nl_geterror(err));
    }

    uint16_t cmd_flags = 0;

    if (rtnl_link_is_bridge(m_link.get())) {
        cmd_flags = BRIDGE_FLAGS_SELF;
    } else
        cmd_flags = BRIDGE_FLAGS_MASTER; // send command to bridge master

    err = nla_put_u16(msg, IFLA_BRIDGE_FLAGS, cmd_flags);

    if (err < 0) {
        nlmsg_free(msg);
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
        nlmsg_free(msg);
        throw std::runtime_error(nl_geterror(err));
    }

    err = nl_send_sync(socket, msg);
    if (err < 0) {
        nlmsg_free(msg);
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

        if (master_ifindex == rtnl_link_get_master(iter) && master_ifindex != rtnl_link_get_ifindex(iter)) {

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
    std::vector<BridgeVlanID> vlans = this->getVlanList();

    std::vector<uint16_t> vlan_list;

    // note: first has to be jumped since it will delete the bridge port, or should it?
    for (int i = 1; i < vlans.size(); i++) {
        vlan_list.push_back(vlans[i].getVid());
    }

    this->removeVlanIDS(vlan_list);
}

std::vector<BridgeFDBEntry> BridgeSlaveRef::getFilteringVids()
{
    nl_sock* socket = NULL;
    nl_msg* msg = NULL;
    int slave_ifindex = 0;
    nlmsghdr* hdr = NULL;
    nl_addr* local_addr = NULL;
    sockaddr_nl nla = { 0 };
    ndmsg neigh_msg = { 0 };
    unsigned char* msg_buf = NULL;
    int error = 0;
    int len = 0;
    std::array<uint8_t, 6> slave_mac_addr;

    // get the binary mac addr of the slave
    local_addr = rtnl_link_get_addr(m_link.get());
    const uint8_t* binary_addr = (uint8_t*)nl_addr_get_binary_addr(local_addr);
    memcpy(slave_mac_addr.data(), binary_addr, 6);
    nl_addr_put(local_addr);

    std::vector<BridgeFDBEntry> entries;

    auto clean = [&]() {
        if (msg)
            nlmsg_free(msg);
        if (socket)
            nl_socket_free(socket);
    };

    socket = nl_socket_alloc();

    if (!socket) {
        throw std::runtime_error("getFilteringVids() failed to alloc socket!");
    }

    error = nl_connect(socket, NETLINK_ROUTE);

    if (error) {
        clean();
        throw std::runtime_error("getFilteringVids() failed to connect to socket!");
    }

    slave_ifindex = rtnl_link_get_ifindex(m_link.get());

    msg = nlmsg_alloc_simple(RTM_GETNEIGH, NLM_F_ACK | NLM_F_DUMP);

    neigh_msg = {
        .ndm_family = AF_BRIDGE,
        .ndm_ifindex = slave_ifindex,
        .ndm_type = RTM_NEWNEIGH
    };

    nlmsg_append(msg, &neigh_msg, sizeof(neigh_msg), nlmsg_padlen(sizeof(neigh_msg)));

    if (!msg) {
        clean();
        throw std::runtime_error("getFilteringVids(), nlmsg_alloc_simple() failed!");
    }

    len = nl_send_auto(socket, msg);
    if (len < 0) {
        clean();
        throw std::runtime_error("getFilteringVids(), nl_send_auto() failed!");
    }

    len = nl_recv(socket, &nla, &msg_buf, NULL);
    if (len <= 0) {
        clean();
        throw std::runtime_error("getFilteringVids(), nl_recv() failed!");
    }

    // validate message type
    hdr = (struct nlmsghdr*)msg_buf;
    if (hdr->nlmsg_type != RTM_NEWNEIGH) {
        clean();
        throw std::runtime_error("getFilteringVids(), header validation failed!");
    }

    int proto_header_len = sizeof(struct ndmsg);

    for (hdr = (nlmsghdr*)msg_buf; NLMSG_OK(hdr, len); hdr = NLMSG_NEXT(hdr, len)) {

        if (hdr->nlmsg_type == NLMSG_DONE)
            break;

        if (hdr->nlmsg_type == NLMSG_ERROR) {
            clean();
            throw std::runtime_error("getFilteringVids(), NLMSG_ERROR!");
        }

        // first get the ifindex from header
        nlattr* hdr_ifindex = (nlattr*)nlmsg_data(hdr);
        if (hdr_ifindex == NULL) {
            clean();
            throw std::runtime_error("getFilteringVids(), HDR_IFINDEX error!");
        }

        int ifindex = nla_get_u16(hdr_ifindex);
        if (ifindex != slave_ifindex) {
            // ifindexes dont match, continue to next
            continue;
        }

        struct nlattr* vlan = nlmsg_find_attr(hdr, proto_header_len, NDA_VLAN);
        if (vlan == NULL) {
            // there is no vlan found, so continue
            continue;
        }

        struct nlattr* ifla_info_data = nlmsg_find_attr(hdr, proto_header_len, NDA_LLADDR);
        if (ifla_info_data == NULL) {
            clean();
            throw std::runtime_error("getFilteringVids(), NDA_ADDR error!");
        }

        const char* addr = nla_get_string(ifla_info_data);
        int vlan_num = nla_get_u16(vlan);
        std::array<uint8_t, 6> mac_addr_arr;

        // 48 bytes, 6 bytes mac addr
        memcpy(mac_addr_arr.data(), addr, 6);

        entries.push_back(BridgeFDBEntry(mac_addr_arr, slave_mac_addr, vlan_num, ifindex));
    }

    clean();

    return entries;
}

void BridgeSlaveRef::addAddressToVids(const std::vector<uint16_t>& vlan_ids, const std::string& address)
{
    add_or_remove_address_to_vids(vlan_ids, address, ADD_ADDRESS);
}

void BridgeSlaveRef::removeAddressFromVids(const std::vector<uint16_t>& vlan_ids, const std::string& address)
{
    add_or_remove_address_to_vids(vlan_ids, address, REMOVE_ADDRESS);
}

void BridgeSlaveRef::add_or_remove_address_to_vids(const std::vector<uint16_t>& vlan_ids, const std::string& address, AddressOperation operation)
{

    rtnl_neigh* neigh = NULL;
    nl_addr* addr = NULL;
    nl_sock* socket = m_socket.get();
    std::string new_addr = address;

    auto clean = [&]() {
        if (neigh != NULL)
            rtnl_neigh_put(neigh);
        if (addr != NULL)
            nl_addr_put(addr);
    };

    // replace characters to match addr
    std::replace(new_addr.begin(), new_addr.end(), '-', ':');

    int err = -1;

    neigh = rtnl_neigh_alloc();

    if (neigh == NULL)
        throw std::runtime_error("Failed to allocate neighbor");

    rtnl_neigh_set_family(neigh, AF_BRIDGE);
    rtnl_neigh_set_ifindex(neigh, rtnl_link_get_ifindex(m_link.get()));

    err = nl_addr_parse(new_addr.c_str(), AF_LLC, &addr);

    if (err < 0) {
        clean();
        throw std::runtime_error(nl_geterror(err));
    }

    rtnl_neigh_set_lladdr(neigh, addr);

    // TODO: research possible state flags
    rtnl_neigh_set_state(neigh, NUD_NOARP);
    rtnl_neigh_set_flags(neigh, NTF_MASTER); // add neigh to bridge master FDB

    for (auto id : vlan_ids) {

        rtnl_neigh_set_vlan(neigh, id);

        switch (operation) {
        case ADD_ADDRESS:
            err = rtnl_neigh_add(socket, neigh, NLM_F_CREATE);
            if (err < 0) {
                clean();
                throw std::runtime_error("Failed to add neigh, " + std::string(nl_geterror(err)));
            };

            break;
        case REMOVE_ADDRESS:
            err = rtnl_neigh_delete(socket, neigh, 0);
            if (err < 0) {
                clean();
                throw std::runtime_error("Failed to delete neigh, " + std::string(nl_geterror(err)));
            };

            break;

        default:
            break;
        }
    }
    clean();
}

bool BridgeSlaveRef::isSubset(const std::vector<uint16_t>& main_list, const std::vector<uint16_t>& subset)
{
    // subset array cannot be larger than main array
    if (main_list.size() < subset.size())
        return false;

    bool found = false;
    for (int i = 0; i < subset.size(); i++) {

        for (int j = 0; j < main_list.size(); j++) {
            if (subset[i] == main_list[j]) {
                found = true;
                break;
            }

            found = false;
        }
        if (!found)
            return false;
    }

    return true;
}

std::vector<BridgeVlanID> BridgeSlaveRef::getVlanList()
{
    struct nl_msg* msg = NULL;
    nl_sock* socket = NULL;
    rtnl_link* link = this->m_link.get();
    int ifindex = rtnl_link_get_ifindex(link);
    struct nlattr* current_vlan_entry = NULL;
    struct nlattr* entry_info = NULL;
    unsigned char* msg_buf = NULL;
    struct bridge_vlan_info port_vlan_list = { 0 };
    struct sockaddr_nl nla = { 0 };
    struct nlmsghdr* hdr = NULL;
    int proto_header_len = 0;
    int remaining = 0;
    int error = 0;
    int len = 0;
    std::vector<BridgeVlanID> vids;

    auto clean = [&]() {
        if (msg != NULL)
            nlmsg_free(msg);
        if (socket != NULL)
            nl_socket_free(socket);
    };

    socket = nl_socket_alloc();

    nl_connect(socket, NETLINK_ROUTE);

    msg = nlmsg_alloc_simple(RTM_GETVLAN, NLM_F_REQUEST | NLM_F_DUMP);
    if (msg == NULL) {
        clean();
        throw std::runtime_error("Failed to allocate netlink message!");
    }

    struct br_vlan_msg vlan_msg = {
        .family = AF_BRIDGE,
        .ifindex = (unsigned)ifindex,
    };

    error = nlmsg_append(msg, &vlan_msg, sizeof(vlan_msg), nlmsg_padlen(sizeof(vlan_msg)));
    if (error) {
        clean();
        throw std::runtime_error("nlmsg_append() error");
    }

    len = nl_send_auto(socket, msg);
    if (len < 0) {
        clean();
        throw std::runtime_error("nl_send_auto() failed");
    }

    len = nl_recv(socket, &nla, &msg_buf, NULL);
    if (len <= 0) {
        clean();
        throw std::runtime_error("nl_recv() failed");
    }

    // validate message type
    hdr = (struct nlmsghdr*)msg_buf;
    if (hdr->nlmsg_type != RTM_NEWVLAN) {
        throw std::runtime_error("nlmsghdr Header validation error!");
    };

    proto_header_len = sizeof(br_vlan_msg);
    current_vlan_entry = nlmsg_find_attr(hdr, proto_header_len, BRIDGE_VLANDB_ENTRY);

    if (current_vlan_entry == NULL) {
        clean();
        // return empty vector, so it does not crash if you remove port ref;
        return {};
    }

    remaining = nlmsg_attrlen(hdr, sizeof(struct br_vlan_msg));

    while (nla_ok(current_vlan_entry, remaining)) {

        entry_info = (nlattr*)nla_data(current_vlan_entry);
        nla_memcpy(&port_vlan_list, entry_info, sizeof(bridge_vlan_info));

        // vids.push_back(port_vlan_list.vid);

        if (nla_is_nested(current_vlan_entry)) {

            nlattr* attributes[BRIDGE_VLANDB_ENTRY_MAX] = { 0 };
            nla_parse_nested(attributes, BRIDGE_VLANDB_ENTRY_MAX, current_vlan_entry, NULL);

            uint16_t flg = nla_get_u16(attributes[BRIDGE_VLANDB_ENTRY_INFO]);

            vids.push_back(BridgeVlanID(port_vlan_list.vid, flg));

            if (attributes[BRIDGE_VLANDB_ENTRY_RANGE] != NULL) {
                // it is range
                uint16_t end = nla_get_u16(attributes[BRIDGE_VLANDB_ENTRY_RANGE]);
                // now parse all of them
                for (int i = port_vlan_list.vid + 1; i <= end; i++) {
                    vids.push_back(BridgeVlanID(i, flg));
                }
            }
        }

        current_vlan_entry = nla_next(current_vlan_entry, &remaining);
    }

    clean();

    return vids;
}

std::unordered_map<BridgeRef::BridgeVidParse, std::string> BridgeRef::parseVlanIDSToString(std::vector<BridgeVlanID> vlans)
{

    if (vlans.empty()) {
        // return empty vector
        return {};
    };

    // lambda for parsing
    auto to_string = [&](std::vector<BridgeVlanID> vlanids) {
        std::string result = std::to_string(vlanids[0].getVid()); // Start with the first number
        int count = 0;

        for (int i = 1; i < vlanids.size(); ++i) {
            if (vlanids[i].getVid() == vlanids[i - 1].getVid() + 1) {
                count++;
            } else {
                if (count >= 2) {
                    result += "-" + std::to_string(vlanids[i - 1].getVid());
                } else if (count == 1) {
                    result += "," + std::to_string(vlanids[i - 1].getVid());
                }
                result += "," + std::to_string(vlanids[i].getVid());
                count = 0;
            }
        }

        if (count >= 2) {
            result += "-" + std::to_string(vlanids.back().getVid());
        } else if (count == 1) {
            result += "," + std::to_string(vlanids.back().getVid());
        }

        return result;
    };

    // split them by tagged/untagged to get consistant data
    std::vector<BridgeVlanID> tagged;
    std::vector<BridgeVlanID> untagged;
    std::unordered_map<BridgeVidParse, std::string> return_strings;

    for (auto&& vlan : vlans) {
        if (vlan.getUntaggedFlag()) {
            untagged.push_back(vlan);
        } else {
            tagged.push_back(vlan);
        }
    }

    // sort them
    // they have < overloaded
    std::sort(tagged.begin(), tagged.end());
    std::sort(untagged.begin(), untagged.end());

    if (!tagged.empty())
        return_strings[TAGGED] = to_string(tagged);
    if (!untagged.empty())
        return_strings[UNTAGGED] = to_string(untagged);

    return return_strings;
}
std::string BridgeRef::rawNumParser(std::vector<uint16_t> nums)
{

    std::sort(nums.begin(), nums.end());
    std::string result = std::to_string(nums[0]); // Start with the first number
    int count = 0;

    for (int i = 1; i < nums.size(); ++i) {
        if (nums[i] == nums[i - 1] + 1) {
            count++;
        } else {
            if (count >= 2) {
                result += "-" + std::to_string(nums[i - 1]);
            } else if (count == 1) {
                result += "," + std::to_string(nums[i - 1]);
            }
            result += "," + std::to_string(nums[i]);
            count = 0;
        }
    }

    if (count >= 2) {
        result += "-" + std::to_string(nums.back());
    } else if (count == 1) {
        result += "," + std::to_string(nums.back());
    }

    return result;
};

// BridgeVid helper class

BridgeVlanID::BridgeVlanID(uint16_t vid, uint16_t flags)
    : vlan_id(vid)
    , flags(flags) {};

bool BridgeVlanID::getUntaggedFlag()
{
    return (bool)(flags &= BRIDGE_VLAN_INFO_UNTAGGED);
}

bool BridgeVlanID::getPvidFlag()
{
    return (bool)(flags &= BRIDGE_VLAN_INFO_PVID);
}

uint16_t BridgeVlanID::getVid()
{
    return this->vlan_id;
}

// overload  < for custom sorting classes
bool BridgeVlanID::operator<(const BridgeVlanID& other) const
{
    return this->vlan_id < other.vlan_id;
};

BridgeFDBEntry::BridgeFDBEntry(std::array<uint8_t, 6> mac, std::array<uint8_t, 6> slave_mac, uint16_t vid, int ifindex)
{
    this->mac = mac;
    this->vid = vid;
    this->ifindex = ifindex;
    this->slave_mac = slave_mac;

    // parse string mac on costruction
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (int i = 0; i < 6; ++i) {
        oss << std::setw(2) << static_cast<int>(mac[i]);
        if (i < 5) {
            oss << ":";
        }
    }

    this->mac_string = oss.str();
}

bool BridgeFDBEntry::isEqualTo(const BridgeFDBEntry& other) const
{
    // compare by the raw data, not the strings
    for (int i = 0; i < mac.size(); i++) {
        if (mac[i] != other.mac[i]) {
            return false;
        }
    }

    return other.ifindex == this->ifindex && other.vid == this->vid;
}

std::array<uint8_t, 6> BridgeFDBEntry::getRawMAC()
{
    return mac;
}

std::string BridgeFDBEntry::getStringMAC()
{
    return mac_string;
}

uint16_t BridgeFDBEntry::getVID()
{
    return vid;
}

int BridgeFDBEntry::getIfindex()
{
    return this->ifindex;
}

bool BridgeFDBEntry::isFiltered()
{
    // if the mac is the same as the slave_adddress,
    // then this vid is filtered
    return mac != slave_mac;
}

bool BridgeFDBEntry::operator==(const BridgeFDBEntry& other) const
{
    return isEqualTo(other);
}
