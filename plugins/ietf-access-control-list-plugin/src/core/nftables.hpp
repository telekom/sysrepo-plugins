#pragma once

#include <nlohmann/json.hpp>
#include <nftables/libnftables.h>
#include <exception>
#include <string>
#include <memory>
#include <list>
#include <optional>
#include <map>

class NFTables;
class NFTTable;
class NFTChain;

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
    void addChain(const std::string&,
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

// class NFTChain {
//     public:
//         NFTChain() = delete;
//         std::string getTableName();
//         std::string getChainName();
//         std::optional<std::string> getType();
//         std::optional<std::string> getHook();
//         std::optional<int16_t> getPrio();
//         std::optional<std::string> getPolicy();
//         //[TODO] addRule
//     private:
//         NFTChain(const std::string&, const std::string&, const std::string&, const std::string&, 
//         std::optional<std::string>, std::optional<std::string>, std::optional<int16_t>,std::optional<std::string>);
// };

// class NFTRule{

// };
