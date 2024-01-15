#include "route.hpp"
#include "address.hpp"
#include "nexthop.hpp"
#include <netlink/route/route.h>
#include <stdexcept>

/**
 * @brief Private constructor accessible only to netlink context. Stores a reference to a route for later access of members.
 */
RouteRef::RouteRef(struct rtnl_route* route, struct nl_sock* socket)
    : m_route(RtnlRoutePtr(route, NlEmptyDeleter<RtnlRoute>))
    , m_socket(NlSocketPtr(socket, NlEmptyDeleter<NlSocket>))
{
}

/**
 * @brief Private constructor accessible only to netlink context. Stores a reference to a route for later access of members.
 */
RouteRef::RouteRef(struct nl_object* route, struct nl_sock* socket)
    : m_route(RtnlRoutePtr(reinterpret_cast<RtnlRoute*>(route), NlEmptyDeleter<RtnlRoute>))
    , m_socket(NlSocketPtr(socket, NlEmptyDeleter<NlSocket>))
{
}

/**
 * @brief Returns the table ID of the route.
 */
std::uint32_t RouteRef::getTable() const { return rtnl_route_get_table(m_route.get()); }

/**
 * @brief Returns the table name of the route.
 */
std::string RouteRef::getTableName() const
{
    char table_buffer[32];

    rtnl_route_table2str(getTable(), table_buffer, sizeof(table_buffer));

    return table_buffer;
}

/**
 * @brief Sets the table ID of the route.
 */
void RouteRef::setTable(std::uint32_t table) { rtnl_route_set_table(m_route.get(), table); }

/**
 * @brief Returns the scope of the route.
 */
std::uint8_t RouteRef::getScope() const { return rtnl_route_get_scope(m_route.get()); }

/**
 * @brief Sets the scope of the route.
 */
void RouteRef::setScope(std::uint8_t scope) { rtnl_route_set_scope(m_route.get(), scope); }

/**
 * @brief Returns the TOS of the route.
 */
std::uint8_t RouteRef::getTOS() const { return rtnl_route_get_tos(m_route.get()); }

/**
 * @brief Sets the TOS of the route.
 */
void RouteRef::setTOS(std::uint8_t tos) { rtnl_route_set_tos(m_route.get(), tos); }

/**
 * @brief Returns the protocol of the route.
 */
std::uint8_t RouteRef::getProtocol() const { return rtnl_route_get_protocol(m_route.get()); }

/**
 * @brief Sets the protocol of the route.
 */
void RouteRef::setProtocol(std::uint8_t protocol) { rtnl_route_set_protocol(m_route.get(), protocol); }

/**
 * @brief Returns the priority of the route.
 */
std::uint32_t RouteRef::getPriority() const { return rtnl_route_get_priority(m_route.get()); }

/**
 * @brief Sets the priority of the route.
 */
void RouteRef::setPriority(std::uint32_t priority) { rtnl_route_set_priority(m_route.get(), priority); }

/**
 * @brief Returns the family of the route.
 */
std::uint8_t RouteRef::getFamily() const { return rtnl_route_get_family(m_route.get()); }

/**
 * @brief Sets the family of the route.
 */
void RouteRef::setFamily(std::uint8_t family)
{
    int error = rtnl_route_set_family(m_route.get(), family);
    if (error != 0) {
        throw std::runtime_error("Unable to set family of the route");
    }
}

/**
 * @brief Returns the type of the route.
 */
std::uint8_t RouteRef::getType() const { return rtnl_route_get_type(m_route.get()); }

/**
 * @brief Sets the type of the route.
 */
void RouteRef::setType(std::uint8_t type)
{
    int error = rtnl_route_set_type(m_route.get(), type);
    if (error != 0) {
        throw std::runtime_error("Unable to set type of the route");
    }
}

/**
 * @brief Returns the flags of the route.
 */
std::uint32_t RouteRef::getFlags() const { return rtnl_route_get_flags(m_route.get()); }

/**
 * @brief Sets the flags of the route.
 */
void RouteRef::setFlags(std::uint32_t flags)
{
    rtnl_route_set_flags(m_route.get(), flags);
}

/**
 * @brief Unsets the flags of the route.
 */
void RouteRef::unsetFlags(std::uint32_t flags) { rtnl_route_unset_flags(m_route.get(), flags); }

/**
 * @brief Returns the destination address of the route.
 */
AddressRef RouteRef::getDestination() const
{
    return AddressRef(rtnl_route_get_dst(m_route.get()), m_socket.get());
}

/**
 * @brief Sets the destination address of the route.
 */
void RouteRef::setDestination(AddressRef addr)
{
    int error = rtnl_route_set_dst(m_route.get(), addr.m_addr.get());
    if (error != 0) {
        throw std::runtime_error("Unable to set destination address of the route");
    }
}

/**
 * @brief Returns the source address of the route.
 */
AddressRef RouteRef::getSource() const
{
    return AddressRef(rtnl_route_get_src(m_route.get()), m_socket.get());
}

/**
 * @brief Sets the source address of the route.
 */
void RouteRef::setSource(AddressRef addr)
{
    int error = rtnl_route_set_src(m_route.get(), addr.m_addr.get());
    if (error != 0) {
        throw std::runtime_error("Unable to set source address of the route");
    }
}

/**
 * @brief Returns the list of next-hops for the given route.
 */
std::list<NextHopRef> RouteRef::getNextHops()
{
    std::list<NextHopRef> nhs;
    const auto n = rtnl_route_get_nnexthops(m_route.get());

    for (auto i = 0; i < n; i++) {
        const auto nh = rtnl_route_nexthop_n(m_route.get(), i);
        nhs.push_back(NextHopRef(nh, m_socket.get()));
    }

    return nhs;
}

void RouteRef::removeNextHop(const std::string& nh_address)
{

    struct Args {
        nl_addr* address;
        rtnl_route* route;
        bool found_nh;
    } arguments {
        .address = NULL,
        .route = m_route.get(),
        .found_nh = false
    };

    int err = 0;

    err = nl_addr_parse(nh_address.c_str(), AF_UNSPEC, &arguments.address);

    if (err < 0) {
        throw std::runtime_error("removeNextHop(), Failed to parse next-hop address!");
    }

    auto nexthop_callback = [](rtnl_nexthop* nh, void* args) {
        char addr_buff[50] = { 0 };
        nl_addr* addr = NULL;

        addr = rtnl_route_nh_get_gateway(nh);

        Args* in_args = (Args*)args;

        if (nl_addr_cmp(addr, in_args->address) == 0) {
            rtnl_route_remove_nexthop(in_args->route, nh);
            in_args->found_nh = true;
        }
    };

    rtnl_route_foreach_nexthop(m_route.get(), nexthop_callback, (void*)&arguments);

    if (!arguments.found_nh) {
        throw std::runtime_error("removeNextHop(), next-hop not found!");
    }
    err = rtnl_route_add(m_socket.get(), m_route.get(), NLM_F_REPLACE);

    if (err < 0) {
        throw std::runtime_error("removeNextHop(), Failed replace route!");
    }
}
