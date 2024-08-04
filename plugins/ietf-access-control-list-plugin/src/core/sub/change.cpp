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