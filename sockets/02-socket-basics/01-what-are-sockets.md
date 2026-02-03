# What are Sockets?

## Definition

A **socket** is an endpoint for communication between two programs running on a network. It's a software abstraction that provides an interface between an application and the network protocol stack (TCP/IP).

Think of a socket as a telephone: it allows your program to "call" another program or "receive calls" from other programs.

## Key Concepts

### Socket = IP Address + Port

A socket is uniquely identified by:
- **IP Address**: Identifies the machine
- **Port Number**: Identifies the application/process
- **Protocol**: TCP or UDP

Together: `IP:PORT` (e.g., `192.168.1.100:8080`)

### Socket Analogy

Imagine a building (server):
- **IP Address**: The building's street address
- **Port**: The apartment/room number
- **Socket**: The door to that room

Clients "knock" on the door (connect to the socket) to communicate.

## Socket Types

### 1. Stream Sockets (TCP)

- **Protocol**: TCP
- **Characteristics**:
  - Connection-oriented (must establish connection first)
  - Reliable (guaranteed delivery)
  - Ordered (data arrives in order)
  - Two-way communication (full-duplex)
  - Byte stream (continuous flow)

- **Use cases**: Web servers, databases, file transfer

### 2. Datagram Sockets (UDP)

- **Protocol**: UDP
- **Characteristics**:
  - Connectionless (no connection needed)
  - Unreliable (no delivery guarantee)
  - Not ordered (may arrive out of order)
  - Faster (less overhead)
  - Message-based (discrete packets)

- **Use cases**: Gaming, streaming, DNS

### 3. Raw Sockets

- **Protocol**: Direct IP access
- **Characteristics**: Bypass transport layer
- **Use cases**: Network tools, custom protocols
- **Note**: Requires special privileges

## Socket Roles

### Server Socket

- **Purpose**: Listens for incoming connections
- **Steps**:
  1. Create socket
  2. Bind to address (IP + port)
  3. Listen for connections
  4. Accept connections
  5. Communicate with clients

### Client Socket

- **Purpose**: Connects to a server
- **Steps**:
  1. Create socket
  2. Connect to server (IP + port)
  3. Send/receive data
  4. Close connection

## Socket Communication Flow

### TCP Communication

```
SERVER                          CLIENT
  │                               │
  ├─ socket()                     ├─ socket()
  ├─ bind(IP, PORT)               │
  ├─ listen()                     │
  ├─ accept() ←───────────────────┼─ connect()
  │   (waiting)                   │
  │                               │
  │ ←─────────────────────────────├─ send()
  │   (receives)                  │
  │                               │
  ├─ recv()                       │
  ├─ send() ──────────────────────→│
  │                               ├─ recv()
  │                               │
  ├─ close()                      ├─ close()
```

### UDP Communication

```
SERVER                          CLIENT
  │                               │
  ├─ socket()                     ├─ socket()
  ├─ bind(IP, PORT)               │
  │                               │
  │ ←─────────────────────────────├─ sendto()
  ├─ recvfrom()                   │
  │                               │
  ├─ sendto() ────────────────────→│
  │                               ├─ recvfrom()
```

## Socket States

### TCP Socket States

1. **CLOSED**: Socket is not in use
2. **LISTEN**: Server waiting for connections
3. **SYN_SENT**: Client initiated connection
4. **SYN_RECEIVED**: Server received connection request
5. **ESTABLISHED**: Connection active, data can flow
6. **FIN_WAIT**: Closing initiated
7. **CLOSE_WAIT**: Remote side closed
8. **CLOSING**: Both sides closing
9. **TIME_WAIT**: Waiting for final cleanup

## Why Use Sockets?

### Advantages

1. **Low-level control**: Direct access to network layer
2. **Performance**: Efficient data transfer
3. **Flexibility**: Can implement custom protocols
4. **Real-time**: Suitable for real-time applications
5. **Cross-platform**: Works on most operating systems

### When to Use Sockets

- ✅ Building custom network protocols
- ✅ Real-time applications (chat, gaming)
- ✅ High-performance servers
- ✅ IoT device communication
- ✅ Distributed systems

### When NOT to Use Sockets

- ❌ Simple HTTP API calls (use HTTP libraries)
- ❌ REST APIs (use HTTP frameworks)
- ❌ Database access (use database drivers)
- ❌ Email sending (use SMTP libraries)

## Socket Programming Languages

Sockets are available in most programming languages:

- **Python**: `socket` module (high-level, easy)
- **C**: `sys/socket.h` (low-level, powerful)
- **Java**: `java.net.Socket` (object-oriented)
- **JavaScript/Node.js**: `net` module (event-driven)
- **Go**: `net` package (concurrent)
- **C++**: `sys/socket.h` (similar to C)

## Socket Family/Address Family

Sockets support different address families:

- **AF_INET**: IPv4 addresses (most common)
- **AF_INET6**: IPv6 addresses
- **AF_UNIX**: Local communication (same machine)
- **AF_BLUETOOTH**: Bluetooth communication

## Domain vs Protocol Family

- **Domain/Address Family**: Type of addresses (AF_INET, AF_INET6)
- **Protocol Family**: Communication protocol (SOCK_STREAM, SOCK_DGRAM)

Common combinations:
- `AF_INET` + `SOCK_STREAM` = IPv4 TCP
- `AF_INET` + `SOCK_DGRAM` = IPv4 UDP
- `AF_INET6` + `SOCK_STREAM` = IPv6 TCP
- `AF_UNIX` + `SOCK_STREAM` = Unix domain socket

## Summary

**Sockets are:**
- Endpoints for network communication
- Identified by IP address + port
- Available in two main types: TCP (stream) and UDP (datagram)
- Used for low-level network programming
- Essential for building network applications

**Next**: Learn about the specific socket API functions and how to use them!

---

**Key Takeaway**: A socket is your program's door to the network. It lets you send and receive data over the internet using TCP or UDP protocols.

