# TCP Error Handling

Robust error handling is crucial for production socket applications. This module covers common errors and how to handle them properly.

## Common Socket Errors

### Connection Errors

#### ConnectionRefusedError

**Occurs when**: Server not listening or rejecting connections

```python
try:
    client.connect(('localhost', 8080))
except ConnectionRefusedError:
    print("Server not accepting connections")
    # Handle: retry, notify user, fallback
```

**Solutions**:
- Check if server is running
- Verify port number
- Check firewall settings
- Implement retry logic

#### ConnectionResetError

**Occurs when**: Remote side forcibly closed connection

```python
try:
    data = client.recv(1024)
except ConnectionResetError:
    print("Connection reset by peer")
    # Handle: cleanup, reconnect if needed
```

**Solutions**:
- Gracefully close local socket
- Handle reconnection logic
- Log error for debugging

#### ConnectionAbortedError

**Occurs when**: Connection aborted locally (software caused)

```python
try:
    client.send(data)
except ConnectionAbortedError:
    print("Connection aborted")
```

**Solutions**:
- Check for local network issues
- Verify socket is still valid

#### TimeoutError

**Occurs when**: Operation exceeds timeout period

```python
client.settimeout(5.0)
try:
    client.connect(('localhost', 8080))
except TimeoutError:
    print("Connection timed out")
```

**Solutions**:
- Increase timeout value
- Check network connectivity
- Implement retry with backoff

### Address Resolution Errors

#### socket.gaierror

**Occurs when**: Hostname cannot be resolved to IP address

```python
try:
    client.connect(('invalid-hostname.com', 80))
except socket.gaierror as e:
    print(f"DNS resolution failed: {e}")
```

**Solutions**:
- Verify hostname spelling
- Check DNS configuration
- Use IP address instead of hostname
- Provide fallback addresses

### Binding Errors

#### OSError: [Errno 48] Address already in use

**Occurs when**: Port already bound by another process

```python
try:
    server.bind(('localhost', 8080))
except OSError as e:
    if e.errno == 48:  # Address already in use
        print("Port 8080 already in use")
        # Solutions:
        # 1. Use SO_REUSEADDR
        # 2. Choose different port
        # 3. Stop conflicting process
```

**Solutions**:
```python
# Set SO_REUSEADDR before bind
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server.bind(('localhost', 8080))
```

#### OSError: [Errno 13] Permission denied

**Occurs when**: Binding to privileged port (< 1024) without root/admin

```python
try:
    server.bind(('localhost', 80))  # Privileged port
except PermissionError:
    print("Need root/admin privileges for port < 1024")
    # Use port >= 1024 instead
```

**Solutions**:
- Use port >= 1024
- Run with elevated privileges (not recommended)
- Use reverse proxy (nginx, etc.)

### Data Transfer Errors

#### BrokenPipeError

**Occurs when**: Trying to send data to closed connection

```python
try:
    client.send(data)
except BrokenPipeError:
    print("Connection closed")
    client.close()
```

**Solutions**:
- Check connection state before sending
- Handle gracefully, close socket

#### socket.timeout

**Occurs when**: Operation exceeds timeout

```python
client.settimeout(10.0)
try:
    data = client.recv(1024)
except socket.timeout:
    print("Receive timeout")
    # Handle: retry, close connection, etc.
```

**Solutions**:
- Adjust timeout values
- Implement retry logic
- Handle as normal condition, not error

## Comprehensive Error Handling Pattern

### Server with Error Handling

```python
import socket
import sys
import logging

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

def handle_client(client, address):
    """Handle client with comprehensive error handling."""
    logger.info(f"Handling client {address}")
    
    try:
        client.settimeout(30.0)  # 30 second timeout
        
        while True:
            try:
                data = client.recv(1024)
                
                if not data:
                    logger.info(f"Client {address} closed connection")
                    break
                
                # Process data
                response = process_data(data)
                
                # Send response
                try:
                    client.sendall(response)
                except (BrokenPipeError, ConnectionResetError) as e:
                    logger.warning(f"Error sending to {address}: {e}")
                    break
                
            except socket.timeout:
                logger.warning(f"Timeout waiting for data from {address}")
                # Send keepalive or close
                break
            
            except ConnectionResetError:
                logger.info(f"Connection reset by {address}")
                break
            
            except Exception as e:
                logger.error(f"Unexpected error with {address}: {e}")
                break
    
    except Exception as e:
        logger.error(f"Fatal error handling {address}: {e}")
    
    finally:
        try:
            client.close()
        except:
            pass
        logger.info(f"Connection to {address} closed")

def process_data(data):
    """Process received data."""
    try:
        return data.upper()
    except Exception as e:
        logger.error(f"Error processing data: {e}")
        return b"ERROR"

def robust_server(host='localhost', port=8080):
    """Server with comprehensive error handling."""
    
    server = None
    
    try:
        # Create socket
        server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        
        # Bind
        try:
            server.bind((host, port))
        except OSError as e:
            if e.errno == 48:  # Address already in use
                logger.error(f"Port {port} already in use")
                sys.exit(1)
            elif e.errno == 13:  # Permission denied
                logger.error(f"Permission denied for port {port}")
                sys.exit(1)
            else:
                raise
        
        # Listen
        server.listen(5)
        logger.info(f"Server listening on {host}:{port}")
        
        while True:
            try:
                client, address = server.accept()
                handle_client(client, address)
            
            except KeyboardInterrupt:
                logger.info("Shutting down server...")
                break
            
            except Exception as e:
                logger.error(f"Error accepting connection: {e}")
                continue
    
    except Exception as e:
        logger.error(f"Fatal server error: {e}")
        sys.exit(1)
    
    finally:
        if server:
            server.close()
        logger.info("Server closed")

if __name__ == '__main__':
    robust_server()
```

### Client with Error Handling

```python
import socket
import time
import logging

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

def robust_client(host='localhost', port=8080, max_retries=3):
    """Client with comprehensive error handling and retry logic."""
    
    for attempt in range(max_retries):
        client = None
        
        try:
            # Create socket
            client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            client.settimeout(10.0)
            
            # Connect
            logger.info(f"Attempting connection to {host}:{port} (attempt {attempt + 1})")
            try:
                client.connect((host, port))
                logger.info("Connected successfully")
            except ConnectionRefusedError:
                logger.error("Connection refused - is server running?")
                if attempt < max_retries - 1:
                    time.sleep(2 ** attempt)  # Exponential backoff
                    continue
                return None
            
            except socket.gaierror as e:
                logger.error(f"DNS resolution failed: {e}")
                return None
            
            except socket.timeout:
                logger.error("Connection timeout")
                if attempt < max_retries - 1:
                    time.sleep(2 ** attempt)
                    continue
                return None
            
            # Communicate
            try:
                # Send
                message = b"Hello, Server!"
                client.sendall(message)
                logger.info("Message sent")
                
                # Receive
                response = client.recv(1024)
                if response:
                    logger.info(f"Response: {response.decode()}")
                else:
                    logger.warning("Empty response received")
                
                return client  # Success
            
            except (BrokenPipeError, ConnectionResetError) as e:
                logger.warning(f"Connection lost during communication: {e}")
                if attempt < max_retries - 1:
                    time.sleep(2 ** attempt)
                    continue
                return None
            
            except socket.timeout:
                logger.warning("Communication timeout")
                return None
        
        except Exception as e:
            logger.error(f"Unexpected error: {e}")
            if attempt < max_retries - 1:
                time.sleep(2 ** attempt)
                continue
            return None
        
        finally:
            if client:
                client.close()
    
    logger.error("Max retries reached")
    return None

if __name__ == '__main__':
    robust_client()
```

## Error Handling Best Practices

### 1. Always Use try-except

```python
# Bad
client.send(data)

# Good
try:
    client.sendall(data)
except (BrokenPipeError, ConnectionResetError):
    handle_connection_error()
```

### 2. Check Connection State

```python
def is_connected(sock):
    """Check if socket is still connected."""
    try:
        sock.getpeername()
        return True
    except socket.error:
        return False

# Usage
if is_connected(client):
    client.send(data)
```

### 3. Use Context Managers

```python
# Python 3.3+ automatically closes sockets
with socket.socket(...) as sock:
    sock.connect(...)
    # use socket
# Automatically closed
```

### 4. Set Appropriate Timeouts

```python
# Short timeout for connections
client.settimeout(5.0)
client.connect(...)

# Longer timeout for data transfer
client.settimeout(30.0)
data = client.recv(1024)
```

### 5. Handle Partial Sends/Receives

```python
def send_all(sock, data):
    """Send all data, handling partial sends."""
    total_sent = 0
    while total_sent < len(data):
        try:
            sent = sock.send(data[total_sent:])
            if sent == 0:
                raise RuntimeError("Socket connection broken")
            total_sent += sent
        except socket.error as e:
            raise

def recv_all(sock, size):
    """Receive exactly 'size' bytes."""
    data = b''
    while len(data) < size:
        chunk = sock.recv(size - len(data))
        if not chunk:
            raise ConnectionError("Connection closed")
        data += chunk
    return data
```

### 6. Log Errors Appropriately

```python
import logging

logger = logging.getLogger(__name__)

try:
    client.connect(...)
except ConnectionRefusedError:
    logger.warning("Connection refused")  # Expected in some cases
except Exception as e:
    logger.error(f"Unexpected error: {e}", exc_info=True)  # Full traceback
```

### 7. Implement Retry Logic

```python
import time

def connect_with_retry(host, port, max_retries=3):
    for attempt in range(max_retries):
        try:
            client = socket.socket(...)
            client.connect((host, port))
            return client
        except ConnectionRefusedError:
            if attempt < max_retries - 1:
                time.sleep(2 ** attempt)  # Exponential backoff
                continue
            raise
```

## Error Recovery Strategies

### 1. Graceful Degradation

```python
try:
    # Try primary server
    client.connect(('primary.example.com', 8080))
except:
    # Fallback to secondary
    client.connect(('secondary.example.com', 8080))
```

### 2. Connection Pooling

```python
class ConnectionPool:
    def __init__(self, host, port, pool_size=5):
        self.host = host
        self.port = port
        self.pool = []
        self.pool_size = pool_size
    
    def get_connection(self):
        # Try to reuse existing connection
        while self.pool:
            conn = self.pool.pop()
            if self.is_valid(conn):
                return conn
        
        # Create new connection
        return self.create_connection()
    
    def return_connection(self, conn):
        if len(self.pool) < self.pool_size and self.is_valid(conn):
            self.pool.append(conn)
        else:
            conn.close()
```

### 3. Health Checks

```python
def health_check(client):
    """Check if connection is healthy."""
    try:
        client.settimeout(1.0)
        # Send ping
        client.sendall(b"PING")
        # Receive pong
        response = client.recv(4)
        return response == b"PONG"
    except:
        return False
```

---

**Key Takeaway**: Comprehensive error handling makes your socket applications robust and production-ready. Always handle common errors, implement retry logic, and provide meaningful error messages.

