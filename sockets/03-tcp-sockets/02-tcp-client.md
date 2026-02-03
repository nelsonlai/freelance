# TCP Client Implementation

TCP clients initiate connections to servers and communicate over reliable, ordered connections. This module covers building TCP clients.

## Basic TCP Client Structure

A TCP client follows this pattern:

1. Create socket
2. Connect to server
3. Send/receive data
4. Close connection

## Minimal TCP Client

```python
import socket

# Create TCP socket
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect to server
client.connect(('localhost', 8080))

# Send data
client.send(b"Hello, Server!")

# Receive response
response = client.recv(1024)
print(f"Response: {response.decode()}")

# Close connection
client.close()
```

## Complete TCP Client Example

```python
import socket
import sys

def tcp_client(host='localhost', port=8080):
    """Simple TCP client that sends a message and receives response."""
    
    client = None
    
    try:
        # Create socket
        client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        
        # Connect to server
        print(f"Connecting to {host}:{port}...")
        try:
            client.connect((host, port))
            print("Connected!")
        except ConnectionRefusedError:
            print(f"Error: Connection refused. Is server running on {host}:{port}?")
            sys.exit(1)
        except socket.gaierror:
            print(f"Error: Could not resolve hostname '{host}'")
            sys.exit(1)
        
        # Send message
        message = "Hello, Server!"
        client.sendall(message.encode())
        print(f"Sent: {message}")
        
        # Receive response
        response = client.recv(1024)
        if response:
            print(f"Received: {response.decode()}")
        else:
            print("Server closed connection")
        
    except Exception as e:
        print(f"Error: {e}")
    
    finally:
        if client:
            client.close()
        print("Connection closed")

if __name__ == '__main__':
    tcp_client()
```

## Interactive Client (Send Multiple Messages)

```python
import socket
import sys

def interactive_client(host='localhost', port=8080):
    """Interactive TCP client for sending multiple messages."""
    
    client = None
    
    try:
        client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client.settimeout(5.0)  # 5 second timeout
        
        # Connect
        try:
            client.connect((host, port))
            print(f"Connected to {host}:{port}")
            print("Type messages (or 'quit' to exit)")
        except Exception as e:
            print(f"Connection failed: {e}")
            return
        
        # Interactive loop
        while True:
            try:
                # Get user input
                message = input("> ")
                
                if message.lower() in ('quit', 'exit', 'q'):
                    break
                
                if not message:
                    continue
                
                # Send message
                client.sendall(message.encode())
                
                # Receive response
                try:
                    response = client.recv(1024)
                    if response:
                        print(f"Server: {response.decode()}")
                    else:
                        print("Server closed connection")
                        break
                except socket.timeout:
                    print("Timeout waiting for response")
                
            except KeyboardInterrupt:
                break
            except Exception as e:
                print(f"Error: {e}")
                break
    
    except Exception as e:
        print(f"Fatal error: {e}")
    
    finally:
        if client:
            client.close()
        print("Disconnected")

if __name__ == '__main__':
    interactive_client()
```

## Client with Request-Response Pattern

```python
import socket
import json

def request_response_client(host='localhost', port=8080):
    """Client that sends JSON requests and receives JSON responses."""
    
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    try:
        client.connect((host, port))
        
        # Send JSON request
        request = {
            "command": "get_status",
            "timestamp": "2024-01-01T12:00:00"
        }
        
        # Encode: length prefix + JSON data
        json_data = json.dumps(request).encode()
        length = len(json_data).to_bytes(4, 'big')
        
        client.sendall(length + json_data)
        print(f"Sent request: {request}")
        
        # Receive response with length prefix
        length_bytes = client.recv(4)
        if len(length_bytes) != 4:
            raise ValueError("Invalid response header")
        
        length = int.from_bytes(length_bytes, 'big')
        response_data = recv_all(client, length)
        
        response = json.loads(response_data.decode())
        print(f"Received response: {response}")
        
    except Exception as e:
        print(f"Error: {e}")
    finally:
        client.close()

def recv_all(sock, size):
    """Receive exactly 'size' bytes."""
    data = b''
    while len(data) < size:
        chunk = sock.recv(size - len(data))
        if not chunk:
            raise ConnectionError("Connection closed before receiving all data")
        data += chunk
    return data

if __name__ == '__main__':
    request_response_client()
```

## File Transfer Client

```python
import socket
import os

def file_transfer_client(host='localhost', port=8080, filename='example.txt'):
    """Client that sends a file to server."""
    
    if not os.path.exists(filename):
        print(f"Error: File '{filename}' not found")
        return
    
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    try:
        client.connect((host, port))
        
        # Send filename
        client.sendall(filename.encode() + b'\n')
        
        # Send file size
        file_size = os.path.getsize(filename)
        client.sendall(file_size.to_bytes(8, 'big'))
        
        # Send file data
        with open(filename, 'rb') as f:
            while True:
                chunk = f.read(4096)  # 4KB chunks
                if not chunk:
                    break
                client.sendall(chunk)
        
        print(f"File '{filename}' sent successfully ({file_size} bytes)")
        
        # Receive confirmation
        response = client.recv(1024)
        print(f"Server response: {response.decode()}")
        
    except Exception as e:
        print(f"Error: {e}")
    finally:
        client.close()

if __name__ == '__main__':
    file_transfer_client('localhost', 8080, 'example.txt')
```

## Connection Retry Logic

```python
import socket
import time

def resilient_client(host='localhost', port=8080, max_retries=3, retry_delay=2):
    """Client with automatic retry on connection failure."""
    
    client = None
    
    for attempt in range(max_retries):
        try:
            client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            client.settimeout(5.0)
            
            print(f"Attempting connection (attempt {attempt + 1}/{max_retries})...")
            client.connect((host, port))
            print("Connected!")
            
            # Use connection
            client.sendall(b"Hello!")
            response = client.recv(1024)
            print(f"Response: {response.decode()}")
            
            return  # Success, exit function
        
        except (ConnectionRefusedError, socket.timeout, OSError) as e:
            print(f"Connection attempt {attempt + 1} failed: {e}")
            if client:
                client.close()
            
            if attempt < max_retries - 1:
                print(f"Retrying in {retry_delay} seconds...")
                time.sleep(retry_delay)
            else:
                print("Max retries reached. Giving up.")
                return
    
    if client:
        client.close()

if __name__ == '__main__':
    resilient_client()
```

## Client Connection States

### Connecting

```python
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# Socket created but not connected

client.connect(('localhost', 8080))
# Socket now connected
```

### Checking Connection State

```python
# Get socket state (platform-specific)
import socket

def is_connected(sock):
    """Check if socket is connected."""
    try:
        # Try to get peer address
        sock.getpeername()
        return True
    except socket.error:
        return False

# Usage
if is_connected(client):
    print("Connected")
else:
    print("Not connected")
```

## Error Handling

### Common Errors

1. **ConnectionRefusedError**
   - Server not running or not listening
   - Solution: Ensure server is running

2. **socket.gaierror**
   - Hostname resolution failed
   - Solution: Check hostname/IP address

3. **socket.timeout**
   - Connection timed out
   - Solution: Check network, firewall, server

4. **OSError: [Errno 61] Connection refused**
   - Server refused connection
   - Solution: Server might be down or firewall blocking

### Comprehensive Error Handling

```python
import socket

def safe_connect(host, port):
    """Connect with comprehensive error handling."""
    
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.settimeout(10.0)
    
    try:
        client.connect((host, port))
        return client
    
    except socket.timeout:
        print("Connection timeout - server not responding")
        client.close()
        return None
    
    except ConnectionRefusedError:
        print(f"Connection refused - server at {host}:{port} not accepting connections")
        client.close()
        return None
    
    except socket.gaierror as e:
        print(f"DNS resolution failed - {e}")
        client.close()
        return None
    
    except OSError as e:
        print(f"Network error - {e}")
        client.close()
        return None
    
    except Exception as e:
        print(f"Unexpected error - {e}")
        client.close()
        return None
```

## Best Practices

### 1. Always Close Connections

```python
# Good
client = socket.socket(...)
try:
    client.connect(...)
    # use client
finally:
    client.close()

# Better: Use context manager (Python 3.3+)
with socket.socket(...) as client:
    client.connect(...)
    # use client
    # automatically closed
```

### 2. Use sendall() Instead of send()

```python
# May not send all data
client.send(data)

# Guarantees all data sent
client.sendall(data)
```

### 3. Handle Partial Receives

```python
# Bad: Assumes all data received
data = client.recv(1024)

# Good: Loop until all data received
data = recv_all(client, expected_size)
```

### 4. Set Timeouts

```python
client.settimeout(30.0)  # 30 second timeout
```

### 5. Use try-finally

```python
client = None
try:
    client = socket.socket(...)
    # use client
finally:
    if client:
        client.close()
```

## Testing Your Client

Test with different servers:

```python
# Test with echo server
tcp_client('localhost', 8080)

# Test with web server
import socket
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(('www.google.com', 80))
client.sendall(b"GET / HTTP/1.1\r\nHost: www.google.com\r\n\r\n")
response = client.recv(4096)
print(response.decode())
client.close()
```

---

**Key Takeaway**: A TCP client creates a socket, connects to a server, communicates, and closes. Proper error handling, timeouts, and connection management are essential for robust clients.

