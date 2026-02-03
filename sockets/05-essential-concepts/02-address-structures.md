# Address Structures

Socket addresses are represented differently in different languages and APIs. This module explains address structures and how to work with them.

## Socket Address Formats

### Python: Tuple Format

Python uses simple tuples for socket addresses:

```python
# IPv4 address tuple: (host, port)
address = ('localhost', 8080)
address = ('192.168.1.100', 8080)
address = ('127.0.0.1', 3000)

# Usage
server.bind(('0.0.0.0', 8080))
client.connect(('example.com', 80))
```

**Format**: `(host_string, port_integer)`
- `host`: String (IP address or hostname)
- `port`: Integer (0-65535)

### C: struct sockaddr

C uses structures for addresses:

```c
#include <sys/socket.h>
#include <netinet/in.h>

// IPv4 address structure
struct sockaddr_in {
    sa_family_t    sin_family;   // Address family (AF_INET)
    in_port_t      sin_port;     // Port number
    struct in_addr sin_addr;     // IP address
    char           sin_zero[8];  // Padding
};

// Usage
struct sockaddr_in server_addr;
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(8080);
server_addr.sin_addr.s_addr = INADDR_ANY;
```

### IPv6 Address Structure

```c
struct sockaddr_in6 {
    sa_family_t     sin6_family;    // AF_INET6
    in_port_t       sin6_port;      // Port number
    uint32_t        sin6_flowinfo;  // Flow information
    struct in6_addr sin6_addr;      // IPv6 address
    uint32_t        sin6_scope_id;  // Scope ID
};
```

## Converting Between Formats

### String to IP Address

```python
import socket

# Convert hostname to IP
ip = socket.gethostbyname('example.com')
# Returns: '93.184.216.34'

# Convert IP to hostname
hostname = socket.gethostbyaddr('93.184.216.34')
# Returns: ('example.com', [], ['93.184.216.34'])

# Get all IPs for a hostname
ips = socket.gethostbyname_ex('example.com')
# Returns: ('example.com', [], ['93.184.216.34'])
```

### IP Address to Integer

```python
import socket
import struct

# IPv4 string to integer
ip_str = '192.168.1.1'
ip_int = struct.unpack('!I', socket.inet_aton(ip_str))[0]
# Returns: 3232235777

# Integer to IPv4 string
ip_str = socket.inet_ntoa(struct.pack('!I', ip_int))
# Returns: '192.168.1.1'

# IPv6 (Python 3.4+)
ip_str = '2001:db8::1'
ip_bytes = socket.inet_pton(socket.AF_INET6, ip_str)
ip_str = socket.inet_ntop(socket.AF_INET6, ip_bytes)
```

## Special Addresses

### INADDR_ANY / 0.0.0.0

**Meaning**: Bind to all available interfaces

```python
# Python
server.bind(('0.0.0.0', 8080))  # All interfaces
server.bind(('', 8080))         # Same as above

# C
server_addr.sin_addr.s_addr = INADDR_ANY;
```

**Use case**: Server accepting connections on any network interface

### 127.0.0.1 / localhost

**Meaning**: Loopback interface (local machine only)

```python
# Python
server.bind(('127.0.0.1', 8080))    # Localhost only
server.bind(('localhost', 8080))    # Same (usually)

# Only accessible from same machine
```

**Use case**: Local testing, local services

### 255.255.255.255

**Meaning**: Broadcast address (IPv4)

```python
# UDP broadcast
client.sendto(data, ('255.255.255.255', 8080))
```

**Use case**: Broadcast messages to all devices on network

## Getting Socket Address Information

### Get Local Address

```python
# Get address this socket is bound to
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind(('0.0.0.0', 8080))
addr = sock.getsockname()
# Returns: ('0.0.0.0', 8080)

# Get actual bound address after binding
sock.bind(('', 0))  # Bind to any port
addr = sock.getsockname()
# Returns: ('0.0.0.0', <assigned_port>)
```

### Get Peer Address

```python
# Get address of connected peer (client side)
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(('example.com', 80))
server_addr = client.getpeername()
# Returns: ('93.184.216.34', 80)

# On server side (after accept)
client_sock, client_addr = server.accept()
# client_addr is already provided
# Or use: client_sock.getpeername()
```

### Get All Interface Addresses

```python
import socket

# Get all IP addresses of this machine
hostname = socket.gethostname()
local_ip = socket.gethostbyname(hostname)

# Get all IPs (including loopback, etc.)
for interface in socket.getaddrinfo(hostname, None):
    print(interface[4][0])  # IP address

# Using netifaces (if installed)
try:
    import netifaces
    for interface in netifaces.interfaces():
        addrs = netifaces.ifaddresses(interface)
        if netifaces.AF_INET in addrs:
            for addr in addrs[netifaces.AF_INET]:
                print(addr['addr'])
except ImportError:
    pass
```

## Address Resolution: getaddrinfo()

The `getaddrinfo()` function is the modern way to resolve addresses:

```python
import socket

# Resolve hostname and port
info = socket.getaddrinfo(
    'example.com',      # hostname
    80,                 # port
    socket.AF_INET,     # address family (or AF_UNSPEC for both)
    socket.SOCK_STREAM  # socket type
)

# Returns list of tuples:
# (family, type, proto, canonname, sockaddr)
# Example: [(2, 1, 6, '', ('93.184.216.34', 80))]

# Use first result
family, socktype, proto, canonname, sockaddr = info[0]
sock = socket.socket(family, socktype)
sock.connect(sockaddr)
```

### Benefits of getaddrinfo()

- Supports both IPv4 and IPv6
- Returns all matching addresses
- Works with hostnames and IPs
- Recommended for modern code

## Working with IPv6

### IPv6 Address Format

```python
# IPv6 address tuple (Python)
address = ('::1', 8080)  # IPv6 localhost
address = ('2001:db8::1', 8080)

# Creating IPv6 socket
sock = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
sock.bind(('::', 8080))  # All IPv6 interfaces
```

### Dual-Stack Sockets (IPv4 + IPv6)

```python
# Create socket that accepts both IPv4 and IPv6
sock = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
sock.setsockopt(socket.IPPROTO_IPV6, socket.IPV6_V6ONLY, 0)
sock.bind(('::', 8080))
# Now accepts both IPv4 and IPv6 connections
```

## Port Numbers

### Well-Known Ports (0-1023)

```python
# Reserved for system services
HTTP_PORT = 80
HTTPS_PORT = 443
SSH_PORT = 22
SMTP_PORT = 25
DNS_PORT = 53

# Need root/admin privileges to bind
```

### Registered Ports (1024-49151)

```python
# For registered applications
MYSQL_PORT = 3306
POSTGRES_PORT = 5432
REDIS_PORT = 6379
MONGO_PORT = 27017
```

### Dynamic/Private Ports (49152-65535)

```python
# For client-side ephemeral ports
# OS assigns automatically for outgoing connections
```

### Getting Available Port

```python
import socket

def get_free_port():
    """Get a free port number."""
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind(('', 0))  # Bind to any available port
    port = sock.getsockname()[1]
    sock.close()
    return port

# Usage
port = get_free_port()
print(f"Free port: {port}")
```

## Address Comparison

```python
# Compare addresses
addr1 = ('192.168.1.1', 8080)
addr2 = ('192.168.1.1', 8080)

if addr1 == addr2:
    print("Same address")

# Compare IPs (ignore port)
if addr1[0] == addr2[0]:
    print("Same IP")
```

## Common Patterns

### Bind to All Interfaces

```python
server.bind(('0.0.0.0', 8080))  # IPv4
# or
server.bind(('', 8080))  # Shorter
```

### Bind to Localhost Only

```python
server.bind(('127.0.0.1', 8080))  # IPv4 localhost
server.bind(('localhost', 8080))  # Usually same
```

### Connect with Hostname Resolution

```python
# Automatically resolves hostname
client.connect(('example.com', 80))

# Or resolve first
ip = socket.gethostbyname('example.com')
client.connect((ip, 80))
```

---

**Key Takeaway**: Socket addresses are represented as `(host, port)` tuples in Python. Use `getaddrinfo()` for modern address resolution, and understand special addresses like `0.0.0.0` (all interfaces) and `127.0.0.1` (localhost).

