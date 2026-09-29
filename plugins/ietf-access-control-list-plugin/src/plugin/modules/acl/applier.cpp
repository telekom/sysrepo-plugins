//
// telekom / sysrepo-plugins
//
// This program is made available under the terms of the
// BSD 3-Clause license which is available at
// https://opensource.org/licenses/BSD-3-Clause
//
// SPDX-FileCopyrightText: 2026 Deutsche Telekom AG
// SPDX-FileContributor: Sartura d.d.
//
// SPDX-License-Identifier: BSD-3-Clause
//

#include "applier.hpp"
#include "common.hpp"
#include "api/nftables.hpp"
#include "api/nft_helper.hpp"

#include <sysrepo.h>

#include <list>
#include <map>
#include <optional>

namespace {

/**
 * @brief nftables protocol and YANG leaf -> nftables field mapping of a match container.
 */
struct MatchFields {
    std::string Protocol; ///< nftables protocol (payload expression) used for the match container.
    std::map<std::string, std::string> Fields; ///< YANG leaf name -> nftables field name.
};

/**
 * @brief Match containers and fields applied on startup.
 *
 * Has to be kept in sync with the rules created by the module change callbacks (change.cpp), so that restarting the
 * plugin recreates the same ruleset that was built from datastore changes. Ports are handled separately (see
 * getPortRule()), ethertype is not applied by the change callbacks and is therefore skipped here as well.
 */
const std::map<std::string, MatchFields> MATCH_FIELDS = {
    { "eth", { "ether", { { "destination-mac-address", "daddr" }, { "source-mac-address", "saddr" } } } },
    { "ipv4", { "ip", { { "dscp", "dscp" }, { "length", "length" }, { "ttl", "ttl" }, { "protocol", "protocol" }, { "ihl", "hdrlength" }, { "destination-ipv4-network", "daddr" }, { "source-ipv4-network", "saddr" } } } },
    { "ipv6", { "ip6", { { "dscp", "dscp" }, { "length", "length" }, { "flow-label", "flowlabel" }, { "destination-ipv6-network", "daddr" }, { "source-ipv6-network", "saddr" } } } },
    { "tcp", { "tcp", { { "sequence-number", "sequence" }, { "acknowledgement-number", "ackseq" }, { "data-offset", "doff" }, { "flags", "flags" }, { "window-size", "window" }, { "urgent-pointer", "urgptr" } } } },
    { "udp", { "udp", { { "length", "length" } } } },
    { "icmp", { "icmp", { { "type", "type" }, { "code", "code" } } } },
};

/**
 * @brief Build the rule for a source-port/destination-port container.
 *
 * Only the port/operator form is supported, same as in the change callbacks.
 *
 * @param port_node source-port or destination-port container node.
 * @param protocol nftables protocol (tcp or udp).
 * @param field nftables field (sport or dport).
 *
 * @return Rule for the port or std::nullopt if no port is set.
 */
std::optional<Match> getPortRule(const libyang::DataNode& port_node, const std::string& protocol, const std::string& field)
{
    std::optional<std::string> port;
    std::string nft_operator;

    for (auto child = port_node.child(); child; child = child->nextSibling()) {
        const std::string name(child->schema().name());
        const std::string value(child->asTerm().valueStr());

        if (name == "port") {
            port = value;
        } else if (name == "operator") {
            if (value == "eq") {
                nft_operator = "==";
            } else if (value == "neq") {
                nft_operator = "!=";
            } else if (value == "lte") {
                nft_operator = "<=";
            } else if (value == "gte") {
                nft_operator = ">=";
            }
        } else if (name == "lower-port" || name == "upper-port") {
            SRPLG_LOG_WRN(getModuleLogPrefix(), "Port ranges are not supported, skipping %s", std::string(port_node.path()).c_str());
            return std::nullopt;
        }
    }

    if (!port) {
        return std::nullopt;
    }

    Match rule;
    rule.Protocol(protocol).Field(field).Value(*port);
    if (!nft_operator.empty()) {
        rule.Operator(nft_operator);
    }

    return rule;
}

/**
 * @brief Build the nftables rules for a single child node of an ACE matches container.
 *
 * @param match Child node of the matches container (match container or ingress/egress interface leaf).
 *
 * @return Rules to add to the ACE chain.
 */
std::list<Match> getMatchRules(const libyang::DataNode& match)
{
    std::list<Match> rules;
    const std::string match_type(match.schema().name());

    if (match_type == "ingress-interface" || match_type == "egress-interface") {
        Match rule;
        rule.Meta(match_type == "ingress-interface" ? "iifname" : "oifname").Value(std::string(match.asTerm().valueStr()));
        rules.push_back(rule);
        return rules;
    }

    const auto match_fields = MATCH_FIELDS.find(match_type);
    if (match_fields == MATCH_FIELDS.end()) {
        return rules;
    }

    const auto& protocol = match_fields->second.Protocol;
    const auto& fields = match_fields->second.Fields;

    for (auto field = match.child(); field; field = field->nextSibling()) {
        const std::string field_name(field->schema().name());

        if (field_name == "source-port" || field_name == "destination-port") {
            if (auto rule = getPortRule(*field, protocol, field_name == "source-port" ? "sport" : "dport")) {
                rules.push_back(*rule);
            }
            continue;
        }

        const auto nft_field = fields.find(field_name);
        if (nft_field == fields.end()) {
            continue;
        }

        Match rule;
        rule.Protocol(protocol).Field(nft_field->second).Value(std::string(field->asTerm().valueStr()));
        rules.push_back(rule);
    }

    return rules;
}

} // namespace

/**
 * @brief Apply datastore content from the provided session to the system.
 *
 * @param session Session to use for retreiving datastore data.
 */
void AclValuesApplier::applyDatastoreValues(sysrepo::Session& session)
{
    SRPLG_LOG_INF(getModuleLogPrefix(), "Loading existing ACLs from datastore");

    // Get all ACLs from the datastore
    auto acls_data = session.getData("/ietf-access-control-list:acls/acl");
    if (!acls_data || !acls_data->child()) {
        SRPLG_LOG_INF(getModuleLogPrefix(), "No existing ACLs found in datastore");
        return;
    }

    NFTables nft;

    // Iterate through each ACL
    for (auto acl = acls_data->child(); acl; acl = acl->nextSibling()) {
        if (std::string(acl->schema().name()) != "acl") {
            continue;
        }

        std::string acl_name;
        std::string acl_type;

        // Extract ACL name and type
        for (auto acl_child = acl->child(); acl_child; acl_child = acl_child->nextSibling()) {
            std::string node_name = acl_child->schema().name();

            if (node_name == "name") {
                acl_name = acl_child->asTerm().valueStr().data();
            } else if (node_name == "type") {
                acl_type = acl_child->asTerm().valueStr().data();
            }
        }

        if (acl_name.empty() || acl_type.empty()) {
            SRPLG_LOG_WRN(getModuleLogPrefix(), "ACL missing name or type, skipping");
            continue;
        }

        SRPLG_LOG_INF(getModuleLogPrefix(), "Processing ACL: %s (type: %s)", acl_name.c_str(), acl_type.c_str());

        // Convert ACL type to NFT type
        NFT_Types table_type = nft::helper::ianaToNFTType(acl_type);
        if (table_type == NFT_Types::NFT_INVALID_TYPE) {
            SRPLG_LOG_ERR(getModuleLogPrefix(), "Invalid ACL type: %s", acl_type.c_str());
            continue;
        }

        // Create nftables table if it doesn't exist
        try {
            auto existing_table = nft.getTable(acl_name, table_type);
            if (!existing_table) {
                SRPLG_LOG_INF(getModuleLogPrefix(), "Creating nftables table: %s", acl_name.c_str());
                nft.addTable(acl_name, table_type);
            } else {
                SRPLG_LOG_INF(getModuleLogPrefix(), "Table %s already exists", acl_name.c_str());
            }
        } catch (const NFTablesCommandExecException& e) {
            SRPLG_LOG_ERR(getModuleLogPrefix(), "Failed to create table %s: %s", acl_name.c_str(), e.what());
            continue;
        }

        // Get the table
        auto nft_table = nft.getTable(acl_name, table_type);
        if (!nft_table) {
            SRPLG_LOG_ERR(getModuleLogPrefix(), "Failed to get table: %s", acl_name.c_str());
            continue;
        }

        // Process ACEs (Access Control Entries)
        for (auto acl_child = acl->child(); acl_child; acl_child = acl_child->nextSibling()) {
            if (std::string(acl_child->schema().name()) != "aces") {
                continue;
            }

            for (auto ace = acl_child->child(); ace; ace = ace->nextSibling()) {
                if (std::string(ace->schema().name()) != "ace") {
                    continue;
                }

                std::string ace_name;
                std::string forwarding_action;

                // Extract ACE details
                for (auto ace_child = ace->child(); ace_child; ace_child = ace_child->nextSibling()) {
                    std::string node_name = ace_child->schema().name();

                    if (node_name == "name") {
                        ace_name = ace_child->asTerm().valueStr().data();
                    } else if (node_name == "actions") {
                        for (auto action_child = ace_child->child(); action_child; action_child = action_child->nextSibling()) {
                            if (std::string(action_child->schema().name()) == "forwarding") {
                                forwarding_action = action_child->asTerm().valueStr().data();
                            }
                        }
                    }
                }

                if (ace_name.empty()) {
                    SRPLG_LOG_WRN(getModuleLogPrefix(), "ACE missing name, skipping");
                    continue;
                }

                SRPLG_LOG_INF(getModuleLogPrefix(), "Processing ACE: %s (action: %s)", ace_name.c_str(), forwarding_action.c_str());

                // Determine chain policy from forwarding action
                NFT_Chain_Policy policy = NFT_Chain_Policy::CH_POLICY_ACCEPT;
                try {
                    if (!forwarding_action.empty()) {
                        policy = nft::helper::ianaToPolicyType(forwarding_action);
                    }
                } catch (...) {
                    SRPLG_LOG_WRN(getModuleLogPrefix(), "Invalid forwarding action: %s, using default", forwarding_action.c_str());
                }

                // Create chain if it doesn't exist
                try {
                    auto existing_chain = nft_table->findChain(ace_name);
                    if (!existing_chain) {
                        SRPLG_LOG_INF(getModuleLogPrefix(), "Creating chain: %s", ace_name.c_str());
                        nft_table->addChain(ace_name, NFT_Chain_Types::CHAIN_FILTER, NFT_Chain_Hooks::CH_HOOK_INPUT, 0, policy);
                    } else {
                        SRPLG_LOG_INF(getModuleLogPrefix(), "Chain %s already exists", ace_name.c_str());
                    }
                } catch (const NFTablesCommandExecException& e) {
                    SRPLG_LOG_ERR(getModuleLogPrefix(), "Failed to create chain %s: %s", ace_name.c_str(), e.what());
                    continue;
                }

                // Get the chain for adding rules
                auto nft_chain = nft_table->findChain(ace_name);
                if (!nft_chain) {
                    SRPLG_LOG_ERR(getModuleLogPrefix(), "Failed to get chain: %s", ace_name.c_str());
                    continue;
                }

                // Process matches and create rules
                for (auto ace_child = ace->child(); ace_child; ace_child = ace_child->nextSibling()) {
                    if (std::string(ace_child->schema().name()) != "matches") {
                        continue;
                    }

                    for (auto match = ace_child->child(); match; match = match->nextSibling()) {
                        std::string match_type(match->schema().name());
                        SRPLG_LOG_DBG(getModuleLogPrefix(), "Processing match type: %s", match_type.c_str());

                        for (const auto& rule : getMatchRules(*match)) {
                            try {
                                nft_chain->addRule(rule);
                            } catch (const NFTablesCommandExecException& e) {
                                SRPLG_LOG_ERR(getModuleLogPrefix(), "Failed to add %s rule: %s", match_type.c_str(), e.what());
                            }
                        }
                    }
                }
            }
        }
    }

    SRPLG_LOG_INF(getModuleLogPrefix(), "Finished loading existing ACLs");
}
