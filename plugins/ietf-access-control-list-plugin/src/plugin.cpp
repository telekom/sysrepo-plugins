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

#include "plugin.hpp"
#include "core/context.hpp"
#include "core/common.hpp"

#include <sysrepo-cpp/Session.hpp>
#include <sysrepo-cpp/Subscription.hpp>
#include <sysrepo-cpp/utils/utils.hpp>
#include <srpcpp.hpp>

#include "modules/acl.hpp"
#include "core/nftables.hpp"
#include "core/nft_helper.hpp"

namespace sr = sysrepo;

/**
 * TODO
 * Register all operational plugin subscriptions.
 *
 * @param sess Session to use for creating subscriptions.
 * @param ctx Plugin context.
 * @param mod Module to use.
 *
 */
void registerOperationalSubscriptions(sr::Session& sess, ietf::acl::PluginContext& ctx, std::unique_ptr<srpc::IModule<ietf::acl::PluginContext>>& mod){
    const auto oper_callbacks = mod->getOperationalCallbacks();

    auto& sub_handle = ctx.getSubscriptionHandle();

    for (auto& cb : oper_callbacks) {
        SRPLG_LOG_INF(ietf::acl::PLUGIN_NAME, "Creating operational subscription for xpath %s", cb.XPath.c_str());
        if (sub_handle.has_value()) {
            sub_handle->onOperGet("ietf-access-control-list", cb.Callback, cb.XPath);
        } else {
            sub_handle = sess.onOperGet("ietf-access-control-list", cb.Callback, cb.XPath);
        }
    }
};

/**
 * TODO
 * Register all module change plugin subscriptions.
 *
 * @param sess Session to use for creating subscriptions.
 * @param ctx Plugin context.
 * @param mod Module to use.
 *
 */
void registerModuleChangeSubscriptions(sr::Session& sess, ietf::acl::PluginContext& ctx, std::unique_ptr<srpc::IModule<ietf::acl::PluginContext>>& mod){
    
    const auto change_callbacks = mod->getModuleChangeCallbacks();

    auto& sub_handle = ctx.getSubscriptionHandle();

    for (auto& cb : change_callbacks) {
        SRPLG_LOG_INF(ietf::acl::PLUGIN_NAME, "Creating module change subscription for xpath %s", cb.XPath.c_str());
        if (sub_handle.has_value()) {
            sub_handle->onModuleChange("ietf-access-control-list", cb.Callback, cb.XPath);
        } else {
            sub_handle = sess.onModuleChange("ietf-access-control-list", cb.Callback, cb.XPath);
        }
    }
};

/**
 * TODO
 * Register all RPC plugin subscriptions.
 *
 * @param sess Session to use for creating subscriptions.
 * @param ctx Plugin context.
 * @param mod Module to use.
 *
 */
void registerRpcSubscriptions(sr::Session& sess, ietf::acl::PluginContext& ctx, std::unique_ptr<srpc::IModule<ietf::acl::PluginContext>>& mod){
    const auto rpc_callbacks = mod->getRpcCallbacks();

    auto& sub_handle = ctx.getSubscriptionHandle();

    for (auto& cb : rpc_callbacks) {
        SRPLG_LOG_INF(ietf::acl::PLUGIN_NAME, "Creating RPC subscription for xpath %s", cb.XPath.c_str());
        if (sub_handle.has_value()) {
            sub_handle->onRPCAction(cb.XPath, cb.Callback);
        } else {
            sub_handle = sess.onRPCAction(cb.XPath, cb.Callback);
        }
    }
};

/**
 * @brief Load and process existing ACL data from the datastore.
 *
 * @param sess Session to use for reading data.
 *
 * @return Error code (SR_ERR_OK on success).
 */
void loadExistingACLs(sr::Session& sess)
{
    try {
        SRPLG_LOG_INF(ietf::acl::PLUGIN_NAME, "Loading existing ACLs from datastore");

        // Get all ACLs from the datastore
        auto acls_data = sess.getData("/ietf-access-control-list:acls/acl");
        if (!acls_data || !acls_data->child()) {
            SRPLG_LOG_INF(ietf::acl::PLUGIN_NAME, "No existing ACLs found in datastore");
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
                SRPLG_LOG_WRN(ietf::acl::PLUGIN_NAME, "ACL missing name or type, skipping");
                continue;
            }

            SRPLG_LOG_INF(ietf::acl::PLUGIN_NAME, "Processing ACL: %s (type: %s)", acl_name.c_str(), acl_type.c_str());

            // Convert ACL type to NFT type
            NFT_Types table_type = nft::helper::ianaToNFTType(acl_type);
            if (table_type == NFT_Types::NFT_INVALID_TYPE) {
                SRPLG_LOG_ERR(ietf::acl::PLUGIN_NAME, "Invalid ACL type: %s", acl_type.c_str());
                continue;
            }

            // Create nftables table if it doesn't exist
            try {
                auto existing_table = nft.getTable(acl_name, table_type);
                if (!existing_table) {
                    SRPLG_LOG_INF(ietf::acl::PLUGIN_NAME, "Creating nftables table: %s", acl_name.c_str());
                    nft.addTable(acl_name, table_type);
                } else {
                    SRPLG_LOG_INF(ietf::acl::PLUGIN_NAME, "Table %s already exists", acl_name.c_str());
                }
            } catch (const NFTablesCommandExecException& e) {
                SRPLG_LOG_ERR(ietf::acl::PLUGIN_NAME, "Failed to create table %s: %s", acl_name.c_str(), e.what());
                continue;
            }

            // Get the table
            auto nft_table = nft.getTable(acl_name, table_type);
            if (!nft_table) {
                SRPLG_LOG_ERR(ietf::acl::PLUGIN_NAME, "Failed to get table: %s", acl_name.c_str());
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
                        SRPLG_LOG_WRN(ietf::acl::PLUGIN_NAME, "ACE missing name, skipping");
                        continue;
                    }

                    SRPLG_LOG_INF(ietf::acl::PLUGIN_NAME, "Processing ACE: %s (action: %s)", ace_name.c_str(), forwarding_action.c_str());

                    // Determine chain policy from forwarding action
                    NFT_Chain_Policy policy = NFT_Chain_Policy::CH_POLICY_ACCEPT;
                    try {
                        if (!forwarding_action.empty()) {
                            policy = nft::helper::ianaToPolicyType(forwarding_action);
                        }
                    } catch (...) {
                        SRPLG_LOG_WRN(ietf::acl::PLUGIN_NAME, "Invalid forwarding action: %s, using default", forwarding_action.c_str());
                    }

                    // Create chain if it doesn't exist
                    try {
                        auto existing_chain = nft_table->findChain(ace_name);
                        if (!existing_chain) {
                            SRPLG_LOG_INF(ietf::acl::PLUGIN_NAME, "Creating chain: %s", ace_name.c_str());
                            nft_table->addChain(ace_name, NFT_Chain_Types::CHAIN_FILTER, NFT_Chain_Hooks::CH_HOOK_INPUT, 0, policy);
                        } else {
                            SRPLG_LOG_INF(ietf::acl::PLUGIN_NAME, "Chain %s already exists", ace_name.c_str());
                        }
                    } catch (const NFTablesCommandExecException& e) {
                        SRPLG_LOG_ERR(ietf::acl::PLUGIN_NAME, "Failed to create chain %s: %s", ace_name.c_str(), e.what());
                        continue;
                    }

                    // Get the chain for adding rules
                    auto nft_chain = nft_table->findChain(ace_name);
                    if (!nft_chain) {
                        SRPLG_LOG_ERR(ietf::acl::PLUGIN_NAME, "Failed to get chain: %s", ace_name.c_str());
                        continue;
                    }

                    // Process matches and create rules
                    for (auto ace_child = ace->child(); ace_child; ace_child = ace_child->nextSibling()) {
                        if (std::string(ace_child->schema().name()) != "matches") {
                            continue;
                        }

                        // Process different match types
                        for (auto match = ace_child->child(); match; match = match->nextSibling()) {
                            std::string match_type = match->schema().name();
                            SRPLG_LOG_DBG(ietf::acl::PLUGIN_NAME, "Processing match type: %s", match_type.c_str());

                            // Process IPv4 matches
                            if (match_type == "ipv4") {
                                for (auto ipv4_field = match->child(); ipv4_field; ipv4_field = ipv4_field->nextSibling()) {
                                    std::string field_name = ipv4_field->schema().name();
                                    std::string value = ipv4_field->asTerm().valueStr().data();

                                    try {
                                        Match rule;
                                        if (field_name == "dscp") {
                                            rule.Protocol("ip").Field("dscp").Value(value);
                                        } else if (field_name == "length") {
                                            rule.Protocol("ip").Field("length").Value(value);
                                        } else if (field_name == "ttl") {
                                            rule.Protocol("ip").Field("ttl").Value(value);
                                        } else if (field_name == "protocol") {
                                            rule.Protocol("ip").Field("protocol").Value(value);
                                        } else if (field_name == "ihl") {
                                            rule.Protocol("ip").Field("hdrlength").Value(value);
                                        } else if (field_name == "destination-ipv4-network") {
                                            rule.Protocol("ip").Field("daddr").Value(value);
                                        } else if (field_name == "source-ipv4-network") {
                                            rule.Protocol("ip").Field("saddr").Value(value);
                                        } else {
                                            continue;
                                        }

                                        SRPLG_LOG_DBG(ietf::acl::PLUGIN_NAME, "Adding IPv4 rule: %s = %s", field_name.c_str(), value.c_str());
                                        nft_chain->addRule(rule);
                                    } catch (const NFTablesCommandExecException& e) {
                                        SRPLG_LOG_ERR(ietf::acl::PLUGIN_NAME, "Failed to add IPv4 rule: %s", e.what());
                                    }
                                }
                            }
                            // Process TCP matches
                            else if (match_type == "tcp") {
                                for (auto tcp_field = match->child(); tcp_field; tcp_field = tcp_field->nextSibling()) {
                                    std::string field_name = tcp_field->schema().name();

                                    try {
                                        Match rule;
                                        if (field_name == "source-port" || field_name == "destination-port") {
                                            // Handle port ranges/operators
                                            for (auto port_child = tcp_field->child(); port_child; port_child = port_child->nextSibling()) {
                                                std::string port_field = port_child->schema().name();

                                                if (port_field == "lower-port" || port_field == "upper-port") {
                                                    // Range case - we'll need both values
                                                    std::string lower, upper;
                                                    for (auto p = tcp_field->child(); p; p = p->nextSibling()) {
                                                        if (std::string(p->schema().name()) == "lower-port") {
                                                            lower = p->asTerm().valueStr().data();
                                                        } else if (std::string(p->schema().name()) == "upper-port") {
                                                            upper = p->asTerm().valueStr().data();
                                                        }
                                                    }
                                                    if (!lower.empty() && !upper.empty()) {
                                                        std::string nft_field = (field_name == "source-port") ? "sport" : "dport";
                                                        rule.Protocol("tcp").Field(nft_field).Range(lower, upper);
                                                        SRPLG_LOG_DBG(ietf::acl::PLUGIN_NAME, "Adding TCP %s range rule: %s-%s", nft_field.c_str(), lower.c_str(), upper.c_str());
                                                        nft_chain->addRule(rule);
                                                    }
                                                    break;
                                                } else if (port_field == "port") {
                                                    // Single port with operator
                                                    std::string port = port_child->asTerm().valueStr().data();
                                                    std::string nft_field = (field_name == "source-port") ? "sport" : "dport";
                                                    rule.Protocol("tcp").Field(nft_field).Value(port);

                                                    // Check for operator
                                                    for (auto p = tcp_field->child(); p; p = p->nextSibling()) {
                                                        if (std::string(p->schema().name()) == "operator") {
                                                            std::string op = p->asTerm().valueStr().data();
                                                            if (op == "lte") rule.Operator("<=");
                                                            else if (op == "gte") rule.Operator(">=");
                                                            else if (op == "eq") rule.Operator("==");
                                                            else if (op == "neq") rule.Operator("!=");
                                                        }
                                                    }

                                                    SRPLG_LOG_DBG(ietf::acl::PLUGIN_NAME, "Adding TCP %s rule: %s", nft_field.c_str(), port.c_str());
                                                    nft_chain->addRule(rule);
                                                    break;
                                                }
                                            }
                                        } else {
                                            // Other TCP fields
                                            std::string value = tcp_field->asTerm().valueStr().data();
                                            if (field_name == "sequence-number") {
                                                rule.Protocol("tcp").Field("sequence").Value(value);
                                            } else if (field_name == "acknowledgement-number") {
                                                rule.Protocol("tcp").Field("ackseq").Value(value);
                                            } else if (field_name == "data-offset") {
                                                rule.Protocol("tcp").Field("doff").Value(value);
                                            } else if (field_name == "flags") {
                                                rule.Protocol("tcp").Field("flags").Value(value);
                                            } else if (field_name == "window-size") {
                                                rule.Protocol("tcp").Field("window").Value(value);
                                            } else if (field_name == "urgent-pointer") {
                                                rule.Protocol("tcp").Field("urgptr").Value(value);
                                            } else {
                                                continue;
                                            }

                                            SRPLG_LOG_DBG(ietf::acl::PLUGIN_NAME, "Adding TCP rule: %s = %s", field_name.c_str(), value.c_str());
                                            nft_chain->addRule(rule);
                                        }
                                    } catch (const NFTablesCommandExecException& e) {
                                        SRPLG_LOG_ERR(ietf::acl::PLUGIN_NAME, "Failed to add TCP rule: %s", e.what());
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        SRPLG_LOG_INF(ietf::acl::PLUGIN_NAME, "Finished loading existing ACLs");

    } catch (const std::exception& e) {
        SRPLG_LOG_ERR(ietf::acl::PLUGIN_NAME, "Error loading existing ACLs: %s", e.what());
    }
}

/**
 * @brief Plugin init callback.
 *
 * @param session Plugin session.
 * @param priv Private data.
 *
 * @return Error code (SR_ERR_OK on success).
 */

int sr_plugin_init_cb(sr_session_ctx_t* session, void** priv)
{
    sr::ErrorCode error = sysrepo::ErrorCode::Ok;
    auto sess = sysrepo::wrapUnmanagedSession(session);
    auto plugin_ctx = new ietf::acl::PluginContext(sess);
    auto& registry(srpc::ModuleRegistry<ietf::acl::PluginContext>::getInstance());
    *priv = static_cast<void*>(plugin_ctx);

    SRPLG_LOG_INF(ietf::acl::PLUGIN_NAME, "Creating plugin subscriptions");

    registry.registerModule<AclModule>(*plugin_ctx);

    // get registered modules and create subscriptions
    auto& modules = registry.getRegisteredModules();
    for (auto& mod : modules) {
        SRPLG_LOG_INF(ietf::acl::PLUGIN_NAME, "Registering operational callbacks for module %s", mod->getName());
        registerOperationalSubscriptions(sess, *plugin_ctx, mod);
        SRPLG_LOG_INF(ietf::acl::PLUGIN_NAME, "Registering module change callbacks for module %s", mod->getName());
        registerModuleChangeSubscriptions(sess, *plugin_ctx, mod);
        SRPLG_LOG_INF(ietf::acl::PLUGIN_NAME, "Registering RPC callbacks for module %s", mod->getName());
        registerRpcSubscriptions(sess, *plugin_ctx, mod);
        SRPLG_LOG_INF(ietf::acl::PLUGIN_NAME, "Registered module %s", mod->getName());
    }

    SRPLG_LOG_INF(ietf::acl::PLUGIN_NAME, "Created plugin subscriptions");

    // Load and process existing ACL data from the datastore
    loadExistingACLs(sess);

    return static_cast<int>(error);
}

void sr_plugin_cleanup_cb(sr_session_ctx_t* session, void* priv)
{
    SRPLG_LOG_INF(ietf::acl::PLUGIN_NAME, "Plugin cleanup called");

    auto& registry(srpc::ModuleRegistry<ietf::acl::PluginContext>::getInstance());
    auto plugin_ctx = static_cast<ietf::acl::PluginContext*>(priv);

    auto& modules = registry.getRegisteredModules();
    for (auto& mod : modules) {
        SRPLG_LOG_INF(ietf::acl::PLUGIN_NAME, "Cleaning up module: %s", mod->getName());
    }

    delete plugin_ctx;

    SRPLG_LOG_INF(ietf::acl::PLUGIN_NAME, "Plugin cleanup finished");
}
