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

#pragma once

#include "context.hpp"

#include <optional>
#include <string_view>

#include <sysrepo-cpp/Session.hpp>

#include <srpcpp/netlink.hpp>

namespace sr = sysrepo;

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path /ietf-interfaces:interfaces/interface[name='%s']/name.
 */
class InterfaceNameModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    InterfaceNameModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ietf-interfaces:interfaces/interface[name='%s']/name.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path /ietf-interfaces:interfaces/interface[name='%s']/description.
 */
class InterfaceDescriptionModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    InterfaceDescriptionModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ietf-interfaces:interfaces/interface[name='%s']/description.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path /ietf-interfaces:interfaces/interface[name='%s']/type.
 */
class InterfaceTypeModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    InterfaceTypeModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ietf-interfaces:interfaces/interface[name='%s']/type.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path /ietf-interfaces:interfaces/interface[name='%s']/enabled.
 */
class InterfaceEnabledModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    InterfaceEnabledModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ietf-interfaces:interfaces/interface[name='%s']/enabled.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/link-up-down-trap-enable.
 */
class InterfaceLinkUpDownTrapEnableModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    InterfaceLinkUpDownTrapEnableModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/link-up-down-trap-enable.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv4/enabled.
 */
class Ipv4EnabledModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    Ipv4EnabledModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv4/enabled.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv4/forwarding.
 */
class Ipv4ForwardingModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    Ipv4ForwardingModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv4/forwarding.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv4/mtu.
 */
class Ipv4MtuModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    Ipv4MtuModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv4/mtu.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv4/address[ip='%s']/ip.
 */
class Ipv4AddrIpModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    Ipv4AddrIpModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv4/address[ip='%s']/ip.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv4/address[ip='%s']/prefix-length.
 */
class Ipv4AddrPrefixLengthModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    Ipv4AddrPrefixLengthModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv4/address[ip='%s']/prefix-length.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv4/address[ip='%s']/netmask.
 */
class Ipv4AddrNetmaskModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    Ipv4AddrNetmaskModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv4/address[ip='%s']/netmask.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv4/address[ip='%s'].
 */
class Ipv4AddrModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    Ipv4AddrModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv4/address[ip='%s'].
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv4/neighbor[ip='%s']/ip.
 */
class Ipv4NeighIpModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    Ipv4NeighIpModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv4/neighbor[ip='%s']/ip.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv4/neighbor[ip='%s']/link-layer-address.
 */
class Ipv4NeighLinkLayerAddressModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    Ipv4NeighLinkLayerAddressModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv4/neighbor[ip='%s']/link-layer-address.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv4/neighbor[ip='%s'].
 */
class Ipv4NeighModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    Ipv4NeighModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv4/neighbor[ip='%s'].
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv4.
 */
class InterfaceIpv4ModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    InterfaceIpv4ModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv4.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv6/enabled.
 */
class Ipv6EnabledModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    Ipv6EnabledModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv6/enabled.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv6/forwarding.
 */
class Ipv6ForwardingModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    Ipv6ForwardingModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv6/forwarding.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv6/mtu.
 */
class Ipv6MtuModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    Ipv6MtuModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv6/mtu.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv6/address[ip='%s']/ip.
 */
class Ipv6AddrIpModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    Ipv6AddrIpModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv6/address[ip='%s']/ip.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv6/address[ip='%s']/prefix-length.
 */
class Ipv6AddrPrefixLengthModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    Ipv6AddrPrefixLengthModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv6/address[ip='%s']/prefix-length.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv6/address[ip='%s'].
 */
class Ipv6AddrModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    Ipv6AddrModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv6/address[ip='%s'].
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv6/neighbor[ip='%s']/ip.
 */
class Ipv6NeighIpModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    Ipv6NeighIpModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv6/neighbor[ip='%s']/ip.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv6/neighbor[ip='%s']/link-layer-address.
 */
class Ipv6NeighLinkLayerAddressModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    Ipv6NeighLinkLayerAddressModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv6/neighbor[ip='%s']/link-layer-address.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv6/neighbor[ip='%s'].
 */
class Ipv6NeighModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    Ipv6NeighModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv6/neighbor[ip='%s'].
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv6/dup-addr-detect-transmits.
 */
class Ipv6DupAddrDetectTransmitsModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    Ipv6DupAddrDetectTransmitsModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv6/dup-addr-detect-transmits.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv6/autoconf/create-global-addresses.
 */
class Ipv6AutoconfCreateGlobalAddressesModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    Ipv6AutoconfCreateGlobalAddressesModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv6/autoconf/create-global-addresses.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv6/autoconf/create-temporary-addresses.
 */
class Ipv6AutoconfCreateTemporaryAddressesModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    Ipv6AutoconfCreateTemporaryAddressesModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv6/autoconf/create-temporary-addresses.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv6/autoconf/temporary-valid-lifetime.
 */
class Ipv6AutoconfTemporaryValidLifetimeModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    Ipv6AutoconfTemporaryValidLifetimeModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv6/autoconf/temporary-valid-lifetime.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv6/autoconf/temporary-preferred-lifetime.
 */
class Ipv6AutoconfTemporaryPreferredLifetimeModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    Ipv6AutoconfTemporaryPreferredLifetimeModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv6/autoconf/temporary-preferred-lifetime.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv6/autoconf.
 */
class Ipv6AutoconfModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    Ipv6AutoconfModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv6/autoconf.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv6.
 */
class InterfaceIpv6ModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    InterfaceIpv6ModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ietf-interfaces:interfaces/interface[name='%s']/ietf-ip:ipv6.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path /ietf-interfaces:interfaces/interface[name='%s'].
 */
class InterfaceModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    InterfaceModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ietf-interfaces:interfaces/interface[name='%s'].
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path /ietf-interfaces:interfaces.
 */
class InterfacesModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    InterfacesModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path /ietf-interfaces:interfaces.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:carrier-delay/down.
 */
class InterfaceCarrierDelayDownModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    InterfaceCarrierDelayDownModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:carrier-delay/down.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:carrier-delay/up.
 */
class InterfaceCarrierDelayUpModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    InterfaceCarrierDelayUpModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:carrier-delay/up.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:carrier-delay.
 */
class InterfaceCarrierDelayModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    InterfaceCarrierDelayModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:carrier-delay.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:dampening/half-life.
 */
class InterfaceDampeningHalfLifeModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    InterfaceDampeningHalfLifeModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:dampening/half-life.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:dampening/reuse.
 */
class InterfaceDampeningReuseModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    InterfaceDampeningReuseModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:dampening/reuse.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:dampening/suppress.
 */
class InterfaceDampeningSuppressModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    InterfaceDampeningSuppressModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:dampening/suppress.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:dampening/max-suppress-time.
 */
class InterfaceDampeningMaxSuppressTimeModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    InterfaceDampeningMaxSuppressTimeModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:dampening/max-suppress-time.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:dampening.
 */
class InterfaceDampeningModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    InterfaceDampeningModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:dampening.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:encapsulation/ietf-if-vlan-encapsulation:dot1q-vlan/outer-tag/tag-type.
 */
class InterfaceEncapsulationDot1QVlanOuterTagTagTypeModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    InterfaceEncapsulationDot1QVlanOuterTagTagTypeModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:encapsulation/ietf-if-vlan-encapsulation:dot1q-vlan/outer-tag/tag-type.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:encapsulation/ietf-if-vlan-encapsulation:dot1q-vlan/outer-tag/vlan-id.
 */
class InterfaceEncapsulationDot1QVlanOuterTagVlanIdModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    InterfaceEncapsulationDot1QVlanOuterTagVlanIdModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:encapsulation/ietf-if-vlan-encapsulation:dot1q-vlan/outer-tag/vlan-id.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:encapsulation/ietf-if-vlan-encapsulation:dot1q-vlan/outer-tag.
 */
class InterfaceEncapsulationDot1QVlanOuterTagModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    InterfaceEncapsulationDot1QVlanOuterTagModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:encapsulation/ietf-if-vlan-encapsulation:dot1q-vlan/outer-tag.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:encapsulation/ietf-if-vlan-encapsulation:dot1q-vlan/second-tag/tag-type.
 */
class InterfaceEncapsulationDot1QVlanSecondTagTagTypeModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    InterfaceEncapsulationDot1QVlanSecondTagTagTypeModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:encapsulation/ietf-if-vlan-encapsulation:dot1q-vlan/second-tag/tag-type.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:encapsulation/ietf-if-vlan-encapsulation:dot1q-vlan/second-tag/vlan-id.
 */
class InterfaceEncapsulationDot1QVlanSecondTagVlanIdModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    InterfaceEncapsulationDot1QVlanSecondTagVlanIdModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:encapsulation/ietf-if-vlan-encapsulation:dot1q-vlan/second-tag/vlan-id.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:encapsulation/ietf-if-vlan-encapsulation:dot1q-vlan/second-tag.
 */
class InterfaceEncapsulationDot1QVlanSecondTagModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    InterfaceEncapsulationDot1QVlanSecondTagModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:encapsulation/ietf-if-vlan-encapsulation:dot1q-vlan/second-tag.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:encapsulation/ietf-if-vlan-encapsulation:dot1q-vlan.
 */
class InterfaceEncapsulationDot1QVlanModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    InterfaceEncapsulationDot1QVlanModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:encapsulation/ietf-if-vlan-encapsulation:dot1q-vlan.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:encapsulation.
 */
class InterfaceEncapsulationModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    InterfaceEncapsulationModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:encapsulation.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:loopback.
 */
class InterfaceLoopbackModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    InterfaceLoopbackModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:loopback.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:max-frame-size.
 */
class InterfaceMaxFrameSizeModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    InterfaceMaxFrameSizeModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:max-frame-size.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};

/**
 * @brief sysrepo-plugin-generator: Generated module change functor for path
 * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:parent-interface.
 */
class InterfaceParentInterfaceModuleChangeCb {
public:
    /**
     * sysrepo-plugin-generator: Generated default constructor.
     *
     * @param ctx Plugin module change context.
     *
     */
    InterfaceParentInterfaceModuleChangeCb(std::shared_ptr<InterfacesModuleChangesContext> ctx);

    /**
     * sysrepo-plugin-generator: Generated module change operator() for path
     * /ietf-interfaces:interfaces/interface[name='%s']/ietf-if-extensions:parent-interface.
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
    std::shared_ptr<InterfacesModuleChangesContext> m_ctx;
};
