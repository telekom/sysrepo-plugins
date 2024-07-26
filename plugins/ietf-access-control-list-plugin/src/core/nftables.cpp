#include "core/nftables.hpp"
#include <iostream>
#include "nftables.hpp"

std::list<NFTTable> NFTables::getTables()
{
    nlohmann::json tables = NFTCommand::getInstance().exec_cmd("list tables")["nftables"];
    std::list<NFTTable> tables_table_list;

    for (auto& table : tables) {
        nlohmann::json table_obj = table["table"];
        if (!table_obj.empty()) {
            tables_table_list.push_back(NFTTable(table_obj["family"], table_obj["name"]));
        };
    }
    return std::move(tables_table_list);
}

std::optional<NFTTable> NFTables::getTable(const std::string& name, NFT_Types family)
{
    nlohmann::json table;

    try {
        table = NFTCommand::getInstance().exec_cmd("list table " + nft_types.at(family) + " " + name);
    }
    catch (std::exception& e) {
        return std::nullopt;
    }
    for (auto& table_obj : table["nftables"]) {
        if (!table_obj["table"].empty()) {
           
            const nlohmann::json tb = table_obj["table"];
            NFT_Types tb_type = NFT_INVALID_TYPE;
            for (auto it = nft_types.begin(); it != nft_types.end(); ++it)
                if (it->second == tb["family"]){
                    tb_type = it->first;
                    break;
                }
                    
            if (tb_type == NFT_INVALID_TYPE) {
                throw NFTablesCommandExecException("Invalid type: " + tb["family"].dump());
            }

            return NFTTable(tb_type, tb["name"]);
        }
    }

    return std::nullopt;
}

NFTTable NFTables::addTable(const std::string& name, const NFT_Types family)
{
    NFTCommand::getInstance().exec_cmd("add table " + nft_types.at(family) + " " + name);

    return NFTTable(family, name);
}

NFTTable::NFTTable(const NFT_Types fam, const std::string& name) :
    m_fam{ fam },
    m_name{ name } {};

std::string NFTTable::getTableName() {
    return m_name;
}

NFT_Types NFTTable::getFamily() {
    return m_fam;
}

NFTCommand& NFTCommand::getInstance()
{
    static NFTCommand instance;
    return instance;
}

nlohmann::json NFTCommand::exec_cmd(const std::string& command)
{
    int err = 0;
    nlohmann::json m_json;

    err = nft_ctx_buffer_output(m_ctx);
    if (err != 0) {
        throw NFTablesCommandExecException("Failed to set buffer nft_ctx_buffer_output()");
    }

    err = nft_run_cmd_from_buffer(m_ctx, command.c_str());
    if (err < 0)
        throw NFTablesCommandExecException("Failed to exec command " + command + "!");

    const char* buff = nft_ctx_get_output_buffer(m_ctx);
    std::string buffer(buff);

    err = nft_ctx_unbuffer_output(m_ctx);
    if (err != 0) {
        throw NFTablesCommandExecException("Failed to unbuffer output!");
    }

    if (!buffer.empty()) {
        m_json = nlohmann::json::parse(buffer);
    }
    else {
        m_json = nlohmann::json::parse("{}");
    }

    return std::move(m_json);
}

NFTCommand::NFTCommand()
{
    std::cout << "NFTCommand Constructed" << std::endl;
    int err = 0;
    m_ctx = NULL;
    m_ctx = nft_ctx_new(NFT_CTX_DEFAULT);
    if (!m_ctx) {
        throw std::bad_alloc();
    }
    //Default settings,  
    nft_ctx_output_set_flags(m_ctx, NFT_CTX_OUTPUT_HANDLE | NFT_CTX_OUTPUT_JSON);
    err = nft_ctx_buffer_error(m_ctx);
    if (err != 0) {
        throw NFTablesCommandExecException("nft_ctx_buffer_error() failed!");
    }
}

NFTCommand::~NFTCommand()
{
    std::cout << "NFTCommand destructed" << std::endl;
    if (m_ctx != NULL) nft_ctx_free(m_ctx);
}
