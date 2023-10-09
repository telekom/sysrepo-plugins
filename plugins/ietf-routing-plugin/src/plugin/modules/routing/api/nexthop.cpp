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
 * @brief Constructs the special value of the next hop.
 */
NextHopSpecial::NextHopSpecial(const std::string& value)
    : m_value(value)
{
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
