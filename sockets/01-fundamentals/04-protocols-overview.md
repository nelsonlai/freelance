# Network Protocols Overview

## What is a Protocol?

A **protocol** is a set of rules that defines how devices communicate over a network. It specifies:
- How to format data
- How to establish connections
- How to handle errors
- How to terminate communication

Think of it as a language that all devices on a network understand.

## Protocol Stack Layers

Protocols are organized in layers, each building on the one below:

```
Application Layer Protocols
    ↓
Transport Layer Protocols (TCP, UDP)
    ↓
Internet Layer Protocol (IP)
    ↓
Link Layer Protocols (Ethernet, Wi-Fi)
```

## Transport Layer Protocols

### TCP (Transmission Control Protocol)

**Characteristics:**
- ✅ **Connection-oriented**: Establishes connection before data transfer
- ✅ **Reliable**: Guarantees delivery and ordering
- ✅ **Flow control**: Prevents overwhelming receiver
- ✅ **Congestion control**: Adapts to network conditions
- ❌ **Slower**: More overhead due to reliability features
- ❌ **Higher latency**: Connection setup time

**Use cases:**
- Web browsing (HTTP/HTTPS)
- Email (SMTP, IMAP)
- File transfer (FTP)
- Remote access (SSH)
- Database connections

**How it works:**
1. **Handshake**: 3-way handshake to establish connection
2. **Data transfer**: Segments data, tracks delivery
3. **Acknowledgments**: Receiver confirms receipt
4. **Teardown**: Clean connection termination

### UDP (User Datagram Protocol)

**Characteristics:**
- ✅ **Connectionless**: No connection setup
- ✅ **Fast**: Low overhead, minimal latency
- ✅ **Simple**: Fewer rules, less complexity
- ❌ **Unreliable**: No delivery guarantees
- ❌ **No ordering**: Packets may arrive out of order
- ❌ **No flow control**: Can overwhelm receiver

**Use cases:**
- Video/audio streaming
- Online gaming
- DNS queries
- Voice over IP (VoIP)
- Broadcasting/multicasting

**How it works:**
1. **Send**: Immediately sends data (datagrams)
2. **No tracking**: No acknowledgment or retransmission
3. **Best effort**: Delivers if possible, discards if not

### TCP vs UDP Comparison

| Feature | TCP | UDP |
|---------|-----|-----|
| Connection | Connection-oriented | Connectionless |
| Reliability | Guaranteed delivery | Best effort |
| Ordering | Guaranteed | Not guaranteed |
| Speed | Slower | Faster |
| Overhead | Higher | Lower |
| Flow control | Yes | No |
| Error detection | Yes | Checksum only |
| Use case | Reliable data transfer | Speed-critical apps |

## Internet Layer Protocol

### IP (Internet Protocol)

- **Purpose**: Routes packets across networks
- **Addressing**: Provides IP addresses
- **Fragmentation**: Breaks large packets into smaller ones
- **Version**: IPv4 (32-bit) or IPv6 (128-bit)
- **Connectionless**: Each packet routed independently

## Application Layer Protocols

### HTTP (Hypertext Transfer Protocol)

- **Port**: 80 (HTTP) or 443 (HTTPS)
- **Type**: Request-response protocol
- **Method**: Client requests, server responds
- **Stateless**: Each request independent
- **Example**: Web browsers and servers

### HTTPS (HTTP Secure)

- **Port**: 443
- **Type**: HTTP over TLS/SSL
- **Features**: Encrypted, authenticated
- **Use case**: Secure web communication

### FTP (File Transfer Protocol)

- **Port**: 21 (control), 20 (data)
- **Purpose**: File transfer
- **Types**: Active and passive modes
- **Security**: Use SFTP (SSH) instead for security

### SMTP (Simple Mail Transfer Protocol)

- **Port**: 25
- **Purpose**: Sending email
- **Type**: Text-based protocol
- **Use case**: Email servers

### DNS (Domain Name System)

- **Port**: 53
- **Protocol**: Usually UDP (can use TCP for large responses)
- **Purpose**: Translates domain names to IP addresses
- **Use case**: Every web request

### SSH (Secure Shell)

- **Port**: 22
- **Protocol**: TCP
- **Purpose**: Secure remote access
- **Features**: Encrypted, authenticated
- **Use case**: Remote server management

### WebSocket

- **Port**: Same as HTTP (80/443)
- **Protocol**: TCP (upgraded from HTTP)
- **Purpose**: Full-duplex communication
- **Features**: Persistent connection, real-time
- **Use case**: Chat apps, live updates

## Protocol Design Principles

### Reliability vs Speed

- **TCP**: Choose for reliability (web, email, files)
- **UDP**: Choose for speed (gaming, streaming)

### Stateful vs Stateless

- **Stateful**: Server remembers previous requests (TCP connections)
- **Stateless**: Each request independent (HTTP, UDP)

### Text-based vs Binary

- **Text-based**: Human-readable (HTTP, SMTP, FTP)
  - Easier to debug
  - More overhead
  - Examples: HTTP, SMTP

- **Binary**: Machine-optimized (protobuf, custom)
  - More efficient
  - Harder to debug
  - Examples: Protocol Buffers, Thrift

## Custom Protocols

When building socket applications, you often design custom protocols:

### Simple Text Protocol

```
CLIENT → SERVER: "GET /status"
SERVER → CLIENT: "OK 200"
```

### Binary Protocol

```
[Header: 4 bytes][Body: variable length]
```

### JSON over TCP

```json
{
  "command": "get_user",
  "id": 12345
}
```

### Protocol Design Tips

1. **Define message format**: Structure, encoding, boundaries
2. **Handle framing**: How to separate messages
3. **Error handling**: What to do when things go wrong
4. **Versioning**: Allow protocol evolution
5. **Documentation**: Clear specification

## Protocol Selection Guide

**Choose TCP when:**
- Data integrity is critical
- Order matters
- You need guaranteed delivery
- Examples: file transfer, database, API

**Choose UDP when:**
- Speed is more important than reliability
- Lost packets are acceptable
- Real-time is critical
- Examples: gaming, streaming, DNS

**Design custom protocol when:**
- Standard protocols don't fit
- You need specific features
- Performance is critical
- Examples: game servers, IoT devices

---

**Key Takeaway**: Protocols define how data is exchanged. Understanding different protocols helps you choose the right one for your application and design effective custom protocols.

