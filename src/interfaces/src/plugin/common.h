#ifndef INTERFACES_PLUGIN_COMMON_H
#define INTERFACES_PLUGIN_COMMON_H

#define PLUGIN_NAME "interfaces-plugin"

#define BASE_YANG_MODEL "ietf-interfaces"

#define INTERFACES_INTERFACES_CONTAINER_YANG_PATH "/" BASE_YANG_MODEL ":interfaces"

#define INTERFACES_INTERFACES_STATE_INTERFACE_NAME_YANG_PATH INTERFACES_INTERFACES_STATE_INTERFACE_YANG_PATH "/name"
#define INTERFACES_INTERFACES_STATE_INTERFACE_TYPE_YANG_PATH INTERFACES_INTERFACES_STATE_INTERFACE_YANG_PATH "/type"
#define INTERFACES_INTERFACES_STATE_INTERFACE_ADMIN_STATUS_YANG_PATH INTERFACES_INTERFACES_STATE_INTERFACE_YANG_PATH "/admin-status"
#define INTERFACES_INTERFACES_STATE_INTERFACE_OPER_STATUS_YANG_PATH INTERFACES_INTERFACES_STATE_INTERFACE_YANG_PATH "/oper-status"
#define INTERFACES_INTERFACES_STATE_INTERFACE_LAST_CHANGE_YANG_PATH INTERFACES_INTERFACES_STATE_INTERFACE_YANG_PATH "/last-change"
#define INTERFACES_INTERFACES_STATE_INTERFACE_IF_INDEX_YANG_PATH INTERFACES_INTERFACES_STATE_INTERFACE_YANG_PATH "/if-index"
#define INTERFACES_INTERFACES_STATE_INTERFACE_PHYS_ADDRESS_YANG_PATH INTERFACES_INTERFACES_STATE_INTERFACE_YANG_PATH "/phys-address"
#define INTERFACES_INTERFACES_STATE_INTERFACE_HIGHER_LAYER_IF_YANG_PATH INTERFACES_INTERFACES_STATE_INTERFACE_YANG_PATH "/higher-layer-if"
#define INTERFACES_INTERFACES_STATE_INTERFACE_LOWER_LAYER_IF_YANG_PATH INTERFACES_INTERFACES_STATE_INTERFACE_YANG_PATH "/lower-layer-if"
#define INTERFACES_INTERFACES_STATE_INTERFACE_SPEED_YANG_PATH INTERFACES_INTERFACES_STATE_INTERFACE_YANG_PATH "/speed"
#define INTERFACES_INTERFACES_STATE_INTERFACE_STATISTICS_DISCONTINUITY_TIME_YANG_PATH INTERFACES_INTERFACES_STATE_INTERFACE_STATISTICS_YANG_PATH "/discontinuity-time"
#define INTERFACES_INTERFACES_STATE_INTERFACE_STATISTICS_IN_OCTETS_YANG_PATH INTERFACES_INTERFACES_STATE_INTERFACE_STATISTICS_YANG_PATH "/in-octets"
#define INTERFACES_INTERFACES_STATE_INTERFACE_STATISTICS_IN_UNICAST_PKTS_YANG_PATH INTERFACES_INTERFACES_STATE_INTERFACE_STATISTICS_YANG_PATH "/in-unicast-pkts"
#define INTERFACES_INTERFACES_STATE_INTERFACE_STATISTICS_IN_BROADCAST_PKTS_YANG_PATH INTERFACES_INTERFACES_STATE_INTERFACE_STATISTICS_YANG_PATH "/in-broadcast-pkts"
#define INTERFACES_INTERFACES_STATE_INTERFACE_STATISTICS_IN_MULTICAST_PKTS_YANG_PATH INTERFACES_INTERFACES_STATE_INTERFACE_STATISTICS_YANG_PATH "/in-multicast-pkts"
#define INTERFACES_INTERFACES_STATE_INTERFACE_STATISTICS_IN_DISCARDS_YANG_PATH INTERFACES_INTERFACES_STATE_INTERFACE_STATISTICS_YANG_PATH "/in-discards"
#define INTERFACES_INTERFACES_STATE_INTERFACE_STATISTICS_IN_ERRORS_YANG_PATH INTERFACES_INTERFACES_STATE_INTERFACE_STATISTICS_YANG_PATH "/in-errors"
#define INTERFACES_INTERFACES_STATE_INTERFACE_STATISTICS_IN_UNKNOWN_PROTOS_YANG_PATH INTERFACES_INTERFACES_STATE_INTERFACE_STATISTICS_YANG_PATH "/in-unknown-protos"
#define INTERFACES_INTERFACES_STATE_INTERFACE_STATISTICS_OUT_OCTETS_YANG_PATH INTERFACES_INTERFACES_STATE_INTERFACE_STATISTICS_YANG_PATH "/out-octets"
#define INTERFACES_INTERFACES_STATE_INTERFACE_STATISTICS_OUT_UNICAST_PKTS_YANG_PATH INTERFACES_INTERFACES_STATE_INTERFACE_STATISTICS_YANG_PATH "/out-unicast-pkts"
#define INTERFACES_INTERFACES_STATE_INTERFACE_STATISTICS_OUT_BROADCAST_PKTS_YANG_PATH INTERFACES_INTERFACES_STATE_INTERFACE_STATISTICS_YANG_PATH "/out-broadcast-pkts"
#define INTERFACES_INTERFACES_STATE_INTERFACE_STATISTICS_OUT_MULTICAST_PKTS_YANG_PATH INTERFACES_INTERFACES_STATE_INTERFACE_STATISTICS_YANG_PATH "/out-multicast-pkts"
#define INTERFACES_INTERFACES_STATE_INTERFACE_STATISTICS_OUT_DISCARDS_YANG_PATH INTERFACES_INTERFACES_STATE_INTERFACE_STATISTICS_YANG_PATH "/out-discards"
#define INTERFACES_INTERFACES_STATE_INTERFACE_STATISTICS_OUT_ERRORS_YANG_PATH INTERFACES_INTERFACES_STATE_INTERFACE_STATISTICS_YANG_PATH "/out-errors"
#define INTERFACES_INTERFACES_STATE_INTERFACE_STATISTICS_YANG_PATH INTERFACES_INTERFACES_STATE_INTERFACE_YANG_PATH "/statistics"
#define INTERFACES_INTERFACES_STATE_INTERFACE_YANG_PATH INTERFACES_INTERFACES_STATE_YANG_PATH "/interface"
#define INTERFACES_INTERFACES_STATE_YANG_PATH "/ietf-interfaces:interfaces-state"
#define INTERFACES_INTERFACES_INTERFACE_NAME_YANG_PATH INTERFACES_INTERFACES_INTERFACE_YANG_PATH "/name"
#define INTERFACES_INTERFACES_INTERFACE_DESCRIPTION_YANG_PATH INTERFACES_INTERFACES_INTERFACE_YANG_PATH "/description"
#define INTERFACES_INTERFACES_INTERFACE_TYPE_YANG_PATH INTERFACES_INTERFACES_INTERFACE_YANG_PATH "/type"
#define INTERFACES_INTERFACES_INTERFACE_ENABLED_YANG_PATH INTERFACES_INTERFACES_INTERFACE_YANG_PATH "/enabled"
#define INTERFACES_INTERFACES_INTERFACE_LINK_UP_DOWN_TRAP_ENABLE_YANG_PATH INTERFACES_INTERFACES_INTERFACE_YANG_PATH "/link-up-down-trap-enable"
#define INTERFACES_INTERFACES_INTERFACE_ADMIN_STATUS_YANG_PATH INTERFACES_INTERFACES_INTERFACE_YANG_PATH "/admin-status"
#define INTERFACES_INTERFACES_INTERFACE_OPER_STATUS_YANG_PATH INTERFACES_INTERFACES_INTERFACE_YANG_PATH "/oper-status"
#define INTERFACES_INTERFACES_INTERFACE_LAST_CHANGE_YANG_PATH INTERFACES_INTERFACES_INTERFACE_YANG_PATH "/last-change"
#define INTERFACES_INTERFACES_INTERFACE_IF_INDEX_YANG_PATH INTERFACES_INTERFACES_INTERFACE_YANG_PATH "/if-index"
#define INTERFACES_INTERFACES_INTERFACE_PHYS_ADDRESS_YANG_PATH INTERFACES_INTERFACES_INTERFACE_YANG_PATH "/phys-address"
#define INTERFACES_INTERFACES_INTERFACE_HIGHER_LAYER_IF_YANG_PATH INTERFACES_INTERFACES_INTERFACE_YANG_PATH "/higher-layer-if"
#define INTERFACES_INTERFACES_INTERFACE_LOWER_LAYER_IF_YANG_PATH INTERFACES_INTERFACES_INTERFACE_YANG_PATH "/lower-layer-if"
#define INTERFACES_INTERFACES_INTERFACE_SPEED_YANG_PATH INTERFACES_INTERFACES_INTERFACE_YANG_PATH "/speed"
#define INTERFACES_INTERFACES_INTERFACE_STATISTICS_DISCONTINUITY_TIME_YANG_PATH INTERFACES_INTERFACES_INTERFACE_STATISTICS_YANG_PATH "/discontinuity-time"
#define INTERFACES_INTERFACES_INTERFACE_STATISTICS_IN_OCTETS_YANG_PATH INTERFACES_INTERFACES_INTERFACE_STATISTICS_YANG_PATH "/in-octets"
#define INTERFACES_INTERFACES_INTERFACE_STATISTICS_IN_UNICAST_PKTS_YANG_PATH INTERFACES_INTERFACES_INTERFACE_STATISTICS_YANG_PATH "/in-unicast-pkts"
#define INTERFACES_INTERFACES_INTERFACE_STATISTICS_IN_BROADCAST_PKTS_YANG_PATH INTERFACES_INTERFACES_INTERFACE_STATISTICS_YANG_PATH "/in-broadcast-pkts"
#define INTERFACES_INTERFACES_INTERFACE_STATISTICS_IN_MULTICAST_PKTS_YANG_PATH INTERFACES_INTERFACES_INTERFACE_STATISTICS_YANG_PATH "/in-multicast-pkts"
#define INTERFACES_INTERFACES_INTERFACE_STATISTICS_IN_DISCARDS_YANG_PATH INTERFACES_INTERFACES_INTERFACE_STATISTICS_YANG_PATH "/in-discards"
#define INTERFACES_INTERFACES_INTERFACE_STATISTICS_IN_ERRORS_YANG_PATH INTERFACES_INTERFACES_INTERFACE_STATISTICS_YANG_PATH "/in-errors"
#define INTERFACES_INTERFACES_INTERFACE_STATISTICS_IN_UNKNOWN_PROTOS_YANG_PATH INTERFACES_INTERFACES_INTERFACE_STATISTICS_YANG_PATH "/in-unknown-protos"
#define INTERFACES_INTERFACES_INTERFACE_STATISTICS_OUT_OCTETS_YANG_PATH INTERFACES_INTERFACES_INTERFACE_STATISTICS_YANG_PATH "/out-octets"
#define INTERFACES_INTERFACES_INTERFACE_STATISTICS_OUT_UNICAST_PKTS_YANG_PATH INTERFACES_INTERFACES_INTERFACE_STATISTICS_YANG_PATH "/out-unicast-pkts"
#define INTERFACES_INTERFACES_INTERFACE_STATISTICS_OUT_BROADCAST_PKTS_YANG_PATH INTERFACES_INTERFACES_INTERFACE_STATISTICS_YANG_PATH "/out-broadcast-pkts"
#define INTERFACES_INTERFACES_INTERFACE_STATISTICS_OUT_MULTICAST_PKTS_YANG_PATH INTERFACES_INTERFACES_INTERFACE_STATISTICS_YANG_PATH "/out-multicast-pkts"
#define INTERFACES_INTERFACES_INTERFACE_STATISTICS_OUT_DISCARDS_YANG_PATH INTERFACES_INTERFACES_INTERFACE_STATISTICS_YANG_PATH "/out-discards"
#define INTERFACES_INTERFACES_INTERFACE_STATISTICS_OUT_ERRORS_YANG_PATH INTERFACES_INTERFACES_INTERFACE_STATISTICS_YANG_PATH "/out-errors"
#define INTERFACES_INTERFACES_INTERFACE_STATISTICS_YANG_PATH INTERFACES_INTERFACES_INTERFACE_YANG_PATH "/statistics"
#define INTERFACES_INTERFACES_INTERFACE_YANG_PATH INTERFACES_INTERFACES_YANG_PATH "/interface"
#define INTERFACES_INTERFACES_YANG_PATH "/ietf-interfaces:interfaces"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#endif // INTERFACES_PLUGIN_COMMON_H
