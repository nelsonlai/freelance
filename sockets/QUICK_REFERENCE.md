# Socket Programming Quick Reference

A quick reference guide for common socket programming tasks and patterns.

## Python Socket Quick Reference

### Creating Sockets

```python
import socket

# TCP socket
tcp_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# UDP socket
udp_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# IPv6 socket
ipv6_sock = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
```

### TCP Server

```python
# Create, bind, listen
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server.bind(('localhost', 8080))
server.listen(5)

# Accept connections
while True:
    client, addr = server.accept()
    data = client.recv(1024)
    client.sendall(b"Response")
    client.close()
```

### TCP Client

```python
# Create and connect
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(('localhost', 8080))

# Send and receive
client.sendall(b"Hello")
response = client.recv(1024)

# Close
client.close()
```

### UDP Server

```python
# Create and bind
server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server.bind(('localhost', 8080))

# Receive and send
while True:
    data, addr = server.recvfrom(1024)
    server.sendto(b"Response", addr)
```

### UDP Client

```python
# Create socket
client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Send and receive
client.sendto(b"Hello", ('localhost', 8080))
data, addr = client.recvfrom(1024)
```

## Common Patterns

### Handle Multiple Clients (Threading)

```python
import threading

def handle_client(client, addr):
    while True:
        data = client.recv(1024)
        if not data:
            break
        client.sendall(data)
    client.close()

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(('localhost', 8080))
server.listen(5)

while True:
    client, addr = server.accept()
    thread = threading.Thread(target=handle_client, args=(client, addr))
    thread.start()
```

### Send All Data

```python
def send_all(sock, data):
    total_sent = 0
    while total_sent < len(data):
        sent = sock.send(data[total_sent:])
        if sent == 0:
            raise RuntimeError("Connection broken")
        total_sent += sent
```

### Receive All Data

```python
def recv_all(sock, size):
    data = b''
    while len(data) < size:
        chunk = sock.recv(size - len(data))
        if not chunk:
            raise ConnectionError("Connection closed")
        data += chunk
    return data
```

### Set Timeout

```python
# Set timeout (seconds)
sock.settimeout(5.0)

try:
    data = sock.recv(1024)
except socket.timeout:
    print("Timeout")
```

### Non-blocking I/O

```python
import errno

sock.setblocking(False)
try:
    data = sock.recv(1024)
except socket.error as e:
    if e.errno == errno.EAGAIN or e.errno == errno.EWOULDBLOCK:
        # No data available
        pass
    else:
        raise
```

## Error Handling

### Common Exceptions

```python
try:
    client.connect(('localhost', 8080))
except ConnectionRefusedError:
    # Server not listening
    pass
except socket.gaierror:
    # DNS resolution failed
    pass
except socket.timeout:
    # Operation timed out
    pass
except OSError as e:
    if e.errno == 48:  # Address already in use
        pass
    elif e.errno == 13:  # Permission denied
        pass
```

## Socket Options

```python
# Reuse address
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

# Enable broadcast (UDP)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

# Set buffer sizes
sock.setsockopt(socket.SOL_SOCKET, socket.SO_RCVBUF, 8192)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_SNDBUF, 8192)

# Keep-alive
sock.setsockopt(socket.SOL_SOCKET, socket.SO_KEEPALIVE, 1)
```

## Address Functions

```python
# Hostname to IP
ip = socket.gethostbyname('example.com')

# Get socket name
addr = sock.getsockname()  # (host, port)

# Get peer name
addr = sock.getpeername()  # (host, port)

# Resolve address
info = socket.getaddrinfo('example.com', 80, socket.AF_INET, socket.SOCK_STREAM)
```

## Byte Ordering

```python
import struct

# Host to network (16-bit)
port = socket.htons(8080)

# Network to host (16-bit)
port = socket.ntohs(port)

# Host to network (32-bit)
value = socket.htonl(12345)

# Network to host (32-bit)
value = socket.ntohl(value)

# Using struct (network byte order)
packed = struct.pack('!H', 8080)  # 2 bytes
port = struct.unpack('!H', packed)[0]
```

## Testing Tools

### Netcat (nc)

```bash
# TCP server
nc -l 8080

# TCP client
nc localhost 8080

# UDP server
nc -u -l 8080

# UDP client
nc -u localhost 8080
```

### Telnet

```bash
# Connect to TCP server
telnet localhost 8080
```

### Python Test Client

```python
import socket
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(('localhost', 8080))
client.sendall(b"test")
print(client.recv(1024))
client.close()
```

## Common Issues

| Issue | Solution |
|-------|----------|
| Address already in use | `setsockopt(SO_REUSEADDR, 1)` |
| Connection refused | Check server is running |
| Timeout | Increase timeout or check network |
| Permission denied | Use port >= 1024 or run as root |
| Broken pipe | Check connection state before sending |

## Best Practices Checklist

- [ ] Always close sockets
- [ ] Handle exceptions
- [ ] Set timeouts
- [ ] Use `sendall()` not `send()`
- [ ] Check for empty `recv()` (connection closed)
- [ ] Set `SO_REUSEADDR` for servers
- [ ] Validate input data
- [ ] Limit buffer sizes
- [ ] Use network byte order for binary data

## Common Port Numbers

| Port | Service |
|------|---------|
| 80 | HTTP |
| 443 | HTTPS |
| 22 | SSH |
| 25 | SMTP |
| 53 | DNS |
| 3306 | MySQL |
| 5432 | PostgreSQL |
| 8080 | Common development port |

---

**See full documentation in individual modules for detailed explanations.**

