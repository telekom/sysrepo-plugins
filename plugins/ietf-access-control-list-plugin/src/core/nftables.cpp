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
                if (it->second == tb["family"]) {
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

NFTChain NFTTable::addChain(const std::string& name, const std::optional<NFT_Chain_Types>& type, const std::optional<NFT_Chain_Hooks>& hook, const std::optional<int32_t>& priority, const std::optional<NFT_Chain_Policy>& policy)
{
    if (name.empty()) throw NFTablesCommandExecException("Chain name cannot be empty!");

    std::string command = "add chain " + utils::getString<NFT_Types>(this->getFamily()) + " " + this->getTableName() + " ";
    bool has_params = false;

    command.append(name);

    if (type || hook || priority || policy) {

        //if one of them has value, they all have to have!
        if (!(type && hook && priority && policy)) {
            throw NFTablesCommandExecException("type, hook, priority, and policy have to be present!");
        }

        has_params = true;
        command.append(" {");
    }

    if (type) command.append(" type " + chain_types.at(*type));
    if (hook) command.append(" hook " + hook_types.at(*hook));
    if (priority) command.append(" priority " + std::to_string(*priority) + "; ");
    if (policy) command.append(" policy " + chain_policy.at(*policy) + " ;");

    if (has_params) command.append(" }");

    std::cout << "CMD: " << command << std::endl;
    NFTCommand::getInstance().exec_cmd(command);

    //if no exception is thrown, we construct NFTChain

    return std::move(NFTChain(name, type, hook, priority, policy, this->getTableName(), this->getFamily()));
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

std::string NFTChain::getTableName()
{
    return m_table_name;
}

std::string NFTChain::getChainName()
{
    return m_chain_name;
}

void NFTChain::addRule(const IP_Match& rule)
{
    std::string command;

    try{
        command = cmd_rule<IP_Match>(rule);
    }catch(...){
        throw NFTablesCommandExecException("Cannot read rule due to type mismatch!");
    }
    std::cout<<"DBG: CMD: "<<command<<std::endl;
    NFTCommand::getInstance().exec_cmd(command);
}

void NFTChain::addRule(const IP6_Match& rule)
{
    std::string command;

    try{
        command = cmd_rule<IP6_Match>(rule);
    }catch(...){
        throw NFTablesCommandExecException("Cannot read rule due to type mismatch!");
    }
    std::cout<<"DBG: CMD: "<<command<<std::endl;
    NFTCommand::getInstance().exec_cmd(command);
}

void NFTChain::addRule(const ETH_Match& rule)
{
    std::string command;

    try{
        command = cmd_rule<ETH_Match>(rule);
    }catch(...){
        throw NFTablesCommandExecException("Cannot read rule due to type mismatch!");
    }
    std::cout<<"DBG: CMD: "<<command<<std::endl;
    NFTCommand::getInstance().exec_cmd(command);
}

void NFTChain::addRule(const TCP_Match& rule)
{
    std::string command;

    try{
        command = cmd_rule<TCP_Match>(rule);
    }catch(...){
        throw NFTablesCommandExecException("Cannot read rule due to type mismatch!");
    }
    std::cout<<"DBG: CMD: "<<command<<std::endl;
    NFTCommand::getInstance().exec_cmd(command);
}

NFTChain::NFTChain(const std::string& chain_name, const std::optional<NFT_Chain_Types>& type, const std::optional<NFT_Chain_Hooks>& hook, const std::optional<int32_t>& priority, const std::optional<NFT_Chain_Policy>& policy, const std::string& table_name, const NFT_Types table_type) :
    m_chain_name(chain_name),
    m_chain_type(type),
    m_chain_priority(priority),
    m_chain_hook(hook),
    m_chain_policy(policy),
    m_table_name(table_name),
    m_table_type(table_type)
{}

IP_Match::IP_Match(IP_Match_Types type) : m_match_type(type) {};
Match::Match() {};

Match& Match::notEqual(void)
{
    m_not_equal = true;
    return *this;
}

Match& Match::equal(void)
{
    m_not_equal = false;
    return *this;
}

bool Match::hasNotEqual(void) const
{
    return m_not_equal;
}

std::string Match::getVal(void) const{
    return m_value;
}

std::string IP_Match::getMatch(void) const
{
    return _ip_match_types.at(m_match_type);
}

IP6_Match::IP6_Match(IP6_Match_Types type) : m_match_type(type) {};

std::string IP6_Match::getMatch(void) const
{
    return _ip6_match_types.at(m_match_type);
}

std::string ETH_Match::getMatch(void) const
{
    return _eth_match_types.at(m_match_type);
}

std::string TCP_Match::getMatch(void) const
{
    return _tcp_match_types.at(m_match_type);
}

std::string IP_Match::getMatchType(void) const
{
    return MATCH_TYPE;
}

std::string IP6_Match::getMatchType(void) const
{
    return MATCH_TYPE;
}

std::string ETH_Match::getMatchType(void) const
{
    return MATCH_TYPE;
}

std::string TCP_Match::getMatchType(void) const
{
    return MATCH_TYPE;
}