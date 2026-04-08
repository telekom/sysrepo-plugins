<!--
SPDX-FileCopyrightText: 2026 Deutsche Telekom AG
SPDX-FileContributor: Sartura d.d.
SPDX-License-Identifier: BSD-3-Clause
-->

# IETF-Hardware plugin documentation

## Running and testing the plugin
The necessary .yang files need to be installed in sysrepo from the `yang` directory

```bash
sysrepoctl -i yang/iana-hardware.yang
sysrepoctl -i yang/ietf-hardware.yang
sysrepoctl -c ietf-hardware -e hardware-sensor -e entity-mib
```

The sysrepo plugin daemon needs to be loaded after the plugin is installed:

```bash
sysrepo-plugind -v 4 -d
```

The functionality can be tested by doing an operational data request through sysrepo; data requests should be made for the `hardware`, `component` nodes:

```bash
sysrepocfg -x "/ietf-hardware:hardware" -X -d operational -f json
```

As described in the module itself the plugin holds configuration data provided by the user in the running data-store and uses the data according to the requirements of the RFC to change the hardware information provided in the operational data-store. A configuration example can be found under the `examples` directory and can be imported in sysrepo using:

```bash
sysrepocfg -I examples/dt-ietf-hardware-plugin-test-config.xml -d running
```

### Nodes that are currently implemented
DONE - nodes are implemented and a value is provided if such information can be retrieved\
NA - node is not implemented because the value can't be found in Linux systems

```
module: ietf-hardware
  +--rw hardware
     +--ro last-change?   yang:date-and-time                          DONE
     +--rw component* [name]                                          DONE
        +--rw name              string                                DONE
        +--rw class             identityref                           DONE
        +--ro physical-index?   int32 {entity-mib}?                   DONE
        +--ro description?      string                                DONE
        +--rw parent?           -> ../../component/name               DONE
        +--rw parent-rel-pos?   int32                                 DONE
        +--ro contains-child*   -> ../../component/name               DONE
        +--ro hardware-rev?     string                                DONE
        +--ro firmware-rev?     string                                DONE
        +--ro software-rev?     string                                DONE
        +--ro serial-num?       string                                DONE
        +--ro mfg-name?         string                                DONE
        +--ro model-name?       string                                DONE
        +--rw alias?            string                                DONE
        +--rw asset-id?         string                                DONE (only configuration side)
        +--ro is-fru?           boolean                               NA
        +--ro mfg-date?         yang:date-and-time                    NA
        +--rw uri*              inet:uri                              DONE (only configuration side)
        +--ro uuid?             yang:uuid                             DONE
        +--rw state {hardware-state}?                                 NA
        |  +--ro state-last-changed?   yang:date-and-time
        |  +--rw admin-state?          admin-state
        |  +--ro oper-state?           oper-state
        |  +--ro usage-state?          usage-state
        |  +--ro alarm-state?          alarm-state
        |  +--ro standby-state?        standby-state
        +--ro sensor-data {hardware-sensor}?                          DONE
           +--ro value?               sensor-value                    DONE
           +--ro value-type?          sensor-value-type               DONE
           +--ro value-scale?         sensor-value-scale              DONE
           +--ro value-precision?     sensor-value-precision          DONE
           +--ro oper-status?         sensor-status                   DONE
           +--ro units-display?       string                          DONE
           +--ro value-timestamp?     yang:date-and-time              DONE
           +--ro value-update-rate?   uint32                          DONE

  notifications:                                                      NA
    +---n hardware-state-change
    +---n hardware-state-oper-enabled {hardware-state}?
    |  +--ro name?          -> /hardware/component/name
    |  +--ro admin-state?   -> /hardware/component/state/admin-state
    |  +--ro alarm-state?   -> /hardware/component/state/alarm-state
    +---n hardware-state-oper-disabled {hardware-state}?
       +--ro name?          -> /hardware/component/name
       +--ro admin-state?   -> /hardware/component/state/admin-state
       +--ro alarm-state?   -> /hardware/component/state/alarm-state
```

### Assumptions made in the nodes value
The plugin uses `lshw` as the go-to tool for hardware information gathering, it has an option to output in json format and in this manner the information is collected by parsing the lshw output. By doing so a wide set of correlations have been made between the tool's output and the IETF-Hardware nodes, below you can find a map summarizing them:

```
IETF-Hardware node                                                     LSHW json node
----------------------------------------------------------------------------------------------------------------------
name (changed to '{parent}:{name} on collision')                       id (non-unique)
class (`unknown` where value isn't defined in IANA-Hardware)           class
physical-index (converted to int32)                                    physid (hex)
description                                                            description
parent                                                                 deducted as ascendant of `children` node
parent-rel-pos (increasing value, starting from 1)                     -
contains-child                                                         children/id (for every child)
hardware-rev                                                           version
firmware-rev                                                           children/id[firmware] OR configuration/firmware
software-rev                                                           configuration/driverversion
serial-num                                                             serial
mfg-name                                                               vendor
model-name                                                             product
alias                                                                  handle
asset-id                                                               -
is-fru                                                                 -
mfg-date                                                               -
uri                                                                    -
uuid                                                                   configuration/uuid
```

### Parent-rel-pos node implementation decision
In this implementation the `parent-rel-pos` is an increasing unsigned integer starting from 1.
* First of all this has been done considering that in modern Linux systems the old classes contained in iana-hardware do not map to real environments and most of the time the class of a component is `unknown` which in turn creates many sibling nodes and identifying a slot/handle ordering between such devices can be quite tricky and for the most part useless. For example consider having a PCI bus node that has as children the pci controller and the usb controller: pci:0, pci:1, pci:2, usb-host:0, usb-host:1; and since all of them can't be mapped to a relevant iana-hardware class will have the class value `unknown`. Thus by the definition you can't have the pci:0 with a `parent-rel-pos` value `0` at the same time usb-host:0 has also the `parent-rel-pos` equal to `0`. The argument could be made that if the pci:0 node has a `parent-rel-pos equal` to `0` then maybe usb-host should use a different ordering scheme starting from 10, but how would this be more useful than incremental values since the recommendation based on slot ordering is broken anyway, in complex systems this could easily scale up to hundreds and having a node `generic:0` be assigned a `parent-rel-pos` of 8001 is of no use and computationally heavy while also taking into consideration nodes that do not match any external numbering or clearly visible ordering while also being in the same hardware class.
* Second of all the recommendations for the `entPhysicalParentRelPos` are applicable only to SNMP agents that implement the ENTITY-MIB and since this plugin bypasses a SNMP implementation mainly because there's no undisclosed SNMP agent in Linux systems that implement the ENTITY-MIB we are going to follow a `consistent (but possibly arbitrary) ordering to a given set of 'sibling' components` that is proposed as a last resort if the `parent-rel-pos` could not be determined by any other means.

### Sensor notification YANG augmentation
As requested we created a module to augment the IETF Hardware model with sensor notifications alongside configurable thresholds. To enable the functionality `sensor-notifications-augment` module needs to be installed:

```bash
sysrepoctl -i yang/sensor-notifications-augment.yang
```

The XML example in `examples` has two component nodes set to monitor arbitrary values and, given the poll-interval value, when those values are crossed `sensor-threshold-crossed` notifications are sent by the implementation. Notifications are only triggered when a sensor value actually crosses a configured threshold (rising or falling), not on every poll. A sensor component can contain multiple thresholds.

```
module: sensor-notifications-augment
  augment /hw:hardware/hw:component:
    +--rw sensor-notifications {hw:hardware-sensor}?
    |  +--rw poll-interval?   uint32
    |  +--rw threshold* [name]
    |     +--rw name    string
    |     +--rw value?  hw:sensor-value
    +---n sensor-threshold-crossed {hw:hardware-sensor}?
       +--ro threshold-name?    -> .../sensor-notifications/threshold/name
       +--ro threshold-value?   -> .../sensor-notifications/threshold/value
       +-- (direction)?
       |  +--:(rising)
       |  |  +--ro rising?    empty
       |  +--:(falling)
       |     +--ro falling?   empty
       +--ro sensor-value?      -> .../hw:sensor-data/hw:value
```
