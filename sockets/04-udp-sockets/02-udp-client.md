# UDP Client Implementation

UDP clients are simpler than TCP clients since no connection is required. This module covers building UDP clients.

## Basic UDP Client

```python
import socket

# Create UDP socket
client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Send data (no connection needed)
message = "Hello, Server!"
server_address = ('localhost', 8080)
client.sendto(message.encode(), server_address)

# Receive response
data, server_addr = client.recvfrom(1024)
print(f"Response: {data.decode()}")

# Close socket
client.close()
```

## Complete UDP Client Example

```python
import socket

def udp_client(host='localhost', port=8080):
    """Simple UDP client."""
    
    client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    
    try:
        server_address = (host, port)
        
        # Send message
        message = "Hello, UDP Server!"
        print(f"Sending to {server_address}: {message}")
        client.sendto(message.encode(), server_address)
        
        # Receive response (with timeout)
        client.settimeout(5.0)
        try:
            data, address = client.recvfrom(1024)
            print(f"Received from {address}: {data.decode()}")
        except socket.timeout:
            print("Timeout waiting for response")
    
    except Exception as e:
        print(f"Error: {e}")
    finally:
        client.close()

if __name__ == '__main__':
    udp_client()
```

## Interactive UDP Client

```python
import socket

def interactive_udp_client(host='localhost', port=8080):
    """Interactive UDP client for sending multiple messages."""
    
    client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    client.settimeout(5.0)
    server_address = (host, port)
    
    print(f"UDP client ready. Sending to {host}:{port}")
    print("Type messages (or 'quit' to exit)")
    
    try:
        while True:
            message = input("> ")
            
            if message.lower() in ('quit', 'exit', 'q'):
                break
            
            if not message:
                continue
            
            # Send message
            try:
                client.sendto(message.encode(), server_address)
                print(f"Sent: {message}")
                
                # Receive response
                try:
                    data, addr = client.recvfrom(1024)
                    print(f"Response: {data.decode()}")
                except socket.timeout:
                    print("No response received (timeout)")
            
            except Exception as e:
                print(f"Error: {e}")
    
    except KeyboardInterrupt:
        print("\nExiting...")
    finally:
        client.close()

if __name__ == '__main__':
    interactive_udp_client()
```

## UDP Client with Retry Logic

```python
import socket
import time

def udp_client_with_retry(host='localhost', port=8080, max_retries=3):
    """UDP client with retry logic for reliability."""
    
    client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    client.settimeout(2.0)
    server_address = (host, port)
    
    message = "Hello, Server!"
    
    for attempt in range(max_retries):
        try:
            # Send message
            client.sendto(message.encode(), server_address)
            print(f"Attempt {attempt + 1}: Sent message")
            
            # Wait for response
            try:
                data, addr = client.recvfrom(1024)
                print(f"Received response: {data.decode()}")
                return  # Success
            except socket.timeout:
                print(f"Attempt {attempt + 1}: No response")
                if attempt < max_retries - 1:
                    time.sleep(1)  # Wait before retry
                    continue
        
        except Exception as e:
            print(f"Error on attempt {attempt + 1}: {e}")
            if attempt < max_retries - 1:
                time.sleep(1)
                continue
    
    print("Max retries reached. Giving up.")
    client.close()

if __name__ == '__main__':
    udp_client_with_retry()
```

## Broadcasting Client

UDP clients can send broadcast messages to all devices on the network:

```python
import socket

def broadcast_client(message="Hello, everyone!", port=8080):
    """UDP client that broadcasts a message."""
    
    client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    
    # Enable broadcast
    client.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    
    # Broadcast address (sends to all devices on local network)
    broadcast_address = ('255.255.255.255', port)
    
    try:
        print(f"Broadcasting: {message}")
        client.sendto(message.encode(), broadcast_address)
        print("Broadcast sent")
        
        # Listen for responses
        client.settimeout(5.0)
        responses = []
        
        while True:
            try:
                data, addr = client.recvfrom(1024)
                responses.append((addr, data.decode()))
                print(f"Response from {addr}: {data.decode()}")
            except socket.timeout:
                break
        
        print(f"\nReceived {len(responses)} responses")
        
    except Exception as e:
        print(f"Error: {e}")
    finally:
        client.close()

if __name__ == '__main__':
    broadcast_client()
```

## Key Differences from TCP Client

### No connect() Call

```python
# TCP: Must connect first
tcp_client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
tcp_client.connect(('localhost', 8080))
tcp_client.send(data)

# UDP: Send directly with sendto()
udp_client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
udp_client.sendto(data, ('localhost', 8080))
```

### Must Specify Address Each Time

```python
# TCP: Address specified once in connect()
tcp_client.connect(('localhost', 8080))
tcp_client.send(data)  # No address needed

# UDP: Address needed for each sendto()
udp_client.sendto(data, ('localhost', 8080))  # Address required
```

### recvfrom() Returns Address

```python
# TCP: recv() returns only data
data = tcp_client.recv(1024)

# UDP: recvfrom() returns data and sender address
data, address = udp_client.recvfrom(1024)
```

## Error Handling

UDP clients need to handle:
- Timeouts (server might not respond)
- Lost datagrams (no delivery guarantee)
- Wrong server address

```python
import socket

def robust_udp_client(host='localhost', port=8080):
    """UDP client with comprehensive error handling."""
    
    client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    client.settimeout(5.0)
    
    server_address = (host, port)
    message = "Hello, Server!"
    
    try:
        # Resolve hostname
        try:
            socket.gethostbyname(host)
        except socket.gaierror:
            print(f"Error: Cannot resolve hostname '{host}'")
            return
        
        # Send message
        try:
            client.sendto(message.encode(), server_address)
            print(f"Sent to {server_address}: {message}")
        except OSError as e:
            print(f"Error sending: {e}")
            return
        
        # Receive response
        try:
            data, addr = client.recvfrom(1024)
            
            # Verify response is from expected server
            if addr[0] == socket.gethostbyname(host):
                print(f"Response from {addr}: {data.decode()}")
            else:
                print(f"Warning: Response from unexpected address {addr}")
        
        except socket.timeout:
            print("Timeout: No response received")
            print("Possible reasons:")
            print("  - Server is not running")
            print("  - Firewall blocking")
            print("  - Datagram lost in transit")
        
        except Exception as e:
            print(f"Error receiving: {e}")
    
    except Exception as e:
        print(f"Unexpected error: {e}")
    
    finally:
        client.close()

if __name__ == '__main__':
    robust_udp_client()
```

## Testing UDP Client

Test your UDP client with netcat:

```bash
# Terminal 1: Start UDP server with netcat
nc -u -l 8080

# Terminal 2: Run your UDP client
python udp_client.py
```

Or use Python server:

```bash
# Terminal 1: Start Python UDP server
python examples/python/03-basic-udp-server.py

# Terminal 2: Run your UDP client
python examples/python/04-basic-udp-client.py
```

---

**Key Takeaway**: UDP clients are simpler than TCP (no connection needed), but require handling timeouts and potential datagram loss. Always specify destination address in sendto() and use recvfrom() to get sender address.

