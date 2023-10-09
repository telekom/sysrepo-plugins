#include "rib.hpp"

#include "../common.hpp"
#include "srpcpp/netlink/address.hpp"

#include <sysrepo.h>

namespace ietf::rt {

/**
 * @brief Default constructor needed for std::map<K, V>.
 */
RoutingInformationBase::Object::Object()
    : m_default(false)
    , m_family(AddressFamily::Other)
{
}

RoutingInformationBase::Object::Object(AddressFamily family, bool is_default, const std::string& description)
    : m_family(family)
    , m_default(is_default)
    , m_description(description)
{
}

/**
 * @brief Add the route to the RIB.
 */
void RoutingInformationBase::Object::addRoute(RouteRef& route)
{
    m_routes.push_back(Route(route));
}

/**
 * @brief Returns the family of the RIB.
 */
AddressFamily RoutingInformationBase::Object::getFamily() const { return m_family; }

/**
 * @brief Returns true if the RIB is default for the given address family.
 */
bool RoutingInformationBase::Object::isDefault() const { return m_default; }

/**
 * @brief Returns the description of the RIB.
 */
std::string RoutingInformationBase::Object::getDescription() const { return m_description; }

/**
 * @brief Creates a RIB hash/YANG list from the list of routes on the system.
 */
RoutingInformationBase::RoutingInformationBase(CacheRef<RouteRef>& routes)
{
    std::map<std::string, std::string> default_descriptions = {
        { "main-ipv4", "main routing table - normal routing table containing all non-policy routes (ipv4 only)" },
        { "main-ipv6", "main routing table - normal routing table containing all non-policy routes (ipv6 only)" },
        { "default-ipv4", "default routing table - empty and reserved for post-processing if previous default rules did not select the packet (ipv4 only)" },
        { "default-ipv6", "default routing table - empty and reserved for post-processing if previous default rules did not select the packet (ipv6 only)" },
        { "local-ipv4", "local routing table - maintained by the kernel, containing high priority control routes for local and broadcast addresses (ipv4 only)" },
        { "local-ipv6", "local routing table - maintained by the kernel, containing high priority control routes for local and broadcast addresses (ipv6 only)" },
    };

    for (auto& route : routes) {
        const auto table_name = route.getTableName();
        const auto family = (AddressFamily)route.getFamily();
        const auto family_name = family == AddressFamily::V4 ? "ipv4" : "ipv6";

        const auto full_name = table_name + "-" + family_name;
        const auto description = default_descriptions[full_name];

        if (m_ribs.find(full_name) == m_ribs.end()) {
            m_ribs[full_name] = RoutingInformationBase::Object(family, table_name == "main", description);
        }

        auto& current_rib = m_ribs.at(full_name);

        SRPLG_LOG_INF(getModuleLogPrefix(), "Route belongs to %s table and is of %s family -> %s", table_name.c_str(), family == AddressFamily::V4 ? "IPv4" : "IPv6", full_name.c_str());
        SRPLG_LOG_INF(getModuleLogPrefix(), "Route: %s -> %s", route.getSource().toString().c_str(), route.getDestination().toString().c_str());
    }
}

}
