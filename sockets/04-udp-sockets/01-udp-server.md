# UDP Server Implementation

UDP (User Datagram Protocol) is connectionless and provides fast, low-overhead communication. This module covers building UDP servers.

## UDP vs TCP Key Differences

| Feature | TCP | UDP |
|---------|-----|-----|
| Connection | Required | Not needed |
| Reliability | Guaranteed | Best effort |
| Ordering | Guaranteed | Not guaranteed |
| Speed | Slower | Faster |
| Use case | Files, web | Gaming, streaming |

## Basic UDP Server

```python
import socket

# Create UDP socket
server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Bind to address
server.bind(('localhost', 8080))

print("UDP server listening on port 8080...")

# Receive and send
while True:
    # Receive data and client address
    data, client_address = server.recvfrom(1024)
    
    print(f"Received from {client_address}: {data.decode()}")
    
    # Send response back
    response = f"Echo: {data.decode()}".encode()
    server.sendto(response, client_address)
```

## Complete UDP Server Example

```python
import socket

def udp_server(host='localhost', port=8080):
    """Simple UDP echo server."""
    
    # Create UDP socket
    server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    
    try:
        # Bind to address
        server.bind((host, port))
        print(f"UDP server listening on {host}:{port}")
        
        while True:
            # Receive datagram
            data, client_address = server.recvfrom(1024)
            
            print(f"Received from {client_address}: {data.decode()}")
            
            # Process data
            response = process_message(data)
            
            # Send response
            server.sendto(response, client_address)
            print(f"Sent response to {client_address}")
    
    except KeyboardInterrupt:
        print("\nShutting down server...")
    except Exception as e:
        print(f"Error: {e}")
    finally:
        server.close()

def process_message(data):
    """Process incoming message and generate response."""
    try:
        message = data.decode('utf-8')
        return f"Response: {message.upper()}".encode('utf-8')
    except UnicodeDecodeError:
        return b"Error: Invalid encoding"

if __name__ == '__main__':
    udp_server()
```

## UDP Server with Error Handling

```python
import socket
import logging

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

def robust_udp_server(host='localhost', port=8080, buffer_size=1024):
    """UDP server with comprehensive error handling."""
    
    server = None
    
    try:
        server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        
        # Bind
        try:
            server.bind((host, port))
        except OSError as e:
            if e.errno == 48:  # Address already in use
                logger.error(f"Port {port} already in use")
                return
            raise
        
        logger.info(f"UDP server listening on {host}:{port}")
        
        while True:
            try:
                # Receive datagram
                data, client_address = server.recvfrom(buffer_size)
                
                logger.info(f"Received {len(data)} bytes from {client_address}")
                
                # Process message
                try:
                    response = process_message(data)
                    
                    # Send response
                    server.sendto(response, client_address)
                    logger.info(f"Sent response to {client_address}")
                
                except Exception as e:
                    logger.error(f"Error processing message: {e}")
                    error_response = b"Error processing request"
                    server.sendto(error_response, client_address)
            
            except socket.error as e:
                logger.error(f"Socket error: {e}")
                continue
            
            except KeyboardInterrupt:
                logger.info("Shutting down server...")
                break
    
    except Exception as e:
        logger.error(f"Fatal error: {e}")
    
    finally:
        if server:
            server.close()
        logger.info("Server closed")

def process_message(data):
    """Process incoming message."""
    return data.upper()

if __name__ == '__main__':
    robust_udp_server()
```

## Handling Large Datagrams

UDP has a maximum datagram size (typically 65507 bytes for IPv4). For larger data:

### Option 1: Split into Multiple Datagrams

```python
def send_large_data(sock, data, address, chunk_size=1024):
    """Send large data in multiple UDP datagrams."""
    
    # Send number of chunks first
    num_chunks = (len(data) + chunk_size - 1) // chunk_size
    sock.sendto(num_chunks.to_bytes(4, 'big'), address)
    
    # Send chunks
    for i in range(num_chunks):
        start = i * chunk_size
        end = start + chunk_size
        chunk = data[start:end]
        
        # Prefix with chunk number
        header = i.to_bytes(4, 'big')
        sock.sendto(header + chunk, address)

def receive_large_data(sock):
    """Receive large data from multiple UDP datagrams."""
    
    # Receive number of chunks
    data, address = sock.recvfrom(4)
    num_chunks = int.from_bytes(data, 'big')
    
    # Receive chunks
    chunks = {}
    while len(chunks) < num_chunks:
        data, addr = sock.recvfrom(1024 + 4)  # chunk + header
        
        if addr != address:
            continue  # Ignore data from different source
        
        chunk_num = int.from_bytes(data[:4], 'big')
        chunk_data = data[4:]
        chunks[chunk_num] = chunk_data
    
    # Reassemble
    result = b''.join(chunks[i] for i in range(num_chunks))
    return result, address
```

**Note**: UDP doesn't guarantee order, so chunk reassembly may need more sophisticated logic.

### Option 2: Use TCP for Large Data

For reliable large data transfer, consider TCP instead of UDP.

## Stateless Request Handling

UDP servers are naturally stateless:

```python
def stateless_udp_server(host='localhost', port=8080):
    """Stateless UDP server - each request is independent."""
    
    server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server.bind((host, port))
    
    print(f"Stateless UDP server on {host}:{port}")
    
    while True:
        data, client_address = server.recvfrom(1024)
        
        # Each request is independent - no state tracking
        try:
            request = data.decode()
            response = handle_request(request)
            server.sendto(response.encode(), client_address)
        except Exception as e:
            error_msg = f"Error: {e}".encode()
            server.sendto(error_msg, client_address)

def handle_request(request):
    """Handle a single request (stateless)."""
    # No memory of previous requests
    if request == "TIME":
        import datetime
        return datetime.datetime.now().isoformat()
    elif request.startswith("ECHO "):
        return request[5:]  # Return everything after "ECHO "
    else:
        return "Unknown command"
```

## Broadcast Server

UDP supports broadcasting (sending to all devices on network):

```python
def broadcast_server(port=8080):
    """UDP server that can respond to broadcast requests."""
    
    server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    
    # Enable broadcast receiving
    server.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    
    # Bind to all interfaces
    server.bind(('', port))  # Empty string = all interfaces
    
    print(f"Broadcast UDP server on port {port}")
    
    while True:
        data, client_address = server.recvfrom(1024)
        
        print(f"Received from {client_address}: {data.decode()}")
        
        # Respond to broadcast or unicast
        response = b"Server response"
        server.sendto(response, client_address)
```

## Timeout Handling

Set timeout to make server responsive to interrupts:

```python
def udp_server_with_timeout(host='localhost', port=8080):
    """UDP server with timeout for graceful shutdown."""
    
    server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server.bind((host, port))
    server.settimeout(1.0)  # 1 second timeout
    
    print(f"UDP server on {host}:{port}")
    
    while True:
        try:
            data, address = server.recvfrom(1024)
            print(f"Received: {data.decode()}")
            server.sendto(b"Response", address)
        
        except socket.timeout:
            # Timeout is expected, continue loop
            continue
        
        except KeyboardInterrupt:
            print("\nShutting down...")
            break
    
    server.close()
```

## Key Concepts

### recvfrom() Returns Address

Unlike TCP `recv()`, UDP `recvfrom()` returns both data and sender address:

```python
data, address = server.recvfrom(1024)
# address is tuple: (ip, port)
```

### sendto() Requires Address

UDP `sendto()` needs destination address (unlike TCP `send()`):

```python
server.sendto(data, ('192.168.1.100', 8080))
```

### No Connection State

UDP has no connection, so:
- No `listen()` or `accept()` needed
- No connection tracking
- Each datagram is independent
- Can receive from any client

### Message Boundaries

UDP preserves message boundaries:
- Each `recvfrom()` gets one complete datagram
- Unlike TCP's byte stream

## Common Issues

### Issue: Datagram Too Large

**Error**: `Message too long`

**Solution**: Split into smaller datagrams or use TCP

### Issue: Lost Datagrams

**Problem**: UDP doesn't guarantee delivery

**Solution**: 
- Implement application-level acknowledgments
- Use TCP if reliability needed
- Accept loss for real-time apps

### Issue: Out-of-Order Delivery

**Problem**: Datagrams may arrive out of order

**Solution**: Add sequence numbers to messages

---

**Key Takeaway**: UDP servers are simpler than TCP (no connections) but require handling of lost/delayed datagrams. Use UDP when speed and low latency matter more than reliability.

