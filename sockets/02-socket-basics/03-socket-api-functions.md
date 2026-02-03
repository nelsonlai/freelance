# Socket API Functions

The Socket API provides a set of functions to create, configure, and use sockets. This module covers the core functions used in socket programming.

## Core Socket Functions

### socket() - Create a Socket

**Purpose**: Creates a new socket

**Syntax** (Python):
```python
socket.socket(family, type, protocol=0)
```

**Parameters**:
- `family`: Address family (AF_INET, AF_INET6, AF_UNIX)
- `type`: Socket type (SOCK_STREAM, SOCK_DGRAM)
- `protocol`: Protocol number (usually 0 for auto-select)

**Returns**: Socket object/file descriptor

**Example**:
```python
import socket

# Create TCP socket
tcp_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Create UDP socket
udp_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
```

**In C**:
```c
int socket(int domain, int type, int protocol);
```

---

### bind() - Bind Socket to Address

**Purpose**: Associates a socket with a specific IP address and port

**Syntax** (Python):
```python
socket.bind(address)
```

**Parameters**:
- `address`: Tuple (host, port)
  - `host`: IP address string or '' (all interfaces) or 'localhost'
  - `port`: Port number (integer)

**Returns**: None (raises exception on error)

**Example**:
```python
# Bind to all interfaces on port 8080
server.bind(('', 8080))

# Bind to localhost only
server.bind(('127.0.0.1', 8080))

# Bind to specific interface
server.bind(('192.168.1.100', 8080))
```

**Common Errors**:
- `OSError: [Errno 48] Address already in use` - Port in use
- `OSError: [Errno 13] Permission denied` - Need privileges for port < 1024

**In C**:
```c
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

---

### listen() - Listen for Connections (TCP Server)

**Purpose**: Makes socket listen for incoming connections (TCP only)

**Syntax** (Python):
```python
socket.listen(backlog)
```

**Parameters**:
- `backlog`: Maximum number of pending connections

**Returns**: None (raises exception on error)

**Example**:
```python
# Allow up to 5 pending connections
server.listen(5)

# Common default value
server.listen(socket.SOMAXCONN)  # System maximum
```

**Note**: Must call `bind()` before `listen()`

**In C**:
```c
int listen(int sockfd, int backlog);
```

---

### accept() - Accept Connection (TCP Server)

**Purpose**: Accepts an incoming connection and returns a new socket for communication

**Syntax** (Python):
```python
socket.accept()
```

**Parameters**: None

**Returns**: Tuple `(socket, address)`
- `socket`: New socket for client communication
- `address`: Tuple `(ip, port)` of client

**Behavior**: Blocks until a connection is available

**Example**:
```python
# Accept connection
client_socket, client_address = server.accept()
print(f"Connection from {client_address}")

# Use client_socket to communicate with client
```

**Note**: The original server socket continues listening for more connections

**In C**:
```c
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```

---

### connect() - Connect to Server (TCP Client)

**Purpose**: Initiates connection to a server (TCP only)

**Syntax** (Python):
```python
socket.connect(address)
```

**Parameters**:
- `address`: Tuple `(host, port)` of server

**Returns**: None (raises exception on error)

**Example**:
```python
# Connect to server
client.connect(('192.168.1.100', 8080))

# Connect using domain name
client.connect(('example.com', 80))
```

**Common Errors**:
- `ConnectionRefusedError` - Server not listening
- `TimeoutError` - Connection timed out
- `gaierror` - Hostname resolution failed

**In C**:
```c
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

---

### send() - Send Data (TCP)

**Purpose**: Sends data over a connected TCP socket

**Syntax** (Python):
```python
socket.send(bytes)
```

**Parameters**:
- `bytes`: Data to send (bytes object)

**Returns**: Number of bytes sent (may be less than requested)

**Example**:
```python
message = b"Hello, Server!"
bytes_sent = client.send(message)
print(f"Sent {bytes_sent} bytes")
```

**Important**: `send()` may not send all data at once. Use loop if needed:
```python
def send_all(sock, data):
    total_sent = 0
    while total_sent < len(data):
        sent = sock.send(data[total_sent:])
        if sent == 0:
            raise RuntimeError("Socket connection broken")
        total_sent += sent
```

**In C**:
```c
ssize_t send(int sockfd, const void *buf, size_t len, int flags);
```

---

### recv() - Receive Data (TCP)

**Purpose**: Receives data from a connected TCP socket

**Syntax** (Python):
```python
socket.recv(bufsize)
```

**Parameters**:
- `bufsize`: Maximum number of bytes to receive

**Returns**: Bytes received (empty bytes if connection closed)

**Behavior**: Blocks until data is available or connection closes

**Example**:
```python
# Receive up to 1024 bytes
data = client.recv(1024)
if not data:
    print("Connection closed")
else:
    print(f"Received: {data.decode()}")
```

**Important**: `recv()` may return partial data. You may need multiple calls:
```python
def recv_all(sock, size):
    data = b''
    while len(data) < size:
        chunk = sock.recv(size - len(data))
        if not chunk:
            break
        data += chunk
    return data
```

**In C**:
```c
ssize_t recv(int sockfd, void *buf, size_t len, int flags);
```

---

### sendto() - Send Data (UDP)

**Purpose**: Sends data to a specific address (UDP)

**Syntax** (Python):
```python
socket.sendto(bytes, address)
```

**Parameters**:
- `bytes`: Data to send
- `address`: Tuple `(host, port)` of destination

**Returns**: Number of bytes sent

**Example**:
```python
message = b"Hello, Server!"
udp_socket.sendto(message, ('192.168.1.100', 8080))
```

**Note**: No connection needed for UDP

**In C**:
```c
ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
               const struct sockaddr *dest_addr, socklen_t addrlen);
```

---

### recvfrom() - Receive Data (UDP)

**Purpose**: Receives data and sender's address (UDP)

**Syntax** (Python):
```python
socket.recvfrom(bufsize)
```

**Parameters**:
- `bufsize`: Maximum number of bytes to receive

**Returns**: Tuple `(data, address)`
- `data`: Received bytes
- `address`: Tuple `(ip, port)` of sender

**Example**:
```python
data, addr = udp_socket.recvfrom(1024)
print(f"Received from {addr}: {data.decode()}")
```

**In C**:
```c
ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
                 struct sockaddr *src_addr, socklen_t *addrlen);
```

---

### close() - Close Socket

**Purpose**: Closes the socket and releases resources

**Syntax** (Python):
```python
socket.close()
```

**Example**:
```python
client.close()
server.close()
```

**Note**: 
- For TCP: Sends FIN packet to close connection gracefully
- Always close sockets when done

**In C**:
```c
int close(int fd);
```

---

## TCP Socket Lifecycle

### Server Side

```python
# 1. Create socket
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# 2. Bind to address
server.bind(('localhost', 8080))

# 3. Listen for connections
server.listen(5)

# 4. Accept connections (loop)
while True:
    client, addr = server.accept()
    # 5. Communicate
    data = client.recv(1024)
    client.send(b"Response")
    # 6. Close client socket
    client.close()

# 7. Close server socket
server.close()
```

### Client Side

```python
# 1. Create socket
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# 2. Connect to server
client.connect(('localhost', 8080))

# 3. Send data
client.send(b"Hello")

# 4. Receive data
response = client.recv(1024)

# 5. Close socket
client.close()
```

## UDP Socket Lifecycle

### Server Side

```python
# 1. Create socket
server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# 2. Bind to address
server.bind(('localhost', 8080))

# 3. Receive and send (loop)
while True:
    data, addr = server.recvfrom(1024)
    server.sendto(b"Response", addr)

# 4. Close socket
server.close()
```

### Client Side

```python
# 1. Create socket
client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# 2. Send data (no connection needed)
client.sendto(b"Hello", ('localhost', 8080))

# 3. Receive response
response, addr = client.recvfrom(1024)

# 4. Close socket
client.close()
```

## Error Handling

Always handle exceptions:

```python
import socket

try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect(('localhost', 8080))
except socket.error as e:
    print(f"Socket error: {e}")
except Exception as e:
    print(f"Error: {e}")
finally:
    s.close()
```

---

**Key Takeaway**: These core functions form the foundation of socket programming. Understanding their purpose, parameters, and order of use is essential for building network applications.

