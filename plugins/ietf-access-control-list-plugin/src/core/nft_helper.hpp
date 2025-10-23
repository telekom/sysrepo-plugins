//
// telekom / sysrepo-plugins
//
// This program is made available under the terms of the
// BSD 3-Clause license which is available at
// https://opensource.org/licenses/BSD-3-Clause
//
// SPDX-FileCopyrightText: 2025 Deutsche Telekom AG
// SPDX-FileContributor: Sartura d.d.
//
// SPDX-License-Identifier: BSD-3-Clause
//

#pragma once

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