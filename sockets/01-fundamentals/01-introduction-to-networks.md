# Introduction to Networks

## What is a Network?

A **network** is a collection of interconnected devices (computers, servers, routers, etc.) that can communicate with each other and share resources. Networks enable data exchange between devices regardless of their physical location.

## Key Concepts

### Network Types

1. **Local Area Network (LAN)**
   - Small geographic area (office, home)
   - High-speed connections
   - Examples: Ethernet, Wi-Fi

2. **Wide Area Network (WAN)**
   - Large geographic area
   - Connects multiple LANs
   - Example: The Internet

3. **Metropolitan Area Network (MAN)**
   - City-wide network
   - Connects multiple LANs in a city

### Network Components

- **Host/Node**: Any device connected to the network
- **Client**: Device requesting services
- **Server**: Device providing services
- **Router**: Device that forwards data packets between networks
- **Switch**: Device that connects devices on the same network

### Why Networks Matter for Socket Programming

Socket programming is about creating applications that communicate over networks. Understanding networks helps you:
- Design better communication protocols
- Troubleshoot connection issues
- Optimize performance
- Understand security implications

## Network Communication Models

### Client-Server Model
- **Server**: Waits for incoming connections, provides services
- **Client**: Initiates connections, requests services
- Most common model in socket programming
- Example: Web browser (client) connects to web server

### Peer-to-Peer (P2P) Model
- All nodes can act as both client and server
- No central server required
- Example: BitTorrent, blockchain networks

## Basic Network Terminology

- **Packet**: A unit of data transmitted over a network
- **Protocol**: Rules governing data transmission
- **IP Address**: Unique identifier for a device on a network
- **Port**: Number identifying a specific process/application
- **Socket**: Endpoint for sending/receiving data

## Next Steps

Understanding networks is foundational. In the next module, we'll explore the OSI model and TCP/IP stack, which provide the theoretical framework for network communication.

---

**Key Takeaway**: Networks enable devices to communicate. Sockets are the programming interface that lets applications use this network communication.

