# TCP Server Implementation

TCP servers are connection-oriented and provide reliable, ordered communication. This module teaches you how to build a TCP server from scratch.

## Basic TCP Server Structure

A TCP server follows this pattern:

1. Create socket
2. Bind to address
3. Listen for connections
4. Accept connections (loop)
5. Handle client communication
6. Close connections

## Minimal TCP Server

```python
import socket

# Create TCP socket
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind to localhost, port 8080
server.bind(('localhost', 8080))

# Listen for connections (max 5 pending)
server.listen(5)

print("Server listening on port 8080...")

# Accept one connection
client, address = server.accept()
print(f"Connection from {address}")

# Receive data
data = client.recv(1024)
print(f"Received: {data.decode()}")

# Send response
client.send(b"Message received!")

# Close client connection
client.close()

# Close server
server.close()
```

## Single-Client Server (Basic Loop)

```python
import socket

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server.bind(('localhost', 8080))
server.listen(5)

print("Server listening on port 8080...")

try:
    while True:
        # Accept connection (blocks until client connects)
        client, address = server.accept()
        print(f"Connection from {address}")
        
        try:
            # Handle client
            while True:
                data = client.recv(1024)
                if not data:  # Client closed connection
                    break
                
                print(f"Received: {data.decode()}")
                response = f"Echo: {data.decode()}".encode()
                client.send(response)
        
        except Exception as e:
            print(f"Error handling client: {e}")
        
        finally:
            client.close()
            print(f"Connection to {address} closed")

except KeyboardInterrupt:
    print("\nServer shutting down...")
finally:
    server.close()
```

## Echo Server (Complete Example)

An echo server receives data and sends it back:

```python
import socket

def echo_server(host='localhost', port=8080):
    """Simple echo server that sends received data back to client."""
    
    # Create socket
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    
    try:
        # Bind to address
        server.bind((host, port))
        
        # Listen
        server.listen(5)
        print(f"Echo server listening on {host}:{port}")
        
        while True:
            # Accept connection
            client, address = server.accept()
            print(f"Connection from {address}")
            
            try:
                while True:
                    # Receive data
                    data = client.recv(1024)
                    
                    if not data:
                        print(f"Client {address} closed connection")
                        break
                    
                    print(f"Received: {data.decode()}")
                    
                    # Echo back
                    client.send(data)
            
            except socket.error as e:
                print(f"Socket error: {e}")
            
            finally:
                client.close()
    
    except Exception as e:
        print(f"Server error: {e}")
    
    finally:
        server.close()

if __name__ == '__main__':
    echo_server()
```

## Server with Error Handling

```python
import socket
import sys

def robust_tcp_server(host='localhost', port=8080):
    """TCP server with comprehensive error handling."""
    
    server = None
    
    try:
        # Create socket
        server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        
        # Bind
        try:
            server.bind((host, port))
        except OSError as e:
            print(f"Error binding to {host}:{port}: {e}")
            sys.exit(1)
        
        # Listen
        server.listen(5)
        print(f"Server listening on {host}:{port}")
        
        while True:
            try:
                # Accept (with timeout)
                server.settimeout(1.0)  # Check for interrupt every second
                client, address = server.accept()
                server.settimeout(None)  # Remove timeout
                
                print(f"Connection from {address}")
                handle_client(client, address)
            
            except socket.timeout:
                # Timeout is okay, continue loop
                continue
            
            except KeyboardInterrupt:
                print("\nShutting down server...")
                break
            
            except Exception as e:
                print(f"Error accepting connection: {e}")
                continue

    except Exception as e:
        print(f"Fatal server error: {e}")
    
    finally:
        if server:
            server.close()
        print("Server closed")

def handle_client(client, address):
    """Handle communication with a single client."""
    try:
        while True:
            data = client.recv(1024)
            
            if not data:
                print(f"Client {address} disconnected")
                break
            
            # Process data
            response = process_request(data)
            
            # Send response
            try:
                client.sendall(response)  # sendall ensures all data is sent
            except socket.error:
                print(f"Error sending to {address}")
                break
    
    except socket.error as e:
        print(f"Socket error with {address}: {e}")
    
    finally:
        client.close()

def process_request(data):
    """Process incoming data and generate response."""
    try:
        message = data.decode('utf-8')
        print(f"Processing: {message}")
        return f"Response: {message.upper()}".encode('utf-8')
    except UnicodeDecodeError:
        return b"Error: Invalid UTF-8 encoding"

if __name__ == '__main__':
    robust_tcp_server()
```

## Key Concepts

### SO_REUSEADDR Option

Allows binding to an address that's in TIME_WAIT state:

```python
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
```

**Why needed**: After closing, socket enters TIME_WAIT (typically 30-120 seconds). Without this option, you can't immediately rebind to the same port.

### Backlog Parameter

```python
server.listen(5)
```

**Meaning**: Maximum number of pending connections in queue.

- Connections arrive faster than you can accept() them
- OS queues them up to backlog limit
- Exceeding backlog → new connections refused
- Common values: 5-128

### send() vs sendall()

**send()**: May not send all data
```python
bytes_sent = client.send(data)  # May be less than len(data)
```

**sendall()**: Sends all data, retries if needed
```python
client.sendall(data)  # Guarantees all data sent or raises exception
```

### recv() Behavior

```python
data = client.recv(1024)
```

- **Blocks** until data arrives or connection closes
- **Returns empty bytes** (`b''`) when connection closed
- **May return less** than requested (check length)
- **1024** is buffer size, not guaranteed amount

## Handling Multiple Clients

### Sequential (One at a Time)

```python
while True:
    client, addr = server.accept()
    handle_client(client, addr)  # Blocks until client disconnects
    # Next client waits until current client finishes
```

**Problem**: Only handles one client at a time.

### Concurrent (Multiple at Once)

See next module: "Handling Multiple Clients" for:
- Threading
- Multiprocessing
- Async/await
- Select/poll/epoll

## Common Issues and Solutions

### Issue 1: "Address already in use"

**Cause**: Port still in use (TIME_WAIT state)

**Solution**:
```python
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
```

### Issue 2: "Connection reset by peer"

**Cause**: Client closed connection unexpectedly

**Solution**: Check for empty recv()
```python
data = client.recv(1024)
if not data:
    break  # Client closed
```

### Issue 3: Incomplete data

**Cause**: TCP is stream, not message-based

**Solution**: Implement message framing
```python
# Send length prefix
length = len(data).to_bytes(4, 'big')
client.sendall(length + data)

# Receive with length
length_bytes = client.recv(4)
if len(length_bytes) != 4:
    break
length = int.from_bytes(length_bytes, 'big')
data = recv_all(client, length)
```

### Issue 4: Server hangs on recv()

**Cause**: Client doesn't send data or closes without sending FIN

**Solution**: Set timeout
```python
client.settimeout(30.0)  # 30 second timeout
```

## Testing Your Server

### Using telnet

```bash
telnet localhost 8080
```

### Using netcat (nc)

```bash
nc localhost 8080
```

### Using Python client

```python
import socket

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(('localhost', 8080))
client.send(b"Hello, Server!")
response = client.recv(1024)
print(response.decode())
client.close()
```

---

**Key Takeaway**: A TCP server creates a listening socket, accepts connections, and handles client communication. Proper error handling and understanding TCP's stream nature are essential for robust servers.

