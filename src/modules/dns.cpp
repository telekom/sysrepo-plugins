#include "dns.hpp"
#include "core/common.hpp"
#include "core/ip.hpp"

#include <core/sdbus.hpp>

// logging
#include <stdexcept>
#include <sysrepo.h>

namespace ietf::sys::dns {

/**
 * @breif Default constructor.
 */
DnsServerList::DnsServerList()
    : SdBus("org.freedesktop.resolve1", "/org/freedesktop/resolve1", "org.freedesktop.resolve1.Manager", "SetLinkDNSEx", "DNSEx")
    , m_ifindex(SYSTEMD_IFINDEX)
{
}

/**
 * @brief Loads the list of DNS servers found currently on the system.
 */
void DnsServerList::loadFromSystem()
{
    // convert from SDBus list to our list
    auto servers = this->importFromSdBus();
    for (auto& s : servers) {
        const auto addr_type = s.get<1>();

        switch (addr_type) {
        case AF_INET:
            m_servers.push_back(DnsServer {
                .InterfaceIndex = s.get<0>(),
                .Address = std::make_unique<ip::Ipv4Address>(s.get<2>()),
                .Port = s.get<3>(),
                .Name = s.get<4>(),
            });
            break;
        case AF_INET6:
            m_servers.push_back(DnsServer {
                .InterfaceIndex = s.get<0>(),
                .Address = std::make_unique<ip::Ipv6Address>(s.get<2>()),
                .Port = s.get<3>(),
                .Name = s.get<4>(),
            });
            break;
        default:
            break;
        }
    }
}

/**
 * @brief Stores the list of DNS servers in the class to the system.
 */
void DnsServerList::storeToSystem()
{
    // convert to SDBus list and store it
    std::vector<sdbus::Struct<int32_t, std::vector<uint8_t>, uint16_t, std::string>> sdbus_data;

    for (auto& server : m_servers) {
        sdbus_data.push_back(sdbus::Struct<int32_t, std::vector<uint8_t>, uint16_t, std::string>(
            server.Address->getVersion(), server.Address->asBytes(), server.Port, server.Name));
    }

    this->exportToSdBus(m_ifindex, sdbus_data);
}

/**
 * @brief Default constructor.
 */
DnsSearchList::DnsSearchList()
    : SdBus("org.freedesktop.resolve1", "/org/freedesktop/resolve1", "org.freedesktop.resolve1.Manager", "SetLinkDomains", "Domains")
    , m_ifindex(SYSTEMD_IFINDEX)
{
}

/**
 * @brief Loads the list of DNS servers found currently on the system.
 */
void DnsSearchList::loadFromSystem()
{
    // convert from SDBus list to our list
    auto domains = this->importFromSdBus();
    for (auto& d : domains) {
        m_search.push_back(DnsSearch {
            .InterfaceIndex = d.get<0>(),
            .Domain = d.get<1>(),
            .Search = d.get<2>(),
        });
    }
}

/**
 * @brief Stores the list of DNS servers in the class to the system.
 */
void DnsSearchList::storeToSystem()
{
    // convert to SDBus list and store it
    std::vector<sdbus::Struct<std::string, bool>> sdbus_data;

    for (auto& search : m_search) {
        sdbus_data.push_back(sdbus::Struct<std::string, bool>(sdbus::make_struct(search.Domain, search.Search)));
    }

    this->exportToSdBus(m_ifindex, sdbus_data);
}
} // end of namespace

namespace ietf::sys::sub::oper {
/**
 * sysrepo-plugin-generator: Generated default constructor.
 *
 * @param ctx Plugin operational context.
 *
 */
DnsSearchOperGetCb::DnsSearchOperGetCb(std::shared_ptr<DnsOperationalContext> ctx) { m_ctx = ctx; }

/**
 * sysrepo-plugin-generator: Generated operator() for path /ietf-system:system/dns-resolver/search.
 *
 * @param session An implicit session for the callback.
 * @param subscriptionId ID the subscription associated with the callback.
 * @param moduleName The module name used for subscribing.
 * @param subXPath The optional xpath used at the time of subscription.
 * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
 * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
 *
 * @return Error code.
 *
 */
sr::ErrorCode DnsSearchOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
    std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
{
    sr::ErrorCode error = sr::ErrorCode::Ok;
    dns::DnsSearchList search_list;

    // load search list and add it to the output yang
    try {
        search_list.loadFromSystem();
    } catch (const std::runtime_error& err) {
        SRPLG_LOG_ERR(ietf::sys::PLUGIN_NAME, "Unable to load DNS search list from the system: %s", err.what());
        error = sr::ErrorCode::OperationFailed;
    }

    // iterate list and add elements to the output tree
    for (auto& iter : search_list) {
        output->newPath("search", iter.Domain);
    }

    return error;
}

/**
 * sysrepo-plugin-generator: Generated default constructor.
 *
 * @param ctx Plugin operational context.
 *
 */
DnsServerNameOperGetCb::DnsServerNameOperGetCb(std::shared_ptr<DnsOperationalContext> ctx) { m_ctx = ctx; }

/**
 * sysrepo-plugin-generator: Generated operator() for path /ietf-system:system/dns-resolver/server[name='%s']/name.
 *
 * @param session An implicit session for the callback.
 * @param subscriptionId ID the subscription associated with the callback.
 * @param moduleName The module name used for subscribing.
 * @param subXPath The optional xpath used at the time of subscription.
 * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
 * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
 *
 * @return Error code.
 *
 */
sr::ErrorCode DnsServerNameOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
    std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
{
    sr::ErrorCode error = sr::ErrorCode::Ok;
    return error;
}

/**
 * sysrepo-plugin-generator: Generated default constructor.
 *
 * @param ctx Plugin operational context.
 *
 */
DnsServerUdpAndTcpAddressOperGetCb::DnsServerUdpAndTcpAddressOperGetCb(std::shared_ptr<DnsOperationalContext> ctx) { m_ctx = ctx; }

/**
 * sysrepo-plugin-generator: Generated operator() for path /ietf-system:system/dns-resolver/server[name='%s']/udp-and-tcp/address.
 *
 * @param session An implicit session for the callback.
 * @param subscriptionId ID the subscription associated with the callback.
 * @param moduleName The module name used for subscribing.
 * @param subXPath The optional xpath used at the time of subscription.
 * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
 * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
 *
 * @return Error code.
 *
 */
sr::ErrorCode DnsServerUdpAndTcpAddressOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
    std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
{
    sr::ErrorCode error = sr::ErrorCode::Ok;
    return error;
}

/**
 * sysrepo-plugin-generator: Generated default constructor.
 *
 * @param ctx Plugin operational context.
 *
 */
DnsServerUdpAndTcpPortOperGetCb::DnsServerUdpAndTcpPortOperGetCb(std::shared_ptr<DnsOperationalContext> ctx) { m_ctx = ctx; }

/**
 * sysrepo-plugin-generator: Generated operator() for path /ietf-system:system/dns-resolver/server[name='%s']/udp-and-tcp/port.
 *
 * @param session An implicit session for the callback.
 * @param subscriptionId ID the subscription associated with the callback.
 * @param moduleName The module name used for subscribing.
 * @param subXPath The optional xpath used at the time of subscription.
 * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
 * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
 *
 * @return Error code.
 *
 */
sr::ErrorCode DnsServerUdpAndTcpPortOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
    std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
{
    sr::ErrorCode error = sr::ErrorCode::Ok;
    return error;
}

/**
 * sysrepo-plugin-generator: Generated default constructor.
 *
 * @param ctx Plugin operational context.
 *
 */
DnsServerUdpAndTcpOperGetCb::DnsServerUdpAndTcpOperGetCb(std::shared_ptr<DnsOperationalContext> ctx) { m_ctx = ctx; }

/**
 * sysrepo-plugin-generator: Generated operator() for path /ietf-system:system/dns-resolver/server[name='%s']/udp-and-tcp.
 *
 * @param session An implicit session for the callback.
 * @param subscriptionId ID the subscription associated with the callback.
 * @param moduleName The module name used for subscribing.
 * @param subXPath The optional xpath used at the time of subscription.
 * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
 * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
 *
 * @return Error code.
 *
 */
sr::ErrorCode DnsServerUdpAndTcpOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
    std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
{
    sr::ErrorCode error = sr::ErrorCode::Ok;
    return error;
}

/**
 * sysrepo-plugin-generator: Generated default constructor.
 *
 * @param ctx Plugin operational context.
 *
 */
DnsServerOperGetCb::DnsServerOperGetCb(std::shared_ptr<DnsOperationalContext> ctx) { m_ctx = ctx; }

/**
 * sysrepo-plugin-generator: Generated operator() for path /ietf-system:system/dns-resolver/server[name='%s'].
 *
 * @param session An implicit session for the callback.
 * @param subscriptionId ID the subscription associated with the callback.
 * @param moduleName The module name used for subscribing.
 * @param subXPath The optional xpath used at the time of subscription.
 * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
 * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
 *
 * @return Error code.
 *
 */
sr::ErrorCode DnsServerOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
    std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
{
    sr::ErrorCode error = sr::ErrorCode::Ok;
    return error;
}

/**
 * sysrepo-plugin-generator: Generated default constructor.
 *
 * @param ctx Plugin operational context.
 *
 */
DnsOptionsTimeoutOperGetCb::DnsOptionsTimeoutOperGetCb(std::shared_ptr<DnsOperationalContext> ctx) { m_ctx = ctx; }

/**
 * sysrepo-plugin-generator: Generated operator() for path /ietf-system:system/dns-resolver/options/timeout.
 *
 * @param session An implicit session for the callback.
 * @param subscriptionId ID the subscription associated with the callback.
 * @param moduleName The module name used for subscribing.
 * @param subXPath The optional xpath used at the time of subscription.
 * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
 * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
 *
 * @return Error code.
 *
 */
sr::ErrorCode DnsOptionsTimeoutOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
    std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
{
    sr::ErrorCode error = sr::ErrorCode::Ok;
    return error;
}

/**
 * sysrepo-plugin-generator: Generated default constructor.
 *
 * @param ctx Plugin operational context.
 *
 */
DnsOptionsAttemptsOperGetCb::DnsOptionsAttemptsOperGetCb(std::shared_ptr<DnsOperationalContext> ctx) { m_ctx = ctx; }

/**
 * sysrepo-plugin-generator: Generated operator() for path /ietf-system:system/dns-resolver/options/attempts.
 *
 * @param session An implicit session for the callback.
 * @param subscriptionId ID the subscription associated with the callback.
 * @param moduleName The module name used for subscribing.
 * @param subXPath The optional xpath used at the time of subscription.
 * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
 * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
 *
 * @return Error code.
 *
 */
sr::ErrorCode DnsOptionsAttemptsOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
    std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
{
    sr::ErrorCode error = sr::ErrorCode::Ok;
    return error;
}

/**
 * sysrepo-plugin-generator: Generated default constructor.
 *
 * @param ctx Plugin operational context.
 *
 */
DnsOptionsOperGetCb::DnsOptionsOperGetCb(std::shared_ptr<DnsOperationalContext> ctx) { m_ctx = ctx; }

/**
 * sysrepo-plugin-generator: Generated operator() for path /ietf-system:system/dns-resolver/options.
 *
 * @param session An implicit session for the callback.
 * @param subscriptionId ID the subscription associated with the callback.
 * @param moduleName The module name used for subscribing.
 * @param subXPath The optional xpath used at the time of subscription.
 * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
 * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
 *
 * @return Error code.
 *
 */
sr::ErrorCode DnsOptionsOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
    std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
{
    sr::ErrorCode error = sr::ErrorCode::Ok;
    return error;
}

/**
 * sysrepo-plugin-generator: Generated default constructor.
 *
 * @param ctx Plugin operational context.
 *
 */
DnsOperGetCb::DnsOperGetCb(std::shared_ptr<DnsOperationalContext> ctx) { m_ctx = ctx; }

/**
 * sysrepo-plugin-generator: Generated operator() for path /ietf-system:system/dns-resolver.
 *
 * @param session An implicit session for the callback.
 * @param subscriptionId ID the subscription associated with the callback.
 * @param moduleName The module name used for subscribing.
 * @param subXPath The optional xpath used at the time of subscription.
 * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
 * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
 *
 * @return Error code.
 *
 */
sr::ErrorCode DnsOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
    std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
{
    sr::ErrorCode error = sr::ErrorCode::Ok;
    return error;
}
}

namespace ietf::sys::sub::change {
/**
 * sysrepo-plugin-generator: Generated default constructor.
 *
 * @param ctx Plugin module change context.
 *
 */
DnsSearchModuleChangeCb::DnsSearchModuleChangeCb(std::shared_ptr<DnsModuleChangesContext> ctx) { m_ctx = ctx; }

/**
 * sysrepo-plugin-generator: Generated module change operator() for path /ietf-system:system/dns-resolver/search.
 *
 * @param session An implicit session for the callback.
 * @param subscriptionId ID the subscription associated with the callback.
 * @param moduleName The module name used for subscribing.
 * @param subXPath The optional xpath used at the time of subscription.
 * @param event Type of the event that has occured.
 * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
 * SR_EV_DONE, for example) have the same request ID.
 *
 * @return Error code.
 *
 */
sr::ErrorCode DnsSearchModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
    std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
{
    sr::ErrorCode error = sr::ErrorCode::Ok;

    // dns::DnsSearchServerList dnsSearchServers;
    // // get all from bus

    // switch (event) {
    // case sysrepo::Event::Change:

    //     if (dnsSearchServers.importListFromSdBus()) {
    //         SRPLG_LOG_ERR(PLUGIN_NAME, "%s", "sd bus import failed!");
    //         return sr::ErrorCode::OperationFailed;
    //     }

    //     // if the call succseeded - continue
    //     for (auto& change : session.getChanges(subXPath->data())) {
    //         switch (change.operation) {
    //         case sysrepo::ChangeOperation::Created:
    //         case sysrepo::ChangeOperation::Modified: {

    //             // get the changed values in node
    //             auto value = change.node.asTerm().value();
    //             auto domain = std::get<std::string>(value);

    //             // no value provided for search param - default true? or maybe another param?
    //             sys::dns::DnsSearchServer server(domain, true);
    //             dnsSearchServers.addDnsSearchServer(server);

    //             break;
    //         }
    //         case sysrepo::ChangeOperation::Deleted: {
    //             // modification:
    //             // first it goes to delete event, then create
    //             // take deleted from here

    //             auto deletedValue = change.node.asTerm().value();
    //             auto deletedDomain = std::get<std::string>(deletedValue);

    //             sys::dns::DnsSearchServer deleted(deletedDomain, true);

    //             dnsSearchServers.removeDnsSearchServer(deleted);

    //             break;
    //         }

    //         case sysrepo::ChangeOperation::Moved:
    //             break;
    //         }
    //     }

    //     // process finished -> export
    //     try {
    //         dnsSearchServers.exportListToSdBus();
    //     } catch (sdbus::Error& e) {
    //         SRPLG_LOG_ERR(PLUGIN_NAME, "%s", e.getMessage().c_str());
    //         return sr::ErrorCode::OperationFailed;
    //     }

    //     break;
    // default:
    //     break;
    // }

    return error;
}

/**
 * sysrepo-plugin-generator: Generated default constructor.
 *
 * @param ctx Plugin module change context.
 *
 */
DnsServerModuleChangeCb::DnsServerModuleChangeCb(std::shared_ptr<DnsModuleChangesContext> ctx) { m_ctx = ctx; }

/**
 * sysrepo-plugin-generator: Generated module change operator() for path /ietf-system:system/dns-resolver/server[name='%s'].
 *
 * @param session An implicit session for the callback.
 * @param subscriptionId ID the subscription associated with the callback.
 * @param moduleName The module name used for subscribing.
 * @param subXPath The optional xpath used at the time of subscription.
 * @param event Type of the event that has occured.
 * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
 * SR_EV_DONE, for example) have the same request ID.
 *
 * @return Error code.
 *
 */
sr::ErrorCode DnsServerModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
    std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
{
    sr::ErrorCode error = sr::ErrorCode::Ok;

    // dns::DnsServerList dnsList;
    // switch (event) {
    // case sysrepo::Event::Change:

    //     // first take all from sdbus
    //     if (dnsList.importListFromSdBus()) {
    //         SRPLG_LOG_ERR(PLUGIN_NAME, "%s", "sd bus import failed!");
    //         return sr::ErrorCode::OperationFailed;
    //     }

    //     for (sysrepo::Change change : session.getChanges(subXPath->data())) {
    //         switch (change.operation) {
    //         case sysrepo::ChangeOperation::Created: {

    //             std::optional<dns::DnsServer> server = dns::getServerFromChangedNode(change.node);

    //             if (server == std::nullopt) {
    //                 error = sr::ErrorCode::OperationFailed;

    //             } else {
    //                 dnsList.addDnsServer(server.value());
    //                 error = sr::ErrorCode::Ok;
    //             }
    //             break;
    //         }

    //         case sysrepo::ChangeOperation::Modified: {

    //             std::optional<dns::DnsServer> server = dns::getServerFromChangedNode(change.node);

    //             if (server == std::nullopt) {
    //                 error = sr::ErrorCode::OperationFailed;

    //             } else {
    //                 // modify here
    //                 try {
    //                     dnsList.modifyDnsServer(server.value());
    //                 } catch (std::exception(&e)) {
    //                     SRPLG_LOG_ERR(PLUGIN_NAME, "%s", e.what());
    //                     return sr::ErrorCode::OperationFailed;
    //                 };

    //                 error = sr::ErrorCode::Ok;
    //             }
    //             break;
    //         }

    //         case sysrepo::ChangeOperation::Deleted: {

    //             std::optional<dns::DnsServer> server = dns::getServerFromChangedNode(change.node);

    //             if (server == std::nullopt) {
    //                 error = sr::ErrorCode::OperationFailed;

    //             } else {
    //                 dnsList.removeDnsServer(server.value());
    //                 error = sr::ErrorCode::Ok;
    //             }

    //             // // deleted code here
    //             break;
    //         }

    //         default:
    //             break;
    //         }
    //     }
    //     if (dnsList.exportListToSdBus() == true) {
    //         return sr::ErrorCode::OperationFailed;
    //     }
    //     break;

    // default:
    //     break;
    // }

    return error;
}

/**
 * sysrepo-plugin-generator: Generated default constructor.
 *
 * @param ctx Plugin module change context.
 *
 */
DnsTimeoutModuleChangeCb::DnsTimeoutModuleChangeCb(std::shared_ptr<DnsModuleChangesContext> ctx) { m_ctx = ctx; }

/**
 * sysrepo-plugin-generator: Generated module change operator() for path /ietf-system:system/dns-resolver/options/timeout.
 *
 * @param session An implicit session for the callback.
 * @param subscriptionId ID the subscription associated with the callback.
 * @param moduleName The module name used for subscribing.
 * @param subXPath The optional xpath used at the time of subscription.
 * @param event Type of the event that has occured.
 * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
 * SR_EV_DONE, for example) have the same request ID.
 *
 * @return Error code.
 *
 */
sr::ErrorCode DnsTimeoutModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
    std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
{
    sr::ErrorCode error = sr::ErrorCode::Ok;
    return error;
}

/**
 * sysrepo-plugin-generator: Generated default constructor.
 *
 * @param ctx Plugin module change context.
 *
 */
DnsAttemptsModuleChangeCb::DnsAttemptsModuleChangeCb(std::shared_ptr<DnsModuleChangesContext> ctx) { m_ctx = ctx; }

/**
 * sysrepo-plugin-generator: Generated module change operator() for path /ietf-system:system/dns-resolver/options/attempts.
 *
 * @param session An implicit session for the callback.
 * @param subscriptionId ID the subscription associated with the callback.
 * @param moduleName The module name used for subscribing.
 * @param subXPath The optional xpath used at the time of subscription.
 * @param event Type of the event that has occured.
 * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
 * SR_EV_DONE, for example) have the same request ID.
 *
 * @return Error code.
 *
 */
sr::ErrorCode DnsAttemptsModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
    std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
{
    sr::ErrorCode error = sr::ErrorCode::Ok;
    return error;
}
}

/**
 * DNS module constructor. Allocates each context.
 */
DnsModule::DnsModule()
{
    m_operContext = std::make_shared<DnsOperationalContext>();
    m_changeContext = std::make_shared<DnsModuleChangesContext>();
    m_rpcContext = std::make_shared<DnsRpcContext>();
}

/**
 * Return the operational context from the module.
 */
std::shared_ptr<srpc::IModuleContext> DnsModule::getOperationalContext() { return m_operContext; }

/**
 * Return the module changes context from the module.
 */
std::shared_ptr<srpc::IModuleContext> DnsModule::getModuleChangesContext() { return m_changeContext; }

/**
 * Return the RPC context from the module.
 */
std::shared_ptr<srpc::IModuleContext> DnsModule::getRpcContext() { return m_rpcContext; }

/**
 * Get all operational callbacks which the module should use.
 */
std::list<OperationalCallback> DnsModule::getOperationalCallbacks()
{
    return {
        OperationalCallback { "/ietf-system:system/dns-resolver/search", ietf::sys::sub::oper::DnsSearchOperGetCb(m_operContext) },
        OperationalCallback { "/ietf-system:system/dns-resolver/server", ietf::sys::sub::oper::DnsServerOperGetCb(m_operContext) },
        OperationalCallback { "/ietf-system:system/dns-resolver/options", ietf::sys::sub::oper::DnsOptionsOperGetCb(m_operContext) },
    };
}

/**
 * Get all module change callbacks which the module should use.
 */
std::list<ModuleChangeCallback> DnsModule::getModuleChangeCallbacks()
{
    return {
        ModuleChangeCallback { "/ietf-system:system/dns-resolver/search", ietf::sys::sub::change::DnsSearchModuleChangeCb(m_changeContext) },
        ModuleChangeCallback { "/ietf-system:system/dns-resolver/server//*", ietf::sys::sub::change::DnsServerModuleChangeCb(m_changeContext) },
    };
}

/**
 * Get all RPC callbacks which the module should use.
 */
std::list<RpcCallback> DnsModule::getRpcCallbacks() { return {}; }

/**
 * Get module name.
 */
constexpr const char* DnsModule::getName() { return "DNS"; }
