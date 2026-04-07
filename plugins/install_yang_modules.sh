#!/bin/bash

# telekom / sysrepo-plugins
#
# This program is made available under the terms of the
# BSD 3-Clause license which is available at
# https://opensource.org/licenses/BSD-3-Clause
#
# SPDX-FileCopyrightText: 2026 Deutsche Telekom AG
# SPDX-FileContributor: Sartura d.d.
#
# SPDX-License-Identifier: BSD-3-Clause
#

# Install all YANG modules required by the sysrepo plugins.
# Run this script from the plugins/ directory.

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR" || exit 1

# ietf-system
sysrepoctl -i ietf-system-plugin/yang/iana-crypt-hash@2014-08-06.yang
sysrepoctl -i ietf-system-plugin/yang/ietf-system@2014-08-06.yang
sysrepoctl -c ietf-system -e timezone-name -e ntp -e authentication -e local-users

# ietf-interfaces
sysrepoctl -i ietf-interfaces-plugin/yang/ietf-interfaces@2018-02-20.yang
sysrepoctl -i ietf-interfaces-plugin/yang/iana-if-type@2017-01-19.yang
sysrepoctl -i ietf-interfaces-plugin/yang/ietf-ip@2018-02-22.yang
sysrepoctl -i ietf-interfaces-plugin/yang/ietf-if-extensions@2020-07-29.yang
sysrepoctl -i ietf-interfaces-plugin/yang/ieee802-dot1q-types.yang
sysrepoctl -i ietf-interfaces-plugin/yang/ietf-if-vlan-encapsulation@2020-07-13.yang
sysrepoctl -c ietf-interfaces -e if-mib
sysrepoctl -c ietf-if-extensions -e sub-interfaces

# ietf-routing
sysrepoctl -i ietf-routing-plugin/yang/ietf-routing@2018-03-13.yang
sysrepoctl -i ietf-routing-plugin/yang/ietf-ipv4-unicast-routing@2018-03-13.yang
sysrepoctl -i ietf-routing-plugin/yang/ietf-ipv6-unicast-routing@2018-03-13.yang -s ietf-routing-plugin/yang/

# ieee802-dot1q-bridge
sysrepoctl -i ieee802-dot1q-bridge-plugin/yang/ieee802-types.yang
sysrepoctl -i ieee802-dot1q-bridge-plugin/yang/ieee802-dot1q-types.yang
sysrepoctl -i ieee802-dot1q-bridge-plugin/yang/ieee802-dot1q-bridge.yang
sysrepoctl -i ieee802-dot1q-bridge-plugin/yang/ieee802-dot1q-tpmr.yang
sysrepoctl -i ieee802-dot1q-bridge-plugin/yang/ieee802-got1q-pb.yang
sysrepoctl -i ieee802-dot1q-bridge-plugin/yang/ieee802-dot1q-vlan-bridge.yang

# ietf-access-control-list
sysrepoctl -i ietf-access-control-list-plugin/yang/ietf-ethertypes@2019-03-04.yang
sysrepoctl -i ietf-access-control-list-plugin/yang/ietf-packet-fields@2019-03-04.yang
sysrepoctl -i ietf-access-control-list-plugin/yang/ietf-access-control-list@2019-03-04.yang
sysrepoctl -c ietf-access-control-list -e match-on-eth -e match-on-ipv4 -e match-on-ipv6 -e match-on-tcp -e match-on-udp -e match-on-icmp -e eth -e ipv4 -e ipv6

# ietf-hardware
sysrepoctl -i ietf-hardware-plugin/yang/iana-hardware.yang
sysrepoctl -i ietf-hardware-plugin/yang/ietf-hardware.yang
sysrepoctl -i ietf-hardware-plugin/yang/sensor-notifications-augment.yang
sysrepoctl -c ietf-hardware -e hardware-sensor -e entity-mib

# os-metrics
sysrepoctl -i os-metrics-plugin/yang/os-metrics.yang
sysrepoctl -c os-metrics -e usage-notifications
