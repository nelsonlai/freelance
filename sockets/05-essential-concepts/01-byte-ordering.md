# Byte Ordering (Endianness)

Byte ordering, or endianness, determines how multi-byte values are stored in memory. This is crucial for network communication where different systems may use different byte orders.

## What is Endianness?

**Endianness** refers to the order in which bytes are stored for multi-byte data types (like integers).

### Big-Endian (Network Byte Order)

- **Most significant byte first**
- Left-to-right ordering
- Example: `0x12345678` stored as `12 34 56 78`
- Used by: Network protocols, some processors (PowerPC, older SPARC)

### Little-Endian (Host Byte Order)

- **Least significant byte first**
- Right-to-left ordering
- Example: `0x12345678` stored as `78 56 34 12`
- Used by: x86/x64 processors (Intel, AMD), ARM (usually)

## Why It Matters in Networking

**Problem**: When sending data over network, different machines may use different byte orders.

**Example**:
```python
# Machine A (little-endian) sends integer 1000
# Stored as: [232, 3, 0, 0]  (little-endian)

# Machine B (big-endian) receives
# Interprets as: [232, 3, 0, 0] = 232 + 3*256 = 1000 ✓ (lucky!)
# But if Machine B is also little-endian and expects big-endian:
# Interprets as: [232, 3, 0, 0] = wrong value ✗
```

**Solution**: Network byte order (big-endian) is the standard for network protocols.

## Socket API Functions

### Convert to Network Byte Order

```python
import socket

# Convert 16-bit integer to network byte order
port = 8080
network_port = socket.htons(port)  # Host TO Network Short

# Convert 32-bit integer to network byte order
ip_int = 0x12345678
network_ip = socket.htonl(ip_int)  # Host TO Network Long
```

### Convert from Network Byte Order

```python
# Convert 16-bit integer from network byte order
network_port = b'\x1f\x90'  # Received from network
host_port = socket.ntohs(network_port)  # Network TO Host Short

# Convert 32-bit integer from network byte order
network_ip = b'\x12\x34\x56\x78'
host_ip = socket.ntohl(network_ip)  # Network TO Host Long
```

## Function Reference

| Function | Purpose | Size |
|----------|---------|------|
| `socket.htons()` | Host to Network Short | 16 bits (2 bytes) |
| `socket.ntohs()` | Network to Host Short | 16 bits (2 bytes) |
| `socket.htonl()` | Host to Network Long | 32 bits (4 bytes) |
| `socket.ntohl()` | Network to Host Long | 32 bits (4 bytes) |

**Note**: Python's socket module handles most conversions automatically when using high-level functions. However, you may need these for:
- Raw socket programming
- Binary protocol design
- Low-level network programming

## Python's Automatic Handling

Python's socket module usually handles byte order automatically:

```python
# Python handles conversion automatically
client.connect(('localhost', 8080))  # Port converted automatically
server.bind(('0.0.0.0', 8080))       # Port converted automatically
```

**But** when working with binary data directly:

```python
import struct

# Manual conversion needed for binary protocols
port = 8080
# Method 1: Use struct with '!' (network byte order)
packed = struct.pack('!H', port)  # H = unsigned short (2 bytes)
# packed is now in network byte order

# Method 2: Use socket functions
packed = socket.htons(port).to_bytes(2, 'big')
```

## Example: Sending Binary Data

```python
import socket
import struct

def send_binary_message(client, message_id, data):
    """Send message with binary header."""
    
    # Message format: [ID: 2 bytes][Length: 4 bytes][Data: variable]
    message_id_network = socket.htons(message_id)
    length_network = socket.htonl(len(data))
    
    # Pack header (network byte order)
    header = struct.pack('!H I', message_id_network, length_network)
    
    # Send header + data
    client.sendall(header + data)

def receive_binary_message(client):
    """Receive message with binary header."""
    
    # Receive header (6 bytes: 2 + 4)
    header = client.recv(6)
    if len(header) != 6:
        raise ValueError("Incomplete header")
    
    # Unpack header (network byte order)
    message_id_network, length_network = struct.unpack('!H I', header)
    
    # Convert to host byte order
    message_id = socket.ntohs(message_id_network)
    length = socket.ntohl(length_network)
    
    # Receive data
    data = recv_all(client, length)
    
    return message_id, data
```

## Using struct Module

The `struct` module provides format specifiers for byte order:

| Format | Byte Order |
|--------|------------|
| `'<'` | Little-endian (host, usually) |
| `'>'` | Big-endian (network) |
| `'!'` | Network byte order (big-endian) |
| `'='` | Native byte order |
| `'@'` | Native byte order, native size |

**Best practice**: Always use `'!'` for network data:

```python
import struct

# Pack integer in network byte order
value = 1000
packed = struct.pack('!I', value)  # I = unsigned int (4 bytes)

# Unpack from network byte order
unpacked = struct.unpack('!I', packed)[0]
```

## Checking Your System's Byte Order

```python
import sys

# Check system byte order
if sys.byteorder == 'little':
    print("System is little-endian")
elif sys.byteorder == 'big':
    print("System is big-endian")
```

Or using socket functions:

```python
import socket

# If htons doesn't change value, system is big-endian
test = 0x1234
if socket.htons(test) == test:
    print("System is big-endian (network byte order)")
else:
    print("System is little-endian (needs conversion)")
```

## Common Mistakes

### Mistake 1: Assuming Host Byte Order

```python
# WRONG: Sending in host byte order
port = 8080
client.send(port.to_bytes(2, sys.byteorder))  # May be wrong!

# CORRECT: Always use network byte order
port = 8080
client.send(socket.htons(port).to_bytes(2, 'big'))  # Always correct
# OR use struct
client.send(struct.pack('!H', port))
```

### Mistake 2: Mixing Byte Orders

```python
# WRONG: Mixing formats
header = struct.pack('I H', length, port)  # Native byte order!
# Use network byte order for both:
header = struct.pack('!I H', length, port)  # ✓
```

### Mistake 3: Ignoring Byte Order for Text

```python
# Text data doesn't need byte order conversion
message = "Hello"
client.send(message.encode())  # ✓ Fine, no conversion needed

# But numbers in binary format do need conversion
number = 1000
client.send(struct.pack('!I', number))  # ✓ Convert to network order
```

## Best Practices

1. **Always use network byte order for binary numeric data**
   ```python
   struct.pack('!I H', length, port)  # ✓
   ```

2. **Use socket module functions when convenient**
   ```python
   socket.htons(port)  # ✓ Clear intent
   ```

3. **Document byte order in protocol specifications**
   ```python
   # Protocol: All integers in network byte order (big-endian)
   ```

4. **Test on different architectures** if possible
   - Little-endian (x86): Most common
   - Big-endian: Less common, but still exists

5. **Use struct format strings explicitly**
   ```python
   # Good: Explicit byte order
   struct.pack('!H I', port, length)
   
   # Avoid: Implicit native order
   struct.pack('H I', port, length)
   ```

## Summary

- **Network byte order** = Big-endian (standard for network protocols)
- **Host byte order** = System-dependent (usually little-endian on x86)
- **Always convert** binary numeric data to network byte order before sending
- **Python's socket module** handles most conversions automatically
- **Use struct with '!'** for explicit network byte order
- **Text data** doesn't need byte order conversion

---

**Key Takeaway**: When sending binary numeric data over the network, always convert to network byte order (big-endian) using `socket.htons()/htonl()` or `struct.pack('!...')` to ensure compatibility across different systems.

