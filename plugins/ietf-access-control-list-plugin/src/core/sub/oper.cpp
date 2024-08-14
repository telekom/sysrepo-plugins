//
// telekom / sysrepo-plugins
//
// This program is made available under the terms of the
// BSD 3-Clause license which is available at
// https://opensource.org/licenses/BSD-3-Clause
//
// SPDX-FileCopyrightText: 2024 Deutsche Telekom AG
// SPDX-FileContributor: Sartura d.d.
//
// SPDX-License-Identifier: BSD-3-Clause
//

#include "oper.hpp"

namespace ietf::acl {
namespace sub::oper {
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin operational context.
     *
     */
    AclNameOperGetCb::AclNameOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/acl[name='%s']/name.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AclNameOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclTypeOperGetCb::AclTypeOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/acl[name='%s']/type.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AclTypeOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceNameOperGetCb::AclAcesAceNameOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/name.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AclAcesAceNameOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesEthDestinationMacAddressOperGetCb::AclAcesAceMatchesEthDestinationMacAddressOperGetCb(
        std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesEthDestinationMacAddressOperGetCb::operator()(sr::Session session, uint32_t subscriptionId,
        std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesEthDestinationMacAddressMaskOperGetCb::AclAcesAceMatchesEthDestinationMacAddressMaskOperGetCb(
        std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesEthDestinationMacAddressMaskOperGetCb::operator()(sr::Session session, uint32_t subscriptionId,
        std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesEthSourceMacAddressOperGetCb::AclAcesAceMatchesEthSourceMacAddressOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesEthSourceMacAddressOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesEthSourceMacAddressMaskOperGetCb::AclAcesAceMatchesEthSourceMacAddressMaskOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesEthSourceMacAddressMaskOperGetCb::operator()(sr::Session session, uint32_t subscriptionId,
        std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesEthEthertypeOperGetCb::AclAcesAceMatchesEthEthertypeOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesEthEthertypeOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesEthOperGetCb::AclAcesAceMatchesEthOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/eth.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AclAcesAceMatchesEthOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesIpv4DscpOperGetCb::AclAcesAceMatchesIpv4DscpOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv4/dscp.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AclAcesAceMatchesIpv4DscpOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesIpv4EcnOperGetCb::AclAcesAceMatchesIpv4EcnOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv4/ecn.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AclAcesAceMatchesIpv4EcnOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesIpv4LengthOperGetCb::AclAcesAceMatchesIpv4LengthOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv4/length.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AclAcesAceMatchesIpv4LengthOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesIpv4TtlOperGetCb::AclAcesAceMatchesIpv4TtlOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv4/ttl.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AclAcesAceMatchesIpv4TtlOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesIpv4ProtocolOperGetCb::AclAcesAceMatchesIpv4ProtocolOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesIpv4ProtocolOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesIpv4IhlOperGetCb::AclAcesAceMatchesIpv4IhlOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv4/ihl.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AclAcesAceMatchesIpv4IhlOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesIpv4FlagsOperGetCb::AclAcesAceMatchesIpv4FlagsOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv4/flags.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AclAcesAceMatchesIpv4FlagsOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesIpv4OffsetOperGetCb::AclAcesAceMatchesIpv4OffsetOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv4/offset.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AclAcesAceMatchesIpv4OffsetOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesIpv4IdentificationOperGetCb::AclAcesAceMatchesIpv4IdentificationOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesIpv4IdentificationOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesIpv4DestinationIpv4NetworkOperGetCb::AclAcesAceMatchesIpv4DestinationIpv4NetworkOperGetCb(
        std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesIpv4DestinationIpv4NetworkOperGetCb::operator()(sr::Session session, uint32_t subscriptionId,
        std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesIpv4SourceIpv4NetworkOperGetCb::AclAcesAceMatchesIpv4SourceIpv4NetworkOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesIpv4SourceIpv4NetworkOperGetCb::operator()(sr::Session session, uint32_t subscriptionId,
        std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesIpv4OperGetCb::AclAcesAceMatchesIpv4OperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv4.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AclAcesAceMatchesIpv4OperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesIpv6DscpOperGetCb::AclAcesAceMatchesIpv6DscpOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv6/dscp.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AclAcesAceMatchesIpv6DscpOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesIpv6EcnOperGetCb::AclAcesAceMatchesIpv6EcnOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv6/ecn.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AclAcesAceMatchesIpv6EcnOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesIpv6LengthOperGetCb::AclAcesAceMatchesIpv6LengthOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv6/length.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AclAcesAceMatchesIpv6LengthOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesIpv6TtlOperGetCb::AclAcesAceMatchesIpv6TtlOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv6/ttl.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AclAcesAceMatchesIpv6TtlOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesIpv6ProtocolOperGetCb::AclAcesAceMatchesIpv6ProtocolOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesIpv6ProtocolOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesIpv6DestinationIpv6NetworkOperGetCb::AclAcesAceMatchesIpv6DestinationIpv6NetworkOperGetCb(
        std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesIpv6DestinationIpv6NetworkOperGetCb::operator()(sr::Session session, uint32_t subscriptionId,
        std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesIpv6SourceIpv6NetworkOperGetCb::AclAcesAceMatchesIpv6SourceIpv6NetworkOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesIpv6SourceIpv6NetworkOperGetCb::operator()(sr::Session session, uint32_t subscriptionId,
        std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesIpv6FlowLabelOperGetCb::AclAcesAceMatchesIpv6FlowLabelOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesIpv6FlowLabelOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesIpv6OperGetCb::AclAcesAceMatchesIpv6OperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/ipv6.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AclAcesAceMatchesIpv6OperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesTcpSequenceNumberOperGetCb::AclAcesAceMatchesTcpSequenceNumberOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesTcpSequenceNumberOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesTcpAcknowledgementNumberOperGetCb::AclAcesAceMatchesTcpAcknowledgementNumberOperGetCb(
        std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesTcpAcknowledgementNumberOperGetCb::operator()(sr::Session session, uint32_t subscriptionId,
        std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesTcpDataOffsetOperGetCb::AclAcesAceMatchesTcpDataOffsetOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesTcpDataOffsetOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesTcpReservedOperGetCb::AclAcesAceMatchesTcpReservedOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/reserved.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AclAcesAceMatchesTcpReservedOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesTcpFlagsOperGetCb::AclAcesAceMatchesTcpFlagsOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/flags.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AclAcesAceMatchesTcpFlagsOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesTcpWindowSizeOperGetCb::AclAcesAceMatchesTcpWindowSizeOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesTcpWindowSizeOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesTcpUrgentPointerOperGetCb::AclAcesAceMatchesTcpUrgentPointerOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesTcpUrgentPointerOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesTcpOptionsOperGetCb::AclAcesAceMatchesTcpOptionsOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp/options.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AclAcesAceMatchesTcpOptionsOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesTcpSourcePortLowerPortOperGetCb::AclAcesAceMatchesTcpSourcePortLowerPortOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesTcpSourcePortLowerPortOperGetCb::operator()(sr::Session session, uint32_t subscriptionId,
        std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesTcpSourcePortUpperPortOperGetCb::AclAcesAceMatchesTcpSourcePortUpperPortOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesTcpSourcePortUpperPortOperGetCb::operator()(sr::Session session, uint32_t subscriptionId,
        std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesTcpSourcePortOperatorOperGetCb::AclAcesAceMatchesTcpSourcePortOperatorOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesTcpSourcePortOperatorOperGetCb::operator()(sr::Session session, uint32_t subscriptionId,
        std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesTcpSourcePortPortOperGetCb::AclAcesAceMatchesTcpSourcePortPortOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesTcpSourcePortPortOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesTcpSourcePortOperGetCb::AclAcesAceMatchesTcpSourcePortOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesTcpSourcePortOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesTcpDestinationPortLowerPortOperGetCb::AclAcesAceMatchesTcpDestinationPortLowerPortOperGetCb(
        std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesTcpDestinationPortLowerPortOperGetCb::operator()(sr::Session session, uint32_t subscriptionId,
        std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesTcpDestinationPortUpperPortOperGetCb::AclAcesAceMatchesTcpDestinationPortUpperPortOperGetCb(
        std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesTcpDestinationPortUpperPortOperGetCb::operator()(sr::Session session, uint32_t subscriptionId,
        std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesTcpDestinationPortOperatorOperGetCb::AclAcesAceMatchesTcpDestinationPortOperatorOperGetCb(
        std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesTcpDestinationPortOperatorOperGetCb::operator()(sr::Session session, uint32_t subscriptionId,
        std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesTcpDestinationPortPortOperGetCb::AclAcesAceMatchesTcpDestinationPortPortOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesTcpDestinationPortPortOperGetCb::operator()(sr::Session session, uint32_t subscriptionId,
        std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesTcpDestinationPortOperGetCb::AclAcesAceMatchesTcpDestinationPortOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesTcpDestinationPortOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesTcpOperGetCb::AclAcesAceMatchesTcpOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/tcp.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AclAcesAceMatchesTcpOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesUdpLengthOperGetCb::AclAcesAceMatchesUdpLengthOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/udp/length.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AclAcesAceMatchesUdpLengthOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesUdpSourcePortLowerPortOperGetCb::AclAcesAceMatchesUdpSourcePortLowerPortOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesUdpSourcePortLowerPortOperGetCb::operator()(sr::Session session, uint32_t subscriptionId,
        std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesUdpSourcePortUpperPortOperGetCb::AclAcesAceMatchesUdpSourcePortUpperPortOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesUdpSourcePortUpperPortOperGetCb::operator()(sr::Session session, uint32_t subscriptionId,
        std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesUdpSourcePortOperatorOperGetCb::AclAcesAceMatchesUdpSourcePortOperatorOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesUdpSourcePortOperatorOperGetCb::operator()(sr::Session session, uint32_t subscriptionId,
        std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesUdpSourcePortPortOperGetCb::AclAcesAceMatchesUdpSourcePortPortOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesUdpSourcePortPortOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesUdpSourcePortOperGetCb::AclAcesAceMatchesUdpSourcePortOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesUdpSourcePortOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesUdpDestinationPortLowerPortOperGetCb::AclAcesAceMatchesUdpDestinationPortLowerPortOperGetCb(
        std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesUdpDestinationPortLowerPortOperGetCb::operator()(sr::Session session, uint32_t subscriptionId,
        std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesUdpDestinationPortUpperPortOperGetCb::AclAcesAceMatchesUdpDestinationPortUpperPortOperGetCb(
        std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesUdpDestinationPortUpperPortOperGetCb::operator()(sr::Session session, uint32_t subscriptionId,
        std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesUdpDestinationPortOperatorOperGetCb::AclAcesAceMatchesUdpDestinationPortOperatorOperGetCb(
        std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesUdpDestinationPortOperatorOperGetCb::operator()(sr::Session session, uint32_t subscriptionId,
        std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesUdpDestinationPortPortOperGetCb::AclAcesAceMatchesUdpDestinationPortPortOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesUdpDestinationPortPortOperGetCb::operator()(sr::Session session, uint32_t subscriptionId,
        std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesUdpDestinationPortOperGetCb::AclAcesAceMatchesUdpDestinationPortOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesUdpDestinationPortOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesUdpOperGetCb::AclAcesAceMatchesUdpOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/udp.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AclAcesAceMatchesUdpOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesIcmpTypeOperGetCb::AclAcesAceMatchesIcmpTypeOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/icmp/type.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AclAcesAceMatchesIcmpTypeOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesIcmpCodeOperGetCb::AclAcesAceMatchesIcmpCodeOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/icmp/code.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AclAcesAceMatchesIcmpCodeOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesIcmpRestOfHeaderOperGetCb::AclAcesAceMatchesIcmpRestOfHeaderOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesIcmpRestOfHeaderOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesIcmpOperGetCb::AclAcesAceMatchesIcmpOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches/icmp.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AclAcesAceMatchesIcmpOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesEgressInterfaceOperGetCb::AclAcesAceMatchesEgressInterfaceOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesEgressInterfaceOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesIngressInterfaceOperGetCb::AclAcesAceMatchesIngressInterfaceOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceMatchesIngressInterfaceOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceMatchesOperGetCb::AclAcesAceMatchesOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/matches.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AclAcesAceMatchesOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceActionsForwardingOperGetCb::AclAcesAceActionsForwardingOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/actions/forwarding.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AclAcesAceActionsForwardingOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceActionsLoggingOperGetCb::AclAcesAceActionsLoggingOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/actions/logging.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AclAcesAceActionsLoggingOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceActionsOperGetCb::AclAcesAceActionsOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/actions.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AclAcesAceActionsOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceStatisticsMatchedPacketsOperGetCb::AclAcesAceStatisticsMatchedPacketsOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceStatisticsMatchedPacketsOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceStatisticsMatchedOctetsOperGetCb::AclAcesAceStatisticsMatchedOctetsOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode AclAcesAceStatisticsMatchedOctetsOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceStatisticsOperGetCb::AclAcesAceStatisticsOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s']/statistics.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AclAcesAceStatisticsOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesAceOperGetCb::AclAcesAceOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/acl[name='%s']/aces/ace[name='%s'].
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AclAcesAceOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclAcesOperGetCb::AclAcesOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/acl[name='%s']/aces.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AclAcesOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclOperGetCb::AclOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/acl[name='%s'].
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AclOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    InterfaceIdOperGetCb::InterfaceIdOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode InterfaceIdOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    IngressAclSetsAclSetNameOperGetCb::IngressAclSetsAclSetNameOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode IngressAclSetsAclSetNameOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    IngressAclSetsAclSetAceStatisticsNameOperGetCb::IngressAclSetsAclSetAceStatisticsNameOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode IngressAclSetsAclSetAceStatisticsNameOperGetCb::operator()(sr::Session session, uint32_t subscriptionId,
        std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    IngressAclSetsAclSetAceStatisticsMatchedPacketsOperGetCb::IngressAclSetsAclSetAceStatisticsMatchedPacketsOperGetCb(
        std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode IngressAclSetsAclSetAceStatisticsMatchedPacketsOperGetCb::operator()(sr::Session session, uint32_t subscriptionId,
        std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    IngressAclSetsAclSetAceStatisticsMatchedOctetsOperGetCb::IngressAclSetsAclSetAceStatisticsMatchedOctetsOperGetCb(
        std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode IngressAclSetsAclSetAceStatisticsMatchedOctetsOperGetCb::operator()(sr::Session session, uint32_t subscriptionId,
        std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    IngressAclSetsAclSetAceStatisticsOperGetCb::IngressAclSetsAclSetAceStatisticsOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode IngressAclSetsAclSetAceStatisticsOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    IngressAclSetsAclSetOperGetCb::IngressAclSetsAclSetOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode IngressAclSetsAclSetOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    IngressAclSetsOperGetCb::IngressAclSetsOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode IngressAclSetsOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    IngressOperGetCb::IngressOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/ingress.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode IngressOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    EgressAclSetsAclSetNameOperGetCb::EgressAclSetsAclSetNameOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode EgressAclSetsAclSetNameOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    EgressAclSetsAclSetAceStatisticsNameOperGetCb::EgressAclSetsAclSetAceStatisticsNameOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode EgressAclSetsAclSetAceStatisticsNameOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    EgressAclSetsAclSetAceStatisticsMatchedPacketsOperGetCb::EgressAclSetsAclSetAceStatisticsMatchedPacketsOperGetCb(
        std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode EgressAclSetsAclSetAceStatisticsMatchedPacketsOperGetCb::operator()(sr::Session session, uint32_t subscriptionId,
        std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    EgressAclSetsAclSetAceStatisticsMatchedOctetsOperGetCb::EgressAclSetsAclSetAceStatisticsMatchedOctetsOperGetCb(
        std::shared_ptr<ietf::acl::OperContext> ctx)
    {
        m_ctx = ctx;
    }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode EgressAclSetsAclSetAceStatisticsMatchedOctetsOperGetCb::operator()(sr::Session session, uint32_t subscriptionId,
        std::string_view moduleName, std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    EgressAclSetsAclSetAceStatisticsOperGetCb::EgressAclSetsAclSetAceStatisticsOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode EgressAclSetsAclSetAceStatisticsOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    EgressAclSetsAclSetOperGetCb::EgressAclSetsAclSetOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode EgressAclSetsAclSetOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    EgressAclSetsOperGetCb::EgressAclSetsOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path
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
    sr::ErrorCode EgressAclSetsOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    EgressOperGetCb::EgressOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s']/egress.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode EgressOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    InterfaceOperGetCb::InterfaceOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/attachment-points/interface[interface-id='%s'].
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode InterfaceOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AttachmentPointsOperGetCb::AttachmentPointsOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls/attachment-points.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AttachmentPointsOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
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
    AclsOperGetCb::AclsOperGetCb(std::shared_ptr<ietf::acl::OperContext> ctx) { m_ctx = ctx; }

    /**
     * sysrepo-plugin-generator: Generated operator() for path /ietf-access-control-list:acls.
     *
     * @param session An implicit session for the callback.
     * @param subscriptionId ID the subscription associated with the callback.
     * @param moduleName The module name used for subscribing.
     * @param subXPath The optional xpath used at the time of subscription.
     * @param requestId Request ID unique for the specific module_name. Connected events for one request (SR_EV_CHANGE and
     * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
     *
     * @return Error code.
     *
     */
    sr::ErrorCode AclsOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName,
        std::optional<std::string_view> subXPath, std::optional<std::string_view> requestXPath, uint32_t requestId,
        std::optional<ly::DataNode>& output)
    {
        sr::ErrorCode error = sr::ErrorCode::Ok;
        return error;
    }

}
}