#include "core/nftables.hpp"
namespace nft::helper {

    inline NFT_Types ianaToNFTType(const std::string& type) {
        //expand here if needed more types
        if (type == "ietf-access-control-list:ipv4-acl-type") {
            return NFT_Types::NFT_IP;
        }
        else if (type == "ietf-access-control-list:ipv6-acl-type") {
            return NFT_Types::NFT_IP6;
        }
        else if (type == "ietf-access-control-list:eth-acl-type") {
            return NFT_Types::NFT_INET;
        }
        else {
            return NFT_Types::NFT_INVALID_TYPE;
        }

    }

    inline NFT_Chain_Policy ianaToPolicyType(const std::string& policy) {

        if (policy == "ietf-access-control-list:accept") {
            return NFT_Chain_Policy::CH_POLICY_ACCEPT;
        }
        else if (policy == "ietf-access-control-list:drop") {
            return NFT_Chain_Policy::CH_POLICY_DROP;
        }
        else throw NFTablesCommandExecException("Unknown policy type " + policy + " !");
    }

}