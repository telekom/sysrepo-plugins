#include "change.hpp"
#include "common.hpp"
#include <sysrepo-cpp/Enum.hpp>
#include <sysrepo.h>

namespace ieee::br {
namespace sub::change {
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    BridgeNameModuleChangeCb::BridgeNameModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/name.
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
    sr::ErrorCode BridgeNameModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
    {
        sr::ErrorCode error = sr::ErrorCode::Ok;

        // get the Netlink context
        auto& nl_ctx = m_ctx->getNetlinkContext();

        switch (event) {
        case sysrepo::Event::Change: {
            for (sysrepo::Change change : session.getChanges("/ieee802-dot1q-bridge:bridges/bridge/name")) {

                const auto& value = change.node.asTerm().value();
                const auto& name_value = std::get<std::string>(value);

                // before creating check if component exists, and/or are the same values
                const auto& component_node = session.getData("/ieee802-dot1q-bridge:bridges/bridge[name='" + name_value + "']/component/name");

                if (component_node.has_value()) {
                    // if it has value check if it is the same, otherwise just continue

                    const std::string& comp_name_node = component_node->findXPath("/ieee802-dot1q-bridge:bridges/bridge[name='" + name_value + "']/component/name['" + name_value + "']").begin()->asTerm().valueStr().data();

                    if (comp_name_node.compare(name_value) != 0) {
                        SRPLG_LOG_ERR(getModuleLogPrefix(), "Diferent values for bridge/name and component/name");
                        return sr::ErrorCode::CallbackFailed;
                    }
                }

                switch (change.operation) {
                case sysrepo::ChangeOperation::Created: {

                    try {

                        nl_ctx.refillCache();
                        // get address node
                        auto ds_addr = session.getOneNode("/ieee802-dot1q-bridge:bridges/bridge/address");
                        nl_ctx.createBridgeInterface(name_value);

                        auto bridge_ref = nl_ctx.getBridgeByName(name_value);

                        bridge_ref->setMacAddr(ds_addr.asTerm().valueStr().data());

                    } catch (std::exception& e) {
                        SRPLG_LOG_ERR(getModuleLogPrefix(), "Failed to create Bridge %s! reason: %s", name_value.c_str(), e.what());
                        error = sr::ErrorCode::CallbackFailed;
                    };

                    break;
                }
                case sysrepo::ChangeOperation::Deleted:
                    // delete the bridge interface
                    nl_ctx.deleteInterface(name_value.data());
                    break;
                default:
                    break;
                }
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
    BridgeAddressModuleChangeCb::BridgeAddressModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/address.
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
    sr::ErrorCode BridgeAddressModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
    {
        sr::ErrorCode error = sr::ErrorCode::Ok;
        switch (event) {
        case sysrepo::Event::Change: {

            for (sysrepo::Change change : session.getChanges("/ieee802-dot1q-bridge:bridges/bridge/address")) {

                // get the Netlink context
                auto& nl_ctx = m_ctx->getNetlinkContext();

                switch (change.operation) {
                case sysrepo::ChangeOperation::Created:
                    break;
                case sysrepo::ChangeOperation::Modified: {

                    // get bridge name (key) value
                    std::string bridge_name = srpc::extractListKeyFromXPath("bridge", "name", change.node.path());

                    const std::string addr_value = change.node.asTerm().valueStr().data();
                    // refill netlink cache
                    nl_ctx.refillCache();

                    auto bridge = nl_ctx.getBridgeByName(bridge_name);

                    if (!bridge.has_value()) {
                        SRPLG_LOG_ERR(getModuleLogPrefix(), "Cannot find bridge %s", bridge_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    try {
                        bridge->setMacAddr(addr_value);
                    } catch (std::runtime_error& e) {
                        error = sr::ErrorCode::CallbackFailed;
                        SRPLG_LOG_ERR(getModuleLogPrefix(), "Failed to modify MAC address %s on bridge %s! reason: %s", addr_value.c_str(), bridge_name.c_str(), e.what());
                    }

                    break;
                }
                case sysrepo::ChangeOperation::Deleted:
                    break;
                default:
                    break;
                }
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
    BridgeBridgeTypeModuleChangeCb::BridgeBridgeTypeModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/bridge-type.
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
    sr::ErrorCode BridgeBridgeTypeModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentNameModuleChangeCb::BridgeComponentNameModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/name.
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
    sr::ErrorCode BridgeComponentNameModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
    {
        sr::ErrorCode error = sr::ErrorCode::Ok;

        switch (event) {
        case sysrepo::Event::Change: {

            for (sysrepo::Change change : session.getChanges("/ieee802-dot1q-bridge:bridges/bridge/component/name")) {

                // get bridge name (key) value
                std::string bridge_name;
                try {
                    bridge_name = session.getOneNode("/ieee802-dot1q-bridge:bridges/bridge/name").asTerm().valueStr().data();
                } catch (std::exception& e) {
                    SRPLG_LOG_ERR(getModuleLogPrefix(), "Cannot get bridge name node, reason: %s", e.what());
                }

                const std::string& value = change.node.asTerm().valueStr().data();

                switch (change.operation) {
                case sysrepo::ChangeOperation::Created:
                    // checks if component name is the same with the bridge name
                    if (value.compare(bridge_name) != 0) {
                        // bridge name and component name are different
                        SRPLG_LOG_ERR(getModuleLogPrefix(), "Diferent value for bridge/name and component/name");
                        error = sr::ErrorCode::CallbackFailed;
                    }
                    break;
                case sysrepo::ChangeOperation::Modified:
                    break;
                case sysrepo::ChangeOperation::Deleted:
                    break;
                default:
                    break;
                }
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
    BridgeComponentIdModuleChangeCb::BridgeComponentIdModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/id.
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
    sr::ErrorCode BridgeComponentIdModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentTypeModuleChangeCb::BridgeComponentTypeModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/type.
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
    sr::ErrorCode BridgeComponentTypeModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentAddressModuleChangeCb::BridgeComponentAddressModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/address.
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
    sr::ErrorCode BridgeComponentAddressModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
    {
        sr::ErrorCode error = sr::ErrorCode::Ok;

        switch (event) {
        case sysrepo::Event::Change: {

            for (sysrepo::Change change : session.getChanges("/ieee802-dot1q-bridge:bridges/bridge/component/address")) {

                // get bridge name (key) value
                std::string bridge_address;
                try {
                    bridge_address = session.getOneNode("/ieee802-dot1q-bridge:bridges/bridge/address").asTerm().valueStr().data();
                } catch (std::exception& e) {
                    SRPLG_LOG_ERR(getModuleLogPrefix(), "Cannot get bridge name node, reason: %s", e.what());
                }

                const std::string& value = change.node.asTerm().valueStr().data();

                switch (change.operation) {
                case sysrepo::ChangeOperation::Created:
                case sysrepo::ChangeOperation::Modified:
                    // checks if component addr is the same with the bridge addr
                    if (value.compare(bridge_address) != 0) {
                        // bridge address and component address are different
                        SRPLG_LOG_ERR(getModuleLogPrefix(), "Diferent value for bridge/address and component/address");
                        error = sr::ErrorCode::CallbackFailed;
                    }

                    break;
                case sysrepo::ChangeOperation::Deleted:
                    break;
                default:
                    break;
                }
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
    BridgeComponentTrafficClassEnabledModuleChangeCb::BridgeComponentTrafficClassEnabledModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/traffic-class-enabled.
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
    sr::ErrorCode BridgeComponentTrafficClassEnabledModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseAgingTimeModuleChangeCb::BridgeComponentFilteringDatabaseAgingTimeModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/aging-time.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseAgingTimeModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
    {
        sr::ErrorCode error = sr::ErrorCode::Ok;

        switch (event) {
        case sysrepo::Event::Change: {

            for (sysrepo::Change change : session.getChanges("/ieee802-dot1q-bridge:bridges/bridge/component/filtering-database/aging-time")) {

                const uint32_t ageing_value = std::get<uint32_t>(change.node.asTerm().value());

                std::string bridge_name = srpc::extractListKeyFromXPath("bridge", "name", change.node.path());

                auto& nl_ctx = m_ctx->getNetlinkContext();

                switch (change.operation) {
                case sysrepo::ChangeOperation::Created:
                case sysrepo::ChangeOperation::Modified: {

                    auto bridge = nl_ctx.getBridgeByName(bridge_name);

                    if (!bridge) {
                        SRPLG_LOG_ERR(getModuleLogPrefix(), "Bridge %s does not exist!", bridge_name.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    bridge->setAgeingTime(ageing_value);

                    break;
                }
                case sysrepo::ChangeOperation::Deleted:
                    // not clear if there is default value
                    break;
                default:
                    break;
                }
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
    BridgeComponentFilteringDatabaseFilteringEntryDatabaseIdModuleChangeCb::BridgeComponentFilteringDatabaseFilteringEntryDatabaseIdModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/database-id.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryDatabaseIdModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseFilteringEntryVidsModuleChangeCb::BridgeComponentFilteringDatabaseFilteringEntryVidsModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/vids.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryVidsModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseFilteringEntryAddressModuleChangeCb::BridgeComponentFilteringDatabaseFilteringEntryAddressModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/address.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryAddressModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseFilteringEntryEntryTypeModuleChangeCb::BridgeComponentFilteringDatabaseFilteringEntryEntryTypeModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/entry-type.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryEntryTypeModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseFilteringEntryPortMapPortRefModuleChangeCb::BridgeComponentFilteringDatabaseFilteringEntryPortMapPortRefModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/port-ref.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryPortMapPortRefModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticFilteringEntriesControlElementModuleChangeCb::BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticFilteringEntriesControlElementModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries/control-element.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticFilteringEntriesControlElementModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticFilteringEntriesConnectionIdentifierModuleChangeCb::BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticFilteringEntriesConnectionIdentifierModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries/connection-identifier.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticFilteringEntriesConnectionIdentifierModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticFilteringEntriesModuleChangeCb::BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticFilteringEntriesModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticFilteringEntriesModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesRegistrarAdminControlModuleChangeCb::BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesRegistrarAdminControlModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries/registrar-admin-control.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesRegistrarAdminControlModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesVlanTransmittedModuleChangeCb::BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesVlanTransmittedModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries/vlan-transmitted.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesVlanTransmittedModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesModuleChangeCb::BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseFilteringEntryPortMapMacAddressRegistrationEntriesControlElementModuleChangeCb::BridgeComponentFilteringDatabaseFilteringEntryPortMapMacAddressRegistrationEntriesControlElementModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/mac-address-registration-entries/control-element.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryPortMapMacAddressRegistrationEntriesControlElementModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseFilteringEntryPortMapMacAddressRegistrationEntriesModuleChangeCb::BridgeComponentFilteringDatabaseFilteringEntryPortMapMacAddressRegistrationEntriesModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/mac-address-registration-entries.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryPortMapMacAddressRegistrationEntriesModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicVlanRegistrationEntriesControlElementModuleChangeCb::BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicVlanRegistrationEntriesControlElementModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-vlan-registration-entries/control-element.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicVlanRegistrationEntriesControlElementModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicVlanRegistrationEntriesModuleChangeCb::BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicVlanRegistrationEntriesModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-vlan-registration-entries.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicVlanRegistrationEntriesModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicReservationEntriesControlElementModuleChangeCb::BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicReservationEntriesControlElementModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-reservation-entries/control-element.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicReservationEntriesControlElementModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicReservationEntriesModuleChangeCb::BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicReservationEntriesModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-reservation-entries.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicReservationEntriesModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicFilteringEntriesControlElementModuleChangeCb::BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicFilteringEntriesControlElementModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-filtering-entries/control-element.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicFilteringEntriesControlElementModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicFilteringEntriesModuleChangeCb::BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicFilteringEntriesModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-filtering-entries.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicFilteringEntriesModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseFilteringEntryPortMapModuleChangeCb::BridgeComponentFilteringDatabaseFilteringEntryPortMapModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s'].
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryPortMapModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseFilteringEntryModuleChangeCb::BridgeComponentFilteringDatabaseFilteringEntryModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s'].
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryDatabaseIdModuleChangeCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryDatabaseIdModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/database-id.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryDatabaseIdModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
    {
        sr::ErrorCode error = sr::ErrorCode::Ok;
        switch (event) {
        case sysrepo::Event::Change: {

            for (sysrepo::Change change : session.getChanges("/ieee802-dot1q-bridge:bridges/bridge/component/filtering-database/vlan-registration-entry/database-id")) {

                // const std::string& value = change.node.asTerm().valueStr().data();

                // auto& nl_ctx = m_ctx->getNetlinkContext();

                switch (change.operation) {
                case sysrepo::ChangeOperation::Created: {

                    // nl_ctx.refillCache();

                    // auto bridge_opt = nl_ctx.getBridgeByName("veth1_bport");

                    // BridgeRef& bridge = bridge_opt.value();

                    // std::vector<uint16_t> vids = BridgeRef::parseStringToVlanIDS("10,12,14,19-23,25");

                    // // for (auto &&i : vids)
                    // // {

                    // // }

                    break;
                }
                case sysrepo::ChangeOperation::Modified:
                    break;
                case sysrepo::ChangeOperation::Deleted:
                    break;
                default:
                    break;
                }
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryVidsModuleChangeCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryVidsModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/vids.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryVidsModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryEntryTypeModuleChangeCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryEntryTypeModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/entry-type.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryEntryTypeModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapPortRefModuleChangeCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapPortRefModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/port-ref.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapPortRefModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
    {
        sr::ErrorCode error = sr::ErrorCode::Ok;

        switch (event) {
        case sysrepo::Event::Change: {

            for (sysrepo::Change change : session.getChanges("/ieee802-dot1q-bridge:bridges/bridge/component/filtering-database/vlan-registration-entry/port-map/port-ref")) {

                const auto& value = change.node.asTerm().value();

                const auto& port_ref = std::get<uint32_t>(value);

                auto& nl_ctx = m_ctx->getNetlinkContext();

                nl_ctx.refillCache();

                std::string bridge_name = srpc::extractListKeyFromXPath("bridge", "name", change.node.path());

                auto bridge_opt = nl_ctx.getBridgeByName(bridge_name);

                if (!bridge_opt.has_value()) {
                    SRPLG_LOG_ERR(getModuleLogPrefix(), "Bridge %s does not exist!", bridge_name.c_str());
                    return sr::ErrorCode::CallbackFailed;
                }

                BridgeRef& bridge = bridge_opt.value();

                std::map<int, std::string> slave_interfaces = bridge.getSlaveInterfacesIfindexName();

                if (slave_interfaces.find(port_ref) == slave_interfaces.end()) {
                    // port ref not found
                    SRPLG_LOG_ERR(getModuleLogPrefix(), "Port ref not found!");
                    return sr::ErrorCode::CallbackFailed;
                }
                // all legit with existing port ref, continue with vids

                auto slave_bridge_ref_opt = bridge.getSlaveByIfindex(port_ref);

                if (!slave_bridge_ref_opt.has_value()) {
                    SRPLG_LOG_ERR(getModuleLogPrefix(), "Bridge slave %s not found!", slave_interfaces.at(port_ref).c_str());
                    return sr::ErrorCode::CallbackFailed;
                }

                switch (change.operation) {
                case sysrepo::ChangeOperation::Created:
                case sysrepo::ChangeOperation::Modified: {

                    // get vids node and parse it
                    // Deleted and Created vids node with previous values must be taken from the session changes.
                    std::string vids_data;

                    for (sysrepo::Change change : session.getChanges("/ieee802-dot1q-bridge:bridges/bridge/component/filtering-database/vlan-registration-entry/vids")) {

                        switch (change.operation) {
                        case sr::ChangeOperation::Created: {
                            // vids node
                            vids_data = change.node.asTerm().valueStr().data();
                            break;
                        }
                        }
                    }

                    if (vids_data.empty()) {
                        SRPLG_LOG_ERR(getModuleLogPrefix(), "Empty vids value for deletion!");
                        return sr::ErrorCode::CallbackFailed;
                    }

                    std::vector<uint16_t> parsed_vids = BridgeRef::parseStringToVlanIDS(vids_data);

                    // //handle flags
                    std::string path = change.node.parent()->path();

                    // get the tagged/untagged flag
                    path.append("/static-vlan-registration-entries/vlan-transmitted");

                    const auto& flags_node = change.node.findPath(path);

                    uint16_t flags = 0;

                    if (flags_node.has_value()) {
                        std::string vlan_flags = flags_node->asTerm().valueStr().data();

                        if (vlan_flags.compare("untagged") == 0) {
                            flags = BRIDGE_VLAN_INFO_UNTAGGED;
                        }
                    }

                    // and finaly modify vlans
                    slave_bridge_ref_opt->addVlanIDS(parsed_vids, flags);
                    break;
                }

                case sysrepo::ChangeOperation::Deleted: {

                    // get vids node and parse it
                    // Deleted and Created vids node with previous values must be taken from the session changes.
                    std::string vids_data;

                    for (sysrepo::Change change : session.getChanges("/ieee802-dot1q-bridge:bridges/bridge/component/filtering-database/vlan-registration-entry/vids")) {

                        switch (change.operation) {
                        case sr::ChangeOperation::Deleted: {
                            // vids node
                            vids_data = change.node.asTerm().valueStr().data();
                            break;
                        }
                        }
                    }

                    if (vids_data.empty()) {
                        SRPLG_LOG_ERR(getModuleLogPrefix(), "Empty vids value for deletion!");
                        return sr::ErrorCode::CallbackFailed;
                    }

                    std::vector<uint16_t> parsed_vids = BridgeRef::parseStringToVlanIDS(vids_data);

                    // and finaly modify vlans
                    slave_bridge_ref_opt->removeVlanIDS(parsed_vids);

                    break;
                }
                default:
                    break;
                }
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticFilteringEntriesControlElementModuleChangeCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticFilteringEntriesControlElementModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries/control-element.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticFilteringEntriesControlElementModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticFilteringEntriesConnectionIdentifierModuleChangeCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticFilteringEntriesConnectionIdentifierModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries/connection-identifier.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticFilteringEntriesConnectionIdentifierModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticFilteringEntriesModuleChangeCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticFilteringEntriesModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticFilteringEntriesModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticVlanRegistrationEntriesRegistrarAdminControlModuleChangeCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticVlanRegistrationEntriesRegistrarAdminControlModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries/registrar-admin-control.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticVlanRegistrationEntriesRegistrarAdminControlModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticVlanRegistrationEntriesVlanTransmittedModuleChangeCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticVlanRegistrationEntriesVlanTransmittedModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries/vlan-transmitted.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticVlanRegistrationEntriesVlanTransmittedModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticVlanRegistrationEntriesModuleChangeCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticVlanRegistrationEntriesModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticVlanRegistrationEntriesModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapMacAddressRegistrationEntriesControlElementModuleChangeCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapMacAddressRegistrationEntriesControlElementModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/mac-address-registration-entries/control-element.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapMacAddressRegistrationEntriesControlElementModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapMacAddressRegistrationEntriesModuleChangeCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapMacAddressRegistrationEntriesModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/mac-address-registration-entries.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapMacAddressRegistrationEntriesModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicVlanRegistrationEntriesControlElementModuleChangeCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicVlanRegistrationEntriesControlElementModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-vlan-registration-entries/control-element.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicVlanRegistrationEntriesControlElementModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicVlanRegistrationEntriesModuleChangeCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicVlanRegistrationEntriesModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-vlan-registration-entries.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicVlanRegistrationEntriesModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicReservationEntriesControlElementModuleChangeCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicReservationEntriesControlElementModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-reservation-entries/control-element.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicReservationEntriesControlElementModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicReservationEntriesModuleChangeCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicReservationEntriesModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-reservation-entries.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicReservationEntriesModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicFilteringEntriesControlElementModuleChangeCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicFilteringEntriesControlElementModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-filtering-entries/control-element.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicFilteringEntriesControlElementModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicFilteringEntriesModuleChangeCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicFilteringEntriesModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-filtering-entries.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicFilteringEntriesModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapModuleChangeCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s'].
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryModuleChangeCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s'].
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentFilteringDatabaseModuleChangeCb::BridgeComponentFilteringDatabaseModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentPermanentDatabaseFilteringEntryDatabaseIdModuleChangeCb::BridgeComponentPermanentDatabaseFilteringEntryDatabaseIdModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/database-id.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryDatabaseIdModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentPermanentDatabaseFilteringEntryVidsModuleChangeCb::BridgeComponentPermanentDatabaseFilteringEntryVidsModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/vids.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryVidsModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentPermanentDatabaseFilteringEntryAddressModuleChangeCb::BridgeComponentPermanentDatabaseFilteringEntryAddressModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/address.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryAddressModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentPermanentDatabaseFilteringEntryPortMapPortRefModuleChangeCb::BridgeComponentPermanentDatabaseFilteringEntryPortMapPortRefModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/port-ref.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryPortMapPortRefModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticFilteringEntriesControlElementModuleChangeCb::BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticFilteringEntriesControlElementModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries/control-element.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticFilteringEntriesControlElementModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticFilteringEntriesConnectionIdentifierModuleChangeCb::BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticFilteringEntriesConnectionIdentifierModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries/connection-identifier.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticFilteringEntriesConnectionIdentifierModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticFilteringEntriesModuleChangeCb::BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticFilteringEntriesModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticFilteringEntriesModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesRegistrarAdminControlModuleChangeCb::BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesRegistrarAdminControlModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries/registrar-admin-control.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesRegistrarAdminControlModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesVlanTransmittedModuleChangeCb::BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesVlanTransmittedModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries/vlan-transmitted.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesVlanTransmittedModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesModuleChangeCb::BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentPermanentDatabaseFilteringEntryPortMapMacAddressRegistrationEntriesControlElementModuleChangeCb::BridgeComponentPermanentDatabaseFilteringEntryPortMapMacAddressRegistrationEntriesControlElementModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/mac-address-registration-entries/control-element.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryPortMapMacAddressRegistrationEntriesControlElementModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentPermanentDatabaseFilteringEntryPortMapMacAddressRegistrationEntriesModuleChangeCb::BridgeComponentPermanentDatabaseFilteringEntryPortMapMacAddressRegistrationEntriesModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/mac-address-registration-entries.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryPortMapMacAddressRegistrationEntriesModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicVlanRegistrationEntriesControlElementModuleChangeCb::BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicVlanRegistrationEntriesControlElementModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-vlan-registration-entries/control-element.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicVlanRegistrationEntriesControlElementModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicVlanRegistrationEntriesModuleChangeCb::BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicVlanRegistrationEntriesModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-vlan-registration-entries.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicVlanRegistrationEntriesModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicReservationEntriesControlElementModuleChangeCb::BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicReservationEntriesControlElementModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-reservation-entries/control-element.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicReservationEntriesControlElementModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicReservationEntriesModuleChangeCb::BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicReservationEntriesModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-reservation-entries.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicReservationEntriesModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicFilteringEntriesControlElementModuleChangeCb::BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicFilteringEntriesControlElementModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-filtering-entries/control-element.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicFilteringEntriesControlElementModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicFilteringEntriesModuleChangeCb::BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicFilteringEntriesModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-filtering-entries.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicFilteringEntriesModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentPermanentDatabaseFilteringEntryPortMapModuleChangeCb::BridgeComponentPermanentDatabaseFilteringEntryPortMapModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s'].
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryPortMapModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentPermanentDatabaseFilteringEntryModuleChangeCb::BridgeComponentPermanentDatabaseFilteringEntryModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s'].
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentPermanentDatabaseModuleChangeCb::BridgeComponentPermanentDatabaseModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    VlanVidModuleChangeCb::VlanVidModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vlan[vid='%s']/vid.
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
    sr::ErrorCode VlanVidModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    VlanNameModuleChangeCb::VlanNameModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vlan[vid='%s']/name.
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
    sr::ErrorCode VlanNameModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentBridgeVlanVlanModuleChangeCb::BridgeComponentBridgeVlanVlanModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vlan[vid='%s'].
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
    sr::ErrorCode BridgeComponentBridgeVlanVlanModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentBridgeVlanProtocolGroupDatabaseDbIndexModuleChangeCb::BridgeComponentBridgeVlanProtocolGroupDatabaseDbIndexModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/protocol-group-database[db-index='%s']/db-index.
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
    sr::ErrorCode BridgeComponentBridgeVlanProtocolGroupDatabaseDbIndexModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentBridgeVlanProtocolGroupDatabaseFrameFormatTypeModuleChangeCb::BridgeComponentBridgeVlanProtocolGroupDatabaseFrameFormatTypeModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/protocol-group-database[db-index='%s']/frame-format-type.
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
    sr::ErrorCode BridgeComponentBridgeVlanProtocolGroupDatabaseFrameFormatTypeModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentBridgeVlanProtocolGroupDatabaseEthertypeModuleChangeCb::BridgeComponentBridgeVlanProtocolGroupDatabaseEthertypeModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/protocol-group-database[db-index='%s']/ethertype.
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
    sr::ErrorCode BridgeComponentBridgeVlanProtocolGroupDatabaseEthertypeModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentBridgeVlanProtocolGroupDatabaseProtocolIdModuleChangeCb::BridgeComponentBridgeVlanProtocolGroupDatabaseProtocolIdModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/protocol-group-database[db-index='%s']/protocol-id.
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
    sr::ErrorCode BridgeComponentBridgeVlanProtocolGroupDatabaseProtocolIdModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentBridgeVlanProtocolGroupDatabaseDsapSsapPairsLlcAddressModuleChangeCb::BridgeComponentBridgeVlanProtocolGroupDatabaseDsapSsapPairsLlcAddressModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/protocol-group-database[db-index='%s']/dsap-ssap-pairs/llc-address.
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
    sr::ErrorCode BridgeComponentBridgeVlanProtocolGroupDatabaseDsapSsapPairsLlcAddressModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentBridgeVlanProtocolGroupDatabaseDsapSsapPairsModuleChangeCb::BridgeComponentBridgeVlanProtocolGroupDatabaseDsapSsapPairsModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/protocol-group-database[db-index='%s']/dsap-ssap-pairs.
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
    sr::ErrorCode BridgeComponentBridgeVlanProtocolGroupDatabaseDsapSsapPairsModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentBridgeVlanProtocolGroupDatabaseGroupIdModuleChangeCb::BridgeComponentBridgeVlanProtocolGroupDatabaseGroupIdModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/protocol-group-database[db-index='%s']/group-id.
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
    sr::ErrorCode BridgeComponentBridgeVlanProtocolGroupDatabaseGroupIdModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentBridgeVlanProtocolGroupDatabaseModuleChangeCb::BridgeComponentBridgeVlanProtocolGroupDatabaseModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/protocol-group-database[db-index='%s'].
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
    sr::ErrorCode BridgeComponentBridgeVlanProtocolGroupDatabaseModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentBridgeVlanVidToFidAllocationVidsModuleChangeCb::BridgeComponentBridgeVlanVidToFidAllocationVidsModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vid-to-fid-allocation[vids='%s']/vids.
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
    sr::ErrorCode BridgeComponentBridgeVlanVidToFidAllocationVidsModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentBridgeVlanVidToFidAllocationModuleChangeCb::BridgeComponentBridgeVlanVidToFidAllocationModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vid-to-fid-allocation[vids='%s'].
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
    sr::ErrorCode BridgeComponentBridgeVlanVidToFidAllocationModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentBridgeVlanFidToVidAllocationFidModuleChangeCb::BridgeComponentBridgeVlanFidToVidAllocationFidModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/fid-to-vid-allocation[fid='%s']/fid.
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
    sr::ErrorCode BridgeComponentBridgeVlanFidToVidAllocationFidModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentBridgeVlanFidToVidAllocationModuleChangeCb::BridgeComponentBridgeVlanFidToVidAllocationModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/fid-to-vid-allocation[fid='%s'].
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
    sr::ErrorCode BridgeComponentBridgeVlanFidToVidAllocationModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentBridgeVlanVidToFidVidModuleChangeCb::BridgeComponentBridgeVlanVidToFidVidModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vid-to-fid[vid='%s']/vid.
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
    sr::ErrorCode BridgeComponentBridgeVlanVidToFidVidModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentBridgeVlanVidToFidFidModuleChangeCb::BridgeComponentBridgeVlanVidToFidFidModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vid-to-fid[vid='%s']/fid.
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
    sr::ErrorCode BridgeComponentBridgeVlanVidToFidFidModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentBridgeVlanVidToFidModuleChangeCb::BridgeComponentBridgeVlanVidToFidModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vid-to-fid[vid='%s'].
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
    sr::ErrorCode BridgeComponentBridgeVlanVidToFidModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentBridgeVlanModuleChangeCb::BridgeComponentBridgeVlanModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan.
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
    sr::ErrorCode BridgeComponentBridgeVlanModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentBridgeMstMstidModuleChangeCb::BridgeComponentBridgeMstMstidModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-mst/mstid.
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
    sr::ErrorCode BridgeComponentBridgeMstMstidModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentBridgeMstFidToMstidFidModuleChangeCb::BridgeComponentBridgeMstFidToMstidFidModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-mst/fid-to-mstid[fid='%s']/fid.
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
    sr::ErrorCode BridgeComponentBridgeMstFidToMstidFidModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentBridgeMstFidToMstidMstidModuleChangeCb::BridgeComponentBridgeMstFidToMstidMstidModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-mst/fid-to-mstid[fid='%s']/mstid.
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
    sr::ErrorCode BridgeComponentBridgeMstFidToMstidMstidModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentBridgeMstFidToMstidModuleChangeCb::BridgeComponentBridgeMstFidToMstidModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-mst/fid-to-mstid[fid='%s'].
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
    sr::ErrorCode BridgeComponentBridgeMstFidToMstidModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentBridgeMstFidToMstidAllocationFidsModuleChangeCb::BridgeComponentBridgeMstFidToMstidAllocationFidsModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-mst/fid-to-mstid-allocation[fids='%s']/fids.
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
    sr::ErrorCode BridgeComponentBridgeMstFidToMstidAllocationFidsModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentBridgeMstFidToMstidAllocationMstidModuleChangeCb::BridgeComponentBridgeMstFidToMstidAllocationMstidModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-mst/fid-to-mstid-allocation[fids='%s']/mstid.
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
    sr::ErrorCode BridgeComponentBridgeMstFidToMstidAllocationMstidModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentBridgeMstFidToMstidAllocationModuleChangeCb::BridgeComponentBridgeMstFidToMstidAllocationModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-mst/fid-to-mstid-allocation[fids='%s'].
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
    sr::ErrorCode BridgeComponentBridgeMstFidToMstidAllocationModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentBridgeMstModuleChangeCb::BridgeComponentBridgeMstModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-mst.
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
    sr::ErrorCode BridgeComponentBridgeMstModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeComponentModuleChangeCb::BridgeComponentModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s'].
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
    sr::ErrorCode BridgeComponentModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgeModuleChangeCb::BridgeModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s'].
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
    sr::ErrorCode BridgeModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
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
    BridgesModuleChangeCb::BridgesModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ieee802-dot1q-bridge:bridges.
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
    sr::ErrorCode BridgesModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
    {
        sr::ErrorCode error = sr::ErrorCode::Ok;
        return error;
    }

    InterfaceBridgePortComponentNameModuleChangeCb::InterfaceBridgePortComponentNameModuleChangeCb(std::shared_ptr<BridgingModuleChangesContext> ctx)
    {
        m_ctx = ctx;
    }

    sr::ErrorCode InterfaceBridgePortComponentNameModuleChangeCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, sr::Event event, uint32_t requestId)
    {
        sr::ErrorCode error = sr::ErrorCode::Ok;

        switch (event) {
        case sysrepo::Event::Change: {

            for (sysrepo::Change change : session.getChanges("/ietf-interfaces:interfaces/interface/bridge-port/component-name")) {

                const std::string bridge_val = change.node.asTerm().valueStr().data();
                // get the netlink context
                NlContext& nl_ctx = m_ctx->getNetlinkContext();

                switch (change.operation) {
                case sysrepo::ChangeOperation::Created:
                case sysrepo::ChangeOperation::Modified: {

                    nl_ctx.refillCache();

                    const std::string name_val = srpc::extractListKeyFromXPath("interface", "name", change.node.path());

                    std::optional<BridgeRef> bridge_opt = nl_ctx.getBridgeByName(bridge_val);

                    if (!bridge_opt.has_value()) {
                        SRPLG_LOG_ERR(getModuleLogPrefix(), "Cannot find bridge %s", bridge_val.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }
                    try {
                        bridge_opt->addInterfaceToBridge(name_val);
                    } catch (std::exception& e) {
                        SRPLG_LOG_ERR(getModuleLogPrefix(), "Cannot bridge interface %s, reason: %s", name_val.c_str(), e.what());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    break;
                }
                case sysrepo::ChangeOperation::Deleted: {

                    nl_ctx.refillCache();

                    const std::string name_val = srpc::extractListKeyFromXPath("interface", "name", change.node.path());

                    std::optional<BridgeRef> bridge_opt = nl_ctx.getBridgeByName(bridge_val);

                    if (!bridge_opt.has_value()) {
                        SRPLG_LOG_ERR(getModuleLogPrefix(), "Cannot find bridge %s", bridge_val.c_str());
                        return sr::ErrorCode::CallbackFailed;
                    }
                    try {
                        bridge_opt->removeInterfaceFromBridge(name_val);
                    } catch (std::exception& e) {
                        SRPLG_LOG_ERR(getModuleLogPrefix(), "Cannot remove bridge interface %s, reason: %s", name_val.c_str(), e.what());
                        return sr::ErrorCode::CallbackFailed;
                    }

                    break;
                }
                default:
                    break;
                }
            }

            break;
        }
        default:
            break;
        }

        return error;
    }

}
}
