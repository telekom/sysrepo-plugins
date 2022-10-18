#include "address.h"
#include "plugin/types.h"
#include "srpc/common.h"
#include "src/utlist.h"

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#include <srpc.h>

interfaces_interface_ipv4_address_element_t* interfaces_interface_ipv4_address_new(void)
{
    return NULL;
}

int interfaces_interface_ipv4_address_add_element(interfaces_interface_ipv4_address_element_t** address, interfaces_interface_ipv4_address_element_t* new_element)
{
    LL_PREPEND(*address, new_element);
    return 0;
}

void interfaces_interface_ipv4_address_free(interfaces_interface_ipv4_address_element_t** address)
{
    interfaces_interface_ipv4_address_element_t *iter = NULL, *tmp = NULL;

    LL_FOREACH_SAFE(*address, iter, tmp)
    {
        // remove from list
        LL_DELETE(*address, iter);

        // free element data
        interfaces_interface_ipv4_address_element_free(&iter);
    }
}

interfaces_interface_ipv4_address_element_t* interfaces_interface_ipv4_address_element_new(void)
{
    interfaces_interface_ipv4_address_element_t* new_element = NULL;

    new_element = malloc(sizeof(interfaces_interface_ipv4_address_element_t));
    new_element->address = (interfaces_interface_ipv4_address_t) { 0 };

    return new_element;
}

void interfaces_interface_ipv4_address_element_free(interfaces_interface_ipv4_address_element_t** el)
{
    if (*el) {
        // IP
        if ((*el)->address.ip) {
            free((*el)->address.ip);
        }

        // netmask if one exists
        if ((*el)->address.subnet_type != interfaces_interface_ipv4_address_subnet_none) {
            if ((*el)->address.subnet_type == interfaces_interface_ipv4_address_subnet_netmask && (*el)->address.subnet.netmask != NULL) {
                free((*el)->address.subnet.netmask);
            }
        }

        // address data
        free(*el);
        *el = NULL;
    }
}

int interfaces_interface_ipv4_address_element_set_ip(interfaces_interface_ipv4_address_element_t** el, const char* ip)
{
    if ((*el)->address.ip) {
        free((*el)->address.ip);
    }

    if (ip) {
        (*el)->address.ip = strdup(ip);
        return (*el)->address.ip == NULL;
    }

    return 0;
}

/* set (deepcopy) an IPv4 address list */
int interfaces_interface_ipv4_address_element_set(interfaces_interface_ipv4_address_element_t** src,
                                                   interfaces_interface_ipv4_address_element_t **dst)
{
    interfaces_interface_ipv4_address_element_t *src_iter = NULL;
    interfaces_interface_ipv4_address_element_t *new_elem = NULL;

    LL_FOREACH(*src, src_iter) {
        new_elem = interfaces_interface_ipv4_address_element_new();
        interfaces_interface_ipv4_address_element_set_ip(&new_elem, src_iter->address.ip);
        interfaces_interface_ipv4_address_element_set_prefix_length(&new_elem, 
                                                                    src_iter->address.subnet.prefix_length);

        interfaces_interface_ipv4_address_add_element(dst, new_elem);
    }
    
    return 0;
}

int interfaces_interface_ipv4_address_element_set_subnet(interfaces_interface_ipv4_address_element_t** el, char *netmask, enum interfaces_interface_ipv4_address_subnet subtype)
{
    int error = 0;
    int prefix_length = 0;

    switch (subtype) {
        case interfaces_interface_ipv4_address_subnet_netmask:
            interfaces_interface_ipv4_address_element_set_netmask(el, netmask);
            break;
        case interfaces_interface_ipv4_address_subnet_prefix_length:
            SRPC_SAFE_CALL(interfaces_interface_ipv4_address_netmask2prefix(netmask, prefix_length), out);
            interfaces_interface_ipv4_address_element_set_prefix_length(el, prefix_length);
            break;
        case interfaces_interface_ipv4_address_subnet_none:
            break;
        default:
            error = -1;            
    }

out:

    return error;
}

int interfaces_interface_ipv4_address_element_set_prefix_length(interfaces_interface_ipv4_address_element_t** el, uint8_t prefix_length)
{
    (*el)->address.subnet.prefix_length = prefix_length;
    (*el)->address.subnet_type = interfaces_interface_ipv4_address_subnet_prefix_length;

    return 0;
}

int interfaces_interface_ipv4_address_element_set_netmask(interfaces_interface_ipv4_address_element_t** el, const char* netmask)
{
    if ((*el)->address.subnet.netmask) {
        free((*el)->address.subnet.netmask);
        (*el)->address.subnet_type = interfaces_interface_ipv4_address_subnet_none;
    }

    if (netmask) {
        (*el)->address.subnet.netmask = strdup(netmask);

        // check for correctly set netmask
        if ((*el)->address.subnet.netmask != NULL) {
            (*el)->address.subnet_type = interfaces_interface_ipv4_address_subnet_netmask;
            return 0;
        } else {
            (*el)->address.subnet_type = interfaces_interface_ipv4_address_subnet_none;
            return 1;
        }
    }

    return 0;
}

int interfaces_interface_ipv4_address_netmask2prefix(const char* netmask, uint8_t* prefix_length)
{
    int error = 0;
    struct in_addr addr = { 0 };
    uint8_t prefix = 0;

    // convert to bits (uint32_t -> addr.s_addr)
    SRPC_SAFE_CALL_ERR_COND(error, error != 1, inet_pton(AF_INET, netmask, &addr), error_out);

    // count address bits
    while (addr.s_addr) {
        if (addr.s_addr & 0x1) {
            ++prefix;
        }

        addr.s_addr >>= 1;
    }

    // set the provided value
    *prefix_length = prefix;

    error = 0;
    goto out;

error_out:
    error = -1;

out:
    return error;
}
