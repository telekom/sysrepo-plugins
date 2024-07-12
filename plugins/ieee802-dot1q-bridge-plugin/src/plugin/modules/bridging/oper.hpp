#pragma once

#include "context.hpp"

#include <optional>
#include <string_view>
#include "srpcpp/netlink.hpp"
#include "srpc/common.h"
#include "common.hpp"

#include <sysrepo-cpp/Session.hpp>
#include <libyang-cpp/Context.hpp>

namespace sr = sysrepo;
namespace ly = libyang;

namespace ieee::br {
namespace sub::oper {
    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/name.
     */
    class BridgeNameOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeNameOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/name.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/address.
     */
    class BridgeAddressOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeAddressOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/address.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/bridge-type.
     */
    class BridgeBridgeTypeOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeBridgeTypeOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/bridge-type.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/ports.
     */
    class BridgePortsOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgePortsOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/ports.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/up-time.
     */
    class BridgeUpTimeOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeUpTimeOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/up-time.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/components.
     */
    class BridgeComponentsOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentsOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/components.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/name.
     */
    class BridgeComponentNameOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentNameOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/name.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/id.
     */
    class BridgeComponentIdOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentIdOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/id.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/type.
     */
    class BridgeComponentTypeOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentTypeOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/type.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/address.
     */
    class BridgeComponentAddressOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentAddressOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/address.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/traffic-class-enabled.
     */
    class BridgeComponentTrafficClassEnabledOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentTrafficClassEnabledOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/traffic-class-enabled.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/ports.
     */
    class BridgeComponentPortsOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentPortsOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/ports.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-port.
     */
    class BridgeComponentBridgePortOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentBridgePortOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-port.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/capabilities/extended-filtering.
     */
    class BridgeComponentCapabilitiesExtendedFilteringOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentCapabilitiesExtendedFilteringOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/capabilities/extended-filtering.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/capabilities/traffic-classes.
     */
    class BridgeComponentCapabilitiesTrafficClassesOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentCapabilitiesTrafficClassesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/capabilities/traffic-classes.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/capabilities/static-entry-individual-port.
     */
    class BridgeComponentCapabilitiesStaticEntryIndividualPortOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentCapabilitiesStaticEntryIndividualPortOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/capabilities/static-entry-individual-port.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/capabilities/ivl-capable.
     */
    class BridgeComponentCapabilitiesIvlCapableOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentCapabilitiesIvlCapableOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/capabilities/ivl-capable.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/capabilities/svl-capable.
     */
    class BridgeComponentCapabilitiesSvlCapableOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentCapabilitiesSvlCapableOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/capabilities/svl-capable.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/capabilities/hybrid-capable.
     */
    class BridgeComponentCapabilitiesHybridCapableOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentCapabilitiesHybridCapableOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/capabilities/hybrid-capable.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/capabilities/configurable-pvid-tagging.
     */
    class BridgeComponentCapabilitiesConfigurablePvidTaggingOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentCapabilitiesConfigurablePvidTaggingOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/capabilities/configurable-pvid-tagging.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/capabilities/local-vlan-capable.
     */
    class BridgeComponentCapabilitiesLocalVlanCapableOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentCapabilitiesLocalVlanCapableOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/capabilities/local-vlan-capable.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/capabilities.
     */
    class BridgeComponentCapabilitiesOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentCapabilitiesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/capabilities.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/aging-time.
     */
    class BridgeComponentFilteringDatabaseAgingTimeOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseAgingTimeOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/aging-time.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/size.
     */
    class BridgeComponentFilteringDatabaseSizeOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseSizeOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/size.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/static-entries.
     */
    class BridgeComponentFilteringDatabaseStaticEntriesOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseStaticEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/static-entries.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/dynamic-entries.
     */
    class BridgeComponentFilteringDatabaseDynamicEntriesOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseDynamicEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/dynamic-entries.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/static-vlan-registration-entries.
     */
    class BridgeComponentFilteringDatabaseStaticVlanRegistrationEntriesOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseStaticVlanRegistrationEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/static-vlan-registration-entries.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/dynamic-vlan-registration-entries.
     */
    class BridgeComponentFilteringDatabaseDynamicVlanRegistrationEntriesOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseDynamicVlanRegistrationEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/dynamic-vlan-registration-entries.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/mac-address-registration-entries.
     */
    class BridgeComponentFilteringDatabaseMacAddressRegistrationEntriesOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseMacAddressRegistrationEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/mac-address-registration-entries.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/database-id.
     */
    class BridgeComponentFilteringDatabaseFilteringEntryDatabaseIdOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseFilteringEntryDatabaseIdOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/database-id.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/vids.
     */
    class BridgeComponentFilteringDatabaseFilteringEntryVidsOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseFilteringEntryVidsOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/vids.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/address.
     */
    class BridgeComponentFilteringDatabaseFilteringEntryAddressOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseFilteringEntryAddressOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/address.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/entry-type.
     */
    class BridgeComponentFilteringDatabaseFilteringEntryEntryTypeOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseFilteringEntryEntryTypeOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/entry-type.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/port-ref.
     */
    class BridgeComponentFilteringDatabaseFilteringEntryPortMapPortRefOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseFilteringEntryPortMapPortRefOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/port-ref.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries/control-element.
     */
    class BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticFilteringEntriesControlElementOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticFilteringEntriesControlElementOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries/control-element.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries/connection-identifier.
     */
    class BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticFilteringEntriesConnectionIdentifierOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticFilteringEntriesConnectionIdentifierOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries/connection-identifier.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries.
     */
    class BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticFilteringEntriesOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticFilteringEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries/registrar-admin-control.
     */
    class BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesRegistrarAdminControlOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesRegistrarAdminControlOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries/registrar-admin-control.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries/vlan-transmitted.
     */
    class BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesVlanTransmittedOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesVlanTransmittedOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries/vlan-transmitted.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries.
     */
    class BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/mac-address-registration-entries/control-element.
     */
    class BridgeComponentFilteringDatabaseFilteringEntryPortMapMacAddressRegistrationEntriesControlElementOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseFilteringEntryPortMapMacAddressRegistrationEntriesControlElementOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/mac-address-registration-entries/control-element.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/mac-address-registration-entries.
     */
    class BridgeComponentFilteringDatabaseFilteringEntryPortMapMacAddressRegistrationEntriesOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseFilteringEntryPortMapMacAddressRegistrationEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/mac-address-registration-entries.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-vlan-registration-entries/control-element.
     */
    class BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicVlanRegistrationEntriesControlElementOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicVlanRegistrationEntriesControlElementOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-vlan-registration-entries/control-element.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-vlan-registration-entries.
     */
    class BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicVlanRegistrationEntriesOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicVlanRegistrationEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-vlan-registration-entries.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-reservation-entries/control-element.
     */
    class BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicReservationEntriesControlElementOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicReservationEntriesControlElementOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-reservation-entries/control-element.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-reservation-entries.
     */
    class BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicReservationEntriesOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicReservationEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-reservation-entries.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-filtering-entries/control-element.
     */
    class BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicFilteringEntriesControlElementOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicFilteringEntriesControlElementOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-filtering-entries/control-element.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-filtering-entries.
     */
    class BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicFilteringEntriesOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseFilteringEntryPortMapDynamicFilteringEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-filtering-entries.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s'].
     */
    class BridgeComponentFilteringDatabaseFilteringEntryPortMapOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseFilteringEntryPortMapOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s'].
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/status.
     */
    class BridgeComponentFilteringDatabaseFilteringEntryStatusOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseFilteringEntryStatusOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/status.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s'].
     */
    class BridgeComponentFilteringDatabaseFilteringEntryOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseFilteringEntryOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/filtering-entry[address='%s'][vids='%s'][database-id='%s'].
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/database-id.
     */
    class BridgeComponentFilteringDatabaseVlanRegistrationEntryDatabaseIdOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseVlanRegistrationEntryDatabaseIdOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/database-id.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/vids.
     */
    class BridgeComponentFilteringDatabaseVlanRegistrationEntryVidsOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseVlanRegistrationEntryVidsOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/vids.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/entry-type.
     */
    class BridgeComponentFilteringDatabaseVlanRegistrationEntryEntryTypeOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseVlanRegistrationEntryEntryTypeOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/entry-type.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/port-ref.
     */
    class BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapPortRefOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapPortRefOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/port-ref.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries/control-element.
     */
    class BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticFilteringEntriesControlElementOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticFilteringEntriesControlElementOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries/control-element.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries/connection-identifier.
     */
    class BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticFilteringEntriesConnectionIdentifierOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticFilteringEntriesConnectionIdentifierOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries/connection-identifier.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries.
     */
    class BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticFilteringEntriesOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticFilteringEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries/registrar-admin-control.
     */
    class BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticVlanRegistrationEntriesRegistrarAdminControlOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticVlanRegistrationEntriesRegistrarAdminControlOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries/registrar-admin-control.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries/vlan-transmitted.
     */
    class BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticVlanRegistrationEntriesVlanTransmittedOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticVlanRegistrationEntriesVlanTransmittedOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries/vlan-transmitted.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries.
     */
    class BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticVlanRegistrationEntriesOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapStaticVlanRegistrationEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/mac-address-registration-entries/control-element.
     */
    class BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapMacAddressRegistrationEntriesControlElementOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapMacAddressRegistrationEntriesControlElementOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/mac-address-registration-entries/control-element.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/mac-address-registration-entries.
     */
    class BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapMacAddressRegistrationEntriesOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapMacAddressRegistrationEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/mac-address-registration-entries.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-vlan-registration-entries/control-element.
     */
    class BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicVlanRegistrationEntriesControlElementOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicVlanRegistrationEntriesControlElementOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-vlan-registration-entries/control-element.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-vlan-registration-entries.
     */
    class BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicVlanRegistrationEntriesOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicVlanRegistrationEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-vlan-registration-entries.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-reservation-entries/control-element.
     */
    class BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicReservationEntriesControlElementOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicReservationEntriesControlElementOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-reservation-entries/control-element.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-reservation-entries.
     */
    class BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicReservationEntriesOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicReservationEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-reservation-entries.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-filtering-entries/control-element.
     */
    class BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicFilteringEntriesControlElementOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicFilteringEntriesControlElementOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-filtering-entries/control-element.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-filtering-entries.
     */
    class BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicFilteringEntriesOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapDynamicFilteringEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-filtering-entries.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s'].
     */
    class BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseVlanRegistrationEntryPortMapOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s']/port-map[port-ref='%s'].
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s'].
     */
    class BridgeComponentFilteringDatabaseVlanRegistrationEntryOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseVlanRegistrationEntryOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database/vlan-registration-entry[vids='%s'][database-id='%s'].
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database.
     */
    class BridgeComponentFilteringDatabaseOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentFilteringDatabaseOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/filtering-database.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/size.
     */
    class BridgeComponentPermanentDatabaseSizeOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentPermanentDatabaseSizeOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/size.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/static-entries.
     */
    class BridgeComponentPermanentDatabaseStaticEntriesOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentPermanentDatabaseStaticEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/static-entries.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/static-vlan-registration-entries.
     */
    class BridgeComponentPermanentDatabaseStaticVlanRegistrationEntriesOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentPermanentDatabaseStaticVlanRegistrationEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/static-vlan-registration-entries.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/database-id.
     */
    class BridgeComponentPermanentDatabaseFilteringEntryDatabaseIdOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentPermanentDatabaseFilteringEntryDatabaseIdOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/database-id.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/vids.
     */
    class BridgeComponentPermanentDatabaseFilteringEntryVidsOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentPermanentDatabaseFilteringEntryVidsOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/vids.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/address.
     */
    class BridgeComponentPermanentDatabaseFilteringEntryAddressOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentPermanentDatabaseFilteringEntryAddressOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/address.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/status.
     */
    class BridgeComponentPermanentDatabaseFilteringEntryStatusOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentPermanentDatabaseFilteringEntryStatusOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/status.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/port-ref.
     */
    class BridgeComponentPermanentDatabaseFilteringEntryPortMapPortRefOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentPermanentDatabaseFilteringEntryPortMapPortRefOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/port-ref.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries/control-element.
     */
    class BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticFilteringEntriesControlElementOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticFilteringEntriesControlElementOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries/control-element.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries/connection-identifier.
     */
    class BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticFilteringEntriesConnectionIdentifierOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticFilteringEntriesConnectionIdentifierOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries/connection-identifier.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries.
     */
    class BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticFilteringEntriesOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticFilteringEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-filtering-entries.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries/registrar-admin-control.
     */
    class BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesRegistrarAdminControlOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesRegistrarAdminControlOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries/registrar-admin-control.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries/vlan-transmitted.
     */
    class BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesVlanTransmittedOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesVlanTransmittedOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries/vlan-transmitted.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries.
     */
    class BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentPermanentDatabaseFilteringEntryPortMapStaticVlanRegistrationEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/static-vlan-registration-entries.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/mac-address-registration-entries/control-element.
     */
    class BridgeComponentPermanentDatabaseFilteringEntryPortMapMacAddressRegistrationEntriesControlElementOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentPermanentDatabaseFilteringEntryPortMapMacAddressRegistrationEntriesControlElementOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/mac-address-registration-entries/control-element.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/mac-address-registration-entries.
     */
    class BridgeComponentPermanentDatabaseFilteringEntryPortMapMacAddressRegistrationEntriesOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentPermanentDatabaseFilteringEntryPortMapMacAddressRegistrationEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/mac-address-registration-entries.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-vlan-registration-entries/control-element.
     */
    class BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicVlanRegistrationEntriesControlElementOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicVlanRegistrationEntriesControlElementOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-vlan-registration-entries/control-element.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-vlan-registration-entries.
     */
    class BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicVlanRegistrationEntriesOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicVlanRegistrationEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-vlan-registration-entries.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-reservation-entries/control-element.
     */
    class BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicReservationEntriesControlElementOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicReservationEntriesControlElementOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-reservation-entries/control-element.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-reservation-entries.
     */
    class BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicReservationEntriesOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicReservationEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-reservation-entries.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-filtering-entries/control-element.
     */
    class BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicFilteringEntriesControlElementOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicFilteringEntriesControlElementOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-filtering-entries/control-element.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-filtering-entries.
     */
    class BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicFilteringEntriesOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentPermanentDatabaseFilteringEntryPortMapDynamicFilteringEntriesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s']/dynamic-filtering-entries.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s'].
     */
    class BridgeComponentPermanentDatabaseFilteringEntryPortMapOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentPermanentDatabaseFilteringEntryPortMapOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s']/port-map[port-ref='%s'].
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s'].
     */
    class BridgeComponentPermanentDatabaseFilteringEntryOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentPermanentDatabaseFilteringEntryOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database/filtering-entry[address='%s'][vids='%s'][database-id='%s'].
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database.
     */
    class BridgeComponentPermanentDatabaseOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentPermanentDatabaseOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/permanent-database.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/version.
     */
    class BridgeComponentBridgeVlanVersionOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentBridgeVlanVersionOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/version.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/max-vids.
     */
    class BridgeComponentBridgeVlanMaxVidsOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentBridgeVlanMaxVidsOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/max-vids.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/override-default-pvid.
     */
    class BridgeComponentBridgeVlanOverrideDefaultPvidOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentBridgeVlanOverrideDefaultPvidOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/override-default-pvid.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/protocol-template.
     */
    class BridgeComponentBridgeVlanProtocolTemplateOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentBridgeVlanProtocolTemplateOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/protocol-template.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/max-msti.
     */
    class BridgeComponentBridgeVlanMaxMstiOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentBridgeVlanMaxMstiOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/max-msti.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vlan[vid='%s']/vid.
     */
    class VlanVidOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        VlanVidOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vlan[vid='%s']/vid.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vlan[vid='%s']/name.
     */
    class VlanNameOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        VlanNameOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vlan[vid='%s']/name.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vlan[vid='%s']/untagged-ports.
     */
    class VlanUntaggedPortsOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        VlanUntaggedPortsOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vlan[vid='%s']/untagged-ports.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vlan[vid='%s']/egress-ports.
     */
    class VlanEgressPortsOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        VlanEgressPortsOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vlan[vid='%s']/egress-ports.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vlan[vid='%s'].
     */
    class BridgeComponentBridgeVlanVlanOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentBridgeVlanVlanOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vlan[vid='%s'].
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/protocol-group-database[db-index='%s']/db-index.
     */
    class BridgeComponentBridgeVlanProtocolGroupDatabaseDbIndexOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentBridgeVlanProtocolGroupDatabaseDbIndexOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/protocol-group-database[db-index='%s']/db-index.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/protocol-group-database[db-index='%s']/frame-format-type.
     */
    class BridgeComponentBridgeVlanProtocolGroupDatabaseFrameFormatTypeOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentBridgeVlanProtocolGroupDatabaseFrameFormatTypeOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/protocol-group-database[db-index='%s']/frame-format-type.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/protocol-group-database[db-index='%s']/ethertype.
     */
    class BridgeComponentBridgeVlanProtocolGroupDatabaseEthertypeOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentBridgeVlanProtocolGroupDatabaseEthertypeOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/protocol-group-database[db-index='%s']/ethertype.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/protocol-group-database[db-index='%s']/protocol-id.
     */
    class BridgeComponentBridgeVlanProtocolGroupDatabaseProtocolIdOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentBridgeVlanProtocolGroupDatabaseProtocolIdOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/protocol-group-database[db-index='%s']/protocol-id.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/protocol-group-database[db-index='%s']/dsap-ssap-pairs/llc-address.
     */
    class BridgeComponentBridgeVlanProtocolGroupDatabaseDsapSsapPairsLlcAddressOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentBridgeVlanProtocolGroupDatabaseDsapSsapPairsLlcAddressOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/protocol-group-database[db-index='%s']/dsap-ssap-pairs/llc-address.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/protocol-group-database[db-index='%s']/dsap-ssap-pairs.
     */
    class BridgeComponentBridgeVlanProtocolGroupDatabaseDsapSsapPairsOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentBridgeVlanProtocolGroupDatabaseDsapSsapPairsOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/protocol-group-database[db-index='%s']/dsap-ssap-pairs.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/protocol-group-database[db-index='%s']/group-id.
     */
    class BridgeComponentBridgeVlanProtocolGroupDatabaseGroupIdOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentBridgeVlanProtocolGroupDatabaseGroupIdOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/protocol-group-database[db-index='%s']/group-id.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/protocol-group-database[db-index='%s'].
     */
    class BridgeComponentBridgeVlanProtocolGroupDatabaseOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentBridgeVlanProtocolGroupDatabaseOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/protocol-group-database[db-index='%s'].
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vid-to-fid-allocation[vids='%s']/vids.
     */
    class BridgeComponentBridgeVlanVidToFidAllocationVidsOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentBridgeVlanVidToFidAllocationVidsOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vid-to-fid-allocation[vids='%s']/vids.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vid-to-fid-allocation[vids='%s']/fid.
     */
    class BridgeComponentBridgeVlanVidToFidAllocationFidOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentBridgeVlanVidToFidAllocationFidOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vid-to-fid-allocation[vids='%s']/fid.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vid-to-fid-allocation[vids='%s']/allocation-type.
     */
    class BridgeComponentBridgeVlanVidToFidAllocationAllocationTypeOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentBridgeVlanVidToFidAllocationAllocationTypeOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vid-to-fid-allocation[vids='%s']/allocation-type.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vid-to-fid-allocation[vids='%s'].
     */
    class BridgeComponentBridgeVlanVidToFidAllocationOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentBridgeVlanVidToFidAllocationOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vid-to-fid-allocation[vids='%s'].
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/fid-to-vid-allocation[fid='%s']/fid.
     */
    class BridgeComponentBridgeVlanFidToVidAllocationFidOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentBridgeVlanFidToVidAllocationFidOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/fid-to-vid-allocation[fid='%s']/fid.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/fid-to-vid-allocation[fid='%s']/allocation-type.
     */
    class BridgeComponentBridgeVlanFidToVidAllocationAllocationTypeOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentBridgeVlanFidToVidAllocationAllocationTypeOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/fid-to-vid-allocation[fid='%s']/allocation-type.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/fid-to-vid-allocation[fid='%s']/vid.
     */
    class BridgeComponentBridgeVlanFidToVidAllocationVidOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentBridgeVlanFidToVidAllocationVidOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/fid-to-vid-allocation[fid='%s']/vid.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/fid-to-vid-allocation[fid='%s'].
     */
    class BridgeComponentBridgeVlanFidToVidAllocationOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentBridgeVlanFidToVidAllocationOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/fid-to-vid-allocation[fid='%s'].
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vid-to-fid[vid='%s']/vid.
     */
    class BridgeComponentBridgeVlanVidToFidVidOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentBridgeVlanVidToFidVidOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vid-to-fid[vid='%s']/vid.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vid-to-fid[vid='%s']/fid.
     */
    class BridgeComponentBridgeVlanVidToFidFidOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentBridgeVlanVidToFidFidOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vid-to-fid[vid='%s']/fid.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vid-to-fid[vid='%s'].
     */
    class BridgeComponentBridgeVlanVidToFidOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentBridgeVlanVidToFidOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan/vid-to-fid[vid='%s'].
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan.
     */
    class BridgeComponentBridgeVlanOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentBridgeVlanOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-vlan.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-mst/mstid.
     */
    class BridgeComponentBridgeMstMstidOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentBridgeMstMstidOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-mst/mstid.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-mst/fid-to-mstid[fid='%s']/fid.
     */
    class BridgeComponentBridgeMstFidToMstidFidOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentBridgeMstFidToMstidFidOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-mst/fid-to-mstid[fid='%s']/fid.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-mst/fid-to-mstid[fid='%s']/mstid.
     */
    class BridgeComponentBridgeMstFidToMstidMstidOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentBridgeMstFidToMstidMstidOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-mst/fid-to-mstid[fid='%s']/mstid.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-mst/fid-to-mstid[fid='%s'].
     */
    class BridgeComponentBridgeMstFidToMstidOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentBridgeMstFidToMstidOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-mst/fid-to-mstid[fid='%s'].
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-mst/fid-to-mstid-allocation[fids='%s']/fids.
     */
    class BridgeComponentBridgeMstFidToMstidAllocationFidsOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentBridgeMstFidToMstidAllocationFidsOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-mst/fid-to-mstid-allocation[fids='%s']/fids.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-mst/fid-to-mstid-allocation[fids='%s']/mstid.
     */
    class BridgeComponentBridgeMstFidToMstidAllocationMstidOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentBridgeMstFidToMstidAllocationMstidOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-mst/fid-to-mstid-allocation[fids='%s']/mstid.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-mst/fid-to-mstid-allocation[fids='%s'].
     */
    class BridgeComponentBridgeMstFidToMstidAllocationOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentBridgeMstFidToMstidAllocationOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-mst/fid-to-mstid-allocation[fids='%s'].
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-mst.
     */
    class BridgeComponentBridgeMstOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentBridgeMstOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s']/bridge-mst.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s'].
     */
    class BridgeComponentOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeComponentOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s']/component[name='%s'].
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges/bridge[name='%s'].
     */
    class BridgeOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgeOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges/bridge[name='%s'].
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ieee802-dot1q-bridge:bridges.
     */
    class BridgesOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        BridgesOperGetCb(std::shared_ptr<BridgingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ieee802-dot1q-bridge:bridges.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<BridgingOperationalContext> m_ctx;
    };

}
}
