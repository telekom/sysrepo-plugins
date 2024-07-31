#pragma once

#include <nlohmann/json.hpp>
#include <nftables/libnftables.h>
#include <exception>
#include <string>
#include <memory>
#include <list>
#include <type_traits>
#include <optional>
#include <map>

class NFTables;
class NFTTable;
class NFTChain;

class IP_Match;
class ETH_Match;
class IP6_Match;
class TCP_Match;

enum NFT_Types {
    NFT_IP,
    NFT_IP6,
    NFT_INET,
    NFT_ARP,
    NFT_BRIDGE,
    NFT_NETDEV,
    NFT_INVALID_TYPE,
};

const std::map<NFT_Types, std::string> nft_types = {
    {NFT_IP,     "ip"},
    {NFT_IP6,    "ip6"},
    {NFT_INET,   "inet"},
    {NFT_ARP,    "arp"},
    {NFT_BRIDGE, "bridge"},
    {NFT_NETDEV, "netdev"},
};

enum NFT_Chain_Types {
    CHAIN_FILTER,
    CHAIN_NAT,
    CHAIN_ROUTE,
};

const std::map<NFT_Chain_Types, std::string> chain_types = {
    {CHAIN_FILTER,  "filter"},
    {CHAIN_NAT,     "nat"},
    {CHAIN_ROUTE,   "route"},
    //expand if needed
};

enum NFT_Chain_Hooks {
    CH_HOOK_INGRESS,
    CH_HOOK_PREROUTING,
    CH_HOOK_INPUT,
    CH_HOOK_FORWARD,
    CH_HOOK_OUTPUT,
    CH_HOOK_POSTROUTING,
};

const std::map<NFT_Chain_Hooks, std::string> hook_types = {
    {CH_HOOK_INGRESS,       "ingress"},
    {CH_HOOK_PREROUTING,    "prerouting"},
    {CH_HOOK_INPUT,         "input"},
    {CH_HOOK_FORWARD,       "forward"},
    {CH_HOOK_OUTPUT,        "output"},
    {CH_HOOK_POSTROUTING,   "postrouting"},
    //expand if needed
};

enum NFT_Chain_Policy {
    CH_POLICY_ACCEPT,
    CH_POLICY_DROP
};

const std::map<NFT_Chain_Policy, std::string> chain_policy = {
    {CH_POLICY_ACCEPT,      "accept"},
    {CH_POLICY_DROP,        "drop"},
    //expand if needed
};

namespace utils {

    // Generic template, will give a compile-time error if not specialized
    template<typename T> inline
        std::string getString(T val) {
        return "Unknown Type!";
    }

    // Template specialization for NFT_Types
    template<> inline
        std::string getString<NFT_Types>(NFT_Types val) {
        auto it = nft_types.find(val);
        return it != nft_types.end() ? it->second : "Unknown NFT Type!";
    }

    // Template specialization for NFT_Chain_Types
    template<> inline
        std::string getString<NFT_Chain_Types>(NFT_Chain_Types val) {
        auto it = chain_types.find(val);
        return it != chain_types.end() ? it->second : "Unknown Chain Type!";
    }

    // Template specialization for NFT_Chain_Hooks
    template<> inline
        std::string getString<NFT_Chain_Hooks>(NFT_Chain_Hooks val) {
        auto it = hook_types.find(val);
        return it != hook_types.end() ? it->second : "Unknown Chain Hook!";
    }

    // Template specialization for NFT_Chain_Policy
    template<> inline
        std::string getString<NFT_Chain_Policy>(NFT_Chain_Policy val) {
        auto it = chain_policy.find(val);
        return it != chain_policy.end() ? it->second : "Unknown Chain Policy!";
    }

};

class NFTablesCommandExecException : public std::exception {
public:
    NFTablesCommandExecException(const std::string what) {
        this->m_what = what;
    }
    virtual const char* what() const noexcept override {
        return m_what.c_str();
    }
private:
    std::string m_what;
};

// NFTCommand
class NFTCommand {
public:
    // Deleted copy constructor and assignment operator
    NFTCommand(const NFTCommand&) = delete;
    NFTCommand& operator=(const NFTCommand&) = delete;
    nlohmann::json exec_cmd(const std::string&);
    static NFTCommand& getInstance();

private:
    // Private constructor to prevent direct instantiation
    NFTCommand();
    ~NFTCommand();
    nft_ctx* m_ctx;
};

class NFTables {

public:
    std::string dumpJSON();
    std::list<NFTTable> getTables();
    //[TODO]
    std::optional<NFTTable> getTable(const std::string&, NFT_Types);
    //[TODO] addTable
    NFTTable addTable(const std::string&, const NFT_Types);

private:

};

class NFTTable {
    friend class NFTables;

public:
    NFTTable() = delete;
    std::string getTableName();
    NFT_Types getFamily();
    //[TODO] addChain
    NFTChain addChain(const std::string&,
        const std::optional<NFT_Chain_Types>&,
        const std::optional<NFT_Chain_Hooks>&,
        const std::optional<int32_t>&,
        const std::optional<NFT_Chain_Policy>&
    );
private:
    NFTTable(const NFT_Types, const std::string&);

    NFT_Types m_fam;
    std::string m_name;
};

class NFTChain {
    friend class NFTTable;
public:
    NFTChain() = delete;
    std::string getTableName();
    std::string getChainName();
    // std::optional<std::string> getType();
    // std::optional<std::string> getHook();
    // std::optional<int16_t> getPrio();
    // std::optional<std::string> getPolicy();
    //[TODO] addRule
    void addRule(const IP_Match&);
    void addRule(const IP6_Match&);
    void addRule(const ETH_Match&);
    void addRule(const TCP_Match&);

private:
    NFTChain(const std::string&,
        const std::optional<NFT_Chain_Types>&,
        const std::optional<NFT_Chain_Hooks>&,
        const std::optional<int32_t>&,
        const std::optional<NFT_Chain_Policy>&,
        const std::string&,
        const NFT_Types);

    std::string m_table_name;
    std::string m_chain_name;
    std::optional<NFT_Chain_Types> m_chain_type;
    std::optional<NFT_Chain_Hooks> m_chain_hook;
    std::optional<int32_t> m_chain_priority;
    std::optional<NFT_Chain_Policy> m_chain_policy;
    NFT_Types m_table_type;

    template<typename T> inline std::string cmd_rule(const T& rule) {
        std::string command = "add rule " +
            nft_types.at(m_table_type) + " " +
            m_table_name + " " +
            m_chain_name + " " +
            rule.getMatchType() + " " +
            rule.getMatch();

        command.append( rule.hasNotEqual() ? " != " : " ");
        command.append(rule.getVal());

        return command;
    }
};

class Match {

    virtual std::string getMatch(void) const = 0;
    virtual std::string getMatchType(void) const = 0;

public:

    Match& notEqual(void);
    Match& equal(void);

    template<typename T> inline
        Match& setValue(const T&);

    template<typename T> inline
        Match& setRange(const T&, const T&);

    bool hasNotEqual(void) const;
    std::string getVal(void) const;

protected:
    Match();

private:
    std::string m_value;
    bool m_not_equal;
};

template<typename T>
inline Match& Match::setValue(const T& val)
{
    if constexpr (std::is_same_v<T, std::string>) {
        //its a string
        m_value = val;
    }
    else if constexpr (std::is_integral_v<T>) {
        // its a number
        m_value = std::to_string(val);
    }
    else {
        throw NFTablesCommandExecException("Wrong value types, please use strings or numbers!");
    };

    return *this;
}

template<typename T>
inline Match& Match::setRange(const T& first, const T& second)
{
    if constexpr (std::is_same_v<T, std::string>) {
        //its a string
        m_value = first + "-" + second;
    }
    else if constexpr (std::is_integral_v<T>) {
        // its a number
        std::string s_first = std::to_string(first);
        std::string s_second = std::to_string(second);
        m_value = s_first + "-" + s_second;
    }
    else {
        throw NFTablesCommandExecException("Wrong value types, please use strings or numbers!");
    };
    return *this;
}

class IP_Match : public Match {

public:

    enum IP_Match_Types {
        IP_DSCP_MATCH,
        IP_LENGTH_MATCH,
        IP_ID_MATCH,
        IP_FRAGMENT_MATCH,
        IP_TTL_MATCH,
        IP_PROTOCOL_MATCH,
        IP_CHECKSUM_MATCH,
        IP_S_ADDR_MATCH,
        IP_D_ADDR_MATCH,
        IP_VERSION_MATCH,
        IP_HDR_LEN_MATCH,
    };


    IP_Match(IP_Match_Types);

    std::string getMatch(void) const override;
    std::string getMatchType(void) const override;

private:

    const std::map<IP_Match_Types, std::string>_ip_match_types = {
        {IP_DSCP_MATCH,             "dscp"},
        {IP_LENGTH_MATCH,           "length"},
        {IP_ID_MATCH,               "id"},
        {IP_FRAGMENT_MATCH,         "frag-off"},
        {IP_TTL_MATCH,              "ttl"},
        {IP_PROTOCOL_MATCH,         "protocol"},
        {IP_CHECKSUM_MATCH,         "checksum"},
        {IP_S_ADDR_MATCH,           "saddr"},
        {IP_D_ADDR_MATCH,           "daddr"},
        {IP_VERSION_MATCH,          "version"},
        {IP_HDR_LEN_MATCH,          "hdrlength"},
    };

    IP_Match_Types m_match_type;
    const std::string MATCH_TYPE = "ip";
};

class IP6_Match : public Match {

public:
    enum IP6_Match_Types {
        IP6_DSCP_MATCH,
        IP6_FLOWLABEL_MATCH,
        IP6_LENGTH_MATCH,
        IP6_NEXT_HDR_MATCH,
        IP6_HOP_LIMIT_MATCH,
        IP6_S_ADDR_MATCH,
        IP6_D_ADDR_MATCH,
        IP6_VERSION_MATCH,
    };


    IP6_Match(IP6_Match_Types);

    std::string getMatch(void) const override;
    std::string getMatchType(void) const override;

private:

    const std::map<IP6_Match_Types, std::string>_ip6_match_types = {
        {IP6_DSCP_MATCH,        "dscp"},
        {IP6_FLOWLABEL_MATCH,   "flowlabel"},
        {IP6_LENGTH_MATCH,      "length"},
        {IP6_NEXT_HDR_MATCH,    "nexthdr"},
        {IP6_HOP_LIMIT_MATCH,   "hoplimit"},
        {IP6_S_ADDR_MATCH,      "saddr"},
        {IP6_D_ADDR_MATCH,      "daddr"},
        {IP6_VERSION_MATCH,     "vetsion"},
    };

    IP6_Match_Types m_match_type;
    const std::string MATCH_TYPE = "ip6";
};

class ETH_Match : public Match {

public:
    enum ETH_Match_Types {
        ETH_S_ADDR_MATCH,
        ETH_D_ADDR_MATCH,
        ETH_TYPE_MATCH,
    };

    ETH_Match(ETH_Match_Types);

    std::string getMatch(void) const override;
    std::string getMatchType(void) const override;

private:

    const std::map<ETH_Match_Types, std::string>_eth_match_types = {
        {ETH_S_ADDR_MATCH,        "saddr"},
        {ETH_D_ADDR_MATCH,        "daddr"},
        {ETH_TYPE_MATCH,           "type"},
    };

    ETH_Match_Types m_match_type;
    const std::string MATCH_TYPE = "ether";
};

class TCP_Match : public Match {

public:
    enum TCP_Match_Types {
        TCP_S_PORT_MATCH,
        TCP_D_PORT_MATCH,
        TCP_SEQ_MATCH,
        TCP_ACK_SEQ_MATCH,
        TCP_FLAGS_MATCH,
        TCP_WINDOW_MATCH,
        TCP_CHECKSUM_MATCH,
        TCP_URG_PTR_MATCH,
        TCP_D_OFFSET_MATCH,
    };

    TCP_Match(TCP_Match_Types);

    std::string getMatch(void) const override;
    std::string getMatchType(void) const override;

private:

    const std::map<TCP_Match_Types, std::string>_tcp_match_types = {
        {TCP_S_PORT_MATCH,      "sport"},
        {TCP_D_PORT_MATCH,      "dport"},
        {TCP_SEQ_MATCH,         "sequence"},
        {TCP_ACK_SEQ_MATCH,     "ackseq"},
        {TCP_FLAGS_MATCH,       "flags"},
        {TCP_WINDOW_MATCH,      "window"},
        {TCP_CHECKSUM_MATCH,    "checksum"},
        {TCP_URG_PTR_MATCH,     "urgptr"},
        {TCP_D_OFFSET_MATCH,    "doff"},
    };

    TCP_Match_Types m_match_type;
    const std::string MATCH_TYPE = "tcp";
};