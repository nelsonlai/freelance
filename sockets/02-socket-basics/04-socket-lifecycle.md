# Socket Lifecycle

Understanding the socket lifecycle is crucial for writing robust network applications. This module explains the complete lifecycle from creation to termination.

## TCP Socket Lifecycle

### Server Socket Lifecycle

```
1. socket()          → Create socket
   ↓
2. bind()            → Bind to address/port
   ↓
3. listen()          → Start listening
   ↓
4. accept()          → Wait for connection (BLOCKING)
   ↓
5. [New Client Socket Created]
   ↓
6. recv()/send()     → Communicate with client
   ↓
7. close()           → Close client socket
   ↓
8. [Back to step 4 for next client]
   ↓
9. close()           → Close server socket (when done)
```

### Client Socket Lifecycle

```
1. socket()          → Create socket
   ↓
2. connect()         → Connect to server (BLOCKING)
   ↓
3. send()/recv()     → Communicate
   ↓
4. close()           → Close socket
```

## Detailed Lifecycle Stages

### Stage 1: Creation (socket())

**Purpose**: Allocate resources for socket

**What happens**:
- Operating system allocates file descriptor
- Socket structure created in kernel
- Socket is in CLOSED state (TCP) or UNBOUND (UDP)

**Code**:
```python
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# Socket created but not yet usable
```

**State**: Socket exists but not bound to any address

---

### Stage 2: Binding (bind()) - Server Only

**Purpose**: Associate socket with local address/port

**What happens**:
- Socket gets a local address (IP + port)
- Port becomes "reserved" for this socket
- Other processes cannot use this port
- Socket enters LISTENING state (after listen())

**Code**:
```python
server.bind(('0.0.0.0', 8080))
# Socket now bound to port 8080
```

**Common Issues**:
- Port already in use → `Address already in use`
- Insufficient privileges → `Permission denied` (ports < 1024)
- Invalid address → `Cannot assign requested address`

**State**: Socket bound, ready to listen or send

---

### Stage 3: Listening (listen()) - TCP Server Only

**Purpose**: Make socket accept incoming connections

**What happens**:
- Socket enters LISTEN state
- OS creates connection queue
- Socket can now accept connections
- Backlog parameter sets queue size

**Code**:
```python
server.listen(5)  # Allow 5 pending connections
# Socket now listening
```

**State**: LISTEN - waiting for connections

---

### Stage 4: Connecting (connect()) - TCP Client Only

**Purpose**: Establish connection to server

**What happens** (3-way handshake):
1. Client sends SYN (synchronize) packet
2. Server responds with SYN-ACK
3. Client sends ACK (acknowledge)
4. Connection established

**Code**:
```python
client.connect(('192.168.1.100', 8080))
# Connection established (or exception raised)
```

**States**:
- `SYN_SENT` → Client sent SYN
- `ESTABLISHED` → Connection active

**Common Issues**:
- Server not listening → `Connection refused`
- Network unreachable → `Network unreachable`
- Firewall blocking → `Connection timed out`

---

### Stage 5: Accepting (accept()) - TCP Server Only

**Purpose**: Accept incoming connection

**What happens**:
- Blocks until connection arrives
- New socket created for client
- Original socket continues listening
- Returns client socket and address

**Code**:
```python
client_sock, client_addr = server.accept()
# New socket for this specific client
```

**Important**: 
- Original server socket unchanged
- Each client gets its own socket
- Server can handle multiple clients concurrently

**State**: Client socket in ESTABLISHED state

---

### Stage 6: Data Transfer (send()/recv() or sendto()/recvfrom())

**Purpose**: Exchange data

**TCP**:
```python
# Server sends
server_socket.send(b"Hello")

# Client receives
data = client_socket.recv(1024)

# Client sends
client_socket.send(b"Response")

# Server receives
data = server_socket.recv(1024)
```

**UDP**:
```python
# Send to specific address
socket.sendto(b"Hello", ('192.168.1.100', 8080))

# Receive from any address
data, addr = socket.recvfrom(1024)
```

**State**: ESTABLISHED (TCP) or UNBOUND (UDP, but bound if server)

---

### Stage 7: Closing (close())

**Purpose**: Terminate connection and free resources

**TCP Connection Closure** (4-way handshake):

**Active Close (client closes)**:
1. Client sends FIN
2. Server responds with ACK
3. Server sends FIN
4. Client responds with ACK
5. Both sides enter TIME_WAIT

**Passive Close (server closes)**:
- Same process, initiated by server

**Code**:
```python
socket.close()
# Connection terminated gracefully
```

**States During Close**:
- `FIN_WAIT_1` → Sent FIN, waiting for ACK
- `FIN_WAIT_2` → Received ACK, waiting for FIN
- `CLOSE_WAIT` → Received FIN, waiting for application close
- `LAST_ACK` → Sent FIN, waiting for final ACK
- `TIME_WAIT` → Waiting for any delayed packets (usually 2*MSL)
- `CLOSED` → Socket fully closed

**UDP Closing**:
- Simpler: just close the socket
- No handshake needed (connectionless)

---

## Complete TCP Server Example

```python
import socket

# Stage 1: Create
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

# Stage 2: Bind
server.bind(('localhost', 8080))

# Stage 3: Listen
server.listen(5)
print("Server listening on port 8080")

try:
    while True:
        # Stage 4: Accept (blocks here)
        client, addr = server.accept()
        print(f"Connection from {addr}")
        
        try:
            # Stage 5: Communicate
            while True:
                data = client.recv(1024)
                if not data:
                    break
                
                response = data.upper()
                client.send(response)
        
        finally:
            # Stage 6: Close client
            client.close()
            print(f"Connection to {addr} closed")

finally:
    # Stage 7: Close server
    server.close()
```

## Complete TCP Client Example

```python
import socket

# Stage 1: Create
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    # Stage 2: Connect
    client.connect(('localhost', 8080))
    print("Connected to server")
    
    # Stage 3: Communicate
    client.send(b"Hello, Server!")
    response = client.recv(1024)
    print(f"Response: {response.decode()}")
    
finally:
    # Stage 4: Close
    client.close()
```

## UDP Socket Lifecycle (Simpler)

### Server
```python
# 1. Create
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# 2. Bind
sock.bind(('localhost', 8080))

# 3. Receive/Send (loop)
while True:
    data, addr = sock.recvfrom(1024)
    sock.sendto(data.upper(), addr)

# 4. Close
sock.close()
```

### Client
```python
# 1. Create
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# 2. Send (no connection)
sock.sendto(b"Hello", ('localhost', 8080))

# 3. Receive
data, addr = sock.recvfrom(1024)

# 4. Close
sock.close()
```

## State Transitions Diagram (TCP)

```
CLOSED
  ↓ [socket()]
UNBOUND
  ↓ [bind()]
BOUND
  ↓ [listen()]                    [connect()]
LISTEN ──────────────────────────> SYN_SENT
  ↓ [accept()]                      ↓
SYN_RCVD                           SYN_SENT
  ↓                                  ↓
ESTABLISHED ←────────────────── ESTABLISHED
  ↓                                  ↓
[data transfer]              [data transfer]
  ↓                                  ↓
[close()]                    [close()]
  ↓                                  ↓
FIN_WAIT_1                     FIN_WAIT_1
  ↓                                  ↓
FIN_WAIT_2                     FIN_WAIT_2
  ↓                                  ↓
TIME_WAIT ←────────────────── TIME_WAIT
  ↓                                  ↓
CLOSED                        CLOSED
```

## Common Lifecycle Issues

### Port Reuse

**Problem**: "Address already in use" after closing socket

**Solution**: Set SO_REUSEADDR option
```python
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server.bind(('localhost', 8080))
```

### Orphaned Connections

**Problem**: Client socket closed but server doesn't know

**Solution**: Check for empty recv()
```python
data = client.recv(1024)
if not data:
    # Connection closed by client
    break
```

### Blocking Operations

**Problem**: `accept()`, `recv()`, `connect()` block indefinitely

**Solutions**:
- Set timeouts: `socket.settimeout(5.0)`
- Use non-blocking mode
- Use select/poll/epoll (advanced)

---

**Key Takeaway**: Understanding the socket lifecycle helps you write correct, efficient, and robust network applications. Each stage has specific requirements and common pitfalls to avoid.

