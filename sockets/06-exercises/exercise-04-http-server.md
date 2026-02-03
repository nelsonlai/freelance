# Exercise 4: Simple HTTP Server

## Objective

Build a minimal HTTP/1.0 server that can serve static files and handle basic HTTP requests.

## Requirements

1. **HTTP Server**: Handle HTTP GET requests
2. **Static File Serving**: Serve files from a directory
3. **Status Codes**: Return appropriate HTTP status codes
4. **Headers**: Send proper HTTP headers
5. **MIME Types**: Detect and send correct Content-Type

## HTTP Protocol Basics

### Request Format

```
GET /index.html HTTP/1.0
Host: localhost:8080
\r\n
```

### Response Format

```
HTTP/1.0 200 OK
Content-Type: text/html
Content-Length: 1234
\r\n
<body>
```

## Basic Implementation

### Server Structure

```python
import socket
import os
import mimetypes

class HTTPServer:
    def __init__(self, host='localhost', port=8080, root_dir='./www'):
        self.host = host
        self.port = port
        self.root_dir = root_dir
    
    def start(self):
        # TODO: Create server, accept connections
        pass
    
    def handle_request(self, client):
        # TODO: Parse HTTP request
        # TODO: Get requested file
        # TODO: Send HTTP response
        pass
    
    def parse_request(self, request):
        # TODO: Parse HTTP request line and headers
        # TODO: Return method, path, headers
        pass
    
    def serve_file(self, client, filepath):
        # TODO: Read file, determine MIME type
        # TODO: Send HTTP response with file content
        pass

if __name__ == '__main__':
    server = HTTPServer()
    server.start()
```

## Implementation Steps

### Step 1: Parse HTTP Request

```python
def parse_request(self, request):
    lines = request.split('\r\n')
    request_line = lines[0]
    method, path, version = request_line.split()
    
    # Parse headers
    headers = {}
    for line in lines[1:]:
        if not line:
            break
        key, value = line.split(':', 1)
        headers[key.strip()] = value.strip()
    
    return method, path, headers
```

### Step 2: Handle File Requests

```python
def get_file_path(self, request_path):
    # Remove leading slash
    path = request_path.lstrip('/')
    
    # Default to index.html
    if not path or path == '/':
        path = 'index.html'
    
    # Join with root directory
    filepath = os.path.join(self.root_dir, path)
    
    # Security: prevent directory traversal
    filepath = os.path.normpath(filepath)
    if not filepath.startswith(os.path.abspath(self.root_dir)):
        return None  # Invalid path
    
    return filepath
```

### Step 3: Send HTTP Response

```python
def send_response(self, client, status_code, headers, body):
    status_messages = {
        200: 'OK',
        404: 'Not Found',
        500: 'Internal Server Error'
    }
    
    response = f"HTTP/1.0 {status_code} {status_messages[status_code]}\r\n"
    
    for key, value in headers.items():
        response += f"{key}: {value}\r\n"
    
    response += "\r\n"
    
    client.sendall(response.encode())
    if body:
        client.sendall(body)
```

### Step 4: Determine MIME Type

```python
def get_mime_type(self, filepath):
    mimetype, _ = mimetypes.guess_type(filepath)
    return mimetype or 'application/octet-stream'
```

## Expected Behavior

### Server Output
```
HTTP server started on localhost:8080
Serving files from: ./www
Waiting for connections...
GET /index.html HTTP/1.0
200 OK
GET /nonexistent.html HTTP/1.0
404 Not Found
```

### Client (Browser)
```
http://localhost:8080/index.html
# Displays index.html
```

## Testing

### Test 1: Basic File Serving

```bash
# Create web directory
mkdir www
echo "<h1>Hello, World!</h1>" > www/index.html

# Start server
python http_server.py

# Browser: http://localhost:8080/index.html
# Or use curl:
curl http://localhost:8080/index.html
```

### Test 2: Different File Types

```bash
# Create various files
echo "test" > www/test.txt
echo "body { color: red; }" > www/style.css
echo "console.log('test');" > www/script.js

# Test each
curl http://localhost:8080/test.txt
curl http://localhost:8080/style.css
curl http://localhost:8080/script.js
```

### Test 3: Error Handling

```bash
# Request non-existent file
curl http://localhost:8080/nonexistent.html
# Should return 404

# Request directory traversal attempt
curl http://localhost:8080/../../../etc/passwd
# Should return 403 or 404 (security)
```

## Advanced Features

### Feature 1: Directory Listing

```
GET /directory/ HTTP/1.0
# List files in directory (if no index.html)
```

### Feature 2: POST Support

```
POST /upload HTTP/1.0
Content-Length: 1234
\r\n
<data>
```

### Feature 3: HTTP/1.1 Keep-Alive

```
Connection: keep-alive
# Reuse connection for multiple requests
```

### Feature 4: Range Requests

```
GET /file.txt HTTP/1.0
Range: bytes=0-1023
# Support partial content requests
```

## HTTP Status Codes to Implement

| Code | Meaning | When to Use |
|------|---------|-------------|
| 200 | OK | Successful request |
| 404 | Not Found | File doesn't exist |
| 403 | Forbidden | Access denied |
| 500 | Internal Server Error | Server error |
| 400 | Bad Request | Invalid request |

## Solution Hints

<details>
<summary>Complete request handler</summary>

```python
def handle_request(self, client):
    try:
        # Receive request
        request = client.recv(4096).decode('utf-8')
        if not request:
            return
        
        # Parse request
        method, path, headers = self.parse_request(request)
        
        if method != 'GET':
            self.send_error(client, 405, "Method Not Allowed")
            return
        
        # Get file path
        filepath = self.get_file_path(path)
        if not filepath or not os.path.exists(filepath):
            self.send_error(client, 404, "Not Found")
            return
        
        # Serve file
        self.serve_file(client, filepath)
    
    except Exception as e:
        self.send_error(client, 500, str(e))
    finally:
        client.close()

def serve_file(self, client, filepath):
    with open(filepath, 'rb') as f:
        content = f.read()
    
    mime_type = self.get_mime_type(filepath)
    
    headers = {
        'Content-Type': mime_type,
        'Content-Length': str(len(content))
    }
    
    self.send_response(client, 200, headers, content)
```

</details>

## Success Criteria

- ✅ Handles HTTP GET requests
- ✅ Serves static files correctly
- ✅ Returns proper HTTP status codes
- ✅ Sends correct Content-Type headers
- ✅ Handles 404 for missing files
- ✅ Prevents directory traversal attacks

## Bonus Challenges

1. Support HTTP/1.1 with keep-alive
2. Implement POST for file uploads
3. Add support for CGI scripts
4. Implement HTTP authentication
5. Add logging of all requests

---

**Congratulations!** You've built a basic web server. This demonstrates how HTTP works at the socket level.

