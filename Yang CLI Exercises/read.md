# YANG Modeling from CLI – IoT Routing / Platform Exercises

## Overview

This project demonstrates how common network device CLI configurations can be represented using **YANG data models**.

The exercises cover five independent configuration features:

1. Interface configuration
2. VLAN configuration
3. Static routing
4. NTP configuration
5. SNMP configuration

The purpose of these exercises is to understand how CLI commands can be translated into structured YANG data models and how those models can later be used with **NETCONF**.

> **Note:** The CLI snippets used in these exercises are illustrative. Real Cisco IOS-XE YANG models may use different namespaces, paths, identities, and leaf names.

---

## Project Structure

```text
YANG-CLI-Exercises/
│
├── device-interface-config.yang
├── device-vlan-config.yang
├── device-routing-config.yang
├── device-ntp-config.yang
├── device-snmp-config.yang
│
└── README.md
```

---

# Exercise 1 – Interface Model

## 1. Original CLI

```text
device(config)# interface ethernet 1/1
device(config-if)# description Uplink-to-Core
device(config-if)# mtu 1500
device(config-if)# admin-status enable
device(config-if)# speed 1000
```

The CLI creates an Ethernet interface and configures its description, MTU, administrative status, and speed.

---

## 2. Modeling Decision

The configuration is modeled using:

* **Container:** `interfaces`
* **List:** `interface`
* **Key:** `name`
* **Leaf:** `name`
* **Leaf:** `description`
* **Leaf:** `mtu`
* **Leaf:** `admin-status`
* **Leaf:** `speed`

An interface is represented as a **list** because a device can contain multiple interfaces.

The interface `name` is used as the key because it uniquely identifies each interface.

### Leaf types

| Leaf           | Type          | Reason                     |
| -------------- | ------------- | -------------------------- |
| `name`         | `string`      | Interface identifier       |
| `description`  | `string`      | Free-form description      |
| `mtu`          | `uint16`      | Non-negative numeric value |
| `admin-status` | `enumeration` | Limited to named states    |
| `speed`        | `uint32`      | Numeric interface speed    |

---

## 3. YANG Code

File:

```text
device-interface-config.yang
```

```yang
module device-interface-config {

    namespace "http://example.com/device-interface-config";
    prefix "if";

    organization
        "Example Organization";

    description
        "YANG model for interface configuration.";

    container interfaces {

        list interface {

            key "name";

            leaf name {
                type string;
            }

            leaf description {
                type string;
            }

            leaf mtu {
                type uint16;
            }

            leaf admin-status {
                type enumeration {
                    enum enable;
                    enum disable;
                }
            }

            leaf speed {
                type uint32;
            }
        }
    }
}
```

---

## 4. Generated YANG Tree

Command:

```powershell
pyang -f tree device-interface-config.yang
```

Expected output:

```text
module: device-interface-config
  +--rw interfaces
     +--rw interface* [name]
        +--rw name             string
        +--rw description?     string
        +--rw mtu?             uint16
        +--rw admin-status?   enumeration
        +--rw speed?           uint32
```

The `*` after `interface` indicates that multiple interface entries can exist.

---

## 5. Expected NETCONF XML

```xml
<interfaces xmlns="http://example.com/device-interface-config">
    <interface>
        <name>ethernet 1/1</name>
        <description>Uplink-to-Core</description>
        <mtu>1500</mtu>
        <admin-status>enable</admin-status>
        <speed>1000</speed>
    </interface>
</interfaces>
```

This XML represents the same configuration as the original CLI commands.

---

## 6. Validation Result

The model was validated using `pyang`.

```powershell
pyang device-interface-config.yang
```

Result:

```text
No errors reported.
```

The tree representation was also generated successfully using:

```powershell
pyang -f tree device-interface-config.yang
```

---

# Exercise 2 – VLAN Model

## 1. Original CLI

```text
device(config)# vlan 100
device(config-vlan)# name IOT-SENSORS
device(config-vlan)# state active
```

This creates VLAN 100, assigns it a name, and sets its state to active.

---

## 2. Modeling Decision

The configuration is modeled using:

* **Container:** `vlans`
* **List:** `vlan`
* **Key:** `id`
* **Leaf:** `id`
* **Leaf:** `name`
* **Leaf:** `state`

A **list** is used because a device can contain many VLANs.

The VLAN ID is used as the key.

### Leaf types

| Leaf    | Type          | Reason                                 |
| ------- | ------------- | -------------------------------------- |
| `id`    | `uint16`      | VLAN ID is numeric                     |
| `name`  | `string`      | VLAN name is text                      |
| `state` | `enumeration` | Only defined states should be accepted |

---

## 3. YANG Code

File:

```text
device-vlan-config.yang
```

```yang
module device-vlan-config {

    namespace "http://example.com/device-vlan-config";
    prefix "vlan";

    organization
        "Example Organization";

    description
        "YANG model for VLAN configuration.";

    container vlans {

        list vlan {

            key "id";

            leaf id {
                type uint16;
            }

            leaf name {
                type string;
            }

            leaf state {
                type enumeration {
                    enum active;
                    enum suspended;
                }
            }
        }
    }
}
```

---

## 4. Generated YANG Tree

```powershell
pyang -f tree device-vlan-config.yang
```

Expected:

```text
module: device-vlan-config
  +--rw vlans
     +--rw vlan* [id]
        +--rw id       uint16
        +--rw name?    string
        +--rw state?   enumeration
```

---

## 5. Expected NETCONF XML

```xml
<vlans xmlns="http://example.com/device-vlan-config">
    <vlan>
        <id>100</id>
        <name>IOT-SENSORS</name>
        <state>active</state>
    </vlan>
</vlans>
```

---

## 6. Validation Result

```powershell
pyang device-vlan-config.yang
```

Result:

```text
No errors reported.
```

The YANG tree was also generated successfully.

---

# Exercise 3 – Static Route Model

## 1. Original CLI

```text
device(config)# ip route 192.168.20.0/24 10.0.0.1
```

This creates a static route to the `192.168.20.0/24` destination through the next-hop address `10.0.0.1`.

---

## 2. Modeling Decision

The configuration is modeled using:

* **Container:** `routing`
* **List:** `static-route`
* **Key:** `destination`
* **Leaf:** `destination`
* **Leaf:** `next-hop`

A list is used because a device can have multiple static routes.

The destination prefix is selected as the key because each route entry is identified by its destination.

### Leaf types

| Leaf          | Type              | Reason                                 |
| ------------- | ----------------- | -------------------------------------- |
| `destination` | `inet:ip-prefix`  | Represents an IPv4/IPv6 network prefix |
| `next-hop`    | `inet:ip-address` | Represents an IP address               |

The standard `ietf-inet-types` module is imported to provide these IP-related types.

---

## 3. YANG Code

File:

```text
device-routing-config.yang
```

```yang
module device-routing-config {

    namespace "http://example.com/device-routing-config";
    prefix "routing";

    import ietf-inet-types {
        prefix inet;
    }

    organization
        "Example Organization";

    description
        "YANG model for static routing configuration.";

    container routing {

        list static-route {

            key "destination";

            leaf destination {
                type inet:ip-prefix;
            }

            leaf next-hop {
                type inet:ip-address;
            }
        }
    }
}
```

---

## 4. Generated YANG Tree

```powershell
pyang -f tree device-routing-config.yang
```

Expected:

```text
module: device-routing-config
  +--rw routing
     +--rw static-route* [destination]
        +--rw destination    inet:ip-prefix
        +--rw next-hop?      inet:ip-address
```

---

## 5. Expected NETCONF XML

```xml
<routing xmlns="http://example.com/device-routing-config">
    <static-route>
        <destination>192.168.20.0/24</destination>
        <next-hop>10.0.0.1</next-hop>
    </static-route>
</routing>
```

---

## 6. Validation Result

```powershell
pyang device-routing-config.yang
```

Result:

```text
No errors reported.
```

The model successfully validates and the YANG tree can be generated.

---

# Exercise 4 – NTP Model

## 1. Original CLI

```text
device(config)# ntp server 192.168.1.10
device(config)# ntp source-interface ethernet 1/1
device(config)# ntp authenticate enable
```

This configuration specifies an NTP server, the source interface used for NTP traffic, and whether NTP authentication is enabled.

---

## 2. Modeling Decision

The structure specified in the exercise is:

* **Container:** `ntp`
* **Container:** `servers`
* **List:** `server`
* **Key:** `address`
* **Leaf:** `address`
* **Leaf:** `source-interface`
* **Leaf:** `authenticate`

A server is modeled as a list because a device can use multiple NTP servers.

The server IP address is used as the list key.

### Leaf types

| Leaf               | Type              | Reason                      |
| ------------------ | ----------------- | --------------------------- |
| `address`          | `inet:ip-address` | NTP server IP address       |
| `source-interface` | `string`          | Interface identifier        |
| `authenticate`     | `boolean`         | Represents enabled/disabled |

---

## 3. YANG Code

File:

```text
device-ntp-config.yang
```

```yang
module device-ntp-config {

    namespace "http://example.com/device-ntp-config";
    prefix "ntp";

    import ietf-inet-types {
        prefix inet;
    }

    organization
        "Example Organization";

    description
        "YANG model for NTP configuration.";

    container ntp {

        container servers {

            list server {

                key "address";

                leaf address {
                    type inet:ip-address;
                }
            }
        }

        leaf source-interface {
            type string;
        }

        leaf authenticate {
            type boolean;
        }
    }
}
```

---

## 4. Generated YANG Tree

```powershell
pyang -f tree device-ntp-config.yang
```

Expected:

```text
module: device-ntp-config
  +--rw ntp
     +--rw servers
     |  +--rw server* [address]
     |     +--rw address    inet:ip-address
     +--rw source-interface?   string
     +--rw authenticate?       boolean
```

---

## 5. Expected NETCONF XML

```xml
<ntp xmlns="http://example.com/device-ntp-config">

    <servers>
        <server>
            <address>192.168.1.10</address>
        </server>
    </servers>

    <source-interface>ethernet 1/1</source-interface>

    <authenticate>true</authenticate>

</ntp>
```

The CLI:

```text
ntp authenticate enable
```

is represented as:

```xml
<authenticate>true</authenticate>
```

---

## 6. Validation Result

```powershell
pyang device-ntp-config.yang
```

Result:

```text
No errors reported.
```

The model validates successfully.

---

# Exercise 5 – SNMP Model

## 1. Original CLI

```text
device(config)# snmp-server community iot-read ro
device(config)# snmp-server location Bangalore-Lab
```

This configuration creates an SNMP community called `iot-read` with read-only access and sets the device location.

---

## 2. Modeling Decision

The structure specified in the exercise is:

* **Container:** `snmp`
* **Container:** `communities`
* **List:** `community`
* **Key:** `name`
* **Leaf:** `name`
* **Leaf:** `access`
* **Leaf:** `location`

A list is used for communities because a device can have multiple SNMP community configurations.

The community name is used as the key.

The access level is modeled as an **enumeration**, because only predefined values such as `ro` and `rw` should be accepted.

### Leaf types

| Leaf       | Type          | Reason                              |
| ---------- | ------------- | ----------------------------------- |
| `name`     | `string`      | SNMP community name                 |
| `access`   | `enumeration` | Represents predefined access levels |
| `location` | `string`      | Device location                     |

---

## 3. YANG Code

File:

```text
device-snmp-config.yang
```

```yang
module device-snmp-config {

    namespace "http://example.com/device-snmp-config";
    prefix "snmp";

    organization
        "Example Organization";

    description
        "YANG model for SNMP configuration.";

    container snmp {

        container communities {

            list community {

                key "name";

                leaf name {
                    type string;
                }

                leaf access {
                    type enumeration {
                        enum ro;
                        enum rw;
                    }
                }
            }
        }

        leaf location {
            type string;
        }
    }
}
```

---

## 4. Generated YANG Tree

```powershell
pyang -f tree device-snmp-config.yang
```

Expected:

```text
module: device-snmp-config
  +--rw snmp
     +--rw communities
     |  +--rw community* [name]
     |     +--rw name       string
     |     +--rw access?    enumeration
     +--rw location?        string
```

---

## 5. Expected NETCONF XML

```xml
<snmp xmlns="http://example.com/device-snmp-config">

    <communities>
        <community>
            <name>iot-read</name>
            <access>ro</access>
        </community>
    </communities>

    <location>Bangalore-Lab</location>

</snmp>
```

---

## 6. Validation Result

```powershell
pyang device-snmp-config.yang
```

Result:

```text
No errors reported.
```

The model validates successfully and the YANG tree is generated correctly.

---

# Overall CLI-to-YANG Mapping

The five exercises demonstrate the following general pattern:

```text
CLI Configuration
       ↓
Identify configuration object
       ↓
Choose container
       ↓
Determine whether multiple instances are possible
       ↓
Create list if required
       ↓
Choose stable key
       ↓
Create typed leaves
       ↓
Validate with pyang
       ↓
Generate YANG tree
       ↓
Represent configuration as NETCONF XML
```

## Summary of the Five Models

| Exercise     | Container              | List           | Key           | Important Types              |
| ------------ | ---------------------- | -------------- | ------------- | ---------------------------- |
| Interface    | `interfaces`           | `interface`    | `name`        | string, uint16, enum, uint32 |
| VLAN         | `vlans`                | `vlan`         | `id`          | uint16, string, enum         |
| Static Route | `routing`              | `static-route` | `destination` | IP prefix, IP address        |
| NTP          | `ntp` / `servers`      | `server`       | `address`     | IP address, string, boolean  |
| SNMP         | `snmp` / `communities` | `community`    | `name`        | string, enumeration          |

---

# Key Concepts Learned

## 1. Container

A `container` groups related configuration data.

Example:

```yang
container interfaces {
    ...
}
```

---

## 2. List

A `list` is used when multiple instances of a configuration object can exist.

Example:

```yang
list interface {
    ...
}
```

A device can therefore have:

```text
interface ethernet 1/1
interface ethernet 1/2
interface ethernet 1/3
```

---

## 3. Key

A key uniquely identifies an entry in a YANG list.

Example:

```yang
list interface {
    key "name";
}
```

The resulting path can be represented as:

```text
/interfaces/interface[name='ethernet 1/1']
```

---

## 4. Leaf

A `leaf` represents an individual data value.

Example:

```yang
leaf mtu {
    type uint16;
}
```

---

## 5. Data Types

YANG provides different types for different kinds of data.

Examples:

```yang
type string;
type uint16;
type uint32;
type boolean;
type enumeration;
type inet:ip-address;
type inet:ip-prefix;
```

Choosing an appropriate type makes the model more precise and allows invalid values to be rejected.

---

# Validation Commands

Each model can be checked using `pyang`.

### Basic validation

```powershell
pyang device-interface-config.yang
```

### Generate tree

```powershell
pyang -f tree device-interface-config.yang
```

The same commands can be used for the other models:

```powershell
pyang device-vlan-config.yang
pyang device-routing-config.yang
pyang device-ntp-config.yang
pyang device-snmp-config.yang
```

---

# Final Understanding

These exercises demonstrate that **CLI syntax and YANG syntax are not a direct one-to-one conversion**.

The CLI is primarily designed for human interaction:

```text
interface ethernet 1/1
description Uplink-to-Core
mtu 1500
```

YANG represents the same configuration as a structured data tree:

```text
interfaces
└── interface[name="ethernet 1/1"]
    ├── description
    └── mtu
```

NETCONF can then use the YANG-defined structure to exchange configuration data using XML.

Therefore, the overall relationship is:

```text
CLI
 │
 │  represents configuration
 ↓
YANG
 │
 │  defines structured data model
 ↓
NETCONF XML
 │
 │  carries configuration data
 ↓
Network Device
```

> **Important:** The models in this project are simplified models created for learning and modeling practice. Production implementations should follow the YANG models and conventions already defined by the target platform or vendor.
