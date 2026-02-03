# Socket Types and Domains

## Socket Domains (Address Families)

The **domain** (also called address family) specifies the address format and communication scope.

### AF_INET (IPv4)

- **Full name**: Address Family Internet
- **Purpose**: IPv4 addresses (32-bit)
- **Format**: Dotted decimal (e.g., `192.168.1.1`)
- **Most common**: Used in most network applications
- **Example**: Web servers, APIs, most TCP/UDP apps

```python
# Python example
import socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
```

### AF_INET6 (IPv6)

- **Full name**: Address Family Internet version 6
- **Purpose**: IPv6 addresses (128-bit)
- **Format**: Hexadecimal groups (e.g., `2001:db8::1`)
- **Future-proof**: Growing adoption
- **Dual-stack**: Can handle both IPv4 and IPv6

```python
# Python example
import socket
s = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
```

### AF_UNIX / AF_LOCAL

- **Purpose**: Local inter-process communication (same machine)
- **Address**: File system path (not IP address)
- **Faster**: No network overhead
- **Use cases**: Process communication, IPC
- **Platform**: Unix-like systems (Linux, macOS)

```python
# Python example
import socket
s = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
s.bind('/tmp/mysocket')
```

### AF_BLUETOOTH

- **Purpose**: Bluetooth communication
- **Protocol**: L2CAP, RFCOMM
- **Use cases**: Bluetooth devices, wireless peripherals
- **Platform**: Linux (requires BlueZ)

### Other Domains (Less Common)

- **AF_PACKET**: Direct link-layer access (Linux)
- **AF_NETLINK**: Kernel-user communication (Linux)
- **AF_X25**: X.25 protocol
- **AF_AX25**: Amateur radio

## Socket Types

The **socket type** determines the communication semantics (how data is transmitted).

### SOCK_STREAM (TCP)

- **Protocol**: TCP (Transmission Control Protocol)
- **Characteristics**:
  - Connection-oriented (must connect before sending)
  - Reliable (guaranteed delivery)
  - Ordered (data arrives in order sent)
  - Byte stream (continuous flow, no message boundaries)
  - Full-duplex (bidirectional)

- **Data Flow**: Continuous stream like a pipe
- **Use Cases**: HTTP, HTTPS, SSH, FTP, databases

```python
# Create TCP socket
tcp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
```

### SOCK_DGRAM (UDP)

- **Protocol**: UDP (User Datagram Protocol)
- **Characteristics**:
  - Connectionless (no connection needed)
  - Unreliable (no delivery guarantee)
  - Not ordered (may arrive out of order)
  - Message-based (discrete packets with boundaries)
  - Fast (low overhead)

- **Data Flow**: Individual datagrams (packets)
- **Use Cases**: DNS, gaming, streaming, VoIP

```python
# Create UDP socket
udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
```

### SOCK_RAW

- **Purpose**: Direct IP protocol access
- **Characteristics**: Bypasses transport layer
- **Requirements**: Root/Administrator privileges
- **Use Cases**: Network tools (ping, traceroute), custom protocols
- **Security**: Can construct custom IP packets

```c
// C example (requires root)
int raw_socket = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
```

### SOCK_SEQPACKET

- **Purpose**: Sequential packet socket
- **Characteristics**: Ordered, connection-oriented, message boundaries
- **Use Cases**: Specialized protocols, rarely used
- **Platform**: Mostly Unix-like systems

### SOCK_RDM

- **Purpose**: Reliable datagram messages
- **Characteristics**: Message boundaries, but connectionless
- **Use Cases**: Rare, specialized applications

## Common Combinations

### IPv4 + TCP (Most Common)

```python
socket.socket(socket.AF_INET, socket.SOCK_STREAM)
```
- Web servers, APIs, databases
- Default for most applications

### IPv4 + UDP

```python
socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
```
- DNS, gaming, streaming
- When speed matters more than reliability

### IPv6 + TCP

```python
socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
```
- Future-proof applications
- Dual-stack support

### Unix Domain + Stream

```python
socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
```
- Inter-process communication
- Same-machine communication

## Choosing Socket Type and Domain

### Choose AF_INET (IPv4) when:
- ✅ Compatibility is important
- ✅ Most common use case
- ✅ Working with existing IPv4 infrastructure

### Choose AF_INET6 (IPv6) when:
- ✅ Future-proofing
- ✅ Need larger address space
- ✅ Working in IPv6-only environment

### Choose AF_UNIX when:
- ✅ Processes on same machine
- ✅ Need better performance
- ✅ Don't need network access

### Choose SOCK_STREAM (TCP) when:
- ✅ Need reliability and ordering
- ✅ Transferring files, web data
- ✅ Connection-oriented communication
- ✅ Can tolerate slight delay

### Choose SOCK_DGRAM (UDP) when:
- ✅ Speed is critical
- ✅ Can tolerate packet loss
- ✅ Real-time applications
- ✅ Broadcasting/multicasting

## Protocol Specification

In most socket APIs, you can explicitly specify the protocol:

```python
# Python - protocol is usually auto-selected
socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)  # 0 = auto
socket.socket(socket.AF_INET, socket.SOCK_STREAM, socket.IPPROTO_TCP)
socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
```

### Common Protocols

- **IPPROTO_TCP**: TCP protocol (6)
- **IPPROTO_UDP**: UDP protocol (17)
- **IPPROTO_ICMP**: ICMP protocol (1)
- **IPPROTO_IP**: IP protocol (0)

## Platform Differences

### Linux/Unix

- Full support for all socket types
- AF_UNIX available
- SOCK_RAW requires root
- Supports advanced features (epoll, etc.)

### Windows

- Limited AF_UNIX support (Windows 10+)
- SOCK_RAW requires admin privileges
- Different API names (Winsock)
- Some limitations compared to Unix

### macOS

- Similar to Linux
- Full Unix domain socket support
- Good socket API compatibility

## Dual-Stack Sockets

Modern applications often support both IPv4 and IPv6:

```python
# Python example - can accept both IPv4 and IPv6
# (implementation depends on system configuration)
socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
```

This allows a single server to handle both address types.

## Best Practices

1. **Default to AF_INET + SOCK_STREAM** for most applications
2. **Use AF_INET6** for new applications (future-proof)
3. **Use AF_UNIX** for same-machine IPC (faster, more secure)
4. **Use SOCK_DGRAM** only when speed > reliability
5. **Avoid SOCK_RAW** unless absolutely necessary (security risk)

---

**Key Takeaway**: Socket domain determines address format (IPv4/IPv6/local), while socket type determines communication method (TCP/UDP). The combination defines your socket's capabilities.

