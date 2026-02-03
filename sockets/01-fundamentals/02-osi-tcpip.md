# OSI Model and TCP/IP Stack

## The OSI (Open Systems Interconnection) Model

The OSI model is a 7-layer conceptual framework that standardizes the functions of a telecommunication or computing system.

### The 7 Layers

1. **Physical Layer (Layer 1)**
   - Transmission of raw bits over physical medium
   - Hardware: cables, hubs, repeaters
   - Concerned with: voltage levels, pin layouts, cable types

2. **Data Link Layer (Layer 2)**
   - Error detection and correction
   - Framing: organizing bits into frames
   - Hardware: switches, bridges
   - Protocols: Ethernet, Wi-Fi (MAC addresses)

3. **Network Layer (Layer 3)**
   - Routing packets across networks
   - Logical addressing (IP addresses)
   - Hardware: routers
   - Protocols: IP, ICMP, ARP

4. **Transport Layer (Layer 4)**
   - End-to-end communication
   - Error recovery and flow control
   - **This is where sockets operate!**
   - Protocols: TCP, UDP

5. **Session Layer (Layer 5)**
   - Managing sessions between applications
   - Dialogue control and synchronization

6. **Presentation Layer (Layer 6)**
   - Data translation, encryption, compression
   - Ensures data format compatibility

7. **Application Layer (Layer 7)**
   - User interfaces and application services
   - Protocols: HTTP, FTP, SMTP, SSH

## TCP/IP Model (Internet Protocol Suite)

The TCP/IP model is a more practical, 4-layer model used on the Internet:

### The 4 Layers

1. **Link Layer (Network Interface)**
   - Combines OSI Physical and Data Link
   - Hardware and drivers
   - Protocols: Ethernet, Wi-Fi

2. **Internet Layer (Network Layer)**
   - Routing packets
   - Protocol: IP (Internet Protocol)
   - Addresses: IPv4 (192.168.12.1) (2^8)^4, IPv6

3. **Transport Layer**
   - End-to-end communication
   - **Sockets interface with this layer**
   - Protocols: TCP, UDP

4. **Application Layer**
   - Combines OSI Session, Presentation, and Application
   - User-facing protocols
   - Protocols: HTTP, FTP, DNS, SSH

## Mapping OSI to TCP/IP

```
OSI Model              TCP/IP Model
-------------------    -------------------
Application            |
Presentation       }   Application
Session            |
-------------------    -------------------
Transport              Transport
-------------------    -------------------
Network                Internet
-------------------    -------------------
Data Link          }   Link
Physical           }
```

## Why This Matters for Socket Programming

### Sockets Operate at Transport Layer

Sockets provide an interface to the **Transport Layer**, allowing applications to:
- Choose TCP (reliable, connection-oriented) or UDP (fast, connectionless)
- Specify source and destination ports
- Control connection behavior

### Understanding Layers Helps You:

1. **Debug Issues**
   - Network layer: routing problems
   - Transport layer: connection problems
   - Application layer: protocol problems

2. **Design Protocols**
   - Know what each layer handles
   - Decide where to implement features

3. **Optimize Performance**
   - Understand overhead at each layer
   - Choose appropriate protocols

## Key Protocols by Layer

### Transport Layer
- **TCP (Transmission Control Protocol)**
  - Reliable, connection-oriented
  - Guarantees delivery, ordering
  - Error checking and correction
  - Slower than UDP
  - Used for: web browsing, email, file transfer

- **UDP (User Datagram Protocol)**
  - Unreliable, connectionless
  - Fast, low overhead
  - No delivery guarantees
  - Used for: video streaming, gaming, DNS

### Internet Layer
- **IPv4**: 32-bit addresses (e.g., 192.168.1.1)
- **IPv6**: 128-bit addresses (e.g., 2001:0db8::1)
- **ICMP**: Error messages and diagnostics (ping uses this)

### Application Layer
- **HTTP/HTTPS**: Web browsing
- **FTP**: File transfer
- **SMTP**: Email sending
- **DNS**: Domain name resolution
- **SSH**: Secure remote access

## Data Encapsulation

As data moves down layers, each adds its header:

```
Application Data
    ↓
[Transport Header] + Application Data
    ↓
[IP Header] + [Transport Header] + Application Data
    ↓
[Ethernet Header] + [IP Header] + [Transport Header] + Application Data
```

This is called **encapsulation**. When receiving, headers are stripped as data moves up layers.

## Practical Example

When you visit a website:
1. **Application Layer**: Browser creates HTTP request
2. **Transport Layer**: TCP segments the data, adds port numbers
3. **Internet Layer**: IP adds source/destination IP addresses
4. **Link Layer**: Ethernet frames the packet for transmission

Sockets let your program interact with the Transport Layer directly!

---

**Key Takeaway**: Sockets interface with the Transport Layer (TCP/UDP), giving you control over how your application communicates over the network.

