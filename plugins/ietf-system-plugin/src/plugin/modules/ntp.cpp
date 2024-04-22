#include "ntp.hpp"
#include <iostream>
#include <srpcpp.hpp>
#include "plugin/common.hpp"

namespace ietf::sys::ntp {
    /**
     * @brief Constructor for the list of ntp servers. Uses the session and augyang ability to retrieve NTP servers on the system.
     */
    NtpServerList::NtpServerList(sr::Session& sess)
        : m_session(sess)
    {
    }

    /**
     * @brief Load the list from the system.
     */
    void NtpServerList::loadFromSystem()
    {
        // load the NTP servers from the configuration file in the session
        const auto path = "/ntp:ntp[config-file=\'/etc/ntp.conf\']";
    }

    /**
     * @brief Store the list to the system.
     */
    void NtpServerList::storeToSystem() { }
}

namespace ietf::sys::ntp::change {
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    NtpEnabledModuleChangeCb::NtpEnabledModuleChangeCb(std::shared_ptr<NtpModuleChangesContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ietf-system:system/ntp/enabled.
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
    sr::ErrorCode NtpEnabledModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    NtpServerNameModuleChangeCb::NtpServerNameModuleChangeCb(std::shared_ptr<NtpModuleChangesContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ietf-system:system/ntp/server[name='%s']/name.
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
    sr::ErrorCode NtpServerNameModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
    {
        sr::ErrorCode error = sr::ErrorCode::Ok;
        switch (event) {
        case sysrepo::Event::Change: {

            NTPDbus ntp;
            std::map<std::string, std::string> to_create, to_delete;
            bool execute_modifications = false;

            for (sysrepo::Change change : session.getChanges(subXPath->data())) {
                switch (change.operation) {
                case sysrepo::ChangeOperation::Created:
                case sysrepo::ChangeOperation::Deleted: {

                    std::string name = srpc::extractListKeysFromXpath("server", change.node.path().data())["name"];
                    std::string address;
                    NTPServerAssociationType assoc_type;
                    bool iburst = false;
                    bool prefer = false;

                    for (libyang::DataNode child : change.node.childrenDfs()) {
                        if (child.isTerm()) {

                            if (child.schema().name() == "address") {
                                address = child.asTerm().valueStr();
                            }
                            else if (child.schema().name() == "association-type") {
                                try {
                                    assoc_type = NTP::parseAssocFromString(child.asTerm().valueStr().data());
                                }
                                catch (NtpUnknownAssociationTypeException) {
                                    ntp.raiseError();
                                }
                            }
                            else if (child.schema().name() == "iburst") {
                                iburst = std::get<bool>(child.asTerm().value());
                            }
                            else if (child.schema().name() == "prefer") {
                                prefer = std::get<bool>(child.asTerm().value());
                            };

                        }

                    }

                    switch (change.operation) {
                    case sysrepo::ChangeOperation::Deleted: {
                        NTPServer ntp_remove(assoc_type, address, iburst, prefer, name);
                        if (!ntp.removeServer(ntp_remove, NTPServerRemoveOpts::FIRST_MATCHING)) {
                            ntp.raiseError();
                            throw NtpEraseException();
                        };
                        break;
                    }
                    case sysrepo::ChangeOperation::Created: {
                        ntp.addServer(NTPServer(assoc_type, address, iburst, prefer, name));
                        break;
                    }
                    default:
                        break;
                    }

                    break;
                }
                default:
                    break;
                }
            }

            for (sysrepo::Change change : session.getChanges(std::string(subXPath->data()).append("//*"))) {
                if (change.operation == sr::ChangeOperation::Modified) {
                    execute_modifications = true;
                    //first we get all data for that node, than we modify the modified one
                    std::string name = srpc::extractListKeysFromXpath("server", change.node.path().data())["name"];

                    auto opt_data_node = session.getData("/ietf-system:system/ntp/server[name='" + name + "']");

                    if (opt_data_node) {
                        auto data_node = opt_data_node->findPath("/ietf-system:system/ntp/server[name='" + name + "']");
                        for (const libyang::DataNode& node : data_node->childrenDfs()) {
                            if (node.isTerm()) {
                                to_create[node.schema().name().data()] = node.asTerm().valueStr();
                            }
                        }
                    }

                    if (change.node.isTerm()) {
                        to_delete[change.node.schema().name().data()] = change.previousValue.value();
                    }
                }

                //fill the empty ones in the delete map
                for (auto pair : to_create) {
                    if (to_delete[pair.first].empty()) {
                        to_delete[pair.first] = pair.second;
                    }
                }
            }

            if (execute_modifications) {

                {   //add scope for memory deallocation
                    std::string name = to_create["name"];
                    NTPServerAssociationType assoc_type;
                    try {
                        assoc_type = NTP::parseAssocFromString(to_create["association-type"]);
                    }
                    catch (NtpUnknownAssociationTypeException) {
                        ntp.raiseError();
                    }
                    std::string ntp_server = to_create["address"];
                    bool iburst = (to_create["iburst"] == "true" ? true : false);
                    bool prefer = (to_create["prefer"] == "true" ? true : false);

                    ntp.addServer(NTPServer(assoc_type, ntp_server, iburst, prefer, name));
                }

                {
                    std::string name = to_delete["name"];
                    NTPServerAssociationType assoc_type;
                    try {
                        assoc_type = NTP::parseAssocFromString(to_delete["association-type"]);
                    }
                    catch (NtpUnknownAssociationTypeException) {
                        ntp.raiseError();
                    }
                    std::string ntp_server = to_delete["address"];
                    bool iburst = (to_delete["iburst"] == "true" ? true : false);
                    bool prefer = (to_delete["prefer"] == "true" ? true : false);

                    if (!ntp.removeServer(NTPServer(assoc_type, ntp_server, iburst, prefer, name), NTPServerRemoveOpts::FIRST_MATCHING)) {
                        ntp.raiseError();
                        throw NtpEraseException();
                    };
                }

                execute_modifications = false;
            }

            try {
                ntp.restartNTP();
            }
            catch (std::exception& e) {
                ntp.raiseError();
                SRPLG_LOG_ERR(PLUGIN_NAME, e.what());
            }
            break;
        }
        default:
            break;
        }
        return error;
    }

    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    NtpServerUdpAddressModuleChangeCb::NtpServerUdpAddressModuleChangeCb(std::shared_ptr<NtpModuleChangesContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ietf-system:system/ntp/server[name='%s']/udp/address.
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
    sr::ErrorCode NtpServerUdpAddressModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    NtpServerUdpPortModuleChangeCb::NtpServerUdpPortModuleChangeCb(std::shared_ptr<NtpModuleChangesContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ietf-system:system/ntp/server[name='%s']/udp/port.
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
    sr::ErrorCode NtpServerUdpPortModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    NtpServerUdpModuleChangeCb::NtpServerUdpModuleChangeCb(std::shared_ptr<NtpModuleChangesContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ietf-system:system/ntp/server[name='%s']/udp.
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
    sr::ErrorCode NtpServerUdpModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    NtpServerAssociationTypeModuleChangeCb::NtpServerAssociationTypeModuleChangeCb(std::shared_ptr<NtpModuleChangesContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ietf-system:system/ntp/server[name='%s']/association-type.
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
    sr::ErrorCode NtpServerAssociationTypeModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    NtpServerIburstModuleChangeCb::NtpServerIburstModuleChangeCb(std::shared_ptr<NtpModuleChangesContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ietf-system:system/ntp/server[name='%s']/iburst.
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
    sr::ErrorCode NtpServerIburstModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    NtpServerPreferModuleChangeCb::NtpServerPreferModuleChangeCb(std::shared_ptr<NtpModuleChangesContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ietf-system:system/ntp/server[name='%s']/prefer.
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
    sr::ErrorCode NtpServerPreferModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    NtpServerModuleChangeCb::NtpServerModuleChangeCb(std::shared_ptr<NtpModuleChangesContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ietf-system:system/ntp/server[name='%s'].
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
    sr::ErrorCode NtpServerModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    NtpModuleChangeCb::NtpModuleChangeCb(std::shared_ptr<NtpModuleChangesContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ietf-system:system/ntp.
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
    sr::ErrorCode NtpModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
    {
        sr::ErrorCode error = sr::ErrorCode::Ok;
        return error;
    }
}

namespace ietf::sys::ntp::oper {
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin operational context.
     *
     */
    NtpEnabledOperGetCb::NtpEnabledOperGetCb(std::shared_ptr<NtpOperationalContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-system:system/ntp/enabled.
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
    sr::ErrorCode NtpEnabledOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    NtpServerNameOperGetCb::NtpServerNameOperGetCb(std::shared_ptr<NtpOperationalContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-system:system/ntp/server[name='%s']/name.
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
    sr::ErrorCode NtpServerNameOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    NtpServerUdpAddressOperGetCb::NtpServerUdpAddressOperGetCb(std::shared_ptr<NtpOperationalContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-system:system/ntp/server[name='%s']/udp/address.
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
    sr::ErrorCode NtpServerUdpAddressOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    NtpServerUdpPortOperGetCb::NtpServerUdpPortOperGetCb(std::shared_ptr<NtpOperationalContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-system:system/ntp/server[name='%s']/udp/port.
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
    sr::ErrorCode NtpServerUdpPortOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    NtpServerUdpOperGetCb::NtpServerUdpOperGetCb(std::shared_ptr<NtpOperationalContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-system:system/ntp/server[name='%s']/udp.
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
    sr::ErrorCode NtpServerUdpOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    NtpServerAssociationTypeOperGetCb::NtpServerAssociationTypeOperGetCb(std::shared_ptr<NtpOperationalContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-system:system/ntp/server[name='%s']/association-type.
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
    sr::ErrorCode NtpServerAssociationTypeOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    NtpServerIburstOperGetCb::NtpServerIburstOperGetCb(std::shared_ptr<NtpOperationalContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-system:system/ntp/server[name='%s']/iburst.
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
    sr::ErrorCode NtpServerIburstOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    NtpServerPreferOperGetCb::NtpServerPreferOperGetCb(std::shared_ptr<NtpOperationalContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-system:system/ntp/server[name='%s']/prefer.
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
    sr::ErrorCode NtpServerPreferOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    NtpServerOperGetCb::NtpServerOperGetCb(std::shared_ptr<NtpOperationalContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-system:system/ntp/server[name='%s'].
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
    sr::ErrorCode NtpServerOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
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
    NtpOperGetCb::NtpOperGetCb(std::shared_ptr<NtpOperationalContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-system:system/ntp.
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
    sr::ErrorCode NtpOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
    {
        sr::ErrorCode error = sr::ErrorCode::Ok;
        return error;
    }
}

/**
 * @brief Apply datastore content from the provided session to the system.
 *
 * @param session Session to use for retreiving datastore data.
 */
void NtpValuesApplier::applyDatastoreValues(sysrepo::Session& session) { }

/**
 * NTP module constructor. Allocates each context.
 */
NtpModule::NtpModule(ietf::sys::PluginContext& plugin_ctx)
    : srpc::IModule<ietf::sys::PluginContext>(plugin_ctx)
{
    m_operContext = std::make_shared<NtpOperationalContext>();
    m_changeContext = std::make_shared<NtpModuleChangesContext>();
    m_rpcContext = std::make_shared<NtpRpcContext>();

    // add values applier
    this->addValueApplier<NtpValuesApplier>();
}

/**
 * Return the operational context from the module.
 */
std::shared_ptr<srpc::IModuleContext> NtpModule::getOperationalContext() { return m_operContext; }

/**
 * Return the module changes context from the module.
 */
std::shared_ptr<srpc::IModuleContext> NtpModule::getModuleChangesContext() { return m_changeContext; }

/**
 * Return the RPC context from the module.
 */
std::shared_ptr<srpc::IModuleContext> NtpModule::getRpcContext() { return m_rpcContext; }

/**
 * Get all operational callbacks which the module should use.
 */
std::list<srpc::OperationalCallback> NtpModule::getOperationalCallbacks()
{
    return {
        srpc::OperationalCallback {
            "ietf-system",
            "/ietf-system:system/ntp/server",
            ietf::sys::ntp::oper::NtpServerOperGetCb(m_operContext),
        },
    };
}

/**
 * Get all module change callbacks which the module should use.
 */
std::list<srpc::ModuleChangeCallback> NtpModule::getModuleChangeCallbacks()
{
    return {
        srpc::ModuleChangeCallback {
            "ietf-system",
            "/ietf-system:system/ntp/server",
            ietf::sys::ntp::change::NtpServerNameModuleChangeCb(m_changeContext),
        },
    };
}

/**
 * Get all RPC callbacks which the module should use.
 */
std::list<srpc::RpcCallback> NtpModule::getRpcCallbacks() { return {}; }

/**
 * Get module name.
 */
constexpr const char* NtpModule::getName() { return "NTP"; }
