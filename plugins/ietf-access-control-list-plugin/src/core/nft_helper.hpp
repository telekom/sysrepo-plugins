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
        else {
            return NFT_Types::NFT_INVALID_TYPE;
        }

    }

}