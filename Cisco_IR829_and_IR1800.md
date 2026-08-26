# Cisco Industrial Router Training Notes
## Cisco IR829 and Cisco IR1800 Series

**Purpose:** Structured study documentation for the Cisco industrial-router material covered during IoT training. The two platforms are documented separately so that their hardware, software, networking, industrial communication, and application-hosting concepts are not mixed together.

---

# PART 1 — CISCO IR829 INDUSTRIAL ROUTER

## 1. Introduction to the Cisco IR829

The **Cisco IR829 Industrial Integrated Services Router** is an industrial router designed to provide networking and secure connectivity in industrial environments.

Unlike a typical home or office router, an industrial router is designed to work with industrial equipment and remote industrial sites. It can connect devices such as PLCs, RTUs, industrial computers, meters, sensors, and other equipment to local or remote networks.

The IR829 can therefore be considered both a **router** and an **industrial IoT gateway**.

Its major roles include:

- Connecting industrial devices and networks
- Providing Ethernet connectivity
- Providing cellular/LTE connectivity
- Providing Wi-Fi connectivity
- Supporting serial/industrial communication
- Routing traffic between networks
- Providing network security
- Supporting VPN connectivity
- Supporting network segmentation
- Providing edge-computing/application-hosting capabilities
- Supporting industrial and SCADA connectivity

The important idea is that the IR829 is not simply a device that forwards packets. In an industrial IoT architecture, it can act as the communication point between industrial equipment, enterprise networks, remote sites, and cloud systems.

---

# 2. Why Industrial Routers Are Used

Industrial environments contain many different types of equipment, and these devices do not necessarily communicate using the same technology.

For example, an industrial site might contain:

- PLCs
- RTUs
- Energy meters
- Sensors
- Actuators
- Industrial PCs
- SCADA systems
- Cameras
- Remote monitoring systems

Different devices may use:

- Ethernet
- RS-232
- RS-485
- Wi-Fi
- Cellular/LTE
- Industrial protocols such as Modbus

The industrial router provides the networking infrastructure required to connect these devices and communicate with other networks.

A remote industrial site can therefore communicate with a central control room, data center, or cloud service even when the site itself has only local industrial equipment.

---

# 3. Main Applications of the IR829

The IR829 can be used in many industrial and remote-connectivity scenarios.

### Factory automation

Industrial machines, PLCs, controllers, and monitoring systems can communicate through the router.

### Remote monitoring

A remote machine or site can send operational information to a central monitoring system.

### Energy and utilities

Meters and other equipment can be connected to remote monitoring or control systems.

### Transportation

Industrial networking can be provided for equipment used in transportation infrastructure.

### SCADA

The router can provide secure WAN connectivity for remote SCADA-related equipment.

### Remote industrial sites

Cellular connectivity allows sites without convenient wired WAN connectivity to communicate with remote systems.

### Edge computing

Applications can process information closer to the industrial equipment instead of sending every piece of data to a remote cloud first.

---

# 4. Ethernet Connectivity

Ethernet is one of the most common interfaces used to connect industrial equipment.

Devices that may use Ethernet include:

- PLCs
- Industrial PCs
- Ethernet-enabled sensors
- Industrial switches
- Cameras
- Servers
- Controllers

For example, a PLC may communicate with the IR829 through Ethernet, while the IR829 communicates with a remote server through a WAN connection.

Ethernet provides the physical/networking path, while higher-level protocols determine how application data is exchanged.

It is important to distinguish:

> Ethernet is a networking technology. It is not itself the industrial application protocol.

---

# 5. Cellular and LTE Connectivity

One of the important capabilities of an industrial router is cellular connectivity.

A remote industrial site may not have a convenient wired WAN connection. In such a situation, the router can use a cellular network to reach a remote network or cloud service.

The general concept is:

**Industrial equipment → IR829 → Cellular network → WAN/Internet → Remote system**

Important cellular concepts include:

- SIM
- Cellular modem
- Mobile network
- Carrier
- APN
- Network registration
- Signal strength
- IP connectivity
- WAN routing

The exact configuration depends on the cellular provider and deployment.

Cellular connectivity can also be useful as a backup WAN path when a primary wired connection fails.

---

# 6. Wi-Fi

The IR829 can also provide Wi-Fi connectivity for supported industrial devices.

Wi-Fi can be useful when wiring every device is inconvenient or when wireless connectivity is required at an industrial site.

Possible devices include:

- Wireless sensors
- Industrial tablets
- Maintenance devices
- Wireless controllers
- Other supported IoT equipment

Wi-Fi provides the local wireless network connection. The router then provides the appropriate network path to other networks.

---

# 7. Serial Connectivity

Industrial systems frequently contain legacy and modern serial equipment.

Two important serial standards are:

- RS-232
- RS-485

These should not be confused with protocols such as Modbus.

### RS-232

RS-232 is a serial electrical/interface standard commonly used for point-to-point communication.

### RS-485

RS-485 is a differential serial electrical standard commonly used in industrial environments.

It supports communication over longer distances and can support multiple devices on a bus depending on the implementation.

The important distinction is:

**RS-232/RS-485 describe the physical/electrical communication layer, while a protocol such as Modbus defines how data is exchanged.**

---

# 8. Industrial Protocols

Industrial devices need communication protocols to exchange meaningful data.

Examples include:

- Modbus
- Modbus RTU
- Modbus TCP
- DNP3
- Other vendor-specific or industrial protocols

The router provides connectivity, while protocol-aware applications or systems may communicate with the industrial devices.

A common example is:

**Modbus RTU over RS-485**

Here:

- RS-485 provides the physical communication method.
- Modbus RTU defines the data-exchange protocol.

Another example is:

**Modbus TCP over Ethernet**

Here:

- Ethernet/IP networking provides the network path.
- TCP provides transport.
- Modbus TCP defines the application-level communication.

---

# 9. Modbus RTU

Modbus RTU is a widely used industrial communication protocol.

A device such as an energy meter may expose measurements through Modbus registers.

The application sends a request to the device and receives a response containing the requested data.

Typical parameters may include:

- Device/slave address
- Baud rate
- Data bits
- Parity
- Stop bits
- Register address
- Function code
- CRC

For communication to work, the communicating devices must use compatible settings.

---

# 10. Modbus TCP

Modbus TCP is the TCP/IP version of Modbus communication.

It allows industrial data to be exchanged over an IP network, commonly using Ethernet.

The conceptual protocol stack is:

- Application: Modbus TCP
- Transport: TCP
- Network: IP
- Network access: Ethernet or another IP-capable interface

This makes Modbus TCP different from Modbus RTU, which is commonly associated with serial communication such as RS-485.

---

# 11. Registers and Industrial Data

Industrial devices often expose measurements through registers.

For example, an energy meter might have a register representing voltage.

Suppose a device manual says:

**Register 100 = Voltage, scaling factor = 0.1**

If the device returns:

**2305**

the application interprets it as:

**2305 × 0.1 = 230.5 V**

Another register might contain current:

**52 × 0.1 = 5.2 A**

The exact register addresses, data types, byte order, and scaling factors are device-specific.

Therefore, the device's register map/documentation must always be checked.

---

# 12. Polling

Polling means repeatedly requesting information from a device.

For example, an application might request an energy meter's voltage every five seconds.

The sequence is:

1. Application sends a request.
2. Device receives the request.
3. Device returns the requested value.
4. Application processes the value.
5. After the configured interval, the application requests the value again.

Polling is common in industrial monitoring systems.

The polling interval must be chosen according to the application's requirements and the device/network capabilities.

---

# 13. SCADA

**SCADA** stands for **Supervisory Control and Data Acquisition**.

SCADA systems are used to monitor and supervise industrial processes.

A typical system may include:

- Sensors
- PLCs
- RTUs
- Communication networks
- SCADA servers
- Operator stations
- HMIs
- Alarms
- Historical data systems

The IR829 can provide network connectivity between remote industrial equipment and centralized SCADA systems.

For example, a remote pumping station may have sensors and an RTU. The IR829 can provide the WAN/cellular connection through which the remote site communicates with a central monitoring system.

The router is therefore part of the communication infrastructure surrounding SCADA; it is not itself the complete SCADA system.

---

# 14. Routing

Routing is the process of determining where IP packets should be sent.

An industrial router may connect multiple networks, such as:

- Industrial LAN
- Management network
- WAN
- Cellular network
- Remote networks

The router uses its routing information to determine the next hop for packets.

Important routing concepts include:

- IP addresses
- Subnet masks/prefixes
- Default gateway
- Routing table
- Static routes
- Dynamic routing
- Next hop
- WAN interfaces

---

# 15. NAT

**NAT** stands for **Network Address Translation**.

NAT translates IP addressing between network environments.

A common scenario is an internal industrial network using private addresses while communicating through a WAN connection.

NAT is a networking function and should not be confused with routing. Routing determines where traffic goes; NAT modifies address information as traffic crosses a translation boundary.

---

# 16. VLAN

A **VLAN**, or Virtual Local Area Network, provides logical separation of networks.

For example, an industrial environment may separate:

- Industrial control traffic
- Management traffic
- Office traffic
- Guest traffic

This provides organizational and security benefits.

VLANs are a Layer 2 networking concept, while routing between different IP networks is a Layer 3 function.

---

# 17. VPN

A **VPN**, or Virtual Private Network, provides a protected communication tunnel across an untrusted or shared network.

A common industrial use is connecting a remote industrial site to a central network securely.

Important VPN concepts include:

- Tunnel
- Encryption
- Authentication
- Key exchange
- IPsec
- Secure remote connectivity

A VPN helps protect data while it travels across networks that are not fully trusted.

---

# 18. Firewall and ACL

Industrial systems must restrict unauthorized network traffic.

A firewall controls traffic according to security policies.

An ACL, or Access Control List, can permit or deny traffic according to criteria such as:

- Source address
- Destination address
- Protocol
- Port

For example, an industrial network may allow only required traffic from a monitoring server and deny unnecessary connections.

Security should be designed so that industrial devices are not unnecessarily exposed to external networks.

---

# 19. Network Segmentation

Network segmentation separates systems into logical or physical security zones.

For example:

- Corporate/office network
- Industrial network
- Management network
- External/WAN network

The goal is to reduce unnecessary communication between systems and limit the effect of a security incident.

In industrial environments, segmentation is especially important because PLCs, controllers, and other operational technology can be safety- or production-critical.

---

# 20. QoS

**QoS** means **Quality of Service**.

QoS allows network traffic to be classified and treated according to priority.

For example, a network may carry:

- Critical industrial traffic
- Voice/video
- Monitoring data
- General business traffic
- Background transfers

When bandwidth is limited, QoS can help ensure that important traffic receives appropriate treatment.

---

# 21. Edge Computing

Edge computing means performing processing closer to where data is generated rather than sending all raw data to a remote cloud.

Without edge processing:

**Device → Network → Cloud → Processing**

With edge processing:

**Device → Local/Edge Application → Processing → Cloud**

For example, suppose an industrial machine generates thousands of readings.

An edge application could:

- Collect the readings
- Filter unnecessary values
- Calculate statistics
- Detect abnormal conditions
- Generate alarms
- Send only relevant information to the cloud

This can reduce bandwidth usage and latency and allow some decisions to be made locally.

---

# 22. Application Hosting and IOx on the IR829

The IR829 supports Cisco's edge application-hosting capabilities through IOx.

The important concept is that the router can perform its normal networking functions while an application-hosting environment provides a place for edge applications to execute.

An edge application might:

- Collect device data
- Process sensor data
- Perform local analytics
- Communicate with an MQTT broker
- Transform protocols/data
- Generate local alerts

This is what makes the device useful as an IoT edge platform rather than only as a network router.

---

# 23. IR829 Virtualization Architecture

The IR829 training material includes a virtualization architecture involving a hypervisor.

Conceptually, the platform can be understood as having physical hardware underneath a virtualization layer, with separate software environments for networking and application/edge workloads.

The important components to understand are:

### Hardware

The physical router hardware provides processing, memory, storage, network interfaces, and other platform resources.

### Hypervisor

The hypervisor provides the virtualization layer and manages virtual machine environments and their access to physical resources.

### IOS environment

The networking environment provides router functions such as routing, interfaces, security, and WAN connectivity.

### Linux/IOx environment

The application side provides the environment required for supported edge applications.

The simplified conceptual representation is:

**IR829 hardware → Hypervisor → networking environment + Linux/IOx environment → edge applications**

This is the architecture that should be associated specifically with the IR829 material.

---

# 24. Virtual Machine

A virtual machine is an isolated software representation of a computer.

A traditional VM can be represented as:

**Physical hardware → Hypervisor → Virtual machine → Guest operating system → Application**

The guest operating system has its own operating-system environment.

A hypervisor manages the virtual machines and their access to physical resources.

---

# 25. Container

A container is a different type of application isolation mechanism.

Conceptually:

**Host environment → Container runtime/application framework → Container → Application**

A container packages an application and its dependencies without requiring a complete guest operating system in the same way a traditional VM does.

Containers are generally lighter than full virtual machines.

This distinction becomes particularly important when studying the IR1800 application-hosting architecture.

---

# 26. MQTT

**MQTT** is a lightweight publish/subscribe messaging protocol commonly used in IoT systems.

MQTT uses a broker.

A publisher sends a message to a topic, and subscribers receive messages for topics to which they are subscribed.

For example:

**Topic:** `factory/meter01/electrical`

**Payload:**

```json
{
  "voltage": 230.5,
  "current": 5.2,
  "power": 1198
}
```

MQTT is useful for IoT because it is lightweight and supports loosely coupled communication between devices/applications and backend systems.

---

# 27. HTTP and REST

IoT applications may also communicate with servers using HTTP/HTTPS.

A common pattern is:

**Application → HTTP/HTTPS request → REST API → Server**

JSON is commonly used as the data format.

For example:

```json
{
  "device": "meter01",
  "temperature": 31.4
}
```

MQTT and HTTP solve different communication requirements. MQTT is commonly useful for publish/subscribe IoT messaging, while HTTP/REST is commonly used for request/response APIs.

---

# 28. Data Processing at the Edge

An industrial application may receive raw values and convert them into useful information.

For example:

1. Read a register.
2. Interpret the raw data type.
3. Apply scaling.
4. Check whether the value is valid.
5. Add device identification and timestamp.
6. Create a structured data object.
7. Publish or transmit the data.

A simplified Python-style example is:

```python
raw_value = read_register(100)

voltage = raw_value * 0.1

data = {
    "device": "meter01",
    "voltage": voltage
}
```

This is only a conceptual example. Actual code depends on the industrial device, communication protocol, library, and application requirements.

---

# 29. Security in Industrial IoT

Security is particularly important because industrial systems can control or monitor physical processes.

Security should protect:

- Industrial devices
- Network infrastructure
- Application software
- Credentials
- Data
- Remote access
- Cloud communication

Important concepts include:

- Authentication
- Authorization
- Encryption
- VPN
- Firewall
- ACLs
- Network segmentation
- Secure management
- Secure application communication

The goal is not only to protect data but also to prevent unauthorized access to industrial operations.

---

# 30. IR829: Important Points to Remember

The most important points from the IR829 training are:

1. The IR829 is an industrial router and IoT gateway.
2. It is designed for industrial and remote networking environments.
3. It supports multiple forms of connectivity such as Ethernet, cellular/LTE, Wi-Fi, and industrial/serial connectivity.
4. It can connect industrial equipment to remote networks and systems.
5. It can be involved in SCADA communication and remote monitoring architectures.
6. Routing determines how IP traffic moves between networks.
7. NAT translates addressing between network environments.
8. VLANs provide logical network separation.
9. VPNs provide protected remote communication.
10. Firewalls and ACLs control permitted network traffic.
11. QoS can prioritize important traffic.
12. RS-232 and RS-485 are physical/electrical communication standards.
13. Modbus is an industrial communication protocol.
14. Modbus RTU commonly operates over serial links such as RS-485.
15. Modbus TCP operates over TCP/IP networks.
16. Industrial devices often expose measurements through registers.
17. Edge computing allows processing closer to the industrial device.
18. IOx provides an application-hosting/edge environment on supported Cisco platforms.
19. The IR829 material includes a hypervisor-based virtualization architecture.
20. The IR829 should therefore be understood as both a networking platform and an edge/IoT platform.

---

# PART 2 — CISCO IR1800 SERIES

# 31. Introduction to the IR1800 Series

The **Cisco Catalyst IR1800 Rugged Series** is a family of rugged industrial routers designed for industrial networking, IoT connectivity, and edge computing.

The family contains multiple models rather than one single hardware configuration.

Examples include:

- IR1821
- IR1831
- IR1833
- IR1835

The exact features and interfaces depend on the model.

Therefore, it is important to distinguish between:

**IR1800 series** — the overall product family

and

**IR1833 / IR1835** — specific models within the family.

---

# 32. Why There Are Multiple IR1800 Models

Different industrial deployments have different requirements.

One site may need:

- More memory
- More cellular connectivity
- More serial interfaces
- Digital I/O
- Different storage requirements
- Different expansion options

Cisco therefore provides different models with different hardware capabilities.

When working with an actual project, the exact model must be identified before configuring or programming against a hardware-specific feature.

---

# 33. IR1800 Hardware

Depending on the model and configuration, the IR1800 family provides combinations of:

- Gigabit Ethernet
- Cellular connectivity
- Wi-Fi
- Serial interfaces
- PoE/PoE+
- SSD/storage
- GNSS
- CAN
- Digital I/O
- Expansion/module capabilities

Not every model provides every feature.

This means that statements about a particular interface should always be associated with the exact IR1800 model.

---

# 34. IR1833 and IR1835

IR1833 and IR1835 are two specific IR1800 models.

They share the general IR1800 platform concept but differ in hardware resources and capabilities.

For example, the IR1835 provides digital I/O capability that is not provided in the same way on the IR1833.

The models also differ in resources such as memory and supported interface combinations.

Therefore, for training purposes:

**IR1800 = family**

**IR1833 = one hardware configuration**

**IR1835 = another hardware configuration**

Do not memorize the entire family as though every model has identical hardware.

---

# 35. IOS-XE

A major software concept associated with the IR1800 is **Cisco IOS-XE**.

IOS-XE is Cisco's modern operating-system architecture used across many Cisco networking platforms.

For the IR1800, IOS-XE provides the networking and platform-management environment.

Relevant functions include:

- Interface configuration
- IP networking
- Routing
- Security
- VPN
- QoS
- WAN connectivity
- Network management
- System monitoring

The important point is that IOS-XE is the primary networking software environment of the IR1800.

---

# 36. IR1800 Networking

The fundamental networking concepts learned from the IR829 remain relevant to the IR1800.

These include:

- Ethernet
- Cellular/LTE
- Wi-Fi
- Serial communication
- IP addressing
- Routing
- NAT
- VLAN
- VPN
- Firewall
- ACL
- QoS
- WAN connectivity

However, the exact commands, hardware interfaces, modules, and platform-specific configuration must be learned from the IR1800 documentation.

---

# 37. Industrial Connectivity on the IR1800

The IR1800 is intended to connect industrial equipment to networks and edge applications.

Examples of connected equipment include:

- PLCs
- RTUs
- Sensors
- Energy meters
- Industrial computers
- Controllers
- Cameras
- Other industrial Ethernet/serial devices

Depending on the model and deployment, communication can occur through:

- Ethernet
- Serial
- Wi-Fi
- Cellular
- Other supported interfaces

---

# 38. IR1800 and SCADA

The IR1800 can form part of an industrial SCADA communication architecture.

For example, a remote industrial installation may contain:

- Sensors
- PLCs
- RTUs
- SCADA-related equipment

The IR1800 provides networking connectivity between the remote site and a central system.

The router is therefore part of the communication infrastructure rather than being the SCADA application itself.

---

# 39. Security on the IR1800

The IR1800 supports the same broad security concepts that are important for industrial networking.

These include:

- VPN
- Firewall
- ACLs
- Authentication
- Encryption
- Network segmentation
- Secure management
- Secure communication

Security is particularly important in industrial environments because unauthorized access can affect physical equipment and production processes.

---

# 40. Edge Computing on the IR1800

The IR1800 can support edge application workloads.

The basic idea is that processing can occur close to the industrial equipment.

For example:

**Industrial sensor → IR1800 → local processing → important result → cloud**

Instead of:

**Industrial sensor → IR1800 → cloud → processing**

Edge processing can reduce latency and unnecessary data transmission.

---

# 41. Application Hosting on the IR1800

The IR1800 supports application hosting for edge workloads.

This allows software applications to run on the industrial platform rather than requiring all processing to happen on an external server.

Applications may perform:

- Data collection
- Data processing
- Local analytics
- Protocol handling
- Filtering
- Local monitoring
- IoT communication
- Cloud communication

This is one of the key reasons the IR1800 is relevant to IoT and edge-computing applications.

---

# 42. IOx on the IR1800

IOx remains an important Cisco edge-application concept.

However, the architecture must not simply be copied from the IR829.

For the IR1800, Cisco's application-hosting architecture uses the platform's IOS-XE environment and application-hosting framework, with supported applications running in containers.

The important conceptual relationship is:

**IR1800 → IOS-XE → application hosting/IOx → containers → edge applications**

This should be remembered as an IR1800 application-hosting concept.

---

# 43. Cisco Application Framework

The application-hosting environment includes Cisco's application framework for managing edge applications.

Its purpose is to provide the mechanisms required to:

- Deploy applications
- Start applications
- Stop applications
- Manage applications
- Provide application resources
- Monitor application status

The exact commands and deployment process are platform/software-version specific.

---

# 44. Containers on the IR1800

The IR1800 application-hosting environment supports containerized applications.

A container packages an application and its required dependencies.

Conceptually, the application-hosting environment provides the infrastructure in which the container runs.

A containerized edge application might contain:

- Python application code
- Required Python libraries
- Configuration
- Application dependencies

The application can then perform local IoT processing.

---

# 45. Why Containers Are Useful for Edge Applications

Containers can make application deployment more consistent because the application and its dependencies can be packaged together.

For example, instead of installing many application dependencies manually on the router, an application can be packaged into an appropriate container image.

This helps with:

- Application isolation
- Dependency management
- Repeatable deployment
- Application portability
- Easier lifecycle management

The exact supported image format, architecture, and resource requirements must be checked for the target IR1800 platform/software release.

---

# 46. IR1800 Application Architecture

The simplified architecture to remember is:

**Physical IR1800 hardware**

→ **IOS-XE**

→ **Application hosting / IOx framework**

→ **Containerized application**

→ **IoT/edge workload**

The application and networking environment work together, but they should not be treated as one piece of software.

IOS-XE provides the main networking/platform environment, while the application-hosting environment provides a way to run supported edge applications.

---

# 47. IR1800 and Industrial Data

The IR1800 can participate in the same type of industrial data architecture described earlier.

For example:

An energy meter may communicate using Modbus RTU over RS-485.

An application can collect the meter's register values, interpret the raw values, process them, and then send the resulting information to a remote system.

The exact implementation depends on the hardware interface, protocol, application, and project requirements.

---

# 48. Modbus and the IR1800

The same Modbus concepts remain relevant:

### Modbus RTU

Commonly associated with serial communication such as RS-485.

### Modbus TCP

Runs over TCP/IP networking, commonly using Ethernet.

### Registers

Contain or expose device information.

### Function codes

Specify operations such as reading or writing supported data.

### Device address

Identifies the device in applicable Modbus configurations.

### CRC

Used for error detection in Modbus RTU frames.

The router/platform does not automatically make every industrial protocol available. The actual protocol communication depends on the supported interfaces and software/application being used.

---

# 49. MQTT and the IR1800

An edge application running on the IR1800 can use IoT communication protocols such as MQTT where supported by the application and deployment.

A typical use case is:

1. Application collects industrial data.
2. Application processes the data.
3. Application creates a structured message.
4. Application connects to an MQTT broker.
5. Application publishes data to a topic.
6. A backend application subscribes to the topic.

Example:

**Topic:** `factory/machine01/status`

**Payload:**

```json
{
  "temperature": 31.4,
  "status": "normal"
}
```

MQTT is therefore an application-level communication mechanism rather than a replacement for Ethernet, LTE, or IP networking.

---

# 50. HTTP/HTTPS and the IR1800

An edge application can also communicate with remote services through HTTP/HTTPS.

A typical architecture is:

**Edge application → HTTPS request → REST API → Remote server**

JSON is commonly used to represent structured data.

HTTPS is important when secure web/API communication is required.

Again, the application determines how the communication is implemented.

---

# 51. IR1800 Architecture vs IR829 Architecture

This is the most important distinction between the two platforms.

## IR829

The IR829 training material includes a hypervisor-based architecture.

Conceptually:

**IR829 hardware → hypervisor → separate software environments → IOx/application environment**

The hypervisor manages virtual machine environments.

## IR1800

The IR1800 uses a different modern architecture.

Conceptually:

**IR1800 hardware → IOS-XE → application hosting/IOx → containers → applications**

Therefore, the older IR829 hypervisor architecture should not be presented as the IR1800 architecture.

