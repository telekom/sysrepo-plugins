#include "change.hpp"
#include <iostream>
#include "core/nftables.hpp"
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

                NFTables nftables;

                auto tab = nftables.getTable("test1", NFT_Types::NFT_IP);

                if(tab){
                    
                   std::list<NFTChain> chains = tab->getChains();

                   for(auto& chain : chains){
                        std::cout<<"CHAIN: "<<chain.getChainName()<<std::endl;
                        std::list<Match> rules = chain.getRules();

                        for(auto& rule : rules){
                            std::cout<<"--------Rule: " <<rule.getValue()<<"is Range :"<<rule.isRange()<<std::endl;
                        }
                   }

                }
                // NFTTable tab = nftables.addTable("test1", NFT_IP);
                // std::cout<<"TAB: "<<tab.getTableName()<<std::endl;

                // auto chain1 = tab.addChain("TESTCHAIN11",std::nullopt,std::nullopt,std::nullopt,std::nullopt);
                // auto chain2 = tab.addChain("TESTCHAIN12",NFT_Chain_Types::CHAIN_FILTER ,NFT_Chain_Hooks::CH_HOOK_INPUT,-111 ,NFT_Chain_Policy::CH_POLICY_DROP);

                // std::cout<<"CHAIN 1"<<chain1.getChainName()<<" AT: "<<chain1.getTableName()<<std::endl;
                // std::cout<<"CHAIN 2"<<chain2.getChainName()<<" AT: "<<chain2.getTableName()<<std::endl;

                
                // chain1.addRule(Match().Meta("oifname").Operator("!=").Value("docker0"));
                // chain1.addRule(Match().Protocol("ip").Field("dscp").Operator("!="));

                // auto table = nftables.getTable("nat", NFT_Types::NFT_IP);

                // if (table) {

                //     for (auto chain : table->getChains()) {

                //         std::cout << "CHAIN: " << chain.getChainName() << std::endl;

                //         std::cout<<"HOOK: "<<(chain.getChainHook() ? utils::getString<NFT_Chain_Hooks>(chain.getChainHook().value()) : "NULL")<<std::endl;
                //         std::cout<<"POLICY: "<<(chain.getChainPolicy() ? utils::getString<NFT_Chain_Policy>(chain.getChainPolicy().value()) : "NULL")<<std::endl;
                //         std::cout<<"TYPE: "<<(chain.getChainType() ? utils::getString<NFT_Chain_Types>(chain.getChainType().value()) : "NULL")<<std::endl;
                //         std::cout<<"PRIO: "<< (chain.getPrio() ? chain.getPrio().value() : 0)<<std::endl;
                //     }
                // }

                
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