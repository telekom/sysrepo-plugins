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

enum NFT_Types {
    NFT_IP,
    NFT_IP6,
    NFT_INET,
    NFT_ARP,
    NFT_BRIDGE,
    NFT_NETDEV,
    NFT_INVALID_TYPE,
};

const std::map<NFT_Types,std::string> nft_types = {
    {NFT_IP,     "ip"},
    {NFT_IP6,    "ip6"},
    {NFT_INET,   "inet"},
    {NFT_ARP,    "arp"},
    {NFT_BRIDGE, "bridge"},
    {NFT_NETDEV, "netdev"},
};

class NFTablesCommandExecException : public std::exception {
    public:
        NFTablesCommandExecException(const std::string what){
            this->m_what = what;
        }
        virtual const char* what() const noexcept override{
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
    private:
        NFTTable(const NFT_Types, const std::string&);

    NFT_Types m_fam;
    std::string m_name;
};

// class NFTChain {
//     public:
//         NFTChain() = delete;
//         std::string getTableName();
//         std::string getHandle();
//         std::string getFamily();
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

// // class NFTRule{

// // };
