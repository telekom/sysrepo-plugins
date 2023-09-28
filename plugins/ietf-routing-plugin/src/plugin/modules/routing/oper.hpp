#pragma once

#include "context.hpp"

#include <iostream>
#include <optional>
#include <string_view>

#include <sysrepo-cpp/Session.hpp>
#include <libyang-cpp/Context.hpp>

namespace sr = sysrepo;
namespace ly = libyang;

namespace ietf::rt {
namespace sub::oper {
    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ietf-routing:routing.
     */
    class RoutingOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        RoutingOperGetCb(std::shared_ptr<RoutingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ietf-routing:routing.
         *
         * @param session An implicit session for the callback.
         * @param subscriptionId ID the subscription associated with the callback.
         * @param moduleName The module name used for subscribing.
         * @param subXPath The optional xpath used at the time of subscription.
         * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
         * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
         *
         * @return Error code.
         *
         */
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath,
            std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<RoutingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ietf-routing:routing/interfaces.
     */
    class RoutingInterfacesOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        RoutingInterfacesOperGetCb(std::shared_ptr<RoutingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ietf-routing:routing.
         *
         * @param session An implicit session for the callback.
         * @param subscriptionId ID the subscription associated with the callback.
         * @param moduleName The module name used for subscribing.
         * @param subXPath The optional xpath used at the time of subscription.
         * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
         * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
         *
         * @return Error code.
         *
         */
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath,
            std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<RoutingOperationalContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ietf-routing:routing/rib.
     */
    class RoutingRibOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        RoutingRibOperGetCb(std::shared_ptr<RoutingOperationalContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ietf-routing:routing.
         *
         * @param session An implicit session for the callback.
         * @param subscriptionId ID the subscription associated with the callback.
         * @param moduleName The module name used for subscribing.
         * @param subXPath The optional xpath used at the time of subscription.
         * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
         * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
         *
         * @return Error code.
         *
         */
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath,
            std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output);

    private:
        std::shared_ptr<RoutingOperationalContext> m_ctx;
    };
}
}
