//
// telekom / sysrepo-plugins
//
// This program is made available under the terms of the
// BSD 3-Clause license which is available at
// https://opensource.org/licenses/BSD-3-Clause
//
// SPDX-FileCopyrightText: 2024 Deutsche Telekom AG
// SPDX-FileContributor: Sartura d.d.
//
// SPDX-License-Identifier: BSD-3-Clause
//

#pragma once

#include <cstdint>
#include <string>
#include <variant>

#include <srpcpp/netlink.hpp>

namespace ietf::rt {
/**
 * @brief Tag for the variant. Holds no value.
 */
struct NextHopNone { };

class NextHopSimple {
public:
    /**
     * @brief Returns the next hop interface index.
     */
    std::int32_t getInterfaceIndex() const;

    /**
     * @brief Returns the gateway of the next hop.
     */
    std::string getGateway() const;

private:
    friend class Route;
    friend class NextHopList;

    /**
     * @brief Constructs the simple value of the next hop.
     */
    NextHopSimple(NextHopRef& nh);

    std::string m_gateway;
    std::int32_t m_ifIndex;
};

class NextHopSpecial {
public:
    /**
     * @brief Returns the next hop value.
     */
    std::string getValue() const;

private:
    friend class Route;

    /**
     * @brief Constructs the special value of the next hop.
     */
    NextHopSpecial(const std::string& value);

    std::string m_value;
};

class NextHopList {
public:
private:
    friend class Route;

    /**
     * @brief Initializes the list by using the netlink next-hops.
     */
    NextHopList(std::list<NextHopRef>& nhs);

    std::list<NextHopSimple> m_list;
};

/**
 * @brief Type alias for next-hop in the ietf-routing YANG module. Union of all possible next-hop variants.
 */
using NextHop = std::variant<NextHopNone, NextHopSimple, NextHopSpecial, NextHopList>;
}
