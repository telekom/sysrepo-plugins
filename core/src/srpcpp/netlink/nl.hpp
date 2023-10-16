#pragma once

#include <memory>
#include <functional>
#include <optional>

///< Type used for deleting libnl allocated structs
template <typename T>
using NlDeleter = std::function<void(T*)>;

///< Type used for deleting libnl allocated structs
template <typename T>
using NlUniquePtr = std::unique_ptr<T, NlDeleter<T>>;

///< Empty deleter which does nothing with the type. Used for storing shared pointers.
template <typename T>
void NlEmptyDeleter(T*) { }

// Predefined classes
class InterfaceRef;
class AddressRef;
class RouteAddressRef;
class NeighborRef;
class RouteRef;
class BridgeRef;
enum class AddressFamily;
template <typename T>
class CacheRef;

enum class NeighborOperations {
    Create,
    Modify,
    Delete,
};

// [TODO]: Make NlContext a singleton - one instance per plugin

/**
 * @brief Netlink context using the libnl library. Used for updating system networking configuration.
 */
class NlContext {
private:
    /**
     * @brief Default constructor. Allocates each member of the class.
     */
    NlContext();

public:
    /**
     * @brief Returns the singleton instance.
     */
    static NlContext& getInstance();

    /**
     * @brief Refill each cache.
     */
    void refillCache(void);

    /**
     * @brief Return names of all links found in the link cache.
     *
     * @return Names of links in the cache.
     */
    std::vector<std::string> getLinkNames();

    /**
     * @brief Return an interface found in cache by name.
     */
    std::optional<InterfaceRef> getInterfaceByName(const std::string& name);

    /**
     * @brief Return an interface found in cache by its index.
     */
    std::optional<InterfaceRef> getInterfaceByIndex(const uint32_t index);

    /**
     * @brief Get Bridge interfaces.
     */
    std::vector<BridgeRef> getBridgeInterfaces();

    /**
     * @brief Get Bridge Interface by name.
     */
    std::optional<BridgeRef> getBridgeByName(std::string name);

    /**
     * @brief Create interface.
     */
    void createInterface(std::string name, std::string type, bool enabled);

    /**
     * @brief Create interface.
     * 
     */
    void createBridgeInterface(std::string name);

    /**
     * @brief Create new address.
     */
    void createAddress(std::string interface_name, std::string address, int prefix_length, AddressFamily fam);

    /**
     * @brief Create a new route.
     */
    void createRoute(const std::string& destination_prefix, const std::string& outgoing_interface, const std::string& next_hop_address);

    /**
     * @brief Delete existing interface, if not existant, throws an exception.
     */
    void deleteInterface(const std::string& name);

    /**
     * @brief Delete existing Address, if not existant, throws an exception.
     */
    void deleteAddress(std::string interface_name, std::string address, int prefix_length, AddressFamily fam);

    /**
     * @brief Delete a route.
     */
    void deleteRoute(const std::string& destination_prefix);

    /**
     * @brief Create Neighbor
     */
    void neighbor(std::string interface_name, std::string address, std::string ll_addr, AddressFamily fam, NeighborOperations oper);

    /**
     * @brief Get the links cache.
     */
    CacheRef<InterfaceRef> getLinkCache();

    /**
     * @brief Get the address cache.
     */
    CacheRef<RouteAddressRef> getAddressCache();

    /**
     * @brief Get the neighbors cache.
     */
    CacheRef<NeighborRef> getNeighborCache();

    /**
     * @brief Get the routes cache.
     */
    CacheRef<RouteRef> getRouteCache();

private:
    NlUniquePtr<struct nl_sock> m_sock; ///< Netlink socket.
    NlUniquePtr<struct nl_cache> m_linkCache; ///< Links cache.
    NlUniquePtr<struct nl_cache> m_addressCache; ///< Addresses cache.
    NlUniquePtr<struct nl_cache> m_neighCache; ///< Neighbors cache.
    NlUniquePtr<struct nl_cache> m_routeCache; ///< Routes cache.
};
