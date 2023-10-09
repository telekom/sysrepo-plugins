#pragma once

#include "route.hpp"

#include <map>
#include <string>

#include <srpcpp/netlink/address.hpp>
#include <srpcpp/netlink.hpp>

namespace ietf::rt {

/**
 * @brief Type alias for the RIB data structure. Internally a hash which is identified by a string name and contains information from the YANG module.
 */
class RoutingInformationBase {
public:
    /**
     * @brief Creates a RIB hash/YANG list from the list of routes on the system.
     */
    RoutingInformationBase(CacheRef<RouteRef>& routes);

private:
    /**
     * @brief Class which contains data from the ietf-routing YANG module and the RIB list element.
     */
    class Object {
    public:
        /**
         * @brief Default constructor needed for std::map<K, V>.
         */
        Object();

        /**
         * @brief Returns the family of the RIB.
         */
        AddressFamily getFamily() const;

        /**
         * @brief Returns true if the RIB is default for the given address family.
         */
        bool isDefault() const;

        /**
         * @brief Returns the description of the RIB.
         */
        std::string getDescription() const;

    private:
        friend class RoutingInformationBase;

        /**
         * @brief Cretes a new RIB object.
         */
        Object(AddressFamily family, bool is_default, const std::string& description);

        /**
         * @brief Add the route to the RIB.
         */
        void addRoute(RouteRef& route);

        AddressFamily m_family;
        bool m_default;
        std::string m_description;
        std::list<Route> m_routes;
    };

    std::map<std::string, Object> m_ribs;
};

}
