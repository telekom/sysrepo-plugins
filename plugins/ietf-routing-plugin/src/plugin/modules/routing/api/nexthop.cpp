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

#include "nexthop.hpp"

namespace ietf::rt {

/**
 * @brief Constructs the simple value of the next hop.
 */
NextHopSimple::NextHopSimple(NextHopRef& nh)
    : m_gateway(nh.getGateway().toString())
    , m_ifIndex(nh.getInterfaceIndex())
{
}

/**
 * @brief Returns the next hop interface index.
 */
std::int32_t NextHopSimple::getInterfaceIndex() const
{
    return m_ifIndex;
}

/**
 * @brief Returns the gateway of the next hop.
 */
std::string NextHopSimple::getGateway() const
{
    return m_gateway;
}

/**
 * @brief Constructs the special value of the next hop.
 */
NextHopSpecial::NextHopSpecial(const std::string& value)
    : m_value(value)
{
}

/**
 * @brief Returns the next hop value.
 */
std::string NextHopSpecial::getValue() const
{
    return m_value;
}

/**
 * @brief Initializes an empty list.
 */
NextHopList::NextHopList(std::list<NextHopRef>& nhs)
{
    for (auto& nh : nhs) {
        m_list.push_back(NextHopSimple(nh));
    }
}

}
