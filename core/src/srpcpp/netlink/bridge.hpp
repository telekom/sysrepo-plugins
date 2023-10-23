#pragma once

#include "nl.hpp"
#include <netlink/route/link/bridge.h>
#include <netlink/route/link/vlan.h>
#include <linux/if_bridge.h>
#include <netlink/netlink.h>
#include <sstream>

#include <arpa/inet.h>
#include <linux/if_ether.h>
#include <linux/if_bridge.h>
#include <linux/if_arp.h>

#include <map>
#include <iostream>

class BridgeSlaveRef {

public:
    friend class NlContext;
    friend class BridgeRef;
    
    std::string getName();

    int getIfindex();

    void addVlanIDS(const std::vector<uint16_t>& vlan_ids, uint16_t flags);

    void removeVlanIDS(const std::vector<uint16_t>& vlan_ids);

    void removeAllVlanIDS();

private:
    void add_or_remove_bridge_vlan_ids(std::vector<bridge_vlan_info> vlan_ids, uint8_t oper);

    using RtnlLink = struct rtnl_link; ///< Route link type alias.
    using RtnlLinkDeleter = NlDeleter<RtnlLink>; ///< Deleter type alias.
    using BridgeLinkPtr = std::unique_ptr<RtnlLink, RtnlLinkDeleter>; ///< Unique pointer type alias.
    using NlSocketPtr = std::unique_ptr<struct nl_sock, NlDeleter<struct nl_sock>>; // Socket type alias.

    /**
     * @brief Private constructor accessible only to netlink context. Stores a reference to a link for later access of link members.
     */
    BridgeSlaveRef(struct rtnl_link* link, struct nl_sock* socket);

    /**
     * @brief Private constructor accessible only to netlink context. Stores a reference to a link for later access of link members.
     */
    BridgeSlaveRef(struct nl_object* link, struct nl_sock* socket);

    BridgeLinkPtr m_link; ///< Link reference.
    NlSocketPtr m_socket; /// socket reference.
};

class BridgeRef {
public:
    friend class NlContext;
    friend class BridgeSlaveRef;

    static std::vector<uint16_t> parseStringToVlanIDS(const std::string& vlan_str);

    std::string getName(void);

    std::string getMacAddr(void);

    std::map<int, std::string> getSlaveInterfacesIfindexName();

    std::vector<BridgeSlaveRef> getSlaveInterfaces();

    std::optional<BridgeSlaveRef> getSlaveByIfindex(int ifindex);

    void addInterfaceToBridge(int ifindex);

    void addInterfaceToBridge(std::string interface_name);

    void removeInterfaceFromBridge(int ifindex);

    void removeInterfaceFromBridge(std::string interface_name);

    void setMacAddr(std::string address);

private:
    enum BridgeOperation {
        BRIDGE_ADD,
        BRIDGE_REMOVE,
    };

    void add_or_remove_interface_to_bridge(int ifindex, const char* interface_name, BridgeOperation op);

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