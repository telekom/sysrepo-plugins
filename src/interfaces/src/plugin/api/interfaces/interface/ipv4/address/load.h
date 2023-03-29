/*
 * telekom / sysrepo-plugin-system
 *
 * This program is made available under the terms of the
 * BSD 3-Clause license which is available at
 * https://opensource.org/licenses/BSD-3-Clause
 *
 * SPDX-FileCopyrightText: 2022 Deutsche Telekom AG
 * SPDX-FileContributor: Sartura Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef INTERFACES_PLUGIN_API_INTERFACES_INTERFACE_IPV4_ADDRESS_LOAD_H
#define INTERFACES_PLUGIN_API_INTERFACES_INTERFACE_IPV4_ADDRESS_LOAD_H

#include "netlink/route/addr.h"
#include "plugin/context.h"
#include "plugin/types.h"

int interfaces_interface_ipv4_address_load_ip(interfaces_ctx_t* ctx, interfaces_interface_ipv4_address_element_t** element, struct rtnl_addr* addr);
int interfaces_interface_ipv4_address_load_prefix_length(interfaces_ctx_t* ctx, interfaces_interface_ipv4_address_element_t** element, struct rtnl_addr* addr);

#endif // INTERFACES_PLUGIN_API_INTERFACES_INTERFACE_IPV4_ADDRESS_LOAD_H
