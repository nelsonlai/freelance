# Socket Security Fundamentals

Security is critical in network programming. This module covers fundamental security concepts and practices for socket applications.

## Security Threats

### Common Threats

1. **Eavesdropping**: Unauthorized interception of data
2. **Man-in-the-Middle (MITM)**: Attacker intercepts and modifies communication
3. **Replay Attacks**: Attacker resends captured messages
4. **Denial of Service (DoS)**: Overwhelming server with requests
5. **Buffer Overflow**: Sending data larger than buffer, causing crashes
6. **Injection Attacks**: Malicious data causing unauthorized actions

## Basic Security Practices

### 1. Input Validation

**Always validate input** from network:

```python
def validate_input(data):
    """Validate input data."""
    # Check length
    if len(data) > MAX_MESSAGE_SIZE:
        raise ValueError("Message too long")
    
    # Check format
    if not data.isprintable():
        raise ValueError("Invalid characters")
    
    # Sanitize
    data = data.strip()
    
    return data
```

### 2. Buffer Size Limits

**Prevent buffer overflow**:

```python
# Bad: No limit
data = client.recv(999999)  # Dangerous!

# Good: Limit buffer size
MAX_BUFFER = 4096
data = client.recv(MAX_BUFFER)
if len(data) == MAX_BUFFER:
    # Might be more data, handle appropriately
    pass
```

### 3. Timeout Protection

**Prevent hanging connections**:

```python
# Set timeouts
client.settimeout(30.0)  # 30 second timeout

try:
    data = client.recv(1024)
except socket.timeout:
    # Handle timeout
    client.close()
```

### 4. Connection Limits

**Prevent DoS attacks**:

```python
MAX_CONNECTIONS = 100
active_connections = 0

def accept_connection():
    global active_connections
    if active_connections >= MAX_CONNECTIONS:
        raise Exception("Too many connections")
    active_connections += 1
    # Accept connection
```

### 5. Resource Limits

**Limit resource usage**:

```python
MAX_FILE_SIZE = 10 * 1024 * 1024  # 10MB
MAX_MESSAGE_SIZE = 64 * 1024  # 64KB

def receive_file(client):
    # Check file size first
    size_header = client.recv(8)
    file_size = int.from_bytes(size_header, 'big')
    
    if file_size > MAX_FILE_SIZE:
        raise ValueError("File too large")
    
    # Receive file with size limit
    # ...
```

## Path Traversal Prevention

**Critical for file servers**:

```python
import os

def safe_path(root_dir, request_path):
    """Prevent directory traversal attacks."""
    
    # Remove leading slash
    path = request_path.lstrip('/')
    
    # Join paths
    full_path = os.path.join(root_dir, path)
    
    # Normalize path (resolve .. and .)
    full_path = os.path.normpath(full_path)
    
    # Get absolute paths
    root_abs = os.path.abspath(root_dir)
    full_abs = os.path.abspath(full_path)
    
    # Verify path is within root directory
    if not full_abs.startswith(root_abs):
        raise ValueError("Path traversal attempt detected")
    
    return full_abs
```

**Example attack prevented**:
```
Attack: /../../../etc/passwd
Result: Rejected (outside root directory)
```

## Rate Limiting

**Prevent abuse**:

```python
from collections import defaultdict
from time import time

class RateLimiter:
    def __init__(self, max_requests=10, window=60):
        self.max_requests = max_requests
        self.window = window  # seconds
        self.requests = defaultdict(list)
    
    def is_allowed(self, client_ip):
        """Check if request is allowed."""
        now = time()
        
        # Clean old requests
        self.requests[client_ip] = [
            t for t in self.requests[client_ip]
            if now - t < self.window
        ]
        
        # Check limit
        if len(self.requests[client_ip]) >= self.max_requests:
            return False
        
        # Record request
        self.requests[client_ip].append(now)
        return True

# Usage
rate_limiter = RateLimiter(max_requests=10, window=60)

def handle_client(client, address):
    if not rate_limiter.is_allowed(address[0]):
        client.sendall(b"Rate limit exceeded")
        client.close()
        return
    # Handle request
```

## Authentication

### Basic Password Authentication

```python
import hashlib

# Store hashed passwords (never store plaintext!)
PASSWORDS = {
    'alice': hashlib.sha256(b'password123').hexdigest(),
    'bob': hashlib.sha256(b'securepass').hexdigest(),
}

def authenticate(username, password):
    """Authenticate user."""
    if username not in PASSWORDS:
        return False
    
    password_hash = hashlib.sha256(password.encode()).hexdigest()
    return PASSWORDS[username] == password_hash

# Usage
def handle_login(client):
    username = client.recv(1024).decode().strip()
    password = client.recv(1024).decode().strip()
    
    if authenticate(username, password):
        client.sendall(b"OK")
    else:
        client.sendall(b"FAIL")
        client.close()
```

### Token-Based Authentication

```python
import secrets
import hashlib

class TokenAuth:
    def __init__(self):
        self.tokens = {}  # token -> (username, expiry_time)
    
    def generate_token(self, username):
        """Generate authentication token."""
        token = secrets.token_urlsafe(32)
        expiry = time.time() + 3600  # 1 hour
        self.tokens[token] = (username, expiry)
        return token
    
    def validate_token(self, token):
        """Validate token."""
        if token not in self.tokens:
            return None
        
        username, expiry = self.tokens[token]
        if time.time() > expiry:
            del self.tokens[token]
            return None
        
        return username
```

## Secure Data Transmission

### Use TLS/SSL

**Always use TLS for sensitive data**:

```python
import ssl

# Server side
context = ssl.create_default_context(ssl.Purpose.CLIENT_AUTH)
context.load_cert_chain('cert.pem', 'key.pem')

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server = context.wrap_socket(server, server_side=True)
server.bind(('localhost', 443))
server.listen(5)

# Client side
context = ssl.create_default_context()
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client = context.wrap_socket(client, server_hostname='example.com')
client.connect(('example.com', 443))
```

See module on TLS/SSL for details.

## Logging and Monitoring

**Log security events**:

```python
import logging

logging.basicConfig(
    filename='security.log',
    level=logging.WARNING,
    format='%(asctime)s - %(levelname)s - %(message)s'
)

def handle_security_event(event_type, details):
    """Log security events."""
    logging.warning(f"{event_type}: {details}")
    
    # Alert on critical events
    if event_type in ['INTRUSION', 'ATTACK']:
        send_alert(event_type, details)

# Usage
try:
    # Handle request
    pass
except ValueError as e:
    handle_security_event('ATTACK', str(e))
```

## Security Checklist

### For Every Socket Application

- [ ] Validate all input
- [ ] Set buffer size limits
- [ ] Implement timeouts
- [ ] Limit connections/resources
- [ ] Prevent path traversal (if handling files)
- [ ] Use TLS for sensitive data
- [ ] Implement authentication (if needed)
- [ ] Add rate limiting
- [ ] Log security events
- [ ] Handle errors gracefully
- [ ] Keep dependencies updated
- [ ] Regular security audits

## Common Vulnerabilities to Avoid

### 1. Unbounded Recv

```python
# BAD: No size limit
data = client.recv(9999999)

# GOOD: Limited size
data = client.recv(4096)
```

### 2. Trusting Client Input

```python
# BAD: Trust client-specified file path
filename = client.recv(1024).decode()
with open(filename, 'r') as f:  # Dangerous!

# GOOD: Validate and sanitize
filename = sanitize_filename(client.recv(1024).decode())
safe_path = validate_path(filename)
with open(safe_path, 'r') as f:
```

### 3. No Timeout

```python
# BAD: Can hang forever
data = client.recv(1024)

# GOOD: Has timeout
client.settimeout(30.0)
data = client.recv(1024)
```

### 4. No Authentication

```python
# BAD: Anyone can access
def handle_request(client):
    secret_data = get_secret_data()
    client.send(secret_data)

# GOOD: Authenticate first
def handle_request(client):
    if not authenticate(client):
        client.close()
        return
    secret_data = get_secret_data()
    client.send(secret_data)
```

## Defense in Depth

**Use multiple security layers**:

1. **Network level**: Firewall, rate limiting
2. **Transport level**: TLS encryption
3. **Application level**: Authentication, input validation
4. **Data level**: Encryption, hashing
5. **Monitoring**: Logging, alerts

---

**Key Takeaway**: Security should be built into socket applications from the start. Always validate input, limit resources, use encryption for sensitive data, and implement proper authentication and authorization.

