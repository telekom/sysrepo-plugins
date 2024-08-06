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
        InterfaceModuleChangeCb::InterfaceModuleChangeCb(std::shared_ptr<ietf::acl::ModuleChangeContext> ctx) { m_ctx = ctx; }

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
        sr::ErrorCode InterfaceModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
            std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
        {
            sr::ErrorCode error = sr::ErrorCode::Ok;
            return error;
        }

    }
}