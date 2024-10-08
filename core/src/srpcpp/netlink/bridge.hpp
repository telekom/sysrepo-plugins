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

#pragma once

#include "nl.hpp"
#include <netlink/route/link/bridge.h>
#include <netlink/route/link/vlan.h>
#include <netlink/route/neighbour.h>
#include <linux/if_bridge.h>
#include <netlink/netlink.h>
#include <sstream>

#include <netlink/route/link/bridge.h>

#include <arpa/inet.h>
#include <linux/if_ether.h>
#include <linux/if_bridge.h>
#include <linux/if_arp.h>

#include <map>
#include <sstream>
#include <iomanip>

// helper class for FilteredVid
class BridgeFDBEntry {

private:
    friend class BridgeSlaveRef;

    std::array<uint8_t, 6> mac;
    std::array<uint8_t, 6> slave_mac;
    uint16_t vid;
    int ifindex;
    std::string mac_string;

    // private constructor
    BridgeFDBEntry(std::array<uint8_t, 6> mac, std::array<uint8_t, 6> slave_mac, uint16_t vid, int ifindex);

public:
    BridgeFDBEntry() = delete;

    bool isEqualTo(const BridgeFDBEntry& other) const;

    std::array<uint8_t, 6> getRawMAC();
    std::string getStringMAC();
    uint16_t getVID();
    int getIfindex();
    bool isFiltered();

    bool operator==(const BridgeFDBEntry& other) const;
};

// Helper class for the vlans
class BridgeVlanID {

private:
    uint16_t vlan_id;
    uint16_t flags;

public:
    // Deleted default constructor
    inline BridgeVlanID() = delete;

    BridgeVlanID(uint16_t vid, uint16_t flags);

    bool getPvidFlag();

    bool getUntaggedFlag();

    uint16_t getVid();

    // overload < operator for custom sorting
    bool operator<(const BridgeVlanID& other) const;
};

class BridgeSlaveRef {

public:
    friend class NlContext;
    friend class BridgeRef;

    std::string getName();

    int getIfindex();

    std::vector<BridgeVlanID> getVlanList();

    void addVlanIDS(const std::vector<uint16_t>& vlan_ids, uint16_t flags);

    void removeVlanIDS(const std::vector<uint16_t>& vlan_ids);

    // [TODO] remove all at once
    void removeAllVlanIDS();

    std::vector<BridgeFDBEntry> getFilteringVids();

    void addAddressToVids(const std::vector<uint16_t>& vlan_ids, const std::string& address);

    void removeAddressFromVids(const std::vector<uint16_t>& vlan_ids, const std::string& address);

    static bool isSubset(const std::vector<uint16_t>& main, const std::vector<uint16_t>& subset);

private:
    enum AddressOperation {
        ADD_ADDRESS,
        REMOVE_ADDRESS
    };

    void add_or_remove_bridge_vlan_ids(std::vector<bridge_vlan_info> vlan_ids, uint8_t oper);

    void add_or_remove_address_to_vids(const std::vector<uint16_t>& vlan_ids, const std::string& address, AddressOperation operation);

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

    enum BridgeVidParse {
        UNTAGGED = false,
        TAGGED = true
    };

    static std::vector<uint16_t> parseStringToVlanIDS(const std::string& vlan_str);

    // fixed size with 2, at pos 0 is tagged, at pos 1 is untagged
    static std::unordered_map<BridgeVidParse, std::string> parseVlanIDSToString(std::vector<BridgeVlanID> vlans);

    static std::string rawNumParser(std::vector<uint16_t> nums);

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

    void setAgeingTime(uint32_t ageingTime);

    uint32_t getAgeingTime();

    bool getSTP();

    void setSTP(bool stp);

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
