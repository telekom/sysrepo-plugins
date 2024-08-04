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
        table = NFTCommand::getInstance().exec_cmd("list table " + utils::getString<NFT_Types>(family) + " " + name);
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
    NFTCommand::getInstance().exec_cmd("add table " + utils::getString<NFT_Types>(family) + " " + name);

    return NFTTable(family, name);
}

void NFTables::deleteTable(const std::string& name, const NFT_Types family)
{
    NFTCommand::getInstance().exec_cmd("delete table " + utils::getString<NFT_Types>(family) + " " + name);
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

    if (type) command.append(" type " + utils::getString<NFT_Chain_Types>(*type));
    if (hook) command.append(" hook " + utils::getString<NFT_Chain_Hooks>(*hook));
    if (priority) command.append(" priority " + std::to_string(*priority) + "; ");
    if (policy) command.append(" policy " + utils::getString<NFT_Chain_Policy>(*policy) + " ;");

    if (has_params) command.append(" }");

    std::cout << "CMD: " << command << std::endl;
    NFTCommand::getInstance().exec_cmd(command);

    //if no exception is thrown, we construct NFTChain

    return std::move(NFTChain(name, type, hook, priority, policy, this->getTableName(), this->getFamily()));
}

std::list<NFTChain> NFTTable::getChains()
{
    std::list<NFTChain> loaded_chains;

    nlohmann::json json_chains = NFTCommand::getInstance().exec_cmd("list chains");
    for (auto chain : json_chains["nftables"]) {
        if (!chain["chain"].empty()) {
            nlohmann::json chain_obj = chain["chain"];
            if (chain_obj["family"] == utils::getString<NFT_Types>(this->getFamily()) &&
                chain_obj["table"] == this->getTableName()) {

                NFT_Types family = utils::getNFTType<NFT_Types>(chain_obj["family"]);
                std::string chain_name = chain_obj["name"];
                std::optional<NFT_Chain_Types> nft_chain_type;
                std::optional<NFT_Chain_Hooks> nft_chain_hook;
                std::optional<NFT_Chain_Policy> nft_chain_policy;
                std::optional<int32_t> nft_priority;

                chain_obj["type"].empty() ? nft_chain_type = std::nullopt : nft_chain_type = utils::getNFTType<NFT_Chain_Types>(chain_obj["type"]);
                chain_obj["hook"].empty() ? nft_chain_hook = std::nullopt : nft_chain_hook = utils::getNFTType<NFT_Chain_Hooks>(chain_obj["hook"]);
                chain_obj["prio"].empty() ? nft_priority = std::nullopt : nft_priority = (int32_t)chain_obj["prio"];
                chain_obj["policy"].empty() ? nft_chain_policy = std::nullopt : nft_chain_policy = utils::getNFTType<NFT_Chain_Policy>(chain_obj["policy"]);

                loaded_chains.push_back(NFTChain(chain_name, nft_chain_type, nft_chain_hook, nft_priority, nft_chain_policy, this->getTableName(), family));

            }
        }
    }
    return loaded_chains;
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

std::optional<NFT_Chain_Types> NFTChain::getChainType()
{
    return m_chain_type;
}

std::optional<NFT_Chain_Hooks> NFTChain::getChainHook()
{
    return m_chain_hook;
}

std::optional<int32_t> NFTChain::getPrio()
{
    return m_chain_priority;
}

std::optional<NFT_Chain_Policy> NFTChain::getChainPolicy()
{
    return m_chain_policy;
}

void NFTChain::addRule(const Match& match)
{
    std::string command = "add rule " + utils::getString<NFT_Types>(m_table_type) + " " +
        m_table_name + " " +
        m_chain_name + " ";

    if (match.isMeta()) {
        command.append(match.getMetaKey().value() + " ");
    }

    if (match.isPayload()) {
        command.append(match.getProtocol().value() + " " + match.getField().value() + " ");
    }

    if (match.getOperator()) {
        command.append(match.getOperator().value() + " ");
    }

    command.append(match.getValue());


    NFTCommand::getInstance().exec_cmd(command);
}

void NFTChain::deleteRule(const Match& rule)
{
    for (auto& m_rule : this->getRules()) {
        if (rule == m_rule) {
            //NOTE! handle is crutial for delete, so we are getting it from the listed object,
            //not from the constructed one
            std::string command = "delete rule " + utils::getString<NFT_Types>(m_table_type) + " " +
                m_table_name + " " + m_chain_name + " handle " + std::to_string(m_rule.m_handle);
            //it will throw an exception if failed to delete
            NFTCommand::getInstance().exec_cmd(command);
            //our job is done, return if deleted
            return;
        }
    }

    std::string rule_string;
    rule_string.append("(");

    if (rule.isMeta()) {
        rule_string.append(rule.m_meta_key.value_or("unknown meta value"));
    }
    else if (rule.isPayload()) {
        rule_string.append(rule.m_protocol.value_or("unknown proto"));
        rule_string.append(" ");
        rule_string.append(rule.m_field.value_or("unknown field"));
        rule_string.append(" ");
    }

    rule_string.append(rule.m_operator);
    rule_string.append(" ");
    rule_string.append(rule.m_value);
    rule_string.append(")");

    throw NFTablesCommandExecException("Cannot find to delete rule: " + rule_string);
}

std::list<Match> NFTChain::getRules()
{

    nlohmann::json ruleset = NFTCommand::getInstance().exec_cmd("list ruleset");
    std::list<Match> matches;
    for (auto& rule : ruleset["nftables"]) {
        if (rule["rule"].empty()) continue; //we are interested in rules only
        if (rule["rule"]["family"] == utils::getString<NFT_Types>(m_table_type) &&
            rule["rule"]["table"] == m_table_name &&
            rule["rule"]["chain"] == m_chain_name) {
            //we found the rule at this chain

            nlohmann::json expr = rule["rule"]["expr"];

            //we only target the single ones 
            if (expr.size() > 1) continue;
            nlohmann::json match = expr.at(0);

            if (match["match"].empty()) continue;

            Match s_match;
            s_match.Operator(match["match"]["op"]);
            s_match.m_handle = rule["rule"]["handle"];

            if (!match["match"]["left"]["meta"].empty()) s_match.Meta(match["match"]["left"]["meta"]["key"]);

            if (!match["match"]["left"]["payload"].empty()) {
                s_match.Protocol(match["match"]["left"]["payload"]["protocol"]);
                s_match.Field(match["match"]["left"]["payload"]["field"]);
            }
            //its a range
            if (match["match"]["right"].contains("range")) {

                std::string from, to;
                if (match["match"]["right"]["range"].at(0).is_string()) {
                    from = match["match"]["right"]["range"].at(0);
                    to = match["match"]["right"]["range"].at(1);
                }
                else {
                    from = match["match"]["right"]["range"].at(0).dump();
                    to = match["match"]["right"]["range"].at(1).dump();
                }
                s_match.Range(from, to);

            }
            else {
                std::string val;
                if (match["match"]["right"].is_string()) {
                    val = match["match"]["right"];
                }
                else {
                    val = match["match"]["right"].dump();
                }

                s_match.Value(val);
            }

            matches.push_back(s_match);
        }
    }

    return matches;

}

std::optional<Match> NFTChain::findRule(const Match& rule)
{
    for (auto& m_rule : this->getRules()) {
        if (rule == m_rule) {
            return m_rule;
        }
    }
    return std::nullopt;
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


Match::Match() : m_operator("=="), m_handle(-1) {}

Match& Match::Operator(const std::string& oper)
{
    m_operator = oper;
    return (*this);
}

Match& Match::Protocol(const std::string& protocol)
{
    m_protocol = protocol;
    return (*this);
}

Match& Match::Field(const std::string& field)
{
    m_field = field;
    return (*this);
}

Match& Match::Meta(const std::string& meta_key)
{
    m_meta_key = meta_key;
    return (*this);
}

Match& Match::Value(const std::string& value)
{
    m_value = value;
    return (*this);
}

Match& Match::Range(const std::string& from, const std::string& to)
{
    m_value = from + "-" + to;
    return (*this);
}

uint16_t Match::getHandle() const
{
    return m_handle;
}

bool Match::isMeta() const
{
    return m_meta_key.has_value();
}

bool Match::isPayload() const
{
    return m_protocol.has_value() && m_field.has_value();
}

bool Match::isRange() const
{
    return (m_value.find("-") != std::string::npos);
}

std::optional<std::string> Match::getMetaKey() const
{
    return m_meta_key;
}

std::optional<std::string> Match::getProtocol() const
{
    return m_protocol;
}

std::optional<std::string> Match::getField() const
{
    return m_field;
}

std::string Match::getValue() const
{
    return m_value;
}

bool Match::operator==(const Match& other) const
{
    std::string m_other_left;
    std::string m_this_left;

    if (this->isMeta()) {
        m_this_left.append(m_meta_key.value_or(""));
    }
    else if (this->isPayload()) {
        m_this_left.append(m_protocol.value_or("") + " " + m_field.value_or(""));
    };

    if (other.isMeta()) {
        m_other_left.append(other.m_meta_key.value_or(""));
    }
    else if (other.isPayload()) {
        m_other_left.append(other.m_protocol.value_or("") + " " + other.m_field.value_or(""));
    };

    return (
        m_other_left == m_this_left &&
        m_operator == other.m_operator &&
        m_value == other.m_value
        );
}

std::optional<std::string> Match::getOperator() const
{
    return m_operator;
}