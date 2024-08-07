#include "change.hpp"
#include "sysrepo.h"
#include <iostream>
#include "core/nftables.hpp"
#include "core/nft_helper.hpp"
#include <list>

namespace ietf::acl {
    namespace sub::change {
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
                        SRPLG_LOG_ERR(PLUGIN_NAME, "Invalid type %s on table %s", table_type_str, table_name.c_str());
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
                            return sr::ErrorCode::CallbackFailed;
                            SRPLG_LOG_ERR(PLUGIN_NAME, "Failed to create chain %s", chain_name);
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
                                return sr::ErrorCode::CallbackFailed;
                                SRPLG_LOG_ERR(PLUGIN_NAME, "Failed to delete chain %s", chain_name);
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

    }
}