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

#include "route.hpp"
#include <linux/rtnetlink.h>

namespace ietf::rt {
/**
 * @brief Constructs the plugin route object from the netlink route reference object.
 */
Route::Route(RouteRef& route_ref)
    : m_preference(route_ref.getPriority())
    , m_nextHop(NextHopNone {})
{
    // try to setup next hop value
    switch (route_ref.getType()) {
    case RTN_BLACKHOLE:
        m_nextHop = NextHopSpecial("blackhole");
        break;
    case RTN_UNREACHABLE:
        m_nextHop = NextHopSpecial("unreachable");
        break;
    case RTN_PROHIBIT:
        m_nextHop = NextHopSpecial("prohibit");
        break;
    case RTN_LOCAL:
        m_nextHop = NextHopSpecial("receive");
        break;
    default:
        auto nhs = route_ref.getNextHops();
        auto count = nhs.size();
        if (count == 1) {
            // single next-hop element
            m_nextHop = NextHopSimple(*nhs.begin());
        } else {
            // create a list
            m_nextHop = NextHopList(nhs);
        }
        break;
    }

    // setup route metadata which can be set from route_ref, the other metadata needs to be set through Route class API
    if (route_ref.getProtocol() == RTPROT_STATIC) {
        m_meta.source_protocol = "ietf-routing:static";
    } else {
        m_meta.source_protocol = "ietf-routing:direct";
    }
}

/**
 * @brief Returns the route preference value.
 */
std::uint32_t Route::getPreference() const
{
    return m_preference;
}

/**
 * @brief Returns the route metadata.
 */
RouteMetadata Route::getMetadata() const
{
    return m_meta;
}

/**
 * @brief Returns the route next hop value.
 */
NextHop& Route::getNextHop()
{
    return m_nextHop;
}
}