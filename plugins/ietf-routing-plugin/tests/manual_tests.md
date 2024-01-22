# routing-plugin manual testing

## Intro
This document contains a list of commands that can be used to test currently
implemented routing-plugin functionality. All commands should be executed while the plugin is
running. Running the interfaces plugin is not necessary for testing.

This is a tree view of `ietf-routing` YANG module nodes currently implemented in the plugin:
```
module: ietf-routing
  +--rw routing
  |  +--rw router-id?                 yang:dotted-quad {router-id}?
  |  +--ro interfaces
  |  |  +--ro interface*   if:interface-ref
  |  +--rw control-plane-protocols
  |  |  +--rw control-plane-protocol* [type name]
  |  |     +--rw type             identityref
  |  |     +--rw name             string
  |  |     +--rw description?     string
  |  |     +--rw static-routes
  |  |        +--rw v4ur:ipv4
  |  |        |  +--rw v4ur:route* [destination-prefix]
  |  |        |     +--rw v4ur:destination-prefix    inet:ipv4-prefix
  |  |        |     +--rw v4ur:description?          string
  |  |        |     +--rw v4ur:next-hop
  |  |        |        +--rw (v4ur:next-hop-options)
  |  |        |           +--:(v4ur:simple-next-hop)
  |  |        |           |  +--rw v4ur:outgoing-interface?   if:interface-ref
  |  |        |           |  +--rw v4ur:next-hop-address?     inet:ipv4-address
  |  |        |           +--:(v4ur:special-next-hop)
  |  |        |           |  +--rw v4ur:special-next-hop?     enumeration
  |  |        |           +--:(v4ur:next-hop-list)
  |  |        |              +--rw v4ur:next-hop-list
  |  |        |                 +--rw v4ur:next-hop* [index]
  |  |        |                    +--rw v4ur:index                 string
  |  |        |                    +--rw v4ur:outgoing-interface?   if:interface-ref
  |  |        |                    +--rw v4ur:next-hop-address?     inet:ipv4-address
  |  |        +--rw v6ur:ipv6
  |  |           +--rw v6ur:route* [destination-prefix]
  |  |              +--rw v6ur:destination-prefix    inet:ipv6-prefix
  |  |              +--rw v6ur:description?          string
  |  |              +--rw v6ur:next-hop
  |  |                 +--rw (v6ur:next-hop-options)
  |  |                    +--:(v6ur:simple-next-hop)
  |  |                    |  +--rw v6ur:outgoing-interface?   if:interface-ref
  |  |                    |  +--rw v6ur:next-hop-address?     inet:ipv6-address
  |  |                    +--:(v6ur:special-next-hop)
  |  |                    |  +--rw v6ur:special-next-hop?     enumeration
  |  |                    +--:(v6ur:next-hop-list)
  |  |                       +--rw v6ur:next-hop-list
  |  |                          +--rw v6ur:next-hop* [index]
  |  |                             +--rw v6ur:index                 string
  |  |                             +--rw v6ur:outgoing-interface?   if:interface-ref
  |  |                             +--rw v6ur:next-hop-address?     inet:ipv6-address
  |  +--rw ribs
  |     +--rw rib* [name]
  |        +--rw name              string
  |        +--rw address-family    identityref
  |        +--ro default-rib?      boolean {multiple-ribs}?
  |        +--ro routes
  |        |  +--ro route* []
  |        |     +--ro route-preference?          route-preference
  |        |     +--ro next-hop
  |        |     |  +--ro (next-hop-options)
  |        |     |     +--:(simple-next-hop)
  |        |     |     |  +--ro outgoing-interface?      if:interface-ref
  |        |     |     |  +--ro v4ur:next-hop-address?   inet:ipv4-address
  |        |     |     |  +--ro v6ur:next-hop-address?   inet:ipv6-address
  |        |     |     +--:(special-next-hop)
  |        |     |     |  +--ro special-next-hop?        enumeration
  |        |     |     +--:(next-hop-list)
  |        |     |        +--ro next-hop-list
  |        |     |           +--ro next-hop* []
  |        |     |              +--ro outgoing-interface?   if:interface-ref
  |        |     |              +--ro v4ur:address?         inet:ipv4-address
  |        |     |              +--ro v6ur:address?         inet:ipv6-address
  |        |     +--ro source-protocol            identityref
  |        |     +--ro active?                    empty
  |        |     +--ro last-updated?              yang:date-and-time
  |        |     +--ro v4ur:destination-prefix?   inet:ipv4-prefix
  |        |     +--ro v6ur:destination-prefix?   inet:ipv6-prefix
  |        +---x active-route
  |        |  +---w input
  |        |  |  +---w v4ur:destination-address?   inet:ipv4-address
  |        |  |  +---w v6ur:destination-address?   inet:ipv6-address
  |        |  +--ro output
  |        |     +--ro route
  |        |        +--ro next-hop
  |        |        |  +--ro (next-hop-options)
  |        |        |     +--:(simple-next-hop)
  |        |        |     |  +--ro outgoing-interface?      if:interface-ref
  |        |        |     |  +--ro v4ur:next-hop-address?   inet:ipv4-address
  |        |        |     |  +--ro v6ur:next-hop-address?   inet:ipv6-address
  |        |        |     +--:(special-next-hop)
  |        |        |     |  +--ro special-next-hop?        enumeration
  |        |        |     +--:(next-hop-list)
  |        |        |        +--ro next-hop-list
  |        |        |           +--ro next-hop* []
  |        |        |              +--ro outgoing-interface?      if:interface-ref
  |        |        |              +--ro v4ur:next-hop-address?   inet:ipv4-address
  |        |        |              +--ro v6ur:next-hop-address?   inet:ipv6-address
  |        |        +--ro source-protocol            identityref
  |        |        +--ro active?                    empty
  |        |        +--ro last-updated?              yang:date-and-time
  |        |        +--ro v4ur:destination-prefix?   inet:ipv4-prefix
  |        |        +--ro v6ur:destination-prefix?   inet:ipv6-prefix
  |        +--rw description?      string
  o--ro routing-state
     +--ro router-id?                 yang:dotted-quad
     o--ro interfaces
     |  o--ro interface*   if:interface-state-ref
     o--ro control-plane-protocols
     |  o--ro control-plane-protocol* [type name]
     |     o--ro type    identityref
     |     o--ro name    string
     o--ro ribs
        o--ro rib* [name]
           o--ro name              string
           +--ro address-family    identityref
           o--ro default-rib?      boolean {multiple-ribs}?
           o--ro routes
           |  o--ro route* []
           |     o--ro route-preference?          route-preference
           |     o--ro next-hop
           |     |  +--ro (next-hop-options)
           |     |     +--:(simple-next-hop)
           |     |     |  +--ro outgoing-interface?      if:interface-ref
           |     |     |  o--ro v4ur:next-hop-address?   inet:ipv4-address
           |     |     |  o--ro v6ur:next-hop-address?   inet:ipv6-address
           |     |     +--:(special-next-hop)
           |     |     |  +--ro special-next-hop?        enumeration
           |     |     +--:(next-hop-list)
           |     |        +--ro next-hop-list
           |     |           +--ro next-hop* []
           |     |              +--ro outgoing-interface?   if:interface-ref
           |     |              o--ro v4ur:address?         inet:ipv4-address
           |     |              o--ro v6ur:address?         inet:ipv6-address
           |     +--ro source-protocol            identityref
           |     +--ro active?                    empty
           |     +--ro last-updated?              yang:date-and-time
           |     o--ro v4ur:destination-prefix?   inet:ipv4-prefix
           |     o--ro v6ur:destination-prefix?   inet:ipv6-prefix
           o---x active-route
              +---w input
              |  o---w v4ur:destination-address?   inet:ipv4-address
              |  o---w v6ur:destination-address?   inet:ipv6-address
              +--ro output
                 o--ro route
                    o--ro next-hop
                    |  +--ro (next-hop-options)
                    |     +--:(simple-next-hop)
                    |     |  +--ro outgoing-interface?      if:interface-ref
                    |     |  o--ro v4ur:next-hop-address?   inet:ipv4-address
                    |     |  o--ro v6ur:next-hop-address?   inet:ipv6-address
                    |     +--:(special-next-hop)
                    |     |  +--ro special-next-hop?        enumeration
                    |     +--:(next-hop-list)
                    |        +--ro next-hop-list
                    |           +--ro next-hop* []
                    |              +--ro outgoing-interface?      if:interface-ref
                    |              o--ro v4ur:next-hop-address?   inet:ipv4-address
                    |              o--ro v6ur:next-hop-address?   inet:ipv6-address
                    +--ro source-protocol            identityref
                    +--ro active?                    empty
                    +--ro last-updated?              yang:date-and-time
                    o--ro v4ur:destination-prefix?   inet:ipv4-prefix
                    o--ro v6ur:destination-prefix?   inet:ipv6-prefix



  augment /if:interfaces/if:interface/ip:ipv6:
    +--rw ipv6-router-advertisements
       +--rw send-advertisements?    boolean
       +--rw max-rtr-adv-interval?   uint16
       +--rw min-rtr-adv-interval?   uint16
       +--rw managed-flag?           boolean
       +--rw other-config-flag?      boolean
       +--rw link-mtu?               uint32
       +--rw reachable-time?         uint32
       +--rw retrans-timer?          uint32
       +--rw cur-hop-limit?          uint8
       +--rw default-lifetime?       uint16
       +--rw prefix-list
          +--rw prefix* [prefix-spec]
             +--rw prefix-spec                 inet:ipv6-prefix
             +--rw (control-adv-prefixes)?
                +--:(no-advertise)
                |  +--rw no-advertise?         empty
                +--:(advertise)
                   +--rw valid-lifetime?       uint32
                   +--rw on-link-flag?         boolean
                   +--rw preferred-lifetime?   uint32
                   +--rw autonomous-flag?      boolean
  augment /if:interfaces-state/if:interface/ip:ipv6:
    o--ro ipv6-router-advertisements
       o--ro send-advertisements?    boolean
       o--ro max-rtr-adv-interval?   uint16
       o--ro min-rtr-adv-interval?   uint16
       o--ro managed-flag?           boolean
       o--ro other-config-flag?      boolean
       o--ro link-mtu?               uint32
       o--ro reachable-time?         uint32
       o--ro retrans-timer?          uint32
       o--ro cur-hop-limit?          uint8
       o--ro default-lifetime?       uint16
       o--ro prefix-list
          o--ro prefix* [prefix-spec]
             o--ro prefix-spec           inet:ipv6-prefix
             o--ro valid-lifetime?       uint32
             o--ro on-link-flag?         boolean
             o--ro preferred-lifetime?   uint32
             o--ro autonomous-flag?      boolean


  augment /if:interfaces/if:interface/ip:ipv6:
    +--rw ipv6-router-advertisements
       +--rw send-advertisements?    boolean
       +--rw max-rtr-adv-interval?   uint16
       +--rw min-rtr-adv-interval?   uint16
       +--rw managed-flag?           boolean
       +--rw other-config-flag?      boolean
       +--rw link-mtu?               uint32
       +--rw reachable-time?         uint32
       +--rw retrans-timer?          uint32
       +--rw cur-hop-limit?          uint8
       +--rw default-lifetime?       uint16
       +--rw prefix-list
          +--rw prefix* [prefix-spec]
             +--rw prefix-spec                 inet:ipv6-prefix
             +--rw (control-adv-prefixes)?
                +--:(no-advertise)
                |  +--rw no-advertise?         empty
                +--:(advertise)
                   +--rw valid-lifetime?       uint32
                   +--rw on-link-flag?         boolean
                   +--rw preferred-lifetime?   uint32
                   +--rw autonomous-flag?      boolean
  augment /if:interfaces-state/if:interface/ip:ipv6:
    o--ro ipv6-router-advertisements
       o--ro send-advertisements?    boolean
       o--ro max-rtr-adv-interval?   uint16
       o--ro min-rtr-adv-interval?   uint16
       o--ro managed-flag?           boolean
       o--ro other-config-flag?      boolean
       o--ro link-mtu?               uint32
       o--ro reachable-time?         uint32
       o--ro retrans-timer?          uint32
       o--ro cur-hop-limit?          uint8
       o--ro default-lifetime?       uint16
       o--ro prefix-list
          o--ro prefix* [prefix-spec]
             o--ro prefix-spec           inet:ipv6-prefix
             o--ro valid-lifetime?       uint32
             o--ro on-link-flag?         boolean
             o--ro preferred-lifetime?   uint32
             o--ro autonomous-flag?      boolean
```

## Create route 

First, the routing model checks the ietf-interfaces plugin running datastore if all the interfaces are present
that will be added into the routing plugin running datastore.


Config data:
```xml
<routing xmlns="urn:ietf:params:xml:ns:yang:ietf-routing">
  <control-plane-protocols>
    <control-plane-protocol>
      <type>static</type>
      <name>unspec</name>
      <static-routes>
        <ipv4 xmlns="urn:ietf:params:xml:ns:yang:ietf-ipv4-unicast-routing">
          <route>
            <destination-prefix>10.10.10.0/24</destination-prefix>
            <next-hop>
              <next-hop-list>
                <next-hop>
                  <index>test5</index>
                  <outgoing-interface>enp0s3</outgoing-interface>
                  <next-hop-address>192.168.0.120</next-hop-address>
                </next-hop>
                <next-hop>
                  <index>test3</index>
                  <outgoing-interface>enp0s3</outgoing-interface>
                  <next-hop-address>192.168.0.130</next-hop-address>
                </next-hop>
                <next-hop>
                  <index>test4</index>
                  <outgoing-interface>enp0s3</outgoing-interface>
                  <next-hop-address>192.168.0.100</next-hop-address>
                </next-hop>
              </next-hop-list>
            </next-hop>
          </route>
        </ipv4>
      </static-routes>
    </control-plane-protocol>
  </control-plane-protocols>
</routing>
```


Creating a route component in the datastore should create a Linux route on the system.

```bash
$ ip route
10.10.10.0/24 proto static 
	nexthop via 192.168.0.120 dev enp0s3 weight 1 
	nexthop via 192.168.0.130 dev enp0s3 weight 1 
	nexthop via 192.168.0.100 dev enp0s3 weight 1 
```

## Operational DS

The operational ds is matching all the routes, from all the tables '<ribs>' from the system:

```bash
sudo sysrepocfg -X -d operational -fjson -x'/ietf-routing:routing'
```
should look like this matching all the routes from all the tables: 

```
{
  "ietf-routing:routing": {
    "interfaces": {
      "interface": [
        "lo",
        "enp0s3",
        "docker0"
      ]
    },
    "control-plane-protocols": {
      "control-plane-protocol": [
        {
          "type": "static",
          "name": "unspec",
          "static-routes": {
            "ietf-ipv4-unicast-routing:ipv4": {
              "route": [
                {
                  "destination-prefix": "10.10.10.0/24",
                  "next-hop": {
                    "next-hop-list": {
                      "next-hop": [
                        {
                          "index": "test5",
                          "outgoing-interface": "enp0s3",
                          "next-hop-address": "192.168.0.120"
                        },
                        {
                          "index": "test3",
                          "outgoing-interface": "enp0s3",
                          "next-hop-address": "192.168.0.130"
                        },
                        {
                          "index": "test4",
                          "outgoing-interface": "enp0s3",
                          "next-hop-address": "192.168.0.100"
                        }
                      ]
                    }
                  }
                },
                {
                  "destination-prefix": "0.0.0.0/0",
                  "next-hop": {
                    "next-hop-list": {
                      "next-hop": [
                        {
                          "index": "index-0",
                          "outgoing-interface": "enp0s3",
                          "next-hop-address": "192.168.0.1"
                        }
                      ]
                    }
                  }
                },
                {
                  "destination-prefix": "172.17.0.0/16",
                  "next-hop": {
                    "next-hop-list": {
                      "next-hop": [
                        {
                          "index": "index-0",
                          "outgoing-interface": "docker0",
                          "next-hop-address": "0.0.0.0"
                        }
                      ]
                    }
                  }
                },
                {
                  "destination-prefix": "192.168.0.0/24",
                  "next-hop": {
                    "next-hop-list": {
                      "next-hop": [
                        {
                          "index": "index-0",
                          "outgoing-interface": "enp0s3",
                          "next-hop-address": "0.0.0.0"
                        }
                      ]
                    }
                  }
                },
                {
                  "destination-prefix": "192.168.0.1/32",
                  "next-hop": {
                    "next-hop-list": {
                      "next-hop": [
                        {
                          "index": "index-0",
                          "outgoing-interface": "enp0s3",
                          "next-hop-address": "0.0.0.0"
                        }
                      ]
                    }
                  }
                }
              ]
            }
          }
        }
      ]
    },
    "ribs": {
      "rib": [
        {
          "name": "local-ipv4",
          "routes": {
            "route": [
              {
                "next-hop": {
                  "next-hop-list": {
                    "next-hop": [
                      {
                        "outgoing-interface": "lo",
                        "ietf-ipv4-unicast-routing:address": "0.0.0.0"
                      }
                    ]
                  }
                },
                "ietf-ipv4-unicast-routing:destination-prefix": "127.0.0.0/8"
              },
              {
                "next-hop": {
                  "next-hop-list": {
                    "next-hop": [
                      {
                        "outgoing-interface": "lo",
                        "ietf-ipv4-unicast-routing:address": "0.0.0.0"
                      }
                    ]
                  }
                },
                "ietf-ipv4-unicast-routing:destination-prefix": "127.0.0.1/32"
              },
              {
                "next-hop": {
                  "next-hop-list": {
                    "next-hop": [
                      {
                        "outgoing-interface": "lo",
                        "ietf-ipv4-unicast-routing:address": "0.0.0.0"
                      }
                    ]
                  }
                },
                "ietf-ipv4-unicast-routing:destination-prefix": "127.255.255.255/32"
              },
              {
                "next-hop": {
                  "next-hop-list": {
                    "next-hop": [
                      {
                        "outgoing-interface": "docker0",
                        "ietf-ipv4-unicast-routing:address": "0.0.0.0"
                      }
                    ]
                  }
                },
                "ietf-ipv4-unicast-routing:destination-prefix": "172.17.0.1/32"
              },
              {
                "next-hop": {
                  "next-hop-list": {
                    "next-hop": [
                      {
                        "outgoing-interface": "docker0",
                        "ietf-ipv4-unicast-routing:address": "0.0.0.0"
                      }
                    ]
                  }
                },
                "ietf-ipv4-unicast-routing:destination-prefix": "172.17.255.255/32"
              },
              {
                "next-hop": {
                  "next-hop-list": {
                    "next-hop": [
                      {
                        "outgoing-interface": "enp0s3",
                        "ietf-ipv4-unicast-routing:address": "0.0.0.0"
                      }
                    ]
                  }
                },
                "ietf-ipv4-unicast-routing:destination-prefix": "192.168.0.104/32"
              },
              {
                "next-hop": {
                  "next-hop-list": {
                    "next-hop": [
                      {
                        "outgoing-interface": "enp0s3",
                        "ietf-ipv4-unicast-routing:address": "0.0.0.0"
                      }
                    ]
                  }
                },
                "ietf-ipv4-unicast-routing:destination-prefix": "192.168.0.255/32"
              },
              {
                "next-hop": {
                  "next-hop-list": {
                    "next-hop": [
                      {
                        "outgoing-interface": "lo",
                        "ietf-ipv6-unicast-routing:address": "::"
                      }
                    ]
                  }
                },
                "ietf-ipv6-unicast-routing:destination-prefix": "::1/128"
              },
              {
                "next-hop": {
                  "next-hop-list": {
                    "next-hop": [
                      {
                        "outgoing-interface": "enp0s3",
                        "ietf-ipv6-unicast-routing:address": "::"
                      }
                    ]
                  }
                },
                "ietf-ipv6-unicast-routing:destination-prefix": "fe80::a00:27ff:fe71:27bf/128"
              },
              {
                "next-hop": {
                  "next-hop-list": {
                    "next-hop": [
                      {
                        "outgoing-interface": "enp0s3",
                        "ietf-ipv6-unicast-routing:address": "::"
                      }
                    ]
                  }
                },
                "ietf-ipv6-unicast-routing:destination-prefix": "ff00::/8"
              }
            ]
          }
        },
        {
          "name": "main-ipv4",
          "routes": {
            "route": [
              {
                "next-hop": {
                  "next-hop-list": {
                    "next-hop": [
                      {
                        "outgoing-interface": "enp0s3",
                        "ietf-ipv4-unicast-routing:address": "192.168.0.1"
                      }
                    ]
                  }
                },
                "ietf-ipv4-unicast-routing:destination-prefix": "0.0.0.0/0"
              },
              {
                "next-hop": {
                  "next-hop-list": {
                    "next-hop": [
                      {
                        "outgoing-interface": "enp0s3",
                        "ietf-ipv4-unicast-routing:address": "192.168.0.120"
                      },
                      {
                        "outgoing-interface": "enp0s3",
                        "ietf-ipv4-unicast-routing:address": "192.168.0.130"
                      },
                      {
                        "outgoing-interface": "enp0s3",
                        "ietf-ipv4-unicast-routing:address": "192.168.0.100"
                      }
                    ]
                  }
                },
                "ietf-ipv4-unicast-routing:destination-prefix": "10.10.10.0/24"
              },
              {
                "next-hop": {
                  "next-hop-list": {
                    "next-hop": [
                      {
                        "outgoing-interface": "enp0s3",
                        "ietf-ipv4-unicast-routing:address": "0.0.0.0"
                      }
                    ]
                  }
                },
                "ietf-ipv4-unicast-routing:destination-prefix": "192.168.0.0/24"
              },
              {
                "next-hop": {
                  "next-hop-list": {
                    "next-hop": [
                      {
                        "outgoing-interface": "enp0s3",
                        "ietf-ipv4-unicast-routing:address": "0.0.0.0"
                      }
                    ]
                  }
                },
                "ietf-ipv4-unicast-routing:destination-prefix": "192.168.0.1/32"
              },
              {
                "next-hop": {
                  "next-hop-list": {
                    "next-hop": [
                      {
                        "outgoing-interface": "lo",
                        "ietf-ipv6-unicast-routing:address": "::"
                      }
                    ]
                  }
                },
                "ietf-ipv6-unicast-routing:destination-prefix": "::1/128"
              },
              {
                "next-hop": {
                  "next-hop-list": {
                    "next-hop": [
                      {
                        "outgoing-interface": "enp0s3",
                        "ietf-ipv6-unicast-routing:address": "::"
                      }
                    ]
                  }
                },
                "ietf-ipv6-unicast-routing:destination-prefix": "fe80::/64"
              }
            ]
          }
        }
      ]
    }
  }
}

```
This is the current route that we added to the system

```
{
                "next-hop": {
                  "next-hop-list": {
                    "next-hop": [
                      {
                        "outgoing-interface": "enp0s3",
                        "ietf-ipv4-unicast-routing:address": "192.168.0.120"
                      },
                      {
                        "outgoing-interface": "enp0s3",
                        "ietf-ipv4-unicast-routing:address": "192.168.0.130"
                      },
                      {
                        "outgoing-interface": "enp0s3",
                        "ietf-ipv4-unicast-routing:address": "192.168.0.100"
                      }
                    ]
                  }
                },
                "ietf-ipv4-unicast-routing:destination-prefix": "10.10.10.0/24"
              },
```

To check all the routes from all the tables on the system:

```bash
$ ip route show table all
```

this should be the output for the current operational ds:

```bash

default via 192.168.0.1 dev enp0s3 proto dhcp src 192.168.0.104 metric 100 
10.10.10.0/24 proto static 
	nexthop via 192.168.0.120 dev enp0s3 weight 1 
	nexthop via 192.168.0.130 dev enp0s3 weight 1 
	nexthop via 192.168.0.100 dev enp0s3 weight 1 
192.168.0.0/24 dev enp0s3 proto kernel scope link src 192.168.0.104 metric 100 
192.168.0.1 dev enp0s3 proto dhcp scope link src 192.168.0.104 metric 100 
local 127.0.0.0/8 dev lo table local proto kernel scope host src 127.0.0.1 
local 127.0.0.1 dev lo table local proto kernel scope host src 127.0.0.1 
broadcast 127.255.255.255 dev lo table local proto kernel scope link src 127.0.0.1 
local 172.17.0.1 dev docker0 table local proto kernel scope host src 172.17.0.1 
broadcast 172.17.255.255 dev docker0 table local proto kernel scope link src 172.17.0.1 linkdown 
local 192.168.0.104 dev enp0s3 table local proto kernel scope host src 192.168.0.104 
broadcast 192.168.0.255 dev enp0s3 table local proto kernel scope link src 192.168.0.104 
::1 dev lo proto kernel metric 256 pref medium
fe80::/64 dev enp0s3 proto kernel metric 256 pref medium
local ::1 dev lo table local proto kernel metric 0 pref medium
local fe80::a00:27ff:fe71:27bf dev enp0s3 table local proto kernel metric 0 pref medium
multicast ff00::/8 dev enp0s3 table local proto kernel metric 256 pref medium

```

## Fill the initial running ds

The plugin should automaticaly fill the intial running ds, if the running datastore is empty.
if the interfaces plugin does not contain all the interfaces that will be added in the routing plugin
then initialy the plugin will throw an exception, and will continue with empty running ds.

```
[ERR] Invalid leafref value "enp0s3" - no target instance "/if:interfaces/if:interface/if:name" with the same value. (Data location "/ietf-routing:routing/control-plane-protocols/control-plane-protocol[type='ietf-routing:static'][name='unspec']/static-routes/ietf-ipv4-unicast-routing:ipv4/route[destination-prefix='192.168.0.1/32']/next-hop/next-hop-list/next-hop[index='index-0']/outgoing-interface".)
[ERR] Validation failed.
[ERR] ietf-routing-plugin: Unable to fill running Datastore, Possible error is matching interfaces in interfaces plugin, Err: Session::applyChanges: Couldn't apply changes: SR_ERR_VALIDATION_FAILED
 Invalid leafref value "enp0s3" - no target instance "/if:interfaces/if:interface/if:name" with the same value. (Data location "/ietf-routing:routing/control-plane-protocols/control-plane-protocol[type='ietf-routing:static'][name='unspec']/static-routes/ietf-ipv4-unicast-routing:ipv4/route[destination-prefix='192.168.0.1/32']/next-hop/next-hop-list/next-hop[index='index-0']/outgoing-interface".) (SR_ERR_LY)
 Validation failed. (SR_ERR_VALIDATION_FAILED)

```


