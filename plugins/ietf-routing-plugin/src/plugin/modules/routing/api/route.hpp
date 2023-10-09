#pragma once

#include "nexthop.hpp"

#include <string>
#include <variant>

#include <srpcpp/netlink.hpp>

namespace ietf::rt {
class RoutingInformationBase;

struct RouteMetadata {
    std::string source_protocol;
    std::string last_updated;
    std::string description;
    bool active = 0;
};

class Route {
public:
    /**
     * @brief Returns the route preference value.
     */
    std::uint32_t getPreference() const;

    /**
     * @brief Returns the route metadata.
     */
    RouteMetadata getMetadata() const;

    /**
     * @brief Returns the route next hop value.
     */
    NextHop& getNextHop();

private:
    friend RoutingInformationBase;

    /**
     * @brief Constructs the plugin route object from the netlink route reference object.
     */
    Route(RouteRef& route_ref);

    std::uint32_t m_preference;
    RouteMetadata m_meta;
    NextHop m_nextHop;
};
}
