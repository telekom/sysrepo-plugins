#include "oper.hpp"

namespace ieee::br {
namespace sub::oper {
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin operational context.
     *
     */
    BridgeNameOperGetCb::BridgeNameOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/name.
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
    sr::ErrorCode BridgeNameOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeAddressOperGetCb::BridgeAddressOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/address.
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
    sr::ErrorCode BridgeAddressOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
    {
        sr::ErrorCode error = sr::ErrorCode::Ok;

        std::string bridge_name = srpc::extractListKeyFromXPath("bridge", "name", output->path());

        auto& nl_ctx = NlContext::getInstance();
        nl_ctx.refillCache();

        // find the bridge
        auto bridge_opt = nl_ctx.getBridgeByName(bridge_name);

        if (!bridge_opt.has_value()) {
            SRPLG_LOG_ERR(getModuleLogPrefix(), "Bridge operational callback failed!");
            return sr::ErrorCode::NotFound;
        }

        std::string bridge_addr = bridge_opt->getMacAddr();

        std::replace(bridge_addr.begin(), bridge_addr.end(), ':', '-');

        output->newPath("address", bridge_addr);
        return error;
    }

    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin operational context.
     *
     */
    BridgeBridgeTypeOperGetCb::BridgeBridgeTypeOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/bridge-type.
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
    sr::ErrorCode BridgeBridgeTypeOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgePortsOperGetCb::BridgePortsOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/ports.
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
    sr::ErrorCode BridgePortsOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
    {
        sr::ErrorCode error = sr::ErrorCode::Ok;
        std::string bridge_name = srpc::extractListKeyFromXPath("bridge", "name", output->path());

        auto& nl_ctx = NlContext::getInstance();
        nl_ctx.refillCache();

        // find the bridge
        auto bridge_opt = nl_ctx.getBridgeByName(bridge_name);

        if (!bridge_opt.has_value()) {
            SRPLG_LOG_ERR(getModuleLogPrefix(), "BridgePortsOperGetCb operational callback failed!");
            return sr::ErrorCode::NotFound;
        }

        int ports = bridge_opt->getSlaveInterfaces().size();

        if (ports > 0)
            output->newPath("ports", std::to_string(ports));

        return error;
    }

    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin operational context.
     *
     */
    BridgeUpTimeOperGetCb::BridgeUpTimeOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/up-time.
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
    sr::ErrorCode BridgeUpTimeOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentsOperGetCb::BridgeComponentsOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/components.
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
    sr::ErrorCode BridgeComponentsOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentNameOperGetCb::BridgeComponentNameOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/name.
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
    sr::ErrorCode BridgeComponentNameOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentIdOperGetCb::BridgeComponentIdOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/id.
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
    sr::ErrorCode BridgeComponentIdOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentTypeOperGetCb::BridgeComponentTypeOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/type.
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
    sr::ErrorCode BridgeComponentTypeOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
    {
        sr::ErrorCode error = sr::ErrorCode::Ok;
        output->newPath("type", "c-vlan-component");
        return error;
    }

    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin operational context.
     *
     */
    BridgeComponentAddressOperGetCb::BridgeComponentAddressOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/address.
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
    sr::ErrorCode BridgeComponentAddressOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentTrafficClassEnabledOperGetCb::BridgeComponentTrafficClassEnabledOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/traffic-class-enabled.
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
    sr::ErrorCode BridgeComponentTrafficClassEnabledOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentPortsOperGetCb::BridgeComponentPortsOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/ports.
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
    sr::ErrorCode BridgeComponentPortsOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentBridgePortOperGetCb::BridgeComponentBridgePortOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-port.
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
    sr::ErrorCode BridgeComponentBridgePortOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentCapabilitiesExtendedFilteringOperGetCb::BridgeComponentCapabilitiesExtendedFilteringOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/capabilities/extended-filtering.
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
    sr::ErrorCode BridgeComponentCapabilitiesExtendedFilteringOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentCapabilitiesTrafficClassesOperGetCb::BridgeComponentCapabilitiesTrafficClassesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/capabilities/traffic-classes.
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
    sr::ErrorCode BridgeComponentCapabilitiesTrafficClassesOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentCapabilitiesStaticEntryIndividualPortOperGetCb::BridgeComponentCapabilitiesStaticEntryIndividualPortOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/capabilities/static-entry-individual-port.
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
    sr::ErrorCode BridgeComponentCapabilitiesStaticEntryIndividualPortOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentCapabilitiesIvlCapableOperGetCb::BridgeComponentCapabilitiesIvlCapableOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/capabilities/ivl-capable.
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
    sr::ErrorCode BridgeComponentCapabilitiesIvlCapableOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentCapabilitiesSvlCapableOperGetCb::BridgeComponentCapabilitiesSvlCapableOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/capabilities/svl-capable.
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
    sr::ErrorCode BridgeComponentCapabilitiesSvlCapableOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentCapabilitiesHybridCapableOperGetCb::BridgeComponentCapabilitiesHybridCapableOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/capabilities/hybrid-capable.
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
    sr::ErrorCode BridgeComponentCapabilitiesHybridCapableOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentCapabilitiesConfigurablePvidTaggingOperGetCb::BridgeComponentCapabilitiesConfigurablePvidTaggingOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/capabilities/configurable-pvid-tagging.
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
    sr::ErrorCode BridgeComponentCapabilitiesConfigurablePvidTaggingOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentCapabilitiesLocalVlanCapableOperGetCb::BridgeComponentCapabilitiesLocalVlanCapableOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/capabilities/local-vlan-capable.
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
    sr::ErrorCode BridgeComponentCapabilitiesLocalVlanCapableOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentCapabilitiesOperGetCb::BridgeComponentCapabilitiesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/capabilities.
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
    sr::ErrorCode BridgeComponentCapabilitiesOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseAgingTimeOperGetCb::BridgeComponentFilteringDatabaseAgingTimeOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/aging-time.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseAgingTimeOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseSizeOperGetCb::BridgeComponentFilteringDatabaseSizeOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/size.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseSizeOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseStaticEntriesOperGetCb::BridgeComponentFilteringDatabaseStaticEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/static-entries.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseStaticEntriesOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseDynamicEntriesOperGetCb::BridgeComponentFilteringDatabaseDynamicEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/dynamic-entries.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseDynamicEntriesOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseStaticVlanRegistrationEntriesOperGetCb::BridgeComponentFilteringDatabaseStaticVlanRegistrationEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/static-vlan-registration-entries.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseStaticVlanRegistrationEntriesOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseDynamicVlanRegistrationEntriesOperGetCb::BridgeComponentFilteringDatabaseDynamicVlanRegistrationEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/dynamic-vlan-registration-entries.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseDynamicVlanRegistrationEntriesOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseMacAddressRegistrationEntriesOperGetCb::BridgeComponentFilteringDatabaseMacAddressRegistrationEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/mac-address-registration-entries.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseMacAddressRegistrationEntriesOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseFilteringEntryDatabaseIdOperGetCb::BridgeComponentFilteringDatabaseFilteringEntryDatabaseIdOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/database-id.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryDatabaseIdOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseFilteringEntryVidsOperGetCb::BridgeComponentFilteringDatabaseFilteringEntryVidsOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/vids.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryVidsOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseFilteringEntryAddressOperGetCb::BridgeComponentFilteringDatabaseFilteringEntryAddressOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/address.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryAddressOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseFilteringEntryEntryTypeOperGetCb::BridgeComponentFilteringDatabaseFilteringEntryEntryTypeOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/entry-type.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryEntryTypeOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseFilteringEntryPortMapPortRefOperGetCb::BridgeComponentFilteringDatabaseFilteringEntryPortMapPortRefOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/port-ref.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryPortMapPortRefOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticFilteringEntriesControlElementOperGetCb::BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticFilteringEntriesControlElementOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries/control-element.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticFilteringEntriesControlElementOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticFilteringEntriesConnectionIdentifierOperGetCb::BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticFilteringEntriesConnectionIdentifierOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries/connection-identifier.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticFilteringEntriesConnectionIdentifierOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticFilteringEntriesOperGetCb::BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticFilteringEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticFilteringEntriesOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesRegistrarAdminControlOperGetCb::BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesRegistrarAdminControlOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries/registrar-admin-control.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesRegistrarAdminControlOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesVlanTransmittedOperGetCb::BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesVlanTransmittedOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries/vlan-transmitted.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesVlanTransmittedOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesOperGetCb::BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseFilteringEntryPortMapMacAddressRegistrationEntriesControlElementOperGetCb::BridgeComponentFilteringDatabaseFilteringEntryPortMapMacAddressRegistrationEntriesControlElementOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/mac-address-registration-entries/control-element.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryPortMapMacAddressRegistrationEntriesControlElementOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseFilteringEntryPortMapMacAddressRegistrationEntriesOperGetCb::BridgeComponentFilteringDatabaseFilteringEntryPortMapMacAddressRegistrationEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/mac-address-registration-entries.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryPortMapMacAddressRegistrationEntriesOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicVlanRegistrationEntriesControlElementOperGetCb::BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicVlanRegistrationEntriesControlElementOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-vlan-registration-entries/control-element.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicVlanRegistrationEntriesControlElementOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicVlanRegistrationEntriesOperGetCb::BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicVlanRegistrationEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-vlan-registration-entries.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicVlanRegistrationEntriesOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicReservationEntriesControlElementOperGetCb::BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicReservationEntriesControlElementOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-reservation-entries/control-element.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicReservationEntriesControlElementOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicReservationEntriesOperGetCb::BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicReservationEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-reservation-entries.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicReservationEntriesOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicFilteringEntriesControlElementOperGetCb::BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicFilteringEntriesControlElementOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-filtering-entries/control-element.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicFilteringEntriesControlElementOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicFilteringEntriesOperGetCb::BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicFilteringEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-filtering-entries.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicFilteringEntriesOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseFilteringEntryPortMapOperGetCb::BridgeComponentFilteringDatabaseFilteringEntryPortMapOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s'].
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryPortMapOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseFilteringEntryStatusOperGetCb::BridgeComponentFilteringDatabaseFilteringEntryStatusOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/status.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryStatusOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseFilteringEntryOperGetCb::BridgeComponentFilteringDatabaseFilteringEntryOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s'].
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
    sr::ErrorCode BridgeComponentFilteringDatabaseFilteringEntryOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryDatabaseIdOperGetCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryDatabaseIdOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/database-id.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryDatabaseIdOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryVidsOperGetCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryVidsOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/vids.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryVidsOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryEntryTypeOperGetCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryEntryTypeOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/entry-type.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryEntryTypeOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapPortRefOperGetCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapPortRefOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/port-ref.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapPortRefOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticFilteringEntriesControlElementOperGetCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticFilteringEntriesControlElementOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries/control-element.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticFilteringEntriesControlElementOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticFilteringEntriesConnectionIdentifierOperGetCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticFilteringEntriesConnectionIdentifierOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries/connection-identifier.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticFilteringEntriesConnectionIdentifierOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticFilteringEntriesOperGetCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticFilteringEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticFilteringEntriesOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticVlanRegistrationEntriesRegistrarAdminControlOperGetCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticVlanRegistrationEntriesRegistrarAdminControlOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries/registrar-admin-control.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticVlanRegistrationEntriesRegistrarAdminControlOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticVlanRegistrationEntriesVlanTransmittedOperGetCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticVlanRegistrationEntriesVlanTransmittedOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries/vlan-transmitted.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticVlanRegistrationEntriesVlanTransmittedOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticVlanRegistrationEntriesOperGetCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticVlanRegistrationEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticVlanRegistrationEntriesOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapMacAddressRegistrationEntriesControlElementOperGetCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapMacAddressRegistrationEntriesControlElementOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/mac-address-registration-entries/control-element.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapMacAddressRegistrationEntriesControlElementOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapMacAddressRegistrationEntriesOperGetCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapMacAddressRegistrationEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/mac-address-registration-entries.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapMacAddressRegistrationEntriesOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicVlanRegistrationEntriesControlElementOperGetCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicVlanRegistrationEntriesControlElementOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-vlan-registration-entries/control-element.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicVlanRegistrationEntriesControlElementOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicVlanRegistrationEntriesOperGetCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicVlanRegistrationEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-vlan-registration-entries.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicVlanRegistrationEntriesOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicReservationEntriesControlElementOperGetCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicReservationEntriesControlElementOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-reservation-entries/control-element.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicReservationEntriesControlElementOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicReservationEntriesOperGetCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicReservationEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-reservation-entries.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicReservationEntriesOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicFilteringEntriesControlElementOperGetCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicFilteringEntriesControlElementOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-filtering-entries/control-element.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicFilteringEntriesControlElementOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicFilteringEntriesOperGetCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicFilteringEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-filtering-entries.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicFilteringEntriesOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapOperGetCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s'].
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseVlanRegistrationEntryOperGetCb::BridgeComponentFilteringDatabaseVlanRegistrationEntryOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s'].
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
    sr::ErrorCode BridgeComponentFilteringDatabaseVlanRegistrationEntryOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentFilteringDatabaseOperGetCb::BridgeComponentFilteringDatabaseOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database.
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
    sr::ErrorCode BridgeComponentFilteringDatabaseOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
    {
        sr::ErrorCode error = sr::ErrorCode::Ok;

        std::string bridge_name = NlContext::getKeyValFromXpath("bridge",output->path())["name"];
        
        auto &nl_ctx = NlContext::getInstance();

        nl_ctx.refillCache();

        auto bridge = nl_ctx.getBridgeByName(bridge_name);

        if(!bridge){
            return sr::ErrorCode::NotFound;
        }

        uint32_t ageing_time = bridge->getAgeingTime();
        
        output->newPath("filtering-database/aging-time",std::to_string(ageing_time));

        return error;
    }

    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin operational context.
     *
     */
    BridgeComponentPermanentDatabaseSizeOperGetCb::BridgeComponentPermanentDatabaseSizeOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/size.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseSizeOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentPermanentDatabaseStaticEntriesOperGetCb::BridgeComponentPermanentDatabaseStaticEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/static-entries.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseStaticEntriesOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentPermanentDatabaseStaticVlanRegistrationEntriesOperGetCb::BridgeComponentPermanentDatabaseStaticVlanRegistrationEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/static-vlan-registration-entries.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseStaticVlanRegistrationEntriesOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentPermanentDatabaseFilteringEntryDatabaseIdOperGetCb::BridgeComponentPermanentDatabaseFilteringEntryDatabaseIdOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/database-id.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryDatabaseIdOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentPermanentDatabaseFilteringEntryVidsOperGetCb::BridgeComponentPermanentDatabaseFilteringEntryVidsOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/vids.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryVidsOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentPermanentDatabaseFilteringEntryAddressOperGetCb::BridgeComponentPermanentDatabaseFilteringEntryAddressOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/address.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryAddressOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentPermanentDatabaseFilteringEntryStatusOperGetCb::BridgeComponentPermanentDatabaseFilteringEntryStatusOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/status.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryStatusOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentPermanentDatabaseFilteringEntryPortMapPortRefOperGetCb::BridgeComponentPermanentDatabaseFilteringEntryPortMapPortRefOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/port-ref.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryPortMapPortRefOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticFilteringEntriesControlElementOperGetCb::BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticFilteringEntriesControlElementOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries/control-element.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticFilteringEntriesControlElementOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticFilteringEntriesConnectionIdentifierOperGetCb::BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticFilteringEntriesConnectionIdentifierOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries/connection-identifier.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticFilteringEntriesConnectionIdentifierOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticFilteringEntriesOperGetCb::BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticFilteringEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticFilteringEntriesOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesRegistrarAdminControlOperGetCb::BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesRegistrarAdminControlOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries/registrar-admin-control.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesRegistrarAdminControlOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesVlanTransmittedOperGetCb::BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesVlanTransmittedOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries/vlan-transmitted.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesVlanTransmittedOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesOperGetCb::BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentPermanentDatabaseFilteringEntryPortMapMacAddressRegistrationEntriesControlElementOperGetCb::BridgeComponentPermanentDatabaseFilteringEntryPortMapMacAddressRegistrationEntriesControlElementOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/mac-address-registration-entries/control-element.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryPortMapMacAddressRegistrationEntriesControlElementOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentPermanentDatabaseFilteringEntryPortMapMacAddressRegistrationEntriesOperGetCb::BridgeComponentPermanentDatabaseFilteringEntryPortMapMacAddressRegistrationEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/mac-address-registration-entries.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryPortMapMacAddressRegistrationEntriesOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicVlanRegistrationEntriesControlElementOperGetCb::BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicVlanRegistrationEntriesControlElementOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-vlan-registration-entries/control-element.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicVlanRegistrationEntriesControlElementOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicVlanRegistrationEntriesOperGetCb::BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicVlanRegistrationEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-vlan-registration-entries.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicVlanRegistrationEntriesOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicReservationEntriesControlElementOperGetCb::BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicReservationEntriesControlElementOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-reservation-entries/control-element.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicReservationEntriesControlElementOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicReservationEntriesOperGetCb::BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicReservationEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-reservation-entries.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicReservationEntriesOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicFilteringEntriesControlElementOperGetCb::BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicFilteringEntriesControlElementOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-filtering-entries/control-element.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicFilteringEntriesControlElementOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicFilteringEntriesOperGetCb::BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicFilteringEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-filtering-entries.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicFilteringEntriesOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentPermanentDatabaseFilteringEntryPortMapOperGetCb::BridgeComponentPermanentDatabaseFilteringEntryPortMapOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s'].
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryPortMapOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentPermanentDatabaseFilteringEntryOperGetCb::BridgeComponentPermanentDatabaseFilteringEntryOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s'].
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
    sr::ErrorCode BridgeComponentPermanentDatabaseFilteringEntryOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentPermanentDatabaseOperGetCb::BridgeComponentPermanentDatabaseOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database.
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
    sr::ErrorCode BridgeComponentPermanentDatabaseOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentBridgeVlanVersionOperGetCb::BridgeComponentBridgeVlanVersionOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/version.
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
    sr::ErrorCode BridgeComponentBridgeVlanVersionOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentBridgeVlanMaxVidsOperGetCb::BridgeComponentBridgeVlanMaxVidsOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/max-vids.
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
    sr::ErrorCode BridgeComponentBridgeVlanMaxVidsOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentBridgeVlanOverrideDefaultPvidOperGetCb::BridgeComponentBridgeVlanOverrideDefaultPvidOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/override-default-pvid.
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
    sr::ErrorCode BridgeComponentBridgeVlanOverrideDefaultPvidOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentBridgeVlanProtocolTemplateOperGetCb::BridgeComponentBridgeVlanProtocolTemplateOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/protocol-template.
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
    sr::ErrorCode BridgeComponentBridgeVlanProtocolTemplateOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentBridgeVlanMaxMstiOperGetCb::BridgeComponentBridgeVlanMaxMstiOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/max-msti.
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
    sr::ErrorCode BridgeComponentBridgeVlanMaxMstiOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    VlanVidOperGetCb::VlanVidOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vlan[vid='%s']/vid.
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
    sr::ErrorCode VlanVidOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    VlanNameOperGetCb::VlanNameOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vlan[vid='%s']/name.
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
    sr::ErrorCode VlanNameOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    VlanUntaggedPortsOperGetCb::VlanUntaggedPortsOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vlan[vid='%s']/untagged-ports.
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
    sr::ErrorCode VlanUntaggedPortsOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    VlanEgressPortsOperGetCb::VlanEgressPortsOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vlan[vid='%s']/egress-ports.
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
    sr::ErrorCode VlanEgressPortsOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentBridgeVlanVlanOperGetCb::BridgeComponentBridgeVlanVlanOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vlan[vid='%s'].
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
    sr::ErrorCode BridgeComponentBridgeVlanVlanOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentBridgeVlanProtocolGroupDatabaseDbIndexOperGetCb::BridgeComponentBridgeVlanProtocolGroupDatabaseDbIndexOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/protocol-group-database[db-index='%s']/db-index.
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
    sr::ErrorCode BridgeComponentBridgeVlanProtocolGroupDatabaseDbIndexOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentBridgeVlanProtocolGroupDatabaseFrameFormatTypeOperGetCb::BridgeComponentBridgeVlanProtocolGroupDatabaseFrameFormatTypeOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/protocol-group-database[db-index='%s']/frame-format-type.
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
    sr::ErrorCode BridgeComponentBridgeVlanProtocolGroupDatabaseFrameFormatTypeOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentBridgeVlanProtocolGroupDatabaseEthertypeOperGetCb::BridgeComponentBridgeVlanProtocolGroupDatabaseEthertypeOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/protocol-group-database[db-index='%s']/ethertype.
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
    sr::ErrorCode BridgeComponentBridgeVlanProtocolGroupDatabaseEthertypeOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentBridgeVlanProtocolGroupDatabaseProtocolIdOperGetCb::BridgeComponentBridgeVlanProtocolGroupDatabaseProtocolIdOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/protocol-group-database[db-index='%s']/protocol-id.
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
    sr::ErrorCode BridgeComponentBridgeVlanProtocolGroupDatabaseProtocolIdOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentBridgeVlanProtocolGroupDatabaseDsapSsapPairsLlcAddressOperGetCb::BridgeComponentBridgeVlanProtocolGroupDatabaseDsapSsapPairsLlcAddressOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/protocol-group-database[db-index='%s']/dsap-ssap-pairs/llc-address.
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
    sr::ErrorCode BridgeComponentBridgeVlanProtocolGroupDatabaseDsapSsapPairsLlcAddressOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentBridgeVlanProtocolGroupDatabaseDsapSsapPairsOperGetCb::BridgeComponentBridgeVlanProtocolGroupDatabaseDsapSsapPairsOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/protocol-group-database[db-index='%s']/dsap-ssap-pairs.
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
    sr::ErrorCode BridgeComponentBridgeVlanProtocolGroupDatabaseDsapSsapPairsOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentBridgeVlanProtocolGroupDatabaseGroupIdOperGetCb::BridgeComponentBridgeVlanProtocolGroupDatabaseGroupIdOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/protocol-group-database[db-index='%s']/group-id.
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
    sr::ErrorCode BridgeComponentBridgeVlanProtocolGroupDatabaseGroupIdOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentBridgeVlanProtocolGroupDatabaseOperGetCb::BridgeComponentBridgeVlanProtocolGroupDatabaseOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/protocol-group-database[db-index='%s'].
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
    sr::ErrorCode BridgeComponentBridgeVlanProtocolGroupDatabaseOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentBridgeVlanVidToFidAllocationVidsOperGetCb::BridgeComponentBridgeVlanVidToFidAllocationVidsOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vid-to-fid-allocation[vids='%s']/vids.
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
    sr::ErrorCode BridgeComponentBridgeVlanVidToFidAllocationVidsOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentBridgeVlanVidToFidAllocationFidOperGetCb::BridgeComponentBridgeVlanVidToFidAllocationFidOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vid-to-fid-allocation[vids='%s']/fid.
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
    sr::ErrorCode BridgeComponentBridgeVlanVidToFidAllocationFidOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentBridgeVlanVidToFidAllocationAllocationTypeOperGetCb::BridgeComponentBridgeVlanVidToFidAllocationAllocationTypeOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vid-to-fid-allocation[vids='%s']/allocation-type.
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
    sr::ErrorCode BridgeComponentBridgeVlanVidToFidAllocationAllocationTypeOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentBridgeVlanVidToFidAllocationOperGetCb::BridgeComponentBridgeVlanVidToFidAllocationOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vid-to-fid-allocation[vids='%s'].
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
    sr::ErrorCode BridgeComponentBridgeVlanVidToFidAllocationOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentBridgeVlanFidToVidAllocationFidOperGetCb::BridgeComponentBridgeVlanFidToVidAllocationFidOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/fid-to-vid-allocation[fid='%s']/fid.
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
    sr::ErrorCode BridgeComponentBridgeVlanFidToVidAllocationFidOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentBridgeVlanFidToVidAllocationAllocationTypeOperGetCb::BridgeComponentBridgeVlanFidToVidAllocationAllocationTypeOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/fid-to-vid-allocation[fid='%s']/allocation-type.
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
    sr::ErrorCode BridgeComponentBridgeVlanFidToVidAllocationAllocationTypeOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentBridgeVlanFidToVidAllocationVidOperGetCb::BridgeComponentBridgeVlanFidToVidAllocationVidOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/fid-to-vid-allocation[fid='%s']/vid.
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
    sr::ErrorCode BridgeComponentBridgeVlanFidToVidAllocationVidOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentBridgeVlanFidToVidAllocationOperGetCb::BridgeComponentBridgeVlanFidToVidAllocationOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/fid-to-vid-allocation[fid='%s'].
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
    sr::ErrorCode BridgeComponentBridgeVlanFidToVidAllocationOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentBridgeVlanVidToFidVidOperGetCb::BridgeComponentBridgeVlanVidToFidVidOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vid-to-fid[vid='%s']/vid.
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
    sr::ErrorCode BridgeComponentBridgeVlanVidToFidVidOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentBridgeVlanVidToFidFidOperGetCb::BridgeComponentBridgeVlanVidToFidFidOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vid-to-fid[vid='%s']/fid.
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
    sr::ErrorCode BridgeComponentBridgeVlanVidToFidFidOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentBridgeVlanVidToFidOperGetCb::BridgeComponentBridgeVlanVidToFidOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vid-to-fid[vid='%s'].
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
    sr::ErrorCode BridgeComponentBridgeVlanVidToFidOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentBridgeVlanOperGetCb::BridgeComponentBridgeVlanOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan.
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
    sr::ErrorCode BridgeComponentBridgeVlanOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
    {
        sr::ErrorCode error = sr::ErrorCode::Ok;

        // first obtain the vids
        auto& nl_ctx = NlContext::getInstance();
        nl_ctx.refillCache();

        // get bridge name
        std::string br_name = NlContext::getKeyValFromXpath("bridge", output->path())["name"];

        auto bridge = nl_ctx.getBridgeByName(br_name);

        if (!bridge) {
            SRPLG_LOG_ERR(getModuleLogPrefix(), "BridgeComponentBridgeVlanOperGetCb failed!");
            return sr::ErrorCode::NotFound;
        }

        std::vector<BridgeSlaveRef> br_slave_ifs = bridge->getSlaveInterfaces();

        for (auto&& i : br_slave_ifs) {

            auto vlan_list = i.getVlanList();
            for (auto&& vlan : vlan_list) {

                std::string untagged_egress = vlan.getUntaggedFlag() ? "untagged-ports" : "egress-ports";
                output->newPath("bridge-vlan/vlan[vid='" + std::to_string(vlan.getVid()) + "']", std::nullopt, libyang::CreationOptions::Update);
                output->newPath("bridge-vlan/vlan[vid='" + std::to_string(vlan.getVid()) + "']/" + untagged_egress, i.getName(), libyang::CreationOptions::Update);
            };
        };

        return error;
    }

    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin operational context.
     *
     */
    BridgeComponentBridgeMstMstidOperGetCb::BridgeComponentBridgeMstMstidOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-mst/mstid.
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
    sr::ErrorCode BridgeComponentBridgeMstMstidOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentBridgeMstFidToMstidFidOperGetCb::BridgeComponentBridgeMstFidToMstidFidOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-mst/fid-to-mstid[fid='%s']/fid.
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
    sr::ErrorCode BridgeComponentBridgeMstFidToMstidFidOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentBridgeMstFidToMstidMstidOperGetCb::BridgeComponentBridgeMstFidToMstidMstidOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-mst/fid-to-mstid[fid='%s']/mstid.
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
    sr::ErrorCode BridgeComponentBridgeMstFidToMstidMstidOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentBridgeMstFidToMstidOperGetCb::BridgeComponentBridgeMstFidToMstidOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-mst/fid-to-mstid[fid='%s'].
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
    sr::ErrorCode BridgeComponentBridgeMstFidToMstidOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentBridgeMstFidToMstidAllocationFidsOperGetCb::BridgeComponentBridgeMstFidToMstidAllocationFidsOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-mst/fid-to-mstid-allocation[fids='%s']/fids.
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
    sr::ErrorCode BridgeComponentBridgeMstFidToMstidAllocationFidsOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentBridgeMstFidToMstidAllocationMstidOperGetCb::BridgeComponentBridgeMstFidToMstidAllocationMstidOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-mst/fid-to-mstid-allocation[fids='%s']/mstid.
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
    sr::ErrorCode BridgeComponentBridgeMstFidToMstidAllocationMstidOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentBridgeMstFidToMstidAllocationOperGetCb::BridgeComponentBridgeMstFidToMstidAllocationOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-mst/fid-to-mstid-allocation[fids='%s'].
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
    sr::ErrorCode BridgeComponentBridgeMstFidToMstidAllocationOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentBridgeMstOperGetCb::BridgeComponentBridgeMstOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-mst.
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
    sr::ErrorCode BridgeComponentBridgeMstOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
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
    BridgeComponentOperGetCb::BridgeComponentOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s'].
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
    sr::ErrorCode BridgeComponentOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
    {
        sr::ErrorCode error = sr::ErrorCode::Ok;

        std::string component_name = srpc::extractListKeyFromXPath("bridge", "name", output->path());
        output->newPath("component[name='" + component_name + "']");
        return error;
    }

    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin operational context.
     *
     */
    BridgeOperGetCb::BridgeOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s'].
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
    sr::ErrorCode BridgeOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
    {
        sr::ErrorCode error = sr::ErrorCode::Ok;
        auto& nl_ctx = NlContext::getInstance();

        std::vector<BridgeRef> bridges = nl_ctx.getBridgeInterfaces();

        for (auto& bridge : bridges) {
            output->newPath("bridge[name='" + bridge.getName() + "']");
        };

        return error;
    }

    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin operational context.
     *
     */
    BridgesOperGetCb::BridgesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ieee802-dot1q-bridge:bridges.
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
    sr::ErrorCode BridgesOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
    {
        sr::ErrorCode error = sr::ErrorCode::Ok;
        return error;
    }

}
}
