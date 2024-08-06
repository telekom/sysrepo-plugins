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
class Match;

// class IP_Match;
// class ETH_Match;
// class IP6_Match;
// class TCP_Match;

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

    // Generic template, will give a compile-time error if not specialized
    template<typename T> inline
        T getNFTType(const std::string& val) {
        return "Unknown Type!";
    }

    // Template specialization for NFT_Types
    template<> inline
        NFT_Types getNFTType<NFT_Types>(const std::string& val) {
        for (auto obj : nft_types) {
            if (val == obj.second) {
                return obj.first;
            }
        };
        throw NFTablesCommandExecException("Unknown NFT_Types type!");
    };

    // Template specialization for NFT_Chain_Types
    template<> inline
        NFT_Chain_Types getNFTType<NFT_Chain_Types>(const std::string& val) {
        for (auto obj : chain_types) {
            if (val == obj.second) {
                return obj.first;
            }
        };
        throw NFTablesCommandExecException("Unknown NFT_Chain_Types type!");
    };

    // Template specialization for NFT_Chain_Hooks
    template<> inline
        NFT_Chain_Hooks getNFTType<NFT_Chain_Hooks>(const std::string& val) {
        for (auto obj : hook_types) {
            if (val == obj.second) {
                return obj.first;
            }
        };
        throw NFTablesCommandExecException("Unknown NFT_Chain_Hooks type!");
    };

    // Template specialization for NFT_Chain_Policy
    template<> inline
        NFT_Chain_Policy getNFTType<NFT_Chain_Policy>(const std::string& val) {
        for (auto obj : chain_policy) {
            if (val == obj.second) {
                return obj.first;
            }
        };
        throw NFTablesCommandExecException("Unknown NFT_Chain_Policy type!");
    };

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
    void deleteTable(const std::string&, const NFT_Types);

private:

};

class NFTTable {
    friend class NFTables;

public:
    NFTTable() = delete;
    std::string getTableName();
    NFT_Types getFamily();
    NFTChain addChain(const std::string&,
        const std::optional<NFT_Chain_Types>&,
        const std::optional<NFT_Chain_Hooks>&,
        const std::optional<int32_t>&,
        const std::optional<NFT_Chain_Policy>&
    );

    void deleteChain(const NFT_Types, const std::string& ,const std::string&);
    std::optional<NFTChain> findChain(const std::string&);

    std::list<NFTChain> getChains();

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
    std::optional<NFT_Chain_Types> getChainType();
    std::optional<NFT_Chain_Hooks> getChainHook();
    std::optional<int32_t> getPrio();
    std::optional<NFT_Chain_Policy> getChainPolicy();
    void updateChainPolicy(const NFT_Chain_Policy policy);
    void addRule(const Match&);
    void deleteRule(const Match&);
    std::list<Match> getRules();
    std::optional<Match> findRule(const Match&);

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

};

class Match {
    friend class NFTChain;
public:
    Match();
    Match& Operator(const std::string&);
    Match& Protocol(const std::string&);
    Match& Field(const std::string&);
    Match& Meta(const std::string&);
    Match& Value(const std::string&);
    Match& Range(const std::string&, const std::string&);

    uint16_t getHandle() const;

    bool isMeta() const;
    bool isPayload() const;
    bool isRange() const;

    std::optional<std::string> getMetaKey() const;
    std::optional<std::string> getProtocol() const;
    std::optional<std::string> getField() const;
    std::optional<std::string> getOperator() const;
    std::string getValue() const;

    bool operator==(const Match&) const;

private:
    int16_t m_handle;
    std::string m_operator;
    std::string m_value;

    std::optional<std::string> m_meta_key;
    std::optional<std::string> m_protocol;
    std::optional<std::string> m_field;

};