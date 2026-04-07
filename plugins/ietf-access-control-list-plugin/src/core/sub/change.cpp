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

#include "change.hpp"
#include "sysrepo.h"
#include <iostream>
#include "core/nftables.hpp"
#include "core/nft_helper.hpp"
#include <list>

namespace ietf::acl {
    namespace sub::change {

        /**
         * Helper function to check if the parent ACL is being deleted.
         * When deleting the whole ACL, child node deletions should be skipped
         * since the table deletion will clean up everything in nftables.
         *
         * @param session The sysrepo session.
         * @param table_name The ACL/table name to check.
         * @return true if the parent ACL's type node is being deleted.
         */
        static bool isParentAclDeleted(sr::Session& session, const std::string& table_name) {
            for (sr::Change deleted_change : session.getChanges(
                "/ietf-access-control-list:acls/acl[name='" + table_name + "']/type")) {
                if (deleted_change.operation == sr::ChangeOperation::Deleted) {
                    return true;
                }
            }
            return false;
        }

        /**
         * Helper function to convert IANA operator to nftables operator.
         *
         * @param iana_op The IANA operator string (eq, neq, lte, gte).
         * @return The nftables operator string (==, !=, <=, >=), or empty if unknown.
         */
        static std::string ianaToNftOperator(const std::string& iana_op) {
            if (iana_op == "eq") return "==";
            if (iana_op == "neq") return "!=";
            if (iana_op == "lte") return "<=";
            if (iana_op == "gte") return ">=";
            return "";
        }

        /**
         * Helper function to get the operator for a port rule from the sibling node.
         * The port xpath is like: .../destination-port/port
         * The operator xpath is: .../destination-port/operator
         *
         * @param session The sysrepo session.
         * @param port_xpath The xpath to the port node.
         * @return The nftables operator string, or empty if not found.
         */
        static std::string getPortOperator(sr::Session& session, const std::string& port_xpath) {
            // Replace "/port" at the end with "/operator"
            std::string op_xpath = port_xpath;
            size_t pos = op_xpath.rfind("/port");
            if (pos != std::string::npos) {
                op_xpath.replace(pos, 5, "/operator");
                try {
                    auto op_node = session.getOneNode(op_xpath.c_str());
                    std::string iana_op = op_node.asTerm().valueStr().data();
                    return ianaToNftOperator(iana_op);
                }
                catch (...) {
                    // Operator node doesn't exist (using range instead)
                    return "";
                }
            }
            return "";
        }

        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin module change context.
         *
         */
        AclModuleChangeCb::AclModuleChangeCb(std::shared_ptr<AclModuleChangesContext> ctx) { m_ctx = ctx; }

        /**
         * sysrepo-plugin-generator: Generated module change operator() for path /ietf-access-control-list:acls/acl[name='%s'].
         *
         * @param session An implicit session for the callback.
         * @param subscriptionId ID the subscription associated with the callback.
         * @param moduleName The module name used for subscribing.
         * @param subXPath The optional xpath used at the time of subscription.
         * @param event Type of the event that has occured.
         * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
         * SR_EV_DONE, for example) have the same request ID.
         *
         * @return Error code.
         *
         */
        sr::ErrorCode AclModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
            std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
        {
            sr::ErrorCode error = sr::ErrorCode::Ok;

            switch (event) {
            case sr::Event::Change: {

                for (sysrepo::Change change : session.getChanges(std::string(subXPath->data()).append("/name"))) {

                    std::string table_name = change.node.asTerm().valueStr().data();
                    std::string table_type_str;

                    NFT_Types type = NFT_Types::NFT_INVALID_TYPE;
                    bool type_found = false;
                    //find the type value in the tree
                    for (const libyang::DataNode& node : change.node.siblings()) {
                        if (node.schema().name() == "type") {
                            type_found = true;
                            table_type_str = node.asTerm().valueStr().data();
                            break;
                        }
                    }

                    if (!type_found) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot obtain /acl/type[name='%s'] node", table_name.c_str());
                        return sr::ErrorCode::NotFound;
                    }

                    type = nft::helper::ianaToNFTType(table_type_str);
                    if (type == NFT_Types::NFT_INVALID_TYPE) {
                        //type cannot be obtained
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Invalid type %s on table %s", table_type_str.c_str(), table_name.c_str());
                        return sr::ErrorCode::NotFound;
                    }

                    NFTables nft;

                    switch (change.operation) {
                    case sr::ChangeOperation::Created: {

                        nft.addTable(table_name, type);

                        break;
                    }
                    case sr::ChangeOperation::Deleted:
                        //delete table
                        try {
                            nft.deleteTable(table_name, type);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }

                        break;

                    default:
                        break;
                    }

                }
                break;
            }
            default:
                break;
            }
            return error;
        }

        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin module change context.
         *
         */
        AclAcesAceModuleChangeCb::AclAcesAceModuleChangeCb(std::shared_ptr<AclModuleChangesContext> ctx) { m_ctx = ctx; }

        /**
         * sysrepo-plugin-generator: Generated module change operator() for path /ietf-access-control-list:acls/acl[name='%s'].
         *
         * @param session An implicit session for the callback.
         * @param subscriptionId ID the subscription associated with the callback.
         * @param moduleName The module name used for subscribing.
         * @param subXPath The optional xpath used at the time of subscription.
         * @param event Type of the event that has occured.
         * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
         * SR_EV_DONE, for example) have the same request ID.
         *
         * @return Error code.
         *
         */
        sr::ErrorCode AclAcesAceModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
            std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
        {
            sr::ErrorCode error = sr::ErrorCode::Ok;

            switch (event) {
            case sr::Event::Change: {

                for (sysrepo::Change change : session.getChanges(std::string(subXPath->data()).append("/name"))) {

                    std::string name_key = srpc::extractListKeysFromXpath("acl", change.node.path().data())["name"];
                    std::string chain_name = change.node.asTerm().valueStr().data();
                    std::string nft_policy_str;

                    NFTables nftables;

                    //now here obtain the mandatory field policy
                    for (const libyang::DataNode& node : change.node.siblings()) {
                        if (node.schema().name() == "actions") {
                            for (const libyang::DataNode& act_node : node.childrenDfs()) {
                                if (act_node.schema().name() == "forwarding") {
                                    nft_policy_str = act_node.asTerm().valueStr().data();
                                }
                            }
                        }
                    }

                    NFT_Chain_Policy policy = nft::helper::ianaToPolicyType(nft_policy_str);

                    switch (change.operation) {
                    case sr::ChangeOperation::Created: {
                        std::string type_str;

                        std::cout << "Created chain" << std::endl;

                        try {
                            auto type_node = session.getOneNode("/ietf-access-control-list:acls/acl[name='" + name_key + "']/type");
                            type_str = type_node.asTerm().valueStr().data();
                        }
                        catch (...) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot obtain /acl[name='%s']/type node", name_key.c_str());
                            return sr::ErrorCode::CallbackFailed;
                        }

                        NFT_Types type = nft::helper::ianaToNFTType(type_str);

                        if (type == NFT_Types::NFT_INVALID_TYPE) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, "Invalid type %s !", type_str.c_str());
                            return sr::ErrorCode::CallbackFailed;
                        }

                        std::optional<NFTTable> table = nftables.getTable(name_key, type);
                        if (!table) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, "Table %s %s does not exist!", utils::getString<NFT_Types>(type).c_str(), name_key.c_str());
                            return sr::ErrorCode::CallbackFailed;
                        }

                        try {
                            table->addChain(chain_name, NFT_Chain_Types::CHAIN_FILTER, NFT_Chain_Hooks::CH_HOOK_INPUT, 0, policy);
                        }
                        catch (...) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, "Failed to create chain %s", chain_name.c_str());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Deleted: {

                        //check here if the table is deleted,so there is no point of deleting the chain
                        bool is_table_deleted = false;
                        for (sr::Change deleted_change : session.getChanges("/ietf-access-control-list:acls/acl[name='" + name_key + "']/type")) {
                            if (deleted_change.operation == sr::ChangeOperation::Deleted) {
                                is_table_deleted = true;
                                break;
                            }
                        }
                        if (!is_table_deleted) {
                            std::string type_str;
                            try {
                                auto type_node = session.getOneNode("/ietf-access-control-list:acls/acl[name='" + name_key + "']/type");
                                type_str = type_node.asTerm().valueStr().data();
                            }
                            catch (...) {
                                SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot obtain /acl[name='%s']/type node", name_key.c_str());
                                return sr::ErrorCode::CallbackFailed;
                            }

                            NFT_Types type = nft::helper::ianaToNFTType(type_str);

                            if (type == NFT_Types::NFT_INVALID_TYPE) {
                                SRPLG_LOG_ERR(PLUGIN_NAME, "Invalid type %s !", type_str.c_str());
                                return sr::ErrorCode::CallbackFailed;
                            };

                            std::optional<NFTTable> table = nftables.getTable(name_key, type);
                            if (!table) {
                                SRPLG_LOG_ERR(PLUGIN_NAME, "Table %s %s does not exist!", utils::getString<NFT_Types>(type).c_str(), name_key.c_str());
                                return sr::ErrorCode::CallbackFailed;
                            }
                            try {
                                table->deleteChain(type, name_key, chain_name);
                            }
                            catch (...) {
                                SRPLG_LOG_ERR(PLUGIN_NAME, "Failed to delete chain %s", chain_name.c_str());
                                return sr::ErrorCode::CallbackFailed;
                            }
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }

                break;
            }
            default:
                break;
            }
            return error;
        }

        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin module change context.
         *
         */
        AclAceActFwModuleChangeCb::AclAceActFwModuleChangeCb(std::shared_ptr<AclModuleChangesContext> ctx) { m_ctx = ctx; }

        /**
         * sysrepo-plugin-generator: Generated module change operator() for path
         * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s'].
         *
         * @param session An implicit session for the callback.
         * @param subscriptionId ID the subscription associated with the callback.
         * @param moduleName The module name used for subscribing.
         * @param subXPath The optional xpath used at the time of subscription.
         * @param event Type of the event that has occured.
         * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
         * SR_EV_DONE, for example) have the same request ID.
         *
         * @return Error code.
         *
         */
        sr::ErrorCode AclAceActFwModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
            std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
        {
            sr::ErrorCode error = sr::ErrorCode::Ok;

            switch (event) {
            case sr::Event::Change: {

                for (sr::Change change : session.getChanges(subXPath->data())) {

                    switch (change.operation) {
                        //Forwarding node can just be modified
                    case sr::ChangeOperation::Modified: {
                        std::string type_str;
                        std::string table_name = srpc::extractListKeysFromXpath("acl", change.node.path())["name"];

                        try {
                            auto type_node = session.getOneNode("/ietf-access-control-list:acls/acl[name='" + table_name + "']/type");
                            type_str = type_node.asTerm().valueStr().data();
                        }
                        catch (...) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot obtain /acl[name='%s']/type node", table_name.c_str());
                            return sr::ErrorCode::CallbackFailed;
                        }

                        NFT_Types table_type = nft::helper::ianaToNFTType(type_str);

                        std::string chain_name = srpc::extractListKeysFromXpath("ace", change.node.path())["name"];

                        NFTables nftables;

                        auto nft_table = nftables.getTable(table_name, table_type);

                        if (!nft_table) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot find table %s!", table_name.c_str());
                            return sr::ErrorCode::CallbackFailed;
                        }

                        auto nft_chain = nft_table->findChain(chain_name);

                        if (!nft_chain) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot find chain %s!", chain_name.c_str());
                            return sr::ErrorCode::CallbackFailed;
                        }

                        try {
                            NFT_Chain_Policy policy = nft::helper::ianaToPolicyType(change.node.asTerm().valueStr().data());
                            nft_chain->updateChainPolicy(policy);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        catch (...) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, "Failed to update policy on chain %s", chain_name.c_str());
                            return sr::ErrorCode::CallbackFailed;
                        }

                        break;
                    }
                    default:
                        break;

                    }

                }

                break;
            }
            default:
                break;
            }

            return error;
        }

        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin module change context.
         *
         */
        AclAceAcesMatchEthModuleChangeCb::AclAceAcesMatchEthModuleChangeCb(std::shared_ptr<AclModuleChangesContext> ctx) { m_ctx = ctx; }

        /**
         * sysrepo-plugin-generator: Generated module change operator() for path
         * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s'].
         *
         * @param session An implicit session for the callback.
         * @param subscriptionId ID the subscription associated with the callback.
         * @param moduleName The module name used for subscribing.
         * @param subXPath The optional xpath used at the time of subscription.
         * @param event Type of the event that has occured.
         * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
         * SR_EV_DONE, for example) have the same request ID.
         *
         * @return Error code.
         *
         */
        sr::ErrorCode AclAceAcesMatchEthModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
            std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
        {
            sr::ErrorCode error = sr::ErrorCode::Ok;

            switch (event) {
            case sr::Event::Change: {

                //destination mac address
                for (sr::Change change : session.getChanges(std::string(subXPath->data()).append("/destination-mac-address"))) {

                    //we have to get the table type, table name, chain, and rule

                    //obtaining table name
                    std::string table_name = srpc::extractListKeysFromXpath("acl", change.node.path())["name"];

                    //obtaining chain name
                    std::string chain_name = srpc::extractListKeysFromXpath("ace", change.node.path())["name"];

                    // Skip if parent ACL is being deleted
                    if (change.operation == sr::ChangeOperation::Deleted && isParentAclDeleted(session, table_name)) {
                        continue;
                    }

                    std::string type_str;

                    //obtaining table type
                    try {
                        auto type_node = session.getOneNode("/ietf-access-control-list:acls/acl[name='" + table_name + "']/type");
                        type_str = type_node.asTerm().valueStr().data();
                    }
                    catch (...) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot obtain /acl[name='%s']/type node", table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    NFTables nft;

                    NFT_Types table_type = nft::helper::ianaToNFTType(type_str);

                    if (table_type == NFT_Types::NFT_INVALID_TYPE) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Invalid type %s !", type_str.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    };

                    //obtaining table
                    std::optional<NFTTable> table = nft.getTable(table_name, table_type);
                    if (!table) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Table %s %s does not exist!", utils::getString<NFT_Types>(table_type).c_str(), table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    //obtaining chain
                    std::optional<NFTChain> chain = table->findChain(chain_name);
                    if (!chain) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Chain %s does not exist!", chain_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    Match rule;

                    switch (change.operation) {
                        //Forwarding node can just be modified
                    case sr::ChangeOperation::Created: {
                        std::string mac = change.node.asTerm().valueStr().data();
                        //constructing rule
                        rule.Protocol("ether").Field("daddr").Value(mac);
                        try {
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Modified: {
                        std::string mac = change.node.asTerm().valueStr().data();
                        std::string old_mac = change.previousValue->data();
                        rule.Protocol("ether").Field("daddr").Value(mac);
                        try {
                            chain->deleteRule(Match().Protocol("ether").Field("daddr").Value(old_mac));
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Deleted: {
                        std::string mac = change.node.asTerm().valueStr().data();
                        rule.Protocol("ether").Field("daddr").Value(mac);
                        try {
                            chain->deleteRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }

                        break;
                    }
                    default:
                        break;

                    }

                }

                //source mac address
                for (sr::Change change : session.getChanges(std::string(subXPath->data()).append("/source-mac-address"))) {

                    //we have to get the table type, table name, chain, and rule

                    //obtaining table name
                    std::string table_name = srpc::extractListKeysFromXpath("acl", change.node.path())["name"];

                    //obtaining chain name
                    std::string chain_name = srpc::extractListKeysFromXpath("ace", change.node.path())["name"];

                    // Skip if parent ACL is being deleted
                    if (change.operation == sr::ChangeOperation::Deleted && isParentAclDeleted(session, table_name)) {
                        continue;
                    }

                    std::string type_str;

                    //obtaining table type
                    try {
                        auto type_node = session.getOneNode("/ietf-access-control-list:acls/acl[name='" + table_name + "']/type");
                        type_str = type_node.asTerm().valueStr().data();
                    }
                    catch (...) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot obtain /acl[name='%s']/type node", table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    NFTables nft;

                    NFT_Types table_type = nft::helper::ianaToNFTType(type_str);

                    if (table_type == NFT_Types::NFT_INVALID_TYPE) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Invalid type %s !", type_str.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    };

                    //obtaining table
                    std::optional<NFTTable> table = nft.getTable(table_name, table_type);
                    if (!table) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Table %s %s does not exist!", utils::getString<NFT_Types>(table_type).c_str(), table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    //obtaining chain
                    std::optional<NFTChain> chain = table->findChain(chain_name);
                    if (!chain) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Chain %s does not exist!", chain_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    Match rule;

                    switch (change.operation) {
                        //Forwarding node can just be modified
                    case sr::ChangeOperation::Created: {
                        std::string mac = change.node.asTerm().valueStr().data();
                        //constructing rule
                        rule.Protocol("ether").Field("saddr").Value(mac);
                        try {
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Modified: {
                        std::string mac = change.node.asTerm().valueStr().data();
                        std::string old_mac = change.previousValue->data();
                        rule.Protocol("ether").Field("daddr").Value(mac);
                        try {
                            chain->deleteRule(Match().Protocol("ether").Field("saddr").Value(old_mac));
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Deleted: {
                        std::string mac = change.node.asTerm().valueStr().data();
                        rule.Protocol("ether").Field("saddr").Value(mac);
                        try {
                            chain->deleteRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }

                        break;
                    }
                    default:
                        break;

                    }

                }

                //ethertype

                //[TODO]: ethertype should be fixed, bug in the nftables api, when returned json numerical values
                // the hex to numerical is incorrect!
                for (sr::Change change : session.getChanges(std::string(subXPath->data()).append("/ethertype"))) {

                    //we have to get the table type, table name, chain, and rule

                    //obtaining table name
                    std::string table_name = srpc::extractListKeysFromXpath("acl", change.node.path())["name"];

                    //obtaining chain name
                    std::string chain_name = srpc::extractListKeysFromXpath("ace", change.node.path())["name"];

                    // Skip if parent ACL is being deleted
                    if (change.operation == sr::ChangeOperation::Deleted && isParentAclDeleted(session, table_name)) {
                        continue;
                    }

                    std::string type_str;

                    //obtaining table type
                    try {
                        auto type_node = session.getOneNode("/ietf-access-control-list:acls/acl[name='" + table_name + "']/type");
                        type_str = type_node.asTerm().valueStr().data();
                    }
                    catch (...) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot obtain /acl[name='%s']/type node", table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    NFTables nft;

                    NFT_Types table_type = nft::helper::ianaToNFTType(type_str);

                    if (table_type == NFT_Types::NFT_INVALID_TYPE) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Invalid type %s !", type_str.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    };

                    //obtaining table
                    std::optional<NFTTable> table = nft.getTable(table_name, table_type);
                    if (!table) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Table %s %s does not exist!", utils::getString<NFT_Types>(table_type).c_str(), table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    //obtaining chain
                    std::optional<NFTChain> chain = table->findChain(chain_name);
                    if (!chain) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Chain %s does not exist!", chain_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    Match rule;

                    switch (change.operation) {
                        //Forwarding node can just be modified
                    case sr::ChangeOperation::Created: {
                        std::string vlan = change.node.asTerm().valueStr().data();
                        //constructing rule
                        rule.Protocol("ether").Field("type").Value(vlan);
                        try {
                            // chain->addRule(rule);
                            
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Modified: {
                        std::string vlan = change.node.asTerm().valueStr().data();
                        std::string old_vlan = change.previousValue->data();
                        rule.Protocol("ether").Field("type").Value(vlan);
                        try {
                            // chain->deleteRule(Match().Protocol("ether").Field("type").Value(old_vlan));
                            // chain->addRule(rule);

                            libyang::Value val;
                            std::cout<<"get val: "<<std::get<uint32_t>(change.node.asTerm().value())<<std::endl;
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Deleted: {
                        std::string vlan = change.node.asTerm().valueStr().data();
                        rule.Protocol("ether").Field("type").Value(vlan);
                        try {
                            // chain->deleteRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }

                        break;
                    }
                    default:
                        break;

                    }

                }

                break;
            }
            default:
                break;
            }

            return error;
        }

        /**
         * @param ctx Plugin module change context.
         *
         */
        AclAceAcesMatchIpv4ModuleChangeCb::AclAceAcesMatchIpv4ModuleChangeCb(std::shared_ptr<AclModuleChangesContext> ctx) { m_ctx = ctx; }

        /**
         * /ietf-access-control-list:acls/acl/aces/ace/matches/ipv4.
         *
         * @param session An implicit session for the callback.
         * @param subscriptionId ID the subscription associated with the callback.
         * @param moduleName The module name used for subscribing.
         * @param subXPath The optional xpath used at the time of subscription.
         * @param event Type of the event that has occured.
         * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
         * SR_EV_DONE, for example) have the same request ID.
         *
         * @return Error code.
         *
         */
        sr::ErrorCode AclAceAcesMatchIpv4ModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
            std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
        {
            sr::ErrorCode error = sr::ErrorCode::Ok;

            switch (event) {
            case sr::Event::Change: {

                // dscp
                for (sr::Change change : session.getChanges(std::string(subXPath->data()).append("/dscp"))) {

                    std::string table_name = srpc::extractListKeysFromXpath("acl", change.node.path().data())["name"];
                    std::string chain_name = srpc::extractListKeysFromXpath("ace", change.node.path().data())["name"];

                    // Skip if parent ACL is being deleted
                    if (change.operation == sr::ChangeOperation::Deleted && isParentAclDeleted(session, table_name)) {
                        continue;
                    }

                    std::string type_str;

                    try {
                        auto type_node = session.getOneNode("/ietf-access-control-list:acls/acl[name='" + table_name + "']/type");
                        type_str = type_node.asTerm().valueStr().data();
                    }
                    catch (...) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot obtain /acl[name='%s']/type node", table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    NFTables nft;

                    NFT_Types table_type = nft::helper::ianaToNFTType(type_str);

                    if (table_type == NFT_Types::NFT_INVALID_TYPE) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Invalid type %s !", type_str.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    };

                    std::optional<NFTTable> table = nft.getTable(table_name, table_type);
                    if (!table) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Table %s %s does not exist!", utils::getString<NFT_Types>(table_type).c_str(), table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    std::optional<NFTChain> chain = table->findChain(chain_name);
                    if (!chain) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Chain %s does not exist!", chain_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    Match rule;

                    switch (change.operation) {
                    case sr::ChangeOperation::Created: {
                        std::string dscp = change.node.asTerm().valueStr().data();
                        rule.Protocol("ip").Field("dscp").Value(dscp);
                        try {
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Modified: {
                        std::string dscp = change.node.asTerm().valueStr().data();
                        std::string old_dscp = change.previousValue->data();
                        rule.Protocol("ip").Field("dscp").Value(dscp);
                        try {
                            chain->deleteRule(Match().Protocol("ip").Field("dscp").Value(old_dscp));
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Deleted: {
                        std::string dscp = change.node.asTerm().valueStr().data();
                        rule.Protocol("ip").Field("dscp").Value(dscp);
                        try {
                            chain->deleteRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }

                // length
                for (sr::Change change : session.getChanges(std::string(subXPath->data()).append("/length"))) {

                    std::string table_name = srpc::extractListKeysFromXpath("acl", change.node.path().data())["name"];
                    std::string chain_name = srpc::extractListKeysFromXpath("ace", change.node.path().data())["name"];

                    // Skip if parent ACL is being deleted
                    if (change.operation == sr::ChangeOperation::Deleted && isParentAclDeleted(session, table_name)) {
                        continue;
                    }

                    std::string type_str;

                    try {
                        auto type_node = session.getOneNode("/ietf-access-control-list:acls/acl[name='" + table_name + "']/type");
                        type_str = type_node.asTerm().valueStr().data();
                    }
                    catch (...) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot obtain /acl[name='%s']/type node", table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    NFTables nft;

                    NFT_Types table_type = nft::helper::ianaToNFTType(type_str);

                    if (table_type == NFT_Types::NFT_INVALID_TYPE) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Invalid type %s !", type_str.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    };

                    std::optional<NFTTable> table = nft.getTable(table_name, table_type);
                    if (!table) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Table %s %s does not exist!", utils::getString<NFT_Types>(table_type).c_str(), table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    std::optional<NFTChain> chain = table->findChain(chain_name);
                    if (!chain) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Chain %s does not exist!", chain_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    Match rule;

                    switch (change.operation) {
                    case sr::ChangeOperation::Created: {
                        std::string length = change.node.asTerm().valueStr().data();
                        rule.Protocol("ip").Field("length").Value(length);
                        try {
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Modified: {
                        std::string length = change.node.asTerm().valueStr().data();
                        std::string old_length = change.previousValue->data();
                        rule.Protocol("ip").Field("length").Value(length);
                        try {
                            chain->deleteRule(Match().Protocol("ip").Field("length").Value(old_length));
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Deleted: {
                        std::string length = change.node.asTerm().valueStr().data();
                        rule.Protocol("ip").Field("length").Value(length);
                        try {
                            chain->deleteRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }

                // ttl
                for (sr::Change change : session.getChanges(std::string(subXPath->data()).append("/ttl"))) {

                    std::string table_name = srpc::extractListKeysFromXpath("acl", change.node.path().data())["name"];
                    std::string chain_name = srpc::extractListKeysFromXpath("ace", change.node.path().data())["name"];

                    // Skip if parent ACL is being deleted
                    if (change.operation == sr::ChangeOperation::Deleted && isParentAclDeleted(session, table_name)) {
                        continue;
                    }

                    std::string type_str;

                    try {
                        auto type_node = session.getOneNode("/ietf-access-control-list:acls/acl[name='" + table_name + "']/type");
                        type_str = type_node.asTerm().valueStr().data();
                    }
                    catch (...) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot obtain /acl[name='%s']/type node", table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    NFTables nft;

                    NFT_Types table_type = nft::helper::ianaToNFTType(type_str);

                    if (table_type == NFT_Types::NFT_INVALID_TYPE) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Invalid type %s !", type_str.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    };

                    std::optional<NFTTable> table = nft.getTable(table_name, table_type);
                    if (!table) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Table %s %s does not exist!", utils::getString<NFT_Types>(table_type).c_str(), table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    std::optional<NFTChain> chain = table->findChain(chain_name);
                    if (!chain) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Chain %s does not exist!", chain_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    Match rule;

                    switch (change.operation) {
                    case sr::ChangeOperation::Created: {
                        std::string ttl = change.node.asTerm().valueStr().data();
                        rule.Protocol("ip").Field("ttl").Value(ttl);
                        try {
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Modified: {
                        std::string ttl = change.node.asTerm().valueStr().data();
                        std::string old_ttl = change.previousValue->data();
                        rule.Protocol("ip").Field("ttl").Value(ttl);
                        try {
                            chain->deleteRule(Match().Protocol("ip").Field("ttl").Value(old_ttl));
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Deleted: {
                        std::string ttl = change.node.asTerm().valueStr().data();
                        rule.Protocol("ip").Field("ttl").Value(ttl);
                        try {
                            chain->deleteRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }

                // protocol
                for (sr::Change change : session.getChanges(std::string(subXPath->data()).append("/protocol"))) {

                    std::string table_name = srpc::extractListKeysFromXpath("acl", change.node.path().data())["name"];
                    std::string chain_name = srpc::extractListKeysFromXpath("ace", change.node.path().data())["name"];

                    // Skip if parent ACL is being deleted
                    if (change.operation == sr::ChangeOperation::Deleted && isParentAclDeleted(session, table_name)) {
                        continue;
                    }

                    std::string type_str;

                    try {
                        auto type_node = session.getOneNode("/ietf-access-control-list:acls/acl[name='" + table_name + "']/type");
                        type_str = type_node.asTerm().valueStr().data();
                    }
                    catch (...) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot obtain /acl[name='%s']/type node", table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    NFTables nft;

                    NFT_Types table_type = nft::helper::ianaToNFTType(type_str);

                    if (table_type == NFT_Types::NFT_INVALID_TYPE) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Invalid type %s !", type_str.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    };

                    std::optional<NFTTable> table = nft.getTable(table_name, table_type);
                    if (!table) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Table %s %s does not exist!", utils::getString<NFT_Types>(table_type).c_str(), table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    std::optional<NFTChain> chain = table->findChain(chain_name);
                    if (!chain) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Chain %s does not exist!", chain_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    Match rule;

                    switch (change.operation) {
                    case sr::ChangeOperation::Created: {
                        std::string protocol = change.node.asTerm().valueStr().data();
                        rule.Protocol("ip").Field("protocol").Value(protocol);
                        try {
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Modified: {
                        std::string protocol = change.node.asTerm().valueStr().data();
                        std::string old_protocol = change.previousValue->data();
                        rule.Protocol("ip").Field("protocol").Value(protocol);
                        try {
                            chain->deleteRule(Match().Protocol("ip").Field("protocol").Value(old_protocol));
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Deleted: {
                        std::string protocol = change.node.asTerm().valueStr().data();
                        rule.Protocol("ip").Field("protocol").Value(protocol);
                        try {
                            chain->deleteRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }

                // ihl
                for (sr::Change change : session.getChanges(std::string(subXPath->data()).append("/ihl"))) {

                    std::string table_name = srpc::extractListKeysFromXpath("acl", change.node.path().data())["name"];
                    std::string chain_name = srpc::extractListKeysFromXpath("ace", change.node.path().data())["name"];

                    // Skip if parent ACL is being deleted
                    if (change.operation == sr::ChangeOperation::Deleted && isParentAclDeleted(session, table_name)) {
                        continue;
                    }

                    std::string type_str;

                    try {
                        auto type_node = session.getOneNode("/ietf-access-control-list:acls/acl[name='" + table_name + "']/type");
                        type_str = type_node.asTerm().valueStr().data();
                    }
                    catch (...) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot obtain /acl[name='%s']/type node", table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    NFTables nft;

                    NFT_Types table_type = nft::helper::ianaToNFTType(type_str);

                    if (table_type == NFT_Types::NFT_INVALID_TYPE) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Invalid type %s !", type_str.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    };

                    std::optional<NFTTable> table = nft.getTable(table_name, table_type);
                    if (!table) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Table %s %s does not exist!", utils::getString<NFT_Types>(table_type).c_str(), table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    std::optional<NFTChain> chain = table->findChain(chain_name);
                    if (!chain) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Chain %s does not exist!", chain_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    Match rule;

                    switch (change.operation) {
                    case sr::ChangeOperation::Created: {
                        std::string ihl = change.node.asTerm().valueStr().data();
                        rule.Protocol("ip").Field("hdrlength").Value(ihl);
                        try {
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Modified: {
                        std::string ihl = change.node.asTerm().valueStr().data();
                        std::string old_ihl = change.previousValue->data();
                        rule.Protocol("ip").Field("hdrlength").Value(ihl);
                        try {
                            chain->deleteRule(Match().Protocol("ip").Field("hdrlength").Value(old_ihl));
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Deleted: {
                        std::string ihl = change.node.asTerm().valueStr().data();
                        rule.Protocol("ip").Field("hdrlength").Value(ihl);
                        try {
                            chain->deleteRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }

                // destination-ipv4-network
                for (sr::Change change : session.getChanges(std::string(subXPath->data()).append("/destination-ipv4-network"))) {

                    std::string table_name = srpc::extractListKeysFromXpath("acl", change.node.path().data())["name"];
                    std::string chain_name = srpc::extractListKeysFromXpath("ace", change.node.path().data())["name"];

                    // Skip if parent ACL is being deleted
                    if (change.operation == sr::ChangeOperation::Deleted && isParentAclDeleted(session, table_name)) {
                        continue;
                    }

                    std::string type_str;

                    try {
                        auto type_node = session.getOneNode("/ietf-access-control-list:acls/acl[name='" + table_name + "']/type");
                        type_str = type_node.asTerm().valueStr().data();
                    }
                    catch (...) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot obtain /acl[name='%s']/type node", table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    NFTables nft;

                    NFT_Types table_type = nft::helper::ianaToNFTType(type_str);

                    if (table_type == NFT_Types::NFT_INVALID_TYPE) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Invalid type %s !", type_str.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    };

                    std::optional<NFTTable> table = nft.getTable(table_name, table_type);
                    if (!table) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Table %s %s does not exist!", utils::getString<NFT_Types>(table_type).c_str(), table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    std::optional<NFTChain> chain = table->findChain(chain_name);
                    if (!chain) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Chain %s does not exist!", chain_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    Match rule;

                    switch (change.operation) {
                    case sr::ChangeOperation::Created: {
                        std::string daddr = change.node.asTerm().valueStr().data();
                        rule.Protocol("ip").Field("daddr").Value(daddr);
                        try {
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Modified: {
                        std::string daddr = change.node.asTerm().valueStr().data();
                        std::string old_daddr = change.previousValue->data();
                        rule.Protocol("ip").Field("daddr").Value(daddr);
                        try {
                            chain->deleteRule(Match().Protocol("ip").Field("daddr").Value(old_daddr));
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Deleted: {
                        std::string daddr = change.node.asTerm().valueStr().data();
                        rule.Protocol("ip").Field("daddr").Value(daddr);
                        try {
                            chain->deleteRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }

                // source-ipv4-network
                for (sr::Change change : session.getChanges(std::string(subXPath->data()).append("/source-ipv4-network"))) {

                    std::string table_name = srpc::extractListKeysFromXpath("acl", change.node.path().data())["name"];
                    std::string chain_name = srpc::extractListKeysFromXpath("ace", change.node.path().data())["name"];

                    // Skip if parent ACL is being deleted
                    if (change.operation == sr::ChangeOperation::Deleted && isParentAclDeleted(session, table_name)) {
                        continue;
                    }

                    std::string type_str;

                    try {
                        auto type_node = session.getOneNode("/ietf-access-control-list:acls/acl[name='" + table_name + "']/type");
                        type_str = type_node.asTerm().valueStr().data();
                    }
                    catch (...) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot obtain /acl[name='%s']/type node", table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    NFTables nft;

                    NFT_Types table_type = nft::helper::ianaToNFTType(type_str);

                    if (table_type == NFT_Types::NFT_INVALID_TYPE) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Invalid type %s !", type_str.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    };

                    std::optional<NFTTable> table = nft.getTable(table_name, table_type);
                    if (!table) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Table %s %s does not exist!", utils::getString<NFT_Types>(table_type).c_str(), table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    std::optional<NFTChain> chain = table->findChain(chain_name);
                    if (!chain) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Chain %s does not exist!", chain_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    Match rule;

                    switch (change.operation) {
                    case sr::ChangeOperation::Created: {
                        std::string saddr = change.node.asTerm().valueStr().data();
                        rule.Protocol("ip").Field("saddr").Value(saddr);
                        try {
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Modified: {
                        std::string saddr = change.node.asTerm().valueStr().data();
                        std::string old_saddr = change.previousValue->data();
                        rule.Protocol("ip").Field("saddr").Value(saddr);
                        try {
                            chain->deleteRule(Match().Protocol("ip").Field("saddr").Value(old_saddr));
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Deleted: {
                        std::string saddr = change.node.asTerm().valueStr().data();
                        rule.Protocol("ip").Field("saddr").Value(saddr);
                        try {
                            chain->deleteRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }

                break;
            }
            default:
                break;
            }

            return error;
        }

        /**
         * @param ctx Plugin module change context.
         *
         */
        AclAceAcesMatchIpv6ModuleChangeCb::AclAceAcesMatchIpv6ModuleChangeCb(std::shared_ptr<AclModuleChangesContext> ctx) { m_ctx = ctx; }

        /**
         * /ietf-access-control-list:acls/acl/aces/ace/matches/ipv6.
         *
         * @param session An implicit session for the callback.
         * @param subscriptionId ID the subscription associated with the callback.
         * @param moduleName The module name used for subscribing.
         * @param subXPath The optional xpath used at the time of subscription.
         * @param event Type of the event that has occured.
         * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
         * SR_EV_DONE, for example) have the same request ID.
         *
         * @return Error code.
         *
         */
        sr::ErrorCode AclAceAcesMatchIpv6ModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
            std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
        {
            sr::ErrorCode error = sr::ErrorCode::Ok;

            switch (event) {
            case sr::Event::Change: {

                // dscp
                for (sr::Change change : session.getChanges(std::string(subXPath->data()).append("/dscp"))) {

                    std::string table_name = srpc::extractListKeysFromXpath("acl", change.node.path().data())["name"];
                    std::string chain_name = srpc::extractListKeysFromXpath("ace", change.node.path().data())["name"];

                    // Skip if parent ACL is being deleted
                    if (change.operation == sr::ChangeOperation::Deleted && isParentAclDeleted(session, table_name)) {
                        continue;
                    }

                    std::string type_str;

                    try {
                        auto type_node = session.getOneNode("/ietf-access-control-list:acls/acl[name='" + table_name + "']/type");
                        type_str = type_node.asTerm().valueStr().data();
                    }
                    catch (...) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot obtain /acl[name='%s']/type node", table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    NFTables nft;

                    NFT_Types table_type = nft::helper::ianaToNFTType(type_str);

                    if (table_type == NFT_Types::NFT_INVALID_TYPE) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Invalid type %s !", type_str.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    };

                    std::optional<NFTTable> table = nft.getTable(table_name, table_type);
                    if (!table) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Table %s %s does not exist!", utils::getString<NFT_Types>(table_type).c_str(), table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    std::optional<NFTChain> chain = table->findChain(chain_name);
                    if (!chain) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Chain %s does not exist!", chain_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    Match rule;

                    switch (change.operation) {
                    case sr::ChangeOperation::Created: {
                        std::string dscp = change.node.asTerm().valueStr().data();
                        rule.Protocol("ip6").Field("dscp").Value(dscp);
                        try {
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Modified: {
                        std::string dscp = change.node.asTerm().valueStr().data();
                        std::string old_dscp = change.previousValue->data();
                        rule.Protocol("ip6").Field("dscp").Value(dscp);
                        try {
                            chain->deleteRule(Match().Protocol("ip6").Field("dscp").Value(old_dscp));
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Deleted: {
                        std::string dscp = change.node.asTerm().valueStr().data();
                        rule.Protocol("ip6").Field("dscp").Value(dscp);
                        try {
                            chain->deleteRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }

                // length
                for (sr::Change change : session.getChanges(std::string(subXPath->data()).append("/length"))) {

                    std::string table_name = srpc::extractListKeysFromXpath("acl", change.node.path().data())["name"];
                    std::string chain_name = srpc::extractListKeysFromXpath("ace", change.node.path().data())["name"];

                    // Skip if parent ACL is being deleted
                    if (change.operation == sr::ChangeOperation::Deleted && isParentAclDeleted(session, table_name)) {
                        continue;
                    }

                    std::string type_str;

                    try {
                        auto type_node = session.getOneNode("/ietf-access-control-list:acls/acl[name='" + table_name + "']/type");
                        type_str = type_node.asTerm().valueStr().data();
                    }
                    catch (...) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot obtain /acl[name='%s']/type node", table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    NFTables nft;

                    NFT_Types table_type = nft::helper::ianaToNFTType(type_str);

                    if (table_type == NFT_Types::NFT_INVALID_TYPE) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Invalid type %s !", type_str.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    };

                    std::optional<NFTTable> table = nft.getTable(table_name, table_type);
                    if (!table) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Table %s %s does not exist!", utils::getString<NFT_Types>(table_type).c_str(), table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    std::optional<NFTChain> chain = table->findChain(chain_name);
                    if (!chain) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Chain %s does not exist!", chain_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    Match rule;

                    switch (change.operation) {
                    case sr::ChangeOperation::Created: {
                        std::string length = change.node.asTerm().valueStr().data();
                        rule.Protocol("ip6").Field("length").Value(length);
                        try {
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Modified: {
                        std::string length = change.node.asTerm().valueStr().data();
                        std::string old_length = change.previousValue->data();
                        rule.Protocol("ip6").Field("length").Value(length);
                        try {
                            chain->deleteRule(Match().Protocol("ip6").Field("length").Value(old_length));
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Deleted: {
                        std::string length = change.node.asTerm().valueStr().data();
                        rule.Protocol("ip6").Field("length").Value(length);
                        try {
                            chain->deleteRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }

                // flow-label
                for (sr::Change change : session.getChanges(std::string(subXPath->data()).append("/flow-label"))) {

                    std::string table_name = srpc::extractListKeysFromXpath("acl", change.node.path().data())["name"];
                    std::string chain_name = srpc::extractListKeysFromXpath("ace", change.node.path().data())["name"];

                    // Skip if parent ACL is being deleted
                    if (change.operation == sr::ChangeOperation::Deleted && isParentAclDeleted(session, table_name)) {
                        continue;
                    }

                    std::string type_str;

                    try {
                        auto type_node = session.getOneNode("/ietf-access-control-list:acls/acl[name='" + table_name + "']/type");
                        type_str = type_node.asTerm().valueStr().data();
                    }
                    catch (...) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot obtain /acl[name='%s']/type node", table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    NFTables nft;

                    NFT_Types table_type = nft::helper::ianaToNFTType(type_str);

                    if (table_type == NFT_Types::NFT_INVALID_TYPE) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Invalid type %s !", type_str.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    };

                    std::optional<NFTTable> table = nft.getTable(table_name, table_type);
                    if (!table) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Table %s %s does not exist!", utils::getString<NFT_Types>(table_type).c_str(), table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    std::optional<NFTChain> chain = table->findChain(chain_name);
                    if (!chain) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Chain %s does not exist!", chain_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    Match rule;

                    switch (change.operation) {
                    case sr::ChangeOperation::Created: {
                        std::string flowlabel = change.node.asTerm().valueStr().data();
                        rule.Protocol("ip6").Field("flowlabel").Value(flowlabel);
                        try {
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Modified: {
                        std::string flowlabel = change.node.asTerm().valueStr().data();
                        std::string old_flowlabel = change.previousValue->data();
                        rule.Protocol("ip6").Field("flowlabel").Value(flowlabel);
                        try {
                            chain->deleteRule(Match().Protocol("ip6").Field("flowlabel").Value(old_flowlabel));
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Deleted: {
                        std::string flowlabel = change.node.asTerm().valueStr().data();
                        rule.Protocol("ip6").Field("flowlabel").Value(flowlabel);
                        try {
                            chain->deleteRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }

                // destination-ipv6-network
                for (sr::Change change : session.getChanges(std::string(subXPath->data()).append("/destination-ipv6-network"))) {

                    std::string table_name = srpc::extractListKeysFromXpath("acl", change.node.path().data())["name"];
                    std::string chain_name = srpc::extractListKeysFromXpath("ace", change.node.path().data())["name"];

                    // Skip if parent ACL is being deleted
                    if (change.operation == sr::ChangeOperation::Deleted && isParentAclDeleted(session, table_name)) {
                        continue;
                    }

                    std::string type_str;

                    try {
                        auto type_node = session.getOneNode("/ietf-access-control-list:acls/acl[name='" + table_name + "']/type");
                        type_str = type_node.asTerm().valueStr().data();
                    }
                    catch (...) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot obtain /acl[name='%s']/type node", table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    NFTables nft;

                    NFT_Types table_type = nft::helper::ianaToNFTType(type_str);

                    if (table_type == NFT_Types::NFT_INVALID_TYPE) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Invalid type %s !", type_str.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    };

                    std::optional<NFTTable> table = nft.getTable(table_name, table_type);
                    if (!table) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Table %s %s does not exist!", utils::getString<NFT_Types>(table_type).c_str(), table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    std::optional<NFTChain> chain = table->findChain(chain_name);
                    if (!chain) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Chain %s does not exist!", chain_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    Match rule;

                    switch (change.operation) {
                    case sr::ChangeOperation::Created: {
                        std::string daddr = change.node.asTerm().valueStr().data();
                        rule.Protocol("ip6").Field("daddr").Value(daddr);
                        try {
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Modified: {
                        std::string daddr = change.node.asTerm().valueStr().data();
                        std::string old_daddr = change.previousValue->data();
                        rule.Protocol("ip6").Field("daddr").Value(daddr);
                        try {
                            chain->deleteRule(Match().Protocol("ip6").Field("daddr").Value(old_daddr));
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Deleted: {
                        std::string daddr = change.node.asTerm().valueStr().data();
                        rule.Protocol("ip6").Field("daddr").Value(daddr);
                        try {
                            chain->deleteRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }

                // source-ipv6-network
                for (sr::Change change : session.getChanges(std::string(subXPath->data()).append("/source-ipv6-network"))) {

                    std::string table_name = srpc::extractListKeysFromXpath("acl", change.node.path().data())["name"];
                    std::string chain_name = srpc::extractListKeysFromXpath("ace", change.node.path().data())["name"];

                    // Skip if parent ACL is being deleted
                    if (change.operation == sr::ChangeOperation::Deleted && isParentAclDeleted(session, table_name)) {
                        continue;
                    }

                    std::string type_str;

                    try {
                        auto type_node = session.getOneNode("/ietf-access-control-list:acls/acl[name='" + table_name + "']/type");
                        type_str = type_node.asTerm().valueStr().data();
                    }
                    catch (...) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot obtain /acl[name='%s']/type node", table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    NFTables nft;

                    NFT_Types table_type = nft::helper::ianaToNFTType(type_str);

                    if (table_type == NFT_Types::NFT_INVALID_TYPE) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Invalid type %s !", type_str.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    };

                    std::optional<NFTTable> table = nft.getTable(table_name, table_type);
                    if (!table) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Table %s %s does not exist!", utils::getString<NFT_Types>(table_type).c_str(), table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    std::optional<NFTChain> chain = table->findChain(chain_name);
                    if (!chain) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Chain %s does not exist!", chain_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    Match rule;

                    switch (change.operation) {
                    case sr::ChangeOperation::Created: {
                        std::string saddr = change.node.asTerm().valueStr().data();
                        rule.Protocol("ip6").Field("saddr").Value(saddr);
                        try {
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Modified: {
                        std::string saddr = change.node.asTerm().valueStr().data();
                        std::string old_saddr = change.previousValue->data();
                        rule.Protocol("ip6").Field("saddr").Value(saddr);
                        try {
                            chain->deleteRule(Match().Protocol("ip6").Field("saddr").Value(old_saddr));
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Deleted: {
                        std::string saddr = change.node.asTerm().valueStr().data();
                        rule.Protocol("ip6").Field("saddr").Value(saddr);
                        try {
                            chain->deleteRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }

                break;
            }
            default:
                break;
            }

            return error;
        }

        /**
         * @param ctx Plugin module change context.
         *
         */
        AclAceAcesMatchTcpModuleChangeCb::AclAceAcesMatchTcpModuleChangeCb(std::shared_ptr<AclModuleChangesContext> ctx) { m_ctx = ctx; }

        /**
         * /ietf-access-control-list:acls/acl/aces/ace/matches/tcp.
         *
         * @param session An implicit session for the callback.
         * @param subscriptionId ID the subscription associated with the callback.
         * @param moduleName The module name used for subscribing.
         * @param subXPath The optional xpath used at the time of subscription.
         * @param event Type of the event that has occured.
         * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
         * SR_EV_DONE, for example) have the same request ID.
         *
         * @return Error code.
         *
         */
        sr::ErrorCode AclAceAcesMatchTcpModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
            std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
        {
            sr::ErrorCode error = sr::ErrorCode::Ok;

            switch (event) {
            case sr::Event::Change: {

                // sequence-number
                for (sr::Change change : session.getChanges(std::string(subXPath->data()).append("/sequence-number"))) {

                    std::string table_name = srpc::extractListKeysFromXpath("acl", change.node.path().data())["name"];
                    std::string chain_name = srpc::extractListKeysFromXpath("ace", change.node.path().data())["name"];

                    // Skip if parent ACL is being deleted
                    if (change.operation == sr::ChangeOperation::Deleted && isParentAclDeleted(session, table_name)) {
                        continue;
                    }

                    std::string type_str;

                    try {
                        auto type_node = session.getOneNode("/ietf-access-control-list:acls/acl[name='" + table_name + "']/type");
                        type_str = type_node.asTerm().valueStr().data();
                    }
                    catch (...) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot obtain /acl[name='%s']/type node", table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    NFTables nft;

                    NFT_Types table_type = nft::helper::ianaToNFTType(type_str);

                    if (table_type == NFT_Types::NFT_INVALID_TYPE) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Invalid type %s !", type_str.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    };

                    std::optional<NFTTable> table = nft.getTable(table_name, table_type);
                    if (!table) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Table %s %s does not exist!", utils::getString<NFT_Types>(table_type).c_str(), table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    std::optional<NFTChain> chain = table->findChain(chain_name);
                    if (!chain) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Chain %s does not exist!", chain_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    Match rule;

                    switch (change.operation) {
                    case sr::ChangeOperation::Created: {
                        std::string sequence = change.node.asTerm().valueStr().data();
                        rule.Protocol("tcp").Field("sequence").Value(sequence);
                        try {
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Modified: {
                        std::string sequence = change.node.asTerm().valueStr().data();
                        std::string old_sequence = change.previousValue->data();
                        rule.Protocol("tcp").Field("sequence").Value(sequence);
                        try {
                            chain->deleteRule(Match().Protocol("tcp").Field("sequence").Value(old_sequence));
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Deleted: {
                        std::string sequence = change.node.asTerm().valueStr().data();
                        rule.Protocol("tcp").Field("sequence").Value(sequence);
                        try {
                            chain->deleteRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }

                // acknowledgement-number
                for (sr::Change change : session.getChanges(std::string(subXPath->data()).append("/acknowledgement-number"))) {

                    std::string table_name = srpc::extractListKeysFromXpath("acl", change.node.path().data())["name"];
                    std::string chain_name = srpc::extractListKeysFromXpath("ace", change.node.path().data())["name"];

                    // Skip if parent ACL is being deleted
                    if (change.operation == sr::ChangeOperation::Deleted && isParentAclDeleted(session, table_name)) {
                        continue;
                    }

                    std::string type_str;

                    try {
                        auto type_node = session.getOneNode("/ietf-access-control-list:acls/acl[name='" + table_name + "']/type");
                        type_str = type_node.asTerm().valueStr().data();
                    }
                    catch (...) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot obtain /acl[name='%s']/type node", table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    NFTables nft;

                    NFT_Types table_type = nft::helper::ianaToNFTType(type_str);

                    if (table_type == NFT_Types::NFT_INVALID_TYPE) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Invalid type %s !", type_str.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    };

                    std::optional<NFTTable> table = nft.getTable(table_name, table_type);
                    if (!table) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Table %s %s does not exist!", utils::getString<NFT_Types>(table_type).c_str(), table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    std::optional<NFTChain> chain = table->findChain(chain_name);
                    if (!chain) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Chain %s does not exist!", chain_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    Match rule;

                    switch (change.operation) {
                    case sr::ChangeOperation::Created: {
                        std::string ackseq = change.node.asTerm().valueStr().data();
                        rule.Protocol("tcp").Field("ackseq").Value(ackseq);
                        try {
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Modified: {
                        std::string ackseq = change.node.asTerm().valueStr().data();
                        std::string old_ackseq = change.previousValue->data();
                        rule.Protocol("tcp").Field("ackseq").Value(ackseq);
                        try {
                            chain->deleteRule(Match().Protocol("tcp").Field("ackseq").Value(old_ackseq));
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Deleted: {
                        std::string ackseq = change.node.asTerm().valueStr().data();
                        rule.Protocol("tcp").Field("ackseq").Value(ackseq);
                        try {
                            chain->deleteRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }

                // data-offset
                for (sr::Change change : session.getChanges(std::string(subXPath->data()).append("/data-offset"))) {

                    std::string table_name = srpc::extractListKeysFromXpath("acl", change.node.path().data())["name"];
                    std::string chain_name = srpc::extractListKeysFromXpath("ace", change.node.path().data())["name"];

                    // Skip if parent ACL is being deleted
                    if (change.operation == sr::ChangeOperation::Deleted && isParentAclDeleted(session, table_name)) {
                        continue;
                    }

                    std::string type_str;

                    try {
                        auto type_node = session.getOneNode("/ietf-access-control-list:acls/acl[name='" + table_name + "']/type");
                        type_str = type_node.asTerm().valueStr().data();
                    }
                    catch (...) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot obtain /acl[name='%s']/type node", table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    NFTables nft;

                    NFT_Types table_type = nft::helper::ianaToNFTType(type_str);

                    if (table_type == NFT_Types::NFT_INVALID_TYPE) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Invalid type %s !", type_str.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    };

                    std::optional<NFTTable> table = nft.getTable(table_name, table_type);
                    if (!table) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Table %s %s does not exist!", utils::getString<NFT_Types>(table_type).c_str(), table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    std::optional<NFTChain> chain = table->findChain(chain_name);
                    if (!chain) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Chain %s does not exist!", chain_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    Match rule;

                    switch (change.operation) {
                    case sr::ChangeOperation::Created: {
                        std::string doff = change.node.asTerm().valueStr().data();
                        rule.Protocol("tcp").Field("doff").Value(doff);
                        try {
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Modified: {
                        std::string doff = change.node.asTerm().valueStr().data();
                        std::string old_doff = change.previousValue->data();
                        rule.Protocol("tcp").Field("doff").Value(doff);
                        try {
                            chain->deleteRule(Match().Protocol("tcp").Field("doff").Value(old_doff));
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Deleted: {
                        std::string doff = change.node.asTerm().valueStr().data();
                        rule.Protocol("tcp").Field("doff").Value(doff);
                        try {
                            chain->deleteRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }

                // flags
                for (sr::Change change : session.getChanges(std::string(subXPath->data()).append("/flags"))) {

                    std::string table_name = srpc::extractListKeysFromXpath("acl", change.node.path().data())["name"];
                    std::string chain_name = srpc::extractListKeysFromXpath("ace", change.node.path().data())["name"];

                    // Skip if parent ACL is being deleted
                    if (change.operation == sr::ChangeOperation::Deleted && isParentAclDeleted(session, table_name)) {
                        continue;
                    }

                    std::string type_str;

                    try {
                        auto type_node = session.getOneNode("/ietf-access-control-list:acls/acl[name='" + table_name + "']/type");
                        type_str = type_node.asTerm().valueStr().data();
                    }
                    catch (...) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot obtain /acl[name='%s']/type node", table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    NFTables nft;

                    NFT_Types table_type = nft::helper::ianaToNFTType(type_str);

                    if (table_type == NFT_Types::NFT_INVALID_TYPE) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Invalid type %s !", type_str.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    };

                    std::optional<NFTTable> table = nft.getTable(table_name, table_type);
                    if (!table) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Table %s %s does not exist!", utils::getString<NFT_Types>(table_type).c_str(), table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    std::optional<NFTChain> chain = table->findChain(chain_name);
                    if (!chain) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Chain %s does not exist!", chain_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    Match rule;

                    switch (change.operation) {
                    case sr::ChangeOperation::Created: {
                        std::string flags = change.node.asTerm().valueStr().data();
                        rule.Protocol("tcp").Field("flags").Value(flags);
                        try {
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Modified: {
                        std::string flags = change.node.asTerm().valueStr().data();
                        std::string old_flags = change.previousValue->data();
                        rule.Protocol("tcp").Field("flags").Value(flags);
                        try {
                            chain->deleteRule(Match().Protocol("tcp").Field("flags").Value(old_flags));
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Deleted: {
                        std::string flags = change.node.asTerm().valueStr().data();
                        rule.Protocol("tcp").Field("flags").Value(flags);
                        try {
                            chain->deleteRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }

                // window-size
                for (sr::Change change : session.getChanges(std::string(subXPath->data()).append("/window-size"))) {

                    std::string table_name = srpc::extractListKeysFromXpath("acl", change.node.path().data())["name"];
                    std::string chain_name = srpc::extractListKeysFromXpath("ace", change.node.path().data())["name"];

                    // Skip if parent ACL is being deleted
                    if (change.operation == sr::ChangeOperation::Deleted && isParentAclDeleted(session, table_name)) {
                        continue;
                    }

                    std::string type_str;

                    try {
                        auto type_node = session.getOneNode("/ietf-access-control-list:acls/acl[name='" + table_name + "']/type");
                        type_str = type_node.asTerm().valueStr().data();
                    }
                    catch (...) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot obtain /acl[name='%s']/type node", table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    NFTables nft;

                    NFT_Types table_type = nft::helper::ianaToNFTType(type_str);

                    if (table_type == NFT_Types::NFT_INVALID_TYPE) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Invalid type %s !", type_str.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    };

                    std::optional<NFTTable> table = nft.getTable(table_name, table_type);
                    if (!table) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Table %s %s does not exist!", utils::getString<NFT_Types>(table_type).c_str(), table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    std::optional<NFTChain> chain = table->findChain(chain_name);
                    if (!chain) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Chain %s does not exist!", chain_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    Match rule;

                    switch (change.operation) {
                    case sr::ChangeOperation::Created: {
                        std::string window = change.node.asTerm().valueStr().data();
                        rule.Protocol("tcp").Field("window").Value(window);
                        try {
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Modified: {
                        std::string window = change.node.asTerm().valueStr().data();
                        std::string old_window = change.previousValue->data();
                        rule.Protocol("tcp").Field("window").Value(window);
                        try {
                            chain->deleteRule(Match().Protocol("tcp").Field("window").Value(old_window));
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Deleted: {
                        std::string window = change.node.asTerm().valueStr().data();
                        rule.Protocol("tcp").Field("window").Value(window);
                        try {
                            chain->deleteRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }

                // urgent-pointer
                for (sr::Change change : session.getChanges(std::string(subXPath->data()).append("/urgent-pointer"))) {

                    std::string table_name = srpc::extractListKeysFromXpath("acl", change.node.path().data())["name"];
                    std::string chain_name = srpc::extractListKeysFromXpath("ace", change.node.path().data())["name"];

                    // Skip if parent ACL is being deleted
                    if (change.operation == sr::ChangeOperation::Deleted && isParentAclDeleted(session, table_name)) {
                        continue;
                    }

                    std::string type_str;

                    try {
                        auto type_node = session.getOneNode("/ietf-access-control-list:acls/acl[name='" + table_name + "']/type");
                        type_str = type_node.asTerm().valueStr().data();
                    }
                    catch (...) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot obtain /acl[name='%s']/type node", table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    NFTables nft;

                    NFT_Types table_type = nft::helper::ianaToNFTType(type_str);

                    if (table_type == NFT_Types::NFT_INVALID_TYPE) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Invalid type %s !", type_str.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    };

                    std::optional<NFTTable> table = nft.getTable(table_name, table_type);
                    if (!table) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Table %s %s does not exist!", utils::getString<NFT_Types>(table_type).c_str(), table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    std::optional<NFTChain> chain = table->findChain(chain_name);
                    if (!chain) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Chain %s does not exist!", chain_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    Match rule;

                    switch (change.operation) {
                    case sr::ChangeOperation::Created: {
                        std::string urgptr = change.node.asTerm().valueStr().data();
                        rule.Protocol("tcp").Field("urgptr").Value(urgptr);
                        try {
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Modified: {
                        std::string urgptr = change.node.asTerm().valueStr().data();
                        std::string old_urgptr = change.previousValue->data();
                        rule.Protocol("tcp").Field("urgptr").Value(urgptr);
                        try {
                            chain->deleteRule(Match().Protocol("tcp").Field("urgptr").Value(old_urgptr));
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Deleted: {
                        std::string urgptr = change.node.asTerm().valueStr().data();
                        rule.Protocol("tcp").Field("urgptr").Value(urgptr);
                        try {
                            chain->deleteRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }

                // source-port/port and destination-port/port
                for (sr::Change change : session.getChanges(std::string(subXPath->data()).append("//port"))) {

                    std::string table_name = srpc::extractListKeysFromXpath("acl", change.node.path().data())["name"];
                    std::string chain_name = srpc::extractListKeysFromXpath("ace", change.node.path().data())["name"];

                    // Skip if parent ACL is being deleted
                    if (change.operation == sr::ChangeOperation::Deleted && isParentAclDeleted(session, table_name)) {
                        continue;
                    }

                    std::string type_str;

                    try {
                        auto type_node = session.getOneNode("/ietf-access-control-list:acls/acl[name='" + table_name + "']/type");
                        type_str = type_node.asTerm().valueStr().data();
                    }
                    catch (...) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot obtain /acl[name='%s']/type node", table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    NFTables nft;

                    NFT_Types table_type = nft::helper::ianaToNFTType(type_str);

                    if (table_type == NFT_Types::NFT_INVALID_TYPE) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Invalid type %s !", type_str.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    };

                    std::optional<NFTTable> table = nft.getTable(table_name, table_type);
                    if (!table) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Table %s %s does not exist!", utils::getString<NFT_Types>(table_type).c_str(), table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    std::optional<NFTChain> chain = table->findChain(chain_name);
                    if (!chain) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Chain %s does not exist!", chain_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    Match rule;

                    // Determine if this is source-port or destination-port
                    const char* xpath = change.node.path().data();
                    bool is_source = (strstr(xpath, "source-port") != nullptr);
                    bool is_dest = (strstr(xpath, "destination-port") != nullptr);

                    if (!is_source && !is_dest) {
                        continue;
                    }

                    std::string field_name = is_source ? "sport" : "dport";

                    // Get the operator from the sibling node (if using operator/port format)
                    std::string nft_operator = getPortOperator(session, xpath);

                    switch (change.operation) {
                    case sr::ChangeOperation::Created: {
                        std::string port = change.node.asTerm().valueStr().data();
                        rule.Protocol("tcp").Field(field_name).Value(port);
                        if (!nft_operator.empty()) {
                            rule.Operator(nft_operator);
                        }
                        try {
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Modified: {
                        // Check if previousValue is available
                        if (!change.previousValue.has_value()) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot get previous value for port modification");
                            return sr::ErrorCode::CallbackFailed;
                        }
                        std::string port = change.node.asTerm().valueStr().data();
                        std::string old_port = change.previousValue->data();
                        rule.Protocol("tcp").Field(field_name).Value(port);
                        if (!nft_operator.empty()) {
                            rule.Operator(nft_operator);
                        }
                        try {
                            // Delete old rule with operator
                            Match old_rule;
                            old_rule.Protocol("tcp").Field(field_name).Value(old_port);
                            if (!nft_operator.empty()) {
                                old_rule.Operator(nft_operator);
                            }
                            chain->deleteRule(old_rule);
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Deleted: {
                        std::string port = change.node.asTerm().valueStr().data();
                        rule.Protocol("tcp").Field(field_name).Value(port);
                        if (!nft_operator.empty()) {
                            rule.Operator(nft_operator);
                        }
                        try {
                            chain->deleteRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }

                break;
            }
            default:
                break;
            }

            return error;
        }

        /**
         * @param ctx Plugin module change context.
         *
         */
        AclAceAcesMatchUdpModuleChangeCb::AclAceAcesMatchUdpModuleChangeCb(std::shared_ptr<AclModuleChangesContext> ctx) { m_ctx = ctx; }

        /**
         * /ietf-access-control-list:acls/acl/aces/ace/matches/udp.
         *
         * @param session An implicit session for the callback.
         * @param subscriptionId ID the subscription associated with the callback.
         * @param moduleName The module name used for subscribing.
         * @param subXPath The optional xpath used at the time of subscription.
         * @param event Type of the event that has occured.
         * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
         * SR_EV_DONE, for example) have the same request ID.
         *
         * @return Error code.
         *
         */
        sr::ErrorCode AclAceAcesMatchUdpModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
            std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
        {
            sr::ErrorCode error = sr::ErrorCode::Ok;

            switch (event) {
            case sr::Event::Change: {

                // length
                for (sr::Change change : session.getChanges(std::string(subXPath->data()).append("/length"))) {

                    std::string table_name = srpc::extractListKeysFromXpath("acl", change.node.path().data())["name"];
                    std::string chain_name = srpc::extractListKeysFromXpath("ace", change.node.path().data())["name"];

                    // Skip if parent ACL is being deleted
                    if (change.operation == sr::ChangeOperation::Deleted && isParentAclDeleted(session, table_name)) {
                        continue;
                    }

                    std::string type_str;

                    try {
                        auto type_node = session.getOneNode("/ietf-access-control-list:acls/acl[name='" + table_name + "']/type");
                        type_str = type_node.asTerm().valueStr().data();
                    }
                    catch (...) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot obtain /acl[name='%s']/type node", table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    NFTables nft;

                    NFT_Types table_type = nft::helper::ianaToNFTType(type_str);

                    if (table_type == NFT_Types::NFT_INVALID_TYPE) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Invalid type %s !", type_str.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    };

                    std::optional<NFTTable> table = nft.getTable(table_name, table_type);
                    if (!table) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Table %s %s does not exist!", utils::getString<NFT_Types>(table_type).c_str(), table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    std::optional<NFTChain> chain = table->findChain(chain_name);
                    if (!chain) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Chain %s does not exist!", chain_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    Match rule;

                    switch (change.operation) {
                    case sr::ChangeOperation::Created: {
                        std::string length = change.node.asTerm().valueStr().data();
                        rule.Protocol("udp").Field("length").Value(length);
                        try {
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Modified: {
                        std::string length = change.node.asTerm().valueStr().data();
                        std::string old_length = change.previousValue->data();
                        rule.Protocol("udp").Field("length").Value(length);
                        try {
                            chain->deleteRule(Match().Protocol("udp").Field("length").Value(old_length));
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Deleted: {
                        std::string length = change.node.asTerm().valueStr().data();
                        rule.Protocol("udp").Field("length").Value(length);
                        try {
                            chain->deleteRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }

                // source-port/port and destination-port/port
                for (sr::Change change : session.getChanges(std::string(subXPath->data()).append("//port"))) {

                    std::string table_name = srpc::extractListKeysFromXpath("acl", change.node.path().data())["name"];
                    std::string chain_name = srpc::extractListKeysFromXpath("ace", change.node.path().data())["name"];

                    // Skip if parent ACL is being deleted
                    if (change.operation == sr::ChangeOperation::Deleted && isParentAclDeleted(session, table_name)) {
                        continue;
                    }

                    std::string type_str;

                    try {
                        auto type_node = session.getOneNode("/ietf-access-control-list:acls/acl[name='" + table_name + "']/type");
                        type_str = type_node.asTerm().valueStr().data();
                    }
                    catch (...) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot obtain /acl[name='%s']/type node", table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    NFTables nft;

                    NFT_Types table_type = nft::helper::ianaToNFTType(type_str);

                    if (table_type == NFT_Types::NFT_INVALID_TYPE) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Invalid type %s !", type_str.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    };

                    std::optional<NFTTable> table = nft.getTable(table_name, table_type);
                    if (!table) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Table %s %s does not exist!", utils::getString<NFT_Types>(table_type).c_str(), table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    std::optional<NFTChain> chain = table->findChain(chain_name);
                    if (!chain) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Chain %s does not exist!", chain_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    Match rule;

                    // Determine if this is source-port or destination-port
                    const char* xpath = change.node.path().data();
                    bool is_source = (strstr(xpath, "source-port") != nullptr);
                    bool is_dest = (strstr(xpath, "destination-port") != nullptr);

                    if (!is_source && !is_dest) {
                        continue;
                    }

                    std::string field_name = is_source ? "sport" : "dport";

                    // Get the operator from the sibling node (if using operator/port format)
                    std::string nft_operator = getPortOperator(session, xpath);

                    switch (change.operation) {
                    case sr::ChangeOperation::Created: {
                        std::string port = change.node.asTerm().valueStr().data();
                        rule.Protocol("udp").Field(field_name).Value(port);
                        if (!nft_operator.empty()) {
                            rule.Operator(nft_operator);
                        }
                        try {
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Modified: {
                        // Check if previousValue is available
                        if (!change.previousValue.has_value()) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot get previous value for port modification");
                            return sr::ErrorCode::CallbackFailed;
                        }
                        std::string port = change.node.asTerm().valueStr().data();
                        std::string old_port = change.previousValue->data();
                        rule.Protocol("udp").Field(field_name).Value(port);
                        if (!nft_operator.empty()) {
                            rule.Operator(nft_operator);
                        }
                        try {
                            // Delete old rule with operator
                            Match old_rule;
                            old_rule.Protocol("udp").Field(field_name).Value(old_port);
                            if (!nft_operator.empty()) {
                                old_rule.Operator(nft_operator);
                            }
                            chain->deleteRule(old_rule);
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Deleted: {
                        std::string port = change.node.asTerm().valueStr().data();
                        rule.Protocol("udp").Field(field_name).Value(port);
                        if (!nft_operator.empty()) {
                            rule.Operator(nft_operator);
                        }
                        try {
                            chain->deleteRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }

                break;
            }
            default:
                break;
            }

            return error;
        }

        /**
         * @param ctx Plugin module change context.
         *
         */
        AclAceAcesMatchIcmpModuleChangeCb::AclAceAcesMatchIcmpModuleChangeCb(std::shared_ptr<AclModuleChangesContext> ctx) { m_ctx = ctx; }

        /**
         * /ietf-access-control-list:acls/acl/aces/ace/matches/icmp.
         *
         * @param session An implicit session for the callback.
         * @param subscriptionId ID the subscription associated with the callback.
         * @param moduleName The module name used for subscribing.
         * @param subXPath The optional xpath used at the time of subscription.
         * @param event Type of the event that has occured.
         * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
         * SR_EV_DONE, for example) have the same request ID.
         *
         * @return Error code.
         *
         */
        sr::ErrorCode AclAceAcesMatchIcmpModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
            std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
        {
            sr::ErrorCode error = sr::ErrorCode::Ok;

            switch (event) {
            case sr::Event::Change: {

                // type
                for (sr::Change change : session.getChanges(std::string(subXPath->data()).append("/type"))) {

                    std::string table_name = srpc::extractListKeysFromXpath("acl", change.node.path().data())["name"];
                    std::string chain_name = srpc::extractListKeysFromXpath("ace", change.node.path().data())["name"];

                    // Skip if parent ACL is being deleted
                    if (change.operation == sr::ChangeOperation::Deleted && isParentAclDeleted(session, table_name)) {
                        continue;
                    }

                    std::string type_str;

                    try {
                        auto type_node = session.getOneNode("/ietf-access-control-list:acls/acl[name='" + table_name + "']/type");
                        type_str = type_node.asTerm().valueStr().data();
                    }
                    catch (...) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot obtain /acl[name='%s']/type node", table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    NFTables nft;

                    NFT_Types table_type = nft::helper::ianaToNFTType(type_str);

                    if (table_type == NFT_Types::NFT_INVALID_TYPE) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Invalid type %s !", type_str.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    };

                    std::optional<NFTTable> table = nft.getTable(table_name, table_type);
                    if (!table) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Table %s %s does not exist!", utils::getString<NFT_Types>(table_type).c_str(), table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    std::optional<NFTChain> chain = table->findChain(chain_name);
                    if (!chain) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Chain %s does not exist!", chain_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    Match rule;

                    switch (change.operation) {
                    case sr::ChangeOperation::Created: {
                        std::string icmp_type = change.node.asTerm().valueStr().data();
                        rule.Protocol("icmp").Field("type").Value(icmp_type);
                        try {
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Modified: {
                        std::string icmp_type = change.node.asTerm().valueStr().data();
                        std::string old_icmp_type = change.previousValue->data();
                        rule.Protocol("icmp").Field("type").Value(icmp_type);
                        try {
                            chain->deleteRule(Match().Protocol("icmp").Field("type").Value(old_icmp_type));
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Deleted: {
                        std::string icmp_type = change.node.asTerm().valueStr().data();
                        rule.Protocol("icmp").Field("type").Value(icmp_type);
                        try {
                            chain->deleteRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }

                // code
                for (sr::Change change : session.getChanges(std::string(subXPath->data()).append("/code"))) {

                    std::string table_name = srpc::extractListKeysFromXpath("acl", change.node.path().data())["name"];
                    std::string chain_name = srpc::extractListKeysFromXpath("ace", change.node.path().data())["name"];

                    // Skip if parent ACL is being deleted
                    if (change.operation == sr::ChangeOperation::Deleted && isParentAclDeleted(session, table_name)) {
                        continue;
                    }

                    std::string type_str;

                    try {
                        auto type_node = session.getOneNode("/ietf-access-control-list:acls/acl[name='" + table_name + "']/type");
                        type_str = type_node.asTerm().valueStr().data();
                    }
                    catch (...) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot obtain /acl[name='%s']/type node", table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    NFTables nft;

                    NFT_Types table_type = nft::helper::ianaToNFTType(type_str);

                    if (table_type == NFT_Types::NFT_INVALID_TYPE) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Invalid type %s !", type_str.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    };

                    std::optional<NFTTable> table = nft.getTable(table_name, table_type);
                    if (!table) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Table %s %s does not exist!", utils::getString<NFT_Types>(table_type).c_str(), table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    std::optional<NFTChain> chain = table->findChain(chain_name);
                    if (!chain) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Chain %s does not exist!", chain_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    Match rule;

                    switch (change.operation) {
                    case sr::ChangeOperation::Created: {
                        std::string code = change.node.asTerm().valueStr().data();
                        rule.Protocol("icmp").Field("code").Value(code);
                        try {
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Modified: {
                        std::string code = change.node.asTerm().valueStr().data();
                        std::string old_code = change.previousValue->data();
                        rule.Protocol("icmp").Field("code").Value(code);
                        try {
                            chain->deleteRule(Match().Protocol("icmp").Field("code").Value(old_code));
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Deleted: {
                        std::string code = change.node.asTerm().valueStr().data();
                        rule.Protocol("icmp").Field("code").Value(code);
                        try {
                            chain->deleteRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }

                break;
            }
            default:
                break;
            }

            return error;
        }

        /**
         * @param ctx Plugin module change context.
         *
         */
        AclAceMatchInterfaceModuleChangeCb::AclAceMatchInterfaceModuleChangeCb(std::shared_ptr<AclModuleChangesContext> ctx) { m_ctx = ctx; }

        /**
         * /ietf-access-control-list:acls/acl/aces/ace/matches.
         *
         * @param session An implicit session for the callback.
         * @param subscriptionId ID the subscription associated with the callback.
         * @param moduleName The module name used for subscribing.
         * @param subXPath The optional xpath used at the time of subscription.
         * @param event Type of the event that has occured.
         * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
         * SR_EV_DONE, for example) have the same request ID.
         *
         * @return Error code.
         *
         */
        sr::ErrorCode AclAceMatchInterfaceModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
            std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
        {
            sr::ErrorCode error = sr::ErrorCode::Ok;

            switch (event) {
            case sr::Event::Change: {

                // ingress-interface
                for (sr::Change change : session.getChanges(std::string(subXPath->data()).append("/ingress-interface"))) {

                    std::string table_name = srpc::extractListKeysFromXpath("acl", change.node.path().data())["name"];
                    std::string chain_name = srpc::extractListKeysFromXpath("ace", change.node.path().data())["name"];

                    // Skip if parent ACL is being deleted
                    if (change.operation == sr::ChangeOperation::Deleted && isParentAclDeleted(session, table_name)) {
                        continue;
                    }

                    std::string type_str;

                    try {
                        auto type_node = session.getOneNode("/ietf-access-control-list:acls/acl[name='" + table_name + "']/type");
                        type_str = type_node.asTerm().valueStr().data();
                    }
                    catch (...) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot obtain /acl[name='%s']/type node", table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    NFTables nft;

                    NFT_Types table_type = nft::helper::ianaToNFTType(type_str);

                    if (table_type == NFT_Types::NFT_INVALID_TYPE) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Invalid type %s !", type_str.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    };

                    std::optional<NFTTable> table = nft.getTable(table_name, table_type);
                    if (!table) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Table %s %s does not exist!", utils::getString<NFT_Types>(table_type).c_str(), table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    std::optional<NFTChain> chain = table->findChain(chain_name);
                    if (!chain) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Chain %s does not exist!", chain_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    Match rule;

                    switch (change.operation) {
                    case sr::ChangeOperation::Created: {
                        std::string iface = change.node.asTerm().valueStr().data();
                        rule.Meta("iifname").Value(iface);
                        try {
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Modified: {
                        std::string iface = change.node.asTerm().valueStr().data();
                        std::string old_iface = change.previousValue->data();
                        rule.Meta("iifname").Value(iface);
                        try {
                            chain->deleteRule(Match().Meta("iifname").Value(old_iface));
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Deleted: {
                        std::string iface = change.node.asTerm().valueStr().data();
                        rule.Meta("iifname").Value(iface);
                        try {
                            chain->deleteRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }

                // egress-interface
                for (sr::Change change : session.getChanges(std::string(subXPath->data()).append("/egress-interface"))) {

                    std::string table_name = srpc::extractListKeysFromXpath("acl", change.node.path().data())["name"];
                    std::string chain_name = srpc::extractListKeysFromXpath("ace", change.node.path().data())["name"];

                    // Skip if parent ACL is being deleted
                    if (change.operation == sr::ChangeOperation::Deleted && isParentAclDeleted(session, table_name)) {
                        continue;
                    }

                    std::string type_str;

                    try {
                        auto type_node = session.getOneNode("/ietf-access-control-list:acls/acl[name='" + table_name + "']/type");
                        type_str = type_node.asTerm().valueStr().data();
                    }
                    catch (...) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Cannot obtain /acl[name='%s']/type node", table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    NFTables nft;

                    NFT_Types table_type = nft::helper::ianaToNFTType(type_str);

                    if (table_type == NFT_Types::NFT_INVALID_TYPE) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Invalid type %s !", type_str.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    };

                    std::optional<NFTTable> table = nft.getTable(table_name, table_type);
                    if (!table) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Table %s %s does not exist!", utils::getString<NFT_Types>(table_type).c_str(), table_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    std::optional<NFTChain> chain = table->findChain(chain_name);
                    if (!chain) {
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Chain %s does not exist!", chain_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    Match rule;

                    switch (change.operation) {
                    case sr::ChangeOperation::Created: {
                        std::string iface = change.node.asTerm().valueStr().data();
                        rule.Meta("oifname").Value(iface);
                        try {
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Modified: {
                        std::string iface = change.node.asTerm().valueStr().data();
                        std::string old_iface = change.previousValue->data();
                        rule.Meta("oifname").Value(iface);
                        try {
                            chain->deleteRule(Match().Meta("oifname").Value(old_iface));
                            chain->addRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    case sr::ChangeOperation::Deleted: {
                        std::string iface = change.node.asTerm().valueStr().data();
                        rule.Meta("oifname").Value(iface);
                        try {
                            chain->deleteRule(rule);
                        }
                        catch (NFTablesCommandExecException& e) {
                            SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
                            return sr::ErrorCode::CallbackFailed;
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }

                break;
            }
            default:
                break;
            }

            return error;
        }

        /**
         * @param ctx Plugin module change context.
         *
         */
        AclAceActLogModuleChangeCb::AclAceActLogModuleChangeCb(std::shared_ptr<AclModuleChangesContext> ctx) { m_ctx = ctx; }

        /**
         * /ietf-access-control-list:acls/acl/aces/ace/actions/logging.
         *
         * @param session An implicit session for the callback.
         * @param subscriptionId ID the subscription associated with the callback.
         * @param moduleName The module name used for subscribing.
         * @param subXPath The optional xpath used at the time of subscription.
         * @param event Type of the event that has occured.
         * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
         * SR_EV_DONE, for example) have the same request ID.
         *
         * @return Error code.
         *
         */
        sr::ErrorCode AclAceActLogModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
            std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
        {
            sr::ErrorCode error = sr::ErrorCode::Ok;

            switch (event) {
            case sr::Event::Change: {

                for (sr::Change change : session.getChanges(subXPath->data())) {

                    std::string table_name = srpc::extractListKeysFromXpath("acl", change.node.path().data())["name"];
                    std::string chain_name = srpc::extractListKeysFromXpath("ace", change.node.path().data())["name"];

                    switch (change.operation) {
                    case sr::ChangeOperation::Created: {
                        SRPLG_LOG_INF(PLUGIN_NAME, "Logging enabled for ACL %s, ACE %s", table_name.c_str(), chain_name.c_str());
                        break;
                    }
                    case sr::ChangeOperation::Modified: {
                        SRPLG_LOG_INF(PLUGIN_NAME, "Logging modified for ACL %s, ACE %s", table_name.c_str(), chain_name.c_str());
                        break;
                    }
                    case sr::ChangeOperation::Deleted: {
                        SRPLG_LOG_INF(PLUGIN_NAME, "Logging disabled for ACL %s, ACE %s", table_name.c_str(), chain_name.c_str());
                        break;
                    }
                    default:
                        break;
                    }
                }

                break;
            }
            default:
                break;
            }

            return error;
        }

    }
}
