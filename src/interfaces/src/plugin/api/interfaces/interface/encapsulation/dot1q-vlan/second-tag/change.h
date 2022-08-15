#ifndef INTERFACES_PLUGIN_API_INTERFACES_INTERFACE_ENCAPSULATION_DOT1Q_VLAN_SECOND_TAG_CHANGE_H
#define INTERFACES_PLUGIN_API_INTERFACES_INTERFACE_ENCAPSULATION_DOT1Q_VLAN_SECOND_TAG_CHANGE_H

#include <srpc.h>
#include <utarray.h>

int interfaces_interface_encapsulation_dot1q_vlan_second_tag_change_vlan_id(void* priv, sr_session_ctx_t* session, const srpc_change_ctx_t* change_ctx);
int interfaces_interface_encapsulation_dot1q_vlan_second_tag_change_tag_type(void* priv, sr_session_ctx_t* session, const srpc_change_ctx_t* change_ctx);

#endif // INTERFACES_PLUGIN_API_INTERFACES_INTERFACE_ENCAPSULATION_DOT1Q_VLAN_SECOND_TAG_CHANGE_H