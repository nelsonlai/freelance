# Non-blocking I/O

Non-blocking I/O allows sockets to perform operations without waiting. This is essential for handling multiple connections efficiently in a single thread.

## Blocking vs Non-blocking

### Blocking I/O (Default)

```python
# Blocks until data is available
data = client.recv(1024)  # Waits here!

# Blocks until connection accepted
client, addr = server.accept()  # Waits here!

# Blocks until connection established
client.connect(('localhost', 8080))  # Waits here!
```

**Problems**:
- Can't handle multiple operations simultaneously
- Blocks entire thread/process
- Poor resource utilization

### Non-blocking I/O

```python
# Returns immediately, even if no data
client.setblocking(False)
try:
    data = client.recv(1024)  # Returns immediately
except socket.error as e:
    if e.errno == errno.EAGAIN or e.errno == errno.EWOULDBLOCK:
        # No data available, try again later
        pass
```

**Benefits**:
- Can check multiple sockets
- Single thread handles many connections
- Better resource utilization

## Setting Non-blocking Mode

### Python Method

```python
import socket

# Method 1: setblocking(False)
client.setblocking(False)

# Method 2: settimeout(0.0)
client.settimeout(0.0)

# Check if non-blocking
is_nonblocking = client.gettimeout() == 0.0
```

### C Method

```c
#include <fcntl.h>

int flags = fcntl(sockfd, F_GETFL, 0);
fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
```

## Non-blocking Operations

### Non-blocking Accept

```python
import socket
import errno

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.setblocking(False)
server.bind(('localhost', 8080))
server.listen(5)

while True:
    try:
        client, addr = server.accept()
        print(f"New connection from {addr}")
        client.setblocking(False)
        # Handle client
    except socket.error as e:
        if e.errno == errno.EAGAIN or e.errno == errno.EWOULDBLOCK:
            # No connection waiting, continue
            continue
        else:
            raise
```

### Non-blocking Receive

```python
def non_blocking_recv(client, buffer_size=1024):
    """Receive data in non-blocking mode."""
    try:
        data = client.recv(buffer_size)
        if data:
            return data
        else:
            # Connection closed
            return None
    except socket.error as e:
        if e.errno == errno.EAGAIN or e.errno == errno.EWOULDBLOCK:
            # No data available
            return b''  # Empty bytes, but connection still open
        else:
            raise
```

### Non-blocking Send

```python
def non_blocking_send(client, data):
    """Send data in non-blocking mode."""
    try:
        sent = client.send(data)
        return sent  # May be less than len(data)
    except socket.error as e:
        if e.errno == errno.EAGAIN or e.errno == errno.EWOULDBLOCK:
            # Send buffer full, try again later
            return 0
        else:
            raise
```

## Handling Multiple Non-blocking Sockets

### Busy Loop (Not Recommended)

```python
clients = [client1, client2, client3]

while True:
    for client in clients:
        try:
            data = client.recv(1024)
            if data:
                process_data(client, data)
        except socket.error as e:
            if e.errno not in (errno.EAGAIN, errno.EWOULDBLOCK):
                # Real error
                clients.remove(client)
    # CPU intensive - constantly checking!
```

**Problem**: High CPU usage, constantly checking sockets.

### Using select() (Better)

```python
import select

readable, writable, exceptional = select.select(
    clients,  # Sockets to check for read
    [],       # Sockets to check for write
    clients,  # Sockets to check for errors
    1.0       # Timeout in seconds
)

for client in readable:
    data = client.recv(1024)
    if data:
        process_data(client, data)
```

See module on select() for details.

## Complete Non-blocking Server Example

```python
import socket
import errno
import select

class NonBlockingServer:
    def __init__(self, host='localhost', port=8080):
        self.host = host
        self.port = port
        self.server = None
        self.clients = []
        self.outputs = []
        self.message_queues = {}
    
    def start(self):
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.server.setblocking(False)
        self.server.bind((self.host, self.port))
        self.server.listen(5)
        
        print(f"Non-blocking server on {self.host}:{self.port}")
        
        inputs = [self.server]
        
        while inputs:
            readable, writable, exceptional = select.select(
                inputs, self.outputs, inputs, 0.1
            )
            
            # Handle readable
            for sock in readable:
                if sock is self.server:
                    # New connection
                    try:
                        client, addr = self.server.accept()
                        client.setblocking(False)
                        inputs.append(client)
                        self.clients.append(client)
                        self.message_queues[client] = []
                        print(f"New connection from {addr}")
                    except socket.error:
                        pass
                else:
                    # Existing client
                    try:
                        data = sock.recv(1024)
                        if data:
                            # Echo back
                            self.message_queues[sock].append(data)
                            if sock not in self.outputs:
                                self.outputs.append(sock)
                        else:
                            # Connection closed
                            self.close_client(sock, inputs)
                    except socket.error:
                        self.close_client(sock, inputs)
            
            # Handle writable
            for sock in writable:
                try:
                    if self.message_queues[sock]:
                        data = self.message_queues[sock].pop(0)
                        sock.send(data)
                    else:
                        self.outputs.remove(sock)
                except socket.error:
                    self.close_client(sock, inputs)
            
            # Handle exceptional
            for sock in exceptional:
                self.close_client(sock, inputs)
    
    def close_client(self, sock, inputs):
        if sock in inputs:
            inputs.remove(sock)
        if sock in self.outputs:
            self.outputs.remove(sock)
        if sock in self.clients:
            self.clients.remove(sock)
        if sock in self.message_queues:
            del self.message_queues[sock]
        sock.close()
```

## Common Patterns

### Check if Data Available

```python
def has_data(sock):
    """Check if socket has data ready to read."""
    readable, _, _ = select.select([sock], [], [], 0.0)
    return sock in readable
```

### Wait for Data with Timeout

```python
def wait_for_data(sock, timeout=1.0):
    """Wait for data with timeout."""
    readable, _, _ = select.select([sock], [], [], timeout)
    return sock in readable
```

## Advantages and Disadvantages

### Advantages

- ✅ Efficient resource usage
- ✅ Single thread handles many connections
- ✅ Responsive to multiple operations
- ✅ No context switching overhead

### Disadvantages

- ❌ More complex code
- ❌ Must handle EAGAIN/EWOULDBLOCK
- ❌ Need select/poll/epoll for efficiency
- ❌ Harder to debug

## Best Practices

1. **Use select/poll/epoll** instead of busy loops
2. **Handle EAGAIN/EWOULDBLOCK** properly
3. **Set appropriate timeouts** when needed
4. **Track send buffers** for partial sends
5. **Use async frameworks** (asyncio) for complex applications

## When to Use Non-blocking I/O

✅ **Use when:**
- Handling many concurrent connections
- Need responsive server
- Building event-driven applications
- CPU-bound operations mixed with I/O

❌ **Avoid when:**
- Simple applications
- Few connections
- Want simplicity over performance

---

**Key Takeaway**: Non-blocking I/O allows handling multiple sockets in a single thread efficiently. Use with select/poll/epoll to avoid busy loops, and always handle EAGAIN/EWOULDBLOCK errors.

