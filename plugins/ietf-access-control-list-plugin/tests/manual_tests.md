# Intro
<!--
SPDX-FileCopyrightText: 2025 Deutsche Telekom AG

SPDX-License-Identifier: CC0-1.0    
-->

# Manual testing

## Intro
This document contains a list of sysrepocfg commands that can be used to testand expected outputs
currently implemented plugin functionality.

It can also serve as a reference containing a list of currently implemented leafs in the model.

It is assumed that the datastore has already been initialized, and the data in examples imported.

The following example xml files from the `../examples` directory are currently available:
* acl_eth_example.xml
* acl_icmp_example.xml
* acl_ipv4_example.xml
* acl_ipv6_example.xml
* acl_tcp_example.xml
* acl_udp_example.xml

To import the acl_tcp_example.xml data run the following command:
```
sysrepocfg --edit=examples/acl_tcp_example.xml -m "ietf-access-control-list"
```

## ietf-access-control-list

First we can confirm that the datastore contains any data at all.

```
$ sysrepocfg -X -m ietf-access-control-list
<acls xmlns="urn:ietf:params:xml:ns:yang:ietf-access-control-list">
  <acl>
    <name>sample-ipv4-acl</name>
    <type xmlns:acl="urn:ietf:params:xml:ns:yang:ietf-access-control-list">acl:ipv4-acl-type</type>
    <aces>
      <ace>
        <name>rule1</name>
        <matches>
          <ipv4>
            <dscp>1</dscp>
            <length>232</length>
            <ttl>232</ttl>
            <protocol>6</protocol>
            <ihl>15</ihl>
            <destination-ipv4-network>198.51.100.0/24</destination-ipv4-network>
            <source-ipv4-network>192.0.2.0/24</source-ipv4-network>
          </ipv4>
        </matches>
        <actions>
          <forwarding xmlns:acl="urn:ietf:params:xml:ns:yang:ietf-access-control-list">acl:drop</forwarding>
        </actions>
      </ace>
    </aces>
  </acl>
  <acl>
    <name>sample-port-acl</name>
    <type xmlns:acl="urn:ietf:params:xml:ns:yang:ietf-access-control-list">acl:ipv4-acl-type</type>
    <aces>
      <ace>
        <name>rule1</name>
        <matches>
          <tcp>
            <sequence-number>22</sequence-number>
            <acknowledgement-number>32</acknowledgement-number>
            <data-offset>8</data-offset>
            <flags>cwr</flags>
            <window-size>33</window-size>
            <urgent-pointer>35</urgent-pointer>
            <source-port>
              <lower-port>16384</lower-port>
              <upper-port>16387</upper-port>
            </source-port>
            <destination-port>
              <operator>lte</operator>
              <port>666</port>
            </destination-port>
          </tcp>
        </matches>
        <actions>
          <forwarding xmlns:acl="urn:ietf:params:xml:ns:yang:ietf-access-control-list">acl:drop</forwarding>
        </actions>
      </ace>
    </aces>
  </acl>
</acls>
```

### Check if the rules are applied on the system:

```
nft -a list ruleset

table ip sample-port-acl { # handle 1
	chain rule1 { # handle 1
		type filter hook input priority filter; policy accept;
		tcp sequence 22 drop # handle 2
		tcp ackseq 32 drop # handle 3
		tcp doff 8 drop # handle 4
		tcp flags cwr drop # handle 5
		tcp window 33 drop # handle 6
		tcp urgptr 35 drop # handle 7
		tcp sport { 16384-16387 } drop # handle 9
		tcp dport <= 666 drop # handle 10
	}
}
```

## Deletion of tables, chains and rules

In order to delete a table (in the above example the family is `ip` and the table name is `sample-port-acl`):
```
nft delete table <family> <table_name>
```
note: family refers to one of the following currently supported table types: `ip`, `ip6` and `bridge`

In order to delete a chain and all of its rules (in the above example the chain name is `rule1`):
```
nft delete chain ip <table_name> <rule_name>
```

In order to delete a specific rule (for example the rule with handle number `3`):
```
nft delete rule ip <table_name> <rule_name> handle <handle_number>
```

## Table name

```
sysrepocfg -X -x '/ietf-access-control-list:acls/acl[name="sample-port-acl"]/name'
<acls xmlns="urn:ietf:params:xml:ns:yang:ietf-access-control-list">
  <acl>
    <name>sample-port-acl</name>
  </acl>
</acls>
```
The table name is represented with the `acl` node from the yang module. The table contains a list of chains (ace node) and rules (matches node).

## Chain name

```
sysrepocfg -X -x '/ietf-access-control-list:acls/acl[name="sample-port-acl"]/aces/ace[name="rule1"]/name'
<acls xmlns="urn:ietf:params:xml:ns:yang:ietf-access-control-list">
  <acl>
    <name>sample-port-acl</name>
    <aces>
      <ace>
        <name>rule1</name>
      </ace>
    </aces>
  </acl>
</acls>
```

The chain name is represented with the `ace` node from the yang module. Multiple chains (aces) can exist for a specific table/acl.

## Rules

```
sysrepocfg -X -x '/ietf-access-control-list:acls/acl[name="sample-port-acl"]/aces/ace[name="rule1"]/matches/tcp'
<acls xmlns="urn:ietf:params:xml:ns:yang:ietf-access-control-list">
  <acl>
    <name>sample-port-acl</name>
    <aces>
      <ace>
        <name>rule1</name>
        <matches>
          <tcp>
            <sequence-number>22</sequence-number>
            <acknowledgement-number>32</acknowledgement-number>
            <data-offset>8</data-offset>
            <flags>cwr</flags>
            <window-size>33</window-size>
            <urgent-pointer>35</urgent-pointer>
            <source-port>
              <lower-port>16384</lower-port>
              <upper-port>16387</upper-port>
            </source-port>
            <destination-port>
              <operator>lte</operator>
              <port>666</port>
            </destination-port>
          </tcp>
        </matches>
      </ace>
    </aces>
  </acl>
</acls>
```

Rules are represented by the `matches` node from the yang module. Multiple rules (matches) can exist for a specific chain/ace.
In this example, a tcp match is displayed.
