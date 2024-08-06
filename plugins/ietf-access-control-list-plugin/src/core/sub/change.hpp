#pragma once

#include "core/context.hpp"

#include <optional>
#include <string_view>
#include "core/sub/context.hpp"

#include <sysrepo-cpp/Session.hpp>

namespace sr = sysrepo;

namespace ietf::acl {
namespace sub::change {
    /**
     * @brief sysrepo-plugin-generator: Generated module change functor for path /ietf-access-control-list:acls/acl[name='%s'].
     */
    class AclModuleChangeCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin module change context.
         *
         */
        AclModuleChangeCb(std::shared_ptr<AclModuleChangesContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated module change operator() for path /ietf-access-control-list:acls/acl[name='%s'].
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath,
            sr::Event event, uint32_t requestId);

    private:
        std::shared_ptr<AclModuleChangesContext> m_ctx;
    };

     /**
     * @brief sysrepo-plugin-generator: Generated module change functor for path /ietf-access-control-list:acls/acl[name='%s']/aces/ace.
     */
    class AclAcesAceModuleChangeCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin module change context.
         *
         */
        AclAcesAceModuleChangeCb(std::shared_ptr<AclModuleChangesContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated module change operator() for path /ietf-access-control-list:acls/acl[name='%s']/aces/ace.
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath,
            sr::Event event, uint32_t requestId);

    private:
        std::shared_ptr<AclModuleChangesContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated module change functor for path
     * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s'].
     */
    class AclAceActFwModuleChangeCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin module change context.
         *
         */
        AclAceActFwModuleChangeCb(std::shared_ptr<AclModuleChangesContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated module change operator() for path
         * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s'].
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
        sr::ErrorCode operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath,
            sr::Event event, uint32_t requestId);

    private:
        std::shared_ptr<AclModuleChangesContext> m_ctx;
    };

}
}