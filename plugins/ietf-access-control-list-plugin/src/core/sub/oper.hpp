#pragma once

#include "core/context.hpp"

#include <iostream>
#include <optional>
#include <string_view>

#include <sysrepo-cpp/Session.hpp>
#include <libyang-cpp/Context.hpp>

namespace sr = sysrepo;
namespace ly = libyang;

namespace ietf::acl {
namespace sub::oper {
    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ietf-access-control-list:acls/acl[name='%s']/name.
     */
    class AclNameOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclNameOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ietf-access-control-list:acls/acl[name='%s']/name.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ietf-access-control-list:acls/acl[name='%s']/type.
     */
    class AclTypeOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclTypeOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ietf-access-control-list:acls/acl[name='%s']/type.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/name.
     */
    class AclAcesAceNameOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceNameOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/name.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/eth/destination-mac-address.
     */
    class AclAcesAceMatchesEthDestinationMacAddressOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesEthDestinationMacAddressOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/eth/destination-mac-address.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/eth/destination-mac-address-mask.
     */
    class AclAcesAceMatchesEthDestinationMacAddressMaskOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesEthDestinationMacAddressMaskOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/eth/destination-mac-address-mask.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/eth/source-mac-address.
     */
    class AclAcesAceMatchesEthSourceMacAddressOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesEthSourceMacAddressOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/eth/source-mac-address.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/eth/source-mac-address-mask.
     */
    class AclAcesAceMatchesEthSourceMacAddressMaskOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesEthSourceMacAddressMaskOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/eth/source-mac-address-mask.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/eth/ethertype.
     */
    class AclAcesAceMatchesEthEthertypeOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesEthEthertypeOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/eth/ethertype.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/eth.
     */
    class AclAcesAceMatchesEthOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesEthOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/eth.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv4/dscp.
     */
    class AclAcesAceMatchesIpv4DscpOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesIpv4DscpOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv4/dscp.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv4/ecn.
     */
    class AclAcesAceMatchesIpv4EcnOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesIpv4EcnOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv4/ecn.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv4/length.
     */
    class AclAcesAceMatchesIpv4LengthOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesIpv4LengthOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv4/length.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv4/ttl.
     */
    class AclAcesAceMatchesIpv4TtlOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesIpv4TtlOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv4/ttl.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv4/protocol.
     */
    class AclAcesAceMatchesIpv4ProtocolOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesIpv4ProtocolOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv4/protocol.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv4/ihl.
     */
    class AclAcesAceMatchesIpv4IhlOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesIpv4IhlOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv4/ihl.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv4/flags.
     */
    class AclAcesAceMatchesIpv4FlagsOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesIpv4FlagsOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv4/flags.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv4/offset.
     */
    class AclAcesAceMatchesIpv4OffsetOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesIpv4OffsetOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv4/offset.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv4/identification.
     */
    class AclAcesAceMatchesIpv4IdentificationOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesIpv4IdentificationOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv4/identification.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv4/destination-ipv4-network.
     */
    class AclAcesAceMatchesIpv4DestinationIpv4NetworkOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesIpv4DestinationIpv4NetworkOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv4/destination-ipv4-network.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv4/source-ipv4-network.
     */
    class AclAcesAceMatchesIpv4SourceIpv4NetworkOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesIpv4SourceIpv4NetworkOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv4/source-ipv4-network.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv4.
     */
    class AclAcesAceMatchesIpv4OperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesIpv4OperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv4.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv6/dscp.
     */
    class AclAcesAceMatchesIpv6DscpOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesIpv6DscpOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv6/dscp.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv6/ecn.
     */
    class AclAcesAceMatchesIpv6EcnOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesIpv6EcnOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv6/ecn.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv6/length.
     */
    class AclAcesAceMatchesIpv6LengthOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesIpv6LengthOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv6/length.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv6/ttl.
     */
    class AclAcesAceMatchesIpv6TtlOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesIpv6TtlOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv6/ttl.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv6/protocol.
     */
    class AclAcesAceMatchesIpv6ProtocolOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesIpv6ProtocolOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv6/protocol.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv6/destination-ipv6-network.
     */
    class AclAcesAceMatchesIpv6DestinationIpv6NetworkOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesIpv6DestinationIpv6NetworkOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv6/destination-ipv6-network.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv6/source-ipv6-network.
     */
    class AclAcesAceMatchesIpv6SourceIpv6NetworkOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesIpv6SourceIpv6NetworkOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv6/source-ipv6-network.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv6/flow-label.
     */
    class AclAcesAceMatchesIpv6FlowLabelOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesIpv6FlowLabelOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv6/flow-label.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv6.
     */
    class AclAcesAceMatchesIpv6OperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesIpv6OperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv6.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/sequence-number.
     */
    class AclAcesAceMatchesTcpSequenceNumberOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesTcpSequenceNumberOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/sequence-number.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/acknowledgement-number.
     */
    class AclAcesAceMatchesTcpAcknowledgementNumberOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesTcpAcknowledgementNumberOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/acknowledgement-number.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/data-offset.
     */
    class AclAcesAceMatchesTcpDataOffsetOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesTcpDataOffsetOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/data-offset.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/reserved.
     */
    class AclAcesAceMatchesTcpReservedOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesTcpReservedOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/reserved.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/flags.
     */
    class AclAcesAceMatchesTcpFlagsOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesTcpFlagsOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/flags.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/window-size.
     */
    class AclAcesAceMatchesTcpWindowSizeOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesTcpWindowSizeOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/window-size.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/urgent-pointer.
     */
    class AclAcesAceMatchesTcpUrgentPointerOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesTcpUrgentPointerOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/urgent-pointer.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/options.
     */
    class AclAcesAceMatchesTcpOptionsOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesTcpOptionsOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/options.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/source-port/lower-port.
     */
    class AclAcesAceMatchesTcpSourcePortLowerPortOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesTcpSourcePortLowerPortOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/source-port/lower-port.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/source-port/upper-port.
     */
    class AclAcesAceMatchesTcpSourcePortUpperPortOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesTcpSourcePortUpperPortOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/source-port/upper-port.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/source-port/operator.
     */
    class AclAcesAceMatchesTcpSourcePortOperatorOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesTcpSourcePortOperatorOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/source-port/operator.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/source-port/port.
     */
    class AclAcesAceMatchesTcpSourcePortPortOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesTcpSourcePortPortOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/source-port/port.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/source-port.
     */
    class AclAcesAceMatchesTcpSourcePortOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesTcpSourcePortOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/source-port.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/destination-port/lower-port.
     */
    class AclAcesAceMatchesTcpDestinationPortLowerPortOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesTcpDestinationPortLowerPortOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/destination-port/lower-port.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/destination-port/upper-port.
     */
    class AclAcesAceMatchesTcpDestinationPortUpperPortOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesTcpDestinationPortUpperPortOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/destination-port/upper-port.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/destination-port/operator.
     */
    class AclAcesAceMatchesTcpDestinationPortOperatorOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesTcpDestinationPortOperatorOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/destination-port/operator.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/destination-port/port.
     */
    class AclAcesAceMatchesTcpDestinationPortPortOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesTcpDestinationPortPortOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/destination-port/port.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/destination-port.
     */
    class AclAcesAceMatchesTcpDestinationPortOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesTcpDestinationPortOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/destination-port.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp.
     */
    class AclAcesAceMatchesTcpOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesTcpOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/udp/length.
     */
    class AclAcesAceMatchesUdpLengthOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesUdpLengthOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/udp/length.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/udp/source-port/lower-port.
     */
    class AclAcesAceMatchesUdpSourcePortLowerPortOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesUdpSourcePortLowerPortOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/udp/source-port/lower-port.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/udp/source-port/upper-port.
     */
    class AclAcesAceMatchesUdpSourcePortUpperPortOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesUdpSourcePortUpperPortOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/udp/source-port/upper-port.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/udp/source-port/operator.
     */
    class AclAcesAceMatchesUdpSourcePortOperatorOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesUdpSourcePortOperatorOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/udp/source-port/operator.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/udp/source-port/port.
     */
    class AclAcesAceMatchesUdpSourcePortPortOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesUdpSourcePortPortOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/udp/source-port/port.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/udp/source-port.
     */
    class AclAcesAceMatchesUdpSourcePortOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesUdpSourcePortOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/udp/source-port.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/udp/destination-port/lower-port.
     */
    class AclAcesAceMatchesUdpDestinationPortLowerPortOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesUdpDestinationPortLowerPortOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/udp/destination-port/lower-port.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/udp/destination-port/upper-port.
     */
    class AclAcesAceMatchesUdpDestinationPortUpperPortOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesUdpDestinationPortUpperPortOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/udp/destination-port/upper-port.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/udp/destination-port/operator.
     */
    class AclAcesAceMatchesUdpDestinationPortOperatorOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesUdpDestinationPortOperatorOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/udp/destination-port/operator.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/udp/destination-port/port.
     */
    class AclAcesAceMatchesUdpDestinationPortPortOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesUdpDestinationPortPortOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/udp/destination-port/port.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/udp/destination-port.
     */
    class AclAcesAceMatchesUdpDestinationPortOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesUdpDestinationPortOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/udp/destination-port.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/udp.
     */
    class AclAcesAceMatchesUdpOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesUdpOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/udp.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/icmp/type.
     */
    class AclAcesAceMatchesIcmpTypeOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesIcmpTypeOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/icmp/type.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/icmp/code.
     */
    class AclAcesAceMatchesIcmpCodeOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesIcmpCodeOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/icmp/code.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/icmp/rest-of-header.
     */
    class AclAcesAceMatchesIcmpRestOfHeaderOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesIcmpRestOfHeaderOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/icmp/rest-of-header.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/icmp.
     */
    class AclAcesAceMatchesIcmpOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesIcmpOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/icmp.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/egress-interface.
     */
    class AclAcesAceMatchesEgressInterfaceOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesEgressInterfaceOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/egress-interface.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ingress-interface.
     */
    class AclAcesAceMatchesIngressInterfaceOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesIngressInterfaceOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ingress-interface.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches.
     */
    class AclAcesAceMatchesOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceMatchesOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/actions/forwarding.
     */
    class AclAcesAceActionsForwardingOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceActionsForwardingOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/actions/forwarding.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/actions/logging.
     */
    class AclAcesAceActionsLoggingOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceActionsLoggingOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/actions/logging.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/actions.
     */
    class AclAcesAceActionsOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceActionsOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/actions.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/statistics/matched-packets.
     */
    class AclAcesAceStatisticsMatchedPacketsOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceStatisticsMatchedPacketsOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/statistics/matched-packets.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/statistics/matched-octets.
     */
    class AclAcesAceStatisticsMatchedOctetsOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceStatisticsMatchedOctetsOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/statistics/matched-octets.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/statistics.
     */
    class AclAcesAceStatisticsOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceStatisticsOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/statistics.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s'].
     */
    class AclAcesAceOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesAceOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s'].
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ietf-access-control-list:acls/acl[name='%s']/aces.
     */
    class AclAcesOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclAcesOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ietf-access-control-list:acls/acl[name='%s']/aces.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ietf-access-control-list:acls/acl[name='%s'].
     */
    class AclOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ietf-access-control-list:acls/acl[name='%s'].
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/interface-id.
     */
    class InterfaceIdOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        InterfaceIdOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/interface-id.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/ingress/acl-sets/acl-set[name='%s']/name.
     */
    class IngressAclSetsAclSetNameOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        IngressAclSetsAclSetNameOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/ingress/acl-sets/acl-set[name='%s']/name.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/ingress/acl-sets/acl-set[name='%s']/ace-statistics[name='%s']/name.
     */
    class IngressAclSetsAclSetAceStatisticsNameOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        IngressAclSetsAclSetAceStatisticsNameOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/ingress/acl-sets/acl-set[name='%s']/ace-statistics[name='%s']/name.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/ingress/acl-sets/acl-set[name='%s']/ace-statistics[name='%s']/matched-packets.
     */
    class IngressAclSetsAclSetAceStatisticsMatchedPacketsOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        IngressAclSetsAclSetAceStatisticsMatchedPacketsOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/ingress/acl-sets/acl-set[name='%s']/ace-statistics[name='%s']/matched-packets.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/ingress/acl-sets/acl-set[name='%s']/ace-statistics[name='%s']/matched-octets.
     */
    class IngressAclSetsAclSetAceStatisticsMatchedOctetsOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        IngressAclSetsAclSetAceStatisticsMatchedOctetsOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/ingress/acl-sets/acl-set[name='%s']/ace-statistics[name='%s']/matched-octets.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/ingress/acl-sets/acl-set[name='%s']/ace-statistics[name='%s'].
     */
    class IngressAclSetsAclSetAceStatisticsOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        IngressAclSetsAclSetAceStatisticsOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/ingress/acl-sets/acl-set[name='%s']/ace-statistics[name='%s'].
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/ingress/acl-sets/acl-set[name='%s'].
     */
    class IngressAclSetsAclSetOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        IngressAclSetsAclSetOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/ingress/acl-sets/acl-set[name='%s'].
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/ingress/acl-sets.
     */
    class IngressAclSetsOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        IngressAclSetsOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/ingress/acl-sets.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/ingress.
     */
    class IngressOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        IngressOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/ingress.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/egress/acl-sets/acl-set[name='%s']/name.
     */
    class EgressAclSetsAclSetNameOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        EgressAclSetsAclSetNameOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/egress/acl-sets/acl-set[name='%s']/name.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/egress/acl-sets/acl-set[name='%s']/ace-statistics[name='%s']/name.
     */
    class EgressAclSetsAclSetAceStatisticsNameOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        EgressAclSetsAclSetAceStatisticsNameOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/egress/acl-sets/acl-set[name='%s']/ace-statistics[name='%s']/name.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/egress/acl-sets/acl-set[name='%s']/ace-statistics[name='%s']/matched-packets.
     */
    class EgressAclSetsAclSetAceStatisticsMatchedPacketsOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        EgressAclSetsAclSetAceStatisticsMatchedPacketsOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/egress/acl-sets/acl-set[name='%s']/ace-statistics[name='%s']/matched-packets.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/egress/acl-sets/acl-set[name='%s']/ace-statistics[name='%s']/matched-octets.
     */
    class EgressAclSetsAclSetAceStatisticsMatchedOctetsOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        EgressAclSetsAclSetAceStatisticsMatchedOctetsOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/egress/acl-sets/acl-set[name='%s']/ace-statistics[name='%s']/matched-octets.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/egress/acl-sets/acl-set[name='%s']/ace-statistics[name='%s'].
     */
    class EgressAclSetsAclSetAceStatisticsOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        EgressAclSetsAclSetAceStatisticsOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/egress/acl-sets/acl-set[name='%s']/ace-statistics[name='%s'].
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/egress/acl-sets/acl-set[name='%s'].
     */
    class EgressAclSetsAclSetOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        EgressAclSetsAclSetOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/egress/acl-sets/acl-set[name='%s'].
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/egress/acl-sets.
     */
    class EgressAclSetsOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        EgressAclSetsOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/egress/acl-sets.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/egress.
     */
    class EgressOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        EgressOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/egress.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path
     * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s'].
     */
    class InterfaceOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        InterfaceOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path
         * /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s'].
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ietf-access-control-list:acls/attachment-points.
     */
    class AttachmentPointsOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AttachmentPointsOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ietf-access-control-list:acls/attachment-points.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

    /**
     * @brief sysrepo-plugin-generator: Generated operational get functor for path /ietf-access-control-list:acls.
     */
    class AclsOperGetCb {
    public:
        /**
         * sysrepo-plugin-generator: Generated default constructor.
         *
         * @param ctx Plugin operational context.
         *
         */
        AclsOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx);

        /**
         * sysrepo-plugin-generator: Generated operational get operator() for path /ietf-access-control-list:acls.
         *
         * @param session An implicit session for the callback.
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
        std::shared_ptr<ietf::acl::OperContext> m_ctx;
    };

}
}