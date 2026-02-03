# TCP/IP 4-Layer Model and WiFi PCI Driver Architecture

## Table of Contents
1. [Introduction](#introduction)
2. [TCP/IP 4-Layer Model Overview](#tcpip-4-layer-model-overview)
3. [Detailed Layer Analysis](#detailed-layer-analysis)
4. [WiFi PCI Driver Architecture](#wifi-pci-driver-architecture)
5. [How WiFi Drivers Interact with Network Layers](#how-wifi-drivers-interact-with-network-layers)
6. [Data Flow Examples](#data-flow-examples)
7. [Linux Kernel Code References](#linux-kernel-code-references)
8. [Summary](#summary)

---

## Introduction

This document provides a comprehensive explanation of the TCP/IP 4-layer model and describes how Linux WiFi PCI card drivers interact with each layer of the network stack. Understanding these layers is crucial for developing and debugging network device drivers.

**Key Concepts:**
- The TCP/IP model consists of 4 layers: Application, Transport, Internet, and Link
- WiFi drivers primarily operate at the Link/Network Access Layer
- Drivers act as an interface between the Linux networking stack and hardware
- The driver abstracts hardware complexity and provides a standardized interface

---

## TCP/IP 4-Layer Model Overview

The TCP/IP model (also called the Internet Protocol Suite) is a conceptual framework that standardizes how network protocols communicate. Unlike the 7-layer OSI model, TCP/IP uses a more practical 4-layer approach:

```
┌─────────────────────────────────────┐
│  Layer 4: Application Layer         │  ← User applications
├─────────────────────────────────────┤
│  Layer 3: Transport Layer           │  ← TCP/UDP
├─────────────────────────────────────┤
│  Layer 2: Internet/Network Layer    │  ← IP (IPv4/IPv6)
├─────────────────────────────────────┤
│  Layer 1: Link/Network Access Layer │  ← Ethernet/WiFi/PPP
└─────────────────────────────────────┘
```

---

## Detailed Layer Analysis

### Layer 4: Application Layer

**Purpose:** Provides services directly to user applications and handles application-specific protocols.

**Key Functions:**
- Application data formatting and encoding
- Protocol-specific processing (HTTP, FTP, SSH, etc.)
- Session management and application-level error handling
- User authentication and authorization

**Protocols:**
- **HTTP/HTTPS** - Web browsing
- **FTP** - File transfer
- **SSH** - Secure shell
- **SMTP/POP3/IMAP** - Email
- **DNS** - Domain name resolution
- **DHCP** - Dynamic IP configuration
- **SNMP** - Network management

**Data Unit:** Application messages or Protocol Data Units (PDU)

**Characteristics:**
- Runs in userspace (not in the kernel)
- Each application uses sockets to communicate with transport layer
- Applications are identified by port numbers assigned by transport layer
- Format depends on application protocol (HTML for HTTP, JSON for REST APIs, etc.)

**Example Flow:**
```
Browser → HTTP Request → Socket API → Transport Layer
```

---

### Layer 3: Transport Layer

**Purpose:** Provides end-to-end data delivery between applications on different hosts.

**Key Functions:**
- **Port Addressing:** Identifies specific applications (e.g., port 80 for HTTP, 22 for SSH)
- **Segmentation/Reassembly:** Breaks large messages into segments and reassembles them
- **Connection Management:** TCP establishes and maintains connections (3-way handshake)
- **Reliability:** TCP provides error detection, retransmission, and flow control
- **Congestion Control:** TCP adjusts transmission rate based on network conditions

**Protocols:**

#### TCP (Transmission Control Protocol)
- **Connection-oriented:** Establishes connection before data transfer
- **Reliable:** Guarantees delivery, ordering, and error correction
- **Flow Control:** Prevents sender from overwhelming receiver
- **Features:**
  - Sequence numbers for ordering
  - Acknowledgment mechanism
  - Retransmission of lost packets
  - Sliding window for flow control

#### UDP (User Datagram Protocol)
- **Connectionless:** No connection establishment required
- **Unreliable:** No guarantees about delivery or ordering
- **Low Overhead:** Minimal header, no connection state
- **Use Cases:** DNS queries, video streaming, real-time applications

**Data Unit:** 
- **TCP:** Segments
- **UDP:** Datagrams

**Header Fields:**
- Source port (16 bits)
- Destination port (16 bits)
- Sequence number (TCP)
- Acknowledgment number (TCP)
- Checksum (error detection)
- Flags (SYN, ACK, FIN, RST for TCP)

**Linux Kernel Location:**
- TCP: `net/ipv4/tcp.c`, `net/ipv4/tcp_input.c`, `net/ipv4/tcp_output.c`
- UDP: `net/ipv4/udp.c`

**Example:**
```
Application data (1000 bytes) 
→ Transport layer adds TCP header (20 bytes)
→ TCP segment (1020 bytes) sent to Internet layer
```

---

### Layer 2: Internet/Network Layer

**Purpose:** Routes packets across multiple networks to reach the destination host.

**Key Functions:**
- **Logical Addressing:** Assigns IP addresses to hosts (e.g., 192.168.1.100)
- **Routing:** Determines the best path through networks to reach destination
- **Packet Fragmentation:** Splits large packets to fit smaller network MTUs
- **Forwarding:** Moves packets between network interfaces
- **ICMP:** Provides control messages (ping, error reporting)

**Protocols:**

#### IP (Internet Protocol)
- **IPv4:** 32-bit addresses (4.3 billion addresses)
- **IPv6:** 128-bit addresses (virtually unlimited)
- **Connectionless:** Each packet routed independently
- **Best Effort:** No delivery guarantees (handled by transport layer)

**Additional Protocols:**
- **ICMP (Internet Control Message Protocol):** Error reporting, ping
- **ARP (Address Resolution Protocol):** Maps IP to MAC addresses
- **IGMP (Internet Group Management Protocol):** Multicast group management

**Data Unit:** Packets (or datagrams)

**IP Header Fields:**
- Version (IPv4/IPv6)
- Header length
- Type of Service (priority, QoS)
- Total length
- Identification (for fragmentation)
- Flags (fragmentation control)
- Fragment offset
- Time To Live (TTL) - prevents infinite loops
- Protocol (TCP=6, UDP=17, ICMP=1)
- Header checksum
- Source IP address (32 bits for IPv4)
- Destination IP address (32 bits for IPv4)
- Options (variable length)

**Routing Process:**
1. Check if destination is on local network (same subnet)
2. If local: Use ARP to find MAC address and send directly
3. If remote: Send to default gateway (router)
4. Router forwards packet toward destination using routing tables

**Linux Kernel Location:**
- IP implementation: `net/ipv4/ip_output.c`, `net/ipv4/ip_input.c`
- Routing: `net/ipv4/route.c`, `net/ipv4/fib_*.c`
- ARP: `net/ipv4/arp.c`

**Example:**
```
TCP segment (1020 bytes)
→ Internet layer adds IP header (20 bytes)
→ IP packet (1040 bytes) with source/dest IP addresses
→ Routing decision determines output interface
```

---

### Layer 1: Link/Network Access Layer

**Purpose:** Handles physical transmission of data over the local network medium.

**Key Functions:**
- **Physical Addressing:** MAC addresses (Media Access Control) - 48-bit hardware addresses
- **Framing:** Encapsulates network layer packets into frames with headers/trailers
- **Error Detection:** CRC (Cyclic Redundancy Check) or FCS (Frame Check Sequence)
- **Media Access Control:** 
  - CSMA/CD for Ethernet (Collision Detection)
  - CSMA/CA for WiFi (Collision Avoidance)
- **Flow Control:** Prevents frame loss at the physical layer

**Technologies:**
- **Ethernet (IEEE 802.3):** Wired networks
- **WiFi (IEEE 802.11):** Wireless networks
- **PPP:** Point-to-point connections
- **Token Ring:** Legacy technology
- **Bluetooth:** Short-range wireless

**Data Unit:** Frames

**Ethernet Frame Structure:**
```
┌─────────────────┬──────────┬──────────┬──────────┬─────┬──────────┐
│ Preamble        │ Dest MAC │ Src MAC  │ EtherType│Data │ CRC/FCS  │
│ (7 bytes)       │ (6 bytes)│ (6 bytes)│ (2 bytes)│     │ (4 bytes)│
└─────────────────┴──────────┴──────────┴──────────┴─────┴──────────┘
```

**WiFi (802.11) Frame Structure:**
```
┌──────────────┬──────────┬──────────┬──────────┬─────┬──────────┐
│ Frame Control│ Duration │ Dest MAC │ Src MAC  │Data │ FCS      │
│ (2 bytes)    │ (2 bytes)│ (6 bytes)│ (6 bytes)│     │ (4 bytes)│
└──────────────┴──────────┴──────────┴──────────┴─────┴──────────┘
```

**MAC Address Format:**
- 48 bits (6 bytes) written as: `XX:XX:XX:XX:XX:XX` (hexadecimal)
- Example: `00:1B:44:11:3A:B7`
- First 3 bytes: OUI (Organizationally Unique Identifier) - identifies manufacturer
- Last 3 bytes: Unique to device

**Linux Kernel Location:**
- Ethernet: `net/ethernet/eth.c`
- 802.11: `net/wireless/`, `net/mac80211/`
- Generic: `net/core/dev.c`, `net/core/skbuff.c`

**Example:**
```
IP packet (1040 bytes)
→ Link layer adds Ethernet header (14 bytes) and CRC (4 bytes)
→ Ethernet frame (1058 bytes) ready for transmission
→ Frame sent over physical medium (cable or radio waves)
```

---

## WiFi PCI Driver Architecture

### Complete Network Stack Architecture

```
┌──────────────────────────────────────────────────────────────────┐
│                    APPLICATION LAYER                             │
│  ┌──────────┐  ┌──────────┐  ┌──────────┐  ┌──────────┐        │
│  │ Browser  │  │ SSH      │  │ Email    │  │ Other    │        │
│  │ (HTTP)   │  │ Client   │  │ Client   │  │ Apps     │        │
│  └────┬─────┘  └────┬─────┘  └────┬─────┘  └────┬─────┘        │
│       │             │             │             │               │
│       └─────────────┴─────────────┴─────────────┘               │
│                            │                                     │
│                    Socket API (userspace)                        │
└────────────────────────────┼─────────────────────────────────────┘
                             │
                             ↓
┌──────────────────────────────────────────────────────────────────┐
│                    TRANSPORT LAYER                               │
│  ┌──────────────────────────────────────────────────────┐       │
│  │  Kernel: net/ipv4/tcp.c, net/ipv4/udp.c              │       │
│  │                                                       │       │
│  │  Functions:                                          │       │
│  │  - tcp_sendmsg() - Send TCP data                     │       │
│  │  - udp_sendmsg() - Send UDP data                     │       │
│  │  - Adds TCP/UDP headers (ports, sequence numbers)   │       │
│  └──────────────────────────────────────────────────────┘       │
└──────────────────────────────────────────────────────────────────┘
                             │
                             ↓
┌──────────────────────────────────────────────────────────────────┐
│                    INTERNET LAYER (IP)                          │
│  ┌──────────────────────────────────────────────────────┐       │
│  │  Kernel: net/ipv4/ip_output.c, net/ipv4/ip_input.c  │       │
│  │                                                       │       │
│  │  Functions:                                          │       │
│  │  - ip_queue_xmit() - Send IP packet                 │       │
│  │  - ip_route_output() - Route packet                 │       │
│  │  - ip_local_deliver() - Receive IP packet           │       │
│  │  - Adds IP headers (IP addresses, TTL, protocol)    │       │
│  └──────────────────────────────────────────────────────┘       │
└──────────────────────────────────────────────────────────────────┘
                             │
                             ↓
┌──────────────────────────────────────────────────────────────────┐
│                    LINK LAYER - Ethernet                        │
│  ┌──────────────────────────────────────────────────────┐       │
│  │  Kernel: net/ethernet/, net/core/dev.c               │       │
│  │                                                       │       │
│  │  Functions:                                          │       │
│  │  - eth_header() - Create Ethernet header            │       │
│  │  - dev_queue_xmit() - Queue packet for transmission │       │
│  │  - Adds Ethernet headers (MAC addresses)            │       │
│  └──────────────────────────────────────────────────────┘       │
└──────────────────────────────────────────────────────────────────┘
                             │
                             ↓
┌──────────────────────────────────────────────────────────────────┐
│                    IEEE 802.11 (WiFi) LAYER                     │
│  ┌──────────────────────────────────────────────────────┐       │
│  │  Kernel: net/wireless/, net/mac80211/                │       │
│  │                                                       │       │
│  │  Subsystem: mac80211                                 │       │
│  │  - Handles WiFi management (scan, connect, auth)    │       │
│  │  - 802.11 frame formatting                          │       │
│  │  - Encryption/decryption (WPA, WPA2)                │       │
│  │  - Rate control                                      │       │
│  │  - Power management                                  │       │
│  │                                                       │       │
│  │  Interface: struct ieee80211_ops                    │       │
│  │  - .tx() - Transmit 802.11 frames                   │       │
│  │  - .start() - Start device                          │       │
│  │  - .config() - Configure channel/power              │       │
│  └──────────────────────────────────────────────────────┘       │
└──────────────────────────────────────────────────────────────────┘
                             │
                             ↓
┌──────────────────────────────────────────────────────────────────┐
│                    WIFI DRIVER (rt2800pci)                      │
│  ┌──────────────────────────────────────────────────────┐       │
│  │  Location: drivers/net/wireless/ralink/rt2x00/      │       │
│  │                                                       │       │
│  │  Key Files:                                          │       │
│  │  - rt2800pci.c - PCI-specific driver code           │       │
│  │  - rt2x00mac.c - mac80211 interface                 │       │
│  │  - rt2x00dev.c - Device management                  │       │
│  │  - rt2x00queue.c - TX/RX queue handling             │       │
│  │                                                       │       │
│  │  Functions:                                          │       │
│  │  - rt2800pci_set_device_state() - Radio control     │       │
│  │  - rt2x00mac_tx() - Transmit frames                 │       │
│  │  - rt2800mmio_interrupt() - Handle interrupts       │       │
│  │  - PCI register access, DMA operations              │       │
│  └──────────────────────────────────────────────────────┘       │
└──────────────────────────────────────────────────────────────────┘
                             │
                             ↓
┌──────────────────────────────────────────────────────────────────┐
│                    PCI BUS & HARDWARE                           │
│  ┌──────────────────────────────────────────────────────┐       │
│  │  Physical PCIe WiFi Card                             │       │
│  │  - PCIe interface                                    │       │
│  │  - Radio hardware (2.4GHz/5GHz)                     │       │
│  │  - Baseband processor                                │       │
│  │  - MAC/PHY hardware                                  │       │
│  │  - DMA engines                                       │       │
│  │  - Interrupt generation                              │       │
│  └──────────────────────────────────────────────────────┘       │
└──────────────────────────────────────────────────────────────────┘
```

---

## How WiFi Drivers Interact with Network Layers

### Layer 1: Link/Network Access Layer (Primary Responsibility)

WiFi drivers have **full implementation** responsibility at the Link Layer:

#### 1. **IEEE 802.11 Frame Handling**

**Transmission:**
```c
// Driver receives 802.11 frames from mac80211
void rt2x00mac_tx(struct ieee80211_hw *hw,
                  struct ieee80211_tx_control *control,
                  struct sk_buff *skb)
{
    // skb contains complete 802.11 frame:
    // - Frame Control field
    // - Address fields (BSSID, source, destination)
    // - Sequence control
    // - Payload (encrypted if needed)
    
    // Driver responsibilities:
    // 1. Queue frame in hardware transmit queue
    // 2. Program hardware DMA descriptors
    // 3. Handle RTS/CTS if required
    // 4. Trigger hardware transmission
    // 5. Report transmission status back to mac80211
}
```

**Reception:**
```c
// Hardware interrupt indicates frame received
void rt2800mmio_interrupt(struct rt2x00_dev *rt2x00dev)
{
    // Driver responsibilities:
    // 1. Read frame from hardware DMA buffers
    // 2. Parse 802.11 frame headers
    // 3. Decrypt if hardware doesn't handle it
    // 4. Validate CRC/FCS
    // 5. Pass frame to mac80211 for processing
    rt2800mmio_rxdone_tasklet(...);
}
```

#### 2. **Physical Addressing (MAC Addresses)**

```c
// Driver reads/writes MAC address to hardware
int rt2x00lib_set_mac_address(struct rt2x00_dev *rt2x00dev, 
                               u8 *eeprom_mac_addr)
{
    // Read MAC address from EEPROM/OTP
    // Write to hardware registers
    // Configure hardware filters to accept frames for this MAC
}

// MAC address filtering
// Driver configures hardware to:
// - Accept frames destined for this device's MAC
// - Accept broadcast frames (FF:FF:FF:FF:FF:FF)
// - Accept multicast frames if subscribed
// - Accept promiscuous mode if enabled
```

#### 3. **Frame Formatting and Encapsulation**

The driver converts between different frame formats:

```
Linux sk_buff (generic network buffer)
    ↓
802.11 frame header (driver/mac80211 adds)
    ↓
Hardware TX descriptor + DMA buffer (driver formats)
    ↓
Hardware transmission over radio waves
```

**Key Operations:**
- Add/remove 802.11 frame headers
- Handle fragmentation (split large frames)
- Handle defragmentation (reassemble fragmented frames)
- Add hardware-specific headers (TX descriptors)

#### 4. **Error Detection and Correction**

```c
// Hardware validates CRC/FCS on reception
// Driver checks:
// - Frame Check Sequence (FCS) from hardware
// - Hardware-reported receive errors
// - Retry count for transmitted frames
// - Acknowledgment status
```

#### 5. **Media Access Control (CSMA/CA)**

WiFi uses **Carrier Sense Multiple Access with Collision Avoidance**:

- **DIFS (Distributed Interframe Space):** Wait before transmitting
- **Backoff Timer:** Random delay to avoid collisions
- **RTS/CTS:** Request-to-Send / Clear-to-Send handshake
- **NAV (Network Allocation Vector):** Virtual carrier sense

```c
// Driver may handle RTS/CTS in software
static int rt2x00mac_tx_rts_cts(struct rt2x00_dev *rt2x00dev,
                                struct data_queue *queue,
                                struct sk_buff *frag_skb)
{
    // Generate RTS or CTS frame
    // Queue it before data frame
    // Handle acknowledgment
}
```

#### 6. **Encryption/Decryption**

```c
// Driver configures hardware encryption keys
int rt2800_config_shared_key(struct rt2x00_dev *rt2x00dev,
                             struct rt2x00lib_crypto *crypto,
                             struct ieee80211_key_conf *key)
{
    // Configure WEP/WPA/WPA2 keys in hardware
    // Set encryption type (TKIP, AES-CCMP)
    // Enable hardware encryption engine
}

// If hardware doesn't support encryption:
// Driver performs encryption/decryption in software
```

---

### Integration with Higher Layers

#### Network Device Interface (`net_device`)

WiFi drivers create a `net_device` structure that provides an Ethernet-like interface:

```c
// Driver registers network device
struct net_device *dev = alloc_etherdev(sizeof(*vif));
dev->netdev_ops = &wifi_netdev_ops;

// Network device operations
static const struct net_device_ops wifi_netdev_ops = {
    .ndo_open = wifi_open,
    .ndo_stop = wifi_stop,
    .ndo_start_xmit = wifi_hard_start_xmit,  // Entry point from IP layer
    .ndo_set_mac_address = wifi_set_mac_address,
    .ndo_set_rx_mode = wifi_set_multicast_list,
    .ndo_get_stats = wifi_get_stats,
    .ndo_tx_timeout = wifi_tx_timeout,
};

register_netdev(dev);
```

**Key Functions:**

1. **`ndo_start_xmit()`** - Entry point from network layer
   ```c
   netdev_tx_t wifi_hard_start_xmit(struct sk_buff *skb,
                                    struct net_device *dev)
   {
       // Receives IP packet from network layer
       // Converts to 802.11 frame (via mac80211)
       // Queues for transmission
   }
   ```

2. **`ndo_open()`** - Initialize device when `ifconfig up`
   ```c
   int wifi_open(struct net_device *dev)
   {
       // Enable radio
       // Allocate DMA buffers
       // Register interrupt handlers
       // Start queues
   }
   ```

3. **`ndo_stop()`** - Shutdown device when `ifconfig down`
   ```c
   int wifi_stop(struct net_device *dev)
   {
       // Disable radio
       // Free DMA buffers
       // Stop queues
       // Unregister interrupts
   }
   ```

#### MAC80211 Subsystem Interface

The driver registers with the mac80211 subsystem using `ieee80211_ops`:

```c
// Driver registers with mac80211
struct ieee80211_hw *hw = ieee80211_alloc_hw(sizeof(*priv), &ops);

static const struct ieee80211_ops rt2800pci_ops = {
    // Core operations
    .tx = rt2x00mac_tx,                    // Transmit 802.11 frames
    .start = rt2x00mac_start,              // Start hardware
    .stop = rt2x00mac_stop,                // Stop hardware
    
    // Interface management
    .add_interface = rt2x00mac_add_interface,    // Create virtual interface
    .remove_interface = rt2x00mac_remove_interface,
    .config = rt2x00mac_config,                  // Configure channel/power
    
    // WiFi management
    .sw_scan_start = rt2x00mac_sw_scan_start,    // Start scanning
    .sw_scan_complete = rt2x00mac_sw_scan_complete,
    .bss_info_changed = rt2x00mac_bss_info_changed,
    
    // Security
    .set_key = rt2x00mac_set_key,                // Configure encryption keys
    
    // Rate control
    .get_tx_stats = rt2x00mac_get_tx_stats,
    .get_stats = rt2x00mac_get_stats,
    
    // Power management
    .ampdu_action = rt2800_ampdu_action,
};
```

**mac80211 Responsibilities:**
- Manages WiFi state machine (scanning, association, authentication)
- Handles 802.11 management frames (beacons, probe requests/responses)
- Manages virtual interfaces (AP, STA, monitor mode)
- Provides rate control algorithms
- Handles power save mode
- Manages encryption keys and algorithms

---

### Layer 2: Internet Layer (Minimal Involvement)

WiFi drivers do **NOT** implement IP directly, but they interact with the IP layer indirectly:

#### What Drivers See:
```c
// Driver receives sk_buff from network layer
// sk_buff contains:
struct sk_buff {
    // Network layer headers (already added)
    __be16 protocol;           // ETH_P_IP, ETH_P_ARP, etc.
    unsigned char *data;       // Points to IP packet + headers
    
    // Link layer information
    unsigned char *mac_header; // Ethernet header
    unsigned int len;          // Total packet length
};
```

#### Driver's Role:
1. **Receive IP packets** from network layer via `net_device`
2. **Pass to mac80211** for 802.11 encapsulation
3. **No IP processing** - driver treats IP as opaque payload
4. **May participate in offloading:**
   - TCP checksum offload
   - Segmentation offload (TSO - TCP Segmentation Offload)
   - Large Receive Offload (LRO)

#### IP Processing Flow:
```
IP Layer (net/ipv4/ip_output.c)
    ↓ ip_queue_xmit()
    ↓ Routing decision
    ↓ Output interface selected (wlan0)
    ↓ dev_queue_xmit() → net_device
    ↓ Driver's ndo_start_xmit()
    ↓ mac80211
    ↓ Driver
```

---

### Layer 3: Transport Layer (No Involvement)

WiFi drivers have **zero involvement** with transport layer:

- **Don't see** TCP/UDP headers
- **Don't process** port numbers
- **Don't handle** TCP connection state
- **Don't implement** TCP/UDP protocols

Transport layer data is **opaque payload** to the driver:

```
Application → "Hello World"
    ↓
TCP → Adds TCP header (port numbers, sequence numbers)
    ↓
IP → Adds IP header (IP addresses)
    ↓
Ethernet → Adds Ethernet header (MAC addresses)
    ↓
802.11 → Adds 802.11 header (WiFi addresses)
    ↓
Driver → Sees as opaque binary data, doesn't parse TCP/UDP
```

---

### Layer 4: Application Layer (No Involvement)

WiFi drivers have **no involvement** with application layer:
- Applications run in userspace
- Drivers run in kernel space
- No direct communication
- All interaction goes through network stack

---

## Data Flow Examples

### Example 1: Sending HTTP Request Over WiFi

**Scenario:** User opens a web browser and navigates to http://example.com

#### Step 1: Application Layer
```
Browser Application:
1. User types URL in browser
2. Browser resolves DNS to IP address (192.0.2.1)
3. Browser creates HTTP GET request:
   GET / HTTP/1.1
   Host: example.com
   ...
4. Browser calls socket API: send(socket_fd, http_request, len)
```

#### Step 2: Transport Layer (TCP)
```c
// Kernel: net/ipv4/tcp.c
tcp_sendmsg(socket, http_request)
{
    // Creates TCP segment
    // Adds TCP header:
    //   - Source port: 54321 (ephemeral)
    //   - Destination port: 80 (HTTP)
    //   - Sequence number: 1000
    //   - Flags: SYN (if new connection)
    //   - Checksum
    // 
    // Passes to IP layer
    ip_queue_xmit(skb);
}
```

**Data:** TCP segment with HTTP request as payload

#### Step 3: Internet Layer (IP)
```c
// Kernel: net/ipv4/ip_output.c
ip_queue_xmit(skb)
{
    // Adds IP header:
    //   - Source IP: 192.168.1.100 (local machine)
    //   - Destination IP: 192.0.2.1 (example.com)
    //   - Protocol: TCP (6)
    //   - TTL: 64
    //   - Header checksum
    
    // Routing decision
    route = ip_route_output_flow(...);
    // Determines output interface: wlan0
    
    // Passes to network device
    dev_queue_xmit(skb);
}
```

**Data:** IP packet containing TCP segment

#### Step 4: Link Layer (Ethernet)
```c
// Kernel: net/core/dev.c
dev_queue_xmit(skb)
{
    // Adds Ethernet header (if needed):
    //   - Destination MAC: Router's MAC or resolved via ARP
    //   - Source MAC: wlan0's MAC address
    //   - EtherType: 0x0800 (IPv4)
    
    // Queues for transmission
    qdisc_enqueue(skb);
    
    // Calls driver's transmit function
    ndev->netdev_ops->ndo_start_xmit(skb, ndev);
}
```

**Data:** Ethernet frame containing IP packet

#### Step 5: WiFi Layer (mac80211)
```c
// Kernel: net/mac80211/tx.c
ieee80211_subif_start_xmit(skb, dev)
{
    // Converts Ethernet frame to 802.11 frame
    // Adds 802.11 header:
    //   - Frame Control
    //   - Duration/ID
    //   - Address 1: BSSID (Access Point MAC)
    //   - Address 2: Source MAC (wlan0)
    //   - Address 3: Destination MAC (router)
    //   - Sequence Control
    
    // Encrypts if WPA/WPA2 enabled
    // Selects transmission rate
    // Calls driver's .tx() callback
    
    hw->ops->tx(hw, control, skb);
}
```

**Data:** 802.11 frame (encrypted if using WPA/WPA2)

#### Step 6: WiFi Driver (rt2800pci)
```c
// drivers/net/wireless/ralink/rt2x00/rt2x00mac.c
void rt2x00mac_tx(struct ieee80211_hw *hw,
                  struct ieee80211_tx_control *control,
                  struct sk_buff *skb)
{
    struct rt2x00_dev *rt2x00dev = hw->priv;
    
    // Get appropriate TX queue
    queue = rt2x00queue_get_tx_queue(rt2x00dev, qid);
    
    // Handle RTS/CTS if required
    if (needs_rts_cts) {
        rt2x00mac_tx_rts_cts(rt2x00dev, queue, skb);
    }
    
    // Write frame to hardware queue
    rt2x00queue_write_tx_frame(queue, skb, control->sta, false);
}

// drivers/net/wireless/ralink/rt2x00/rt2x00queue.c
int rt2x00queue_write_tx_frame(struct data_queue *queue,
                               struct sk_buff *skb,
                               struct ieee80211_sta *sta,
                               bool immediate)
{
    // Allocate DMA buffer
    // Copy 802.11 frame to DMA buffer
    // Program hardware TX descriptor:
    //   - DMA address
    //   - Frame length
    //   - Encryption settings
    //   - Rate information
    //   - Retry count
    // 
    // Trigger hardware transmission
    rt2x00queue_kick(queue);
    
    // Hardware transmits frame over 2.4GHz/5GHz radio
}
```

**Hardware Operations:**
1. DMA engine reads frame from memory
2. Baseband processor modulates signal
3. Radio transmits over selected channel (e.g., channel 6 at 2.437 GHz)
4. Waits for ACK from Access Point
5. Generates interrupt when transmission complete

#### Step 7: Physical Transmission
```
802.11 frame transmitted as radio waves:
- Frequency: 2.4 GHz or 5 GHz
- Modulation: OFDM, DSSS, etc.
- Power level: Controlled by driver
- Antenna: Physical antenna radiates signal
```

---

### Example 2: Receiving HTTP Response Over WiFi

#### Step 1: Physical Reception
```
Radio waves received by antenna:
- Signal demodulated by baseband processor
- Frame decoded and CRC checked
- Hardware generates interrupt
```

#### Step 2: WiFi Driver Interrupt Handler
```c
// drivers/net/wireless/ralink/rt2x00/rt2800mmio.c
irqreturn_t rt2800mmio_interrupt(int irq, void *dev_instance)
{
    struct rt2x00_dev *rt2x00dev = dev_instance;
    
    // Read interrupt status from hardware
    status = rt2x00mmio_register_read(rt2x00dev, INT_SOURCE_CSR);
    
    if (status & INT_SOURCE_CSR_RX_DONE) {
        // Frame received
        tasklet_schedule(&rt2x00dev->rxdone_tasklet);
    }
    
    if (status & INT_SOURCE_CSR_TX_DONE) {
        // Transmission complete
        tasklet_schedule(&rt2x00dev->txdone_tasklet);
    }
    
    return IRQ_HANDLED;
}
```

#### Step 3: Frame Reception Processing
```c
// drivers/net/wireless/ralink/rt2x00/rt2800mmio.c
void rt2800mmio_rxdone_tasklet(unsigned long data)
{
    // Read RX descriptor from hardware
    // Check for errors (CRC, decryption failures)
    // Read frame data from DMA buffer
    // Allocate sk_buff
    // Copy frame data to sk_buff
    // Parse 802.11 headers
    // Decrypt if needed (or hardware did it)
    // Validate frame
    // Pass to mac80211
    rt2x00lib_rxdone(entry);
}
```

#### Step 4: MAC80211 Processing
```c
// Kernel: net/mac80211/rx.c
void ieee80211_rx_irqsafe(struct ieee80211_hw *hw, struct sk_buff *skb)
{
    // Validate 802.11 frame
    // Remove 802.11 headers
    // Convert to Ethernet frame format
    // Handle management frames (beacons, etc.)
    // Update connection state
    // Pass to network layer
    ieee80211_deliver_skb(skb);
}
```

#### Step 5: Network Layer Processing
```c
// Kernel: net/core/dev.c
netif_receive_skb(skb)
{
    // Determine protocol (IP, ARP, etc.)
    // Remove Ethernet header
    // Pass to appropriate protocol handler
}

// Kernel: net/ipv4/ip_input.c
ip_local_deliver(skb)
{
    // Validate IP header
    // Check destination IP (matches local IP?)
    // Reassemble fragmented packets
    // Check IP protocol field
    // Pass to transport layer (TCP=6, UDP=17)
}
```

#### Step 6: Transport Layer Processing
```c
// Kernel: net/ipv4/tcp.c
tcp_v4_rcv(skb)
{
    // Validate TCP header
    // Find TCP socket based on source/dest IP and ports
    // Check sequence numbers
    // Send ACK if needed
    // Reassemble segments in order
    // Pass complete data to application
    tcp_queue_rcv_established(sk, skb);
}
```

#### Step 7: Application Layer
```c
// Kernel: net/socket.c
// Data queued to socket receive buffer
// Application's recv() call returns data
// Browser receives HTTP response:
//   HTTP/1.1 200 OK
//   Content-Type: text/html
//   ...
//   <html>...</html>
```

---

## Linux Kernel Code References

### WiFi Driver Code Locations

**Driver Implementation:**
- Main driver: `drivers/net/wireless/ralink/rt2x00/rt2800pci.c`
- MAC80211 interface: `drivers/net/wireless/ralink/rt2x00/rt2x00mac.c`
- Device management: `drivers/net/wireless/ralink/rt2x00/rt2x00dev.c`
- Queue handling: `drivers/net/wireless/ralink/rt2x00/rt2x00queue.c`
- PCI operations: `drivers/net/wireless/ralink/rt2x00/rt2x00pci.c`

**Key Functions:**

```c
// Radio control
rt2800pci_set_device_state()      // Set radio state (on/off/sleep)
rt2x00lib_enable_radio()          // Enable WiFi radio

// Frame transmission
rt2x00mac_tx()                     // Transmit 802.11 frames
rt2x00queue_write_tx_frame()      // Queue frame to hardware
rt2x00queue_kick()                 // Trigger hardware transmission

// Frame reception
rt2800mmio_interrupt()            // Interrupt handler
rt2800mmio_rxdone_tasklet()       // Process received frames
rt2x00lib_rxdone()                // Complete RX processing

// Configuration
rt2x00mac_config()                // Configure channel, power, etc.
rt2x00mac_add_interface()         // Create virtual interface
rt2x00mac_sw_scan_start()         // Start WiFi scanning
rt2x00mac_set_key()               // Configure encryption keys
```

### Network Stack Code Locations

**Transport Layer:**
- TCP: `net/ipv4/tcp.c`, `net/ipv4/tcp_input.c`, `net/ipv4/tcp_output.c`
- UDP: `net/ipv4/udp.c`
- Socket interface: `net/socket.c`

**Internet Layer:**
- IP output: `net/ipv4/ip_output.c`
- IP input: `net/ipv4/ip_input.c`
- Routing: `net/ipv4/route.c`, `net/ipv4/fib_*.c`
- ARP: `net/ipv4/arp.c`

**Link Layer:**
- Network device core: `net/core/dev.c`
- Ethernet: `net/ethernet/eth.c`
- Socket buffers: `net/core/skbuff.c`

**WiFi/MAC80211:**
- MAC80211 core: `net/mac80211/`
- Configuration: `net/wireless/`
- nl80211 (userspace API): `net/wireless/nl80211.c`

---

## Summary

### Layer Involvement Summary Table

| Layer | Driver Involvement | Details |
|-------|-------------------|---------|
| **Application** | **None** | Driver doesn't see application data. Applications run in userspace and communicate via sockets. |
| **Transport (TCP/UDP)** | **None** | Driver sees transport data as opaque payload. Doesn't process port numbers, sequence numbers, or connection state. |
| **Internet (IP)** | **Minimal** | Driver receives IP packets from network layer. May participate in offloading (checksum, TSO). Does not implement IP routing or processing. |
| **Link (802.11/Ethernet)** | **Full Implementation** | Driver's primary responsibility. Handles frame formatting, MAC addressing, encryption, media access control (CSMA/CA), error detection, hardware control. |

### Key Takeaways

1. **WiFi drivers operate primarily at the Link/Network Access Layer**
   - Implement IEEE 802.11 frame handling
   - Manage hardware radio and DMA operations
   - Handle encryption/decryption
   - Implement media access control

2. **Drivers provide abstraction**
   - Hide hardware complexity from upper layers
   - Present standard network device interface (`net_device`)
   - Integrate with mac80211 for WiFi management
   - Enable IP packets to be sent/received over WiFi

3. **Clear separation of concerns**
   - Upper layers (IP, TCP, applications) don't know about WiFi specifics
   - WiFi driver doesn't need to understand application protocols
   - Each layer focuses on its specific responsibilities

4. **Integration points**
   - `net_device` interface for network layer
   - `ieee80211_ops` interface for mac80211
   - PCI bus interface for hardware
   - Interrupt handlers for asynchronous events

### Driver Responsibilities Checklist

**Hardware Management:**
- [x] PCI device detection and initialization
- [x] Radio enable/disable
- [x] Power management (sleep, wake)
- [x] Register access
- [x] DMA buffer allocation and management

**Frame Processing:**
- [x] Transmit 802.11 frames to hardware
- [x] Receive 802.11 frames from hardware
- [x] Frame queuing and scheduling
- [x] Error handling and retry logic
- [x] RTS/CTS handling

**802.11 Features:**
- [x] Encryption/decryption configuration
- [x] Rate control support
- [x] Power save mode
- [x] Hardware filtering (MAC address, multicast)
- [x] Beacon handling (for AP mode)

**Network Stack Integration:**
- [x] Register `net_device`
- [x] Implement `net_device_ops`
- [x] Register with mac80211
- [x] Implement `ieee80211_ops`
- [x] Handle interrupts
- [x] Statistics collection

**What Drivers DON'T Do:**
- [ ] Parse IP headers
- [ ] Process TCP/UDP
- [ ] Route packets
- [ ] Understand application protocols
- [ ] Implement WiFi management state machine (handled by mac80211)

---

## Conclusion

WiFi PCI drivers are critical components that bridge the gap between the Linux networking stack and physical WiFi hardware. While they primarily operate at the Link/Network Access Layer, they integrate seamlessly with all layers above to enable transparent network communication. Understanding the TCP/IP model and how drivers fit into it is essential for effective driver development and debugging.

The layered architecture provides clear separation of concerns, allowing each component to focus on its specific responsibilities while working together to enable end-to-end network communication over wireless media.

---

## Additional Resources

- **Linux Wireless Documentation:** `Documentation/networking/`
- **MAC80211 Documentation:** `Documentation/driver-api/80211/`
- **WiFi Driver Development:** `Documentation/networking/device_drivers/wifi/`
- **Network Stack Internals:** `Documentation/networking/`
- **PCI Driver Development:** `Documentation/PCI/`

---

*Document Generated: 2024*
*Based on Linux Kernel Source Analysis*
