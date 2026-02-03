# Intermediate Level - Module 2: Reverse Proxy

## 📚 Learning Objectives

By the end of this module, you will:
- Understand what a reverse proxy is
- Configure NGINX as a reverse proxy
- Proxy to different backend servers
- Handle headers and proxy settings
- Configure WebSocket proxying
- Understand proxy buffering

## 🔄 What is a Reverse Proxy?

A reverse proxy is a server that sits between clients and backend servers. It receives requests from clients and forwards them to backend servers, then returns the response.

### Forward Proxy vs Reverse Proxy

**Forward Proxy:**
- Client → Proxy → Internet
- Hides client identity
- Used by clients (browsers)

**Reverse Proxy:**
- Client → Proxy → Backend Server
- Hides backend server identity
- Used by servers

### Benefits of Reverse Proxy

1. **Load Distribution**: Distribute requests across multiple backends
2. **SSL Termination**: Handle HTTPS, forward HTTP to backends
3. **Caching**: Cache responses from backends
4. **Security**: Hide backend server details
5. **Compression**: Compress responses
6. **Routing**: Route requests based on URL patterns

## 🔧 Basic Reverse Proxy Configuration

### Simple Proxy

```nginx
server {
    listen 80;
    server_name example.com;
    
    location / {
        # Proxy all requests to backend server
        proxy_pass http://localhost:8080;
        
        # Pass original host header
        proxy_set_header Host $host;
        
        # Pass client IP
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header X-Forwarded-Proto $scheme;
    }
}
```

### Proxy to Different Backend

```nginx
server {
    listen 80;
    server_name example.com;
    
    # Proxy to backend application server
    location / {
        proxy_pass http://127.0.0.1:3000;
        
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header X-Forwarded-Proto $scheme;
    }
}
```

## 📋 Essential Proxy Directives

### proxy_pass

Forwards requests to a backend server:

```nginx
location / {
    proxy_pass http://backend-server:port;
}
```

**Important Notes:**
- If `proxy_pass` has a path, the location path is replaced
- If `proxy_pass` has no path, the full URI is passed

```nginx
# Example 1: Full URI passed
location /app/ {
    proxy_pass http://backend:8080;  # /app/users → http://backend:8080/app/users
}

# Example 2: Path replaced
location /app/ {
    proxy_pass http://backend:8080/api/;  # /app/users → http://backend:8080/api/users
}
```

### proxy_set_header

Sets headers sent to the backend:

```nginx
location / {
    proxy_pass http://backend:8080;
    
    # Standard headers
    proxy_set_header Host $host;
    proxy_set_header X-Real-IP $remote_addr;
    proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
    proxy_set_header X-Forwarded-Proto $scheme;
    
    # Custom headers
    proxy_set_header X-Custom-Header "value";
}
```

### Common Headers Explained

- **Host**: Original host from client request
- **X-Real-IP**: Client's real IP address
- **X-Forwarded-For**: Chain of proxy IPs
- **X-Forwarded-Proto**: Original protocol (http/https)
- **X-Forwarded-Host**: Original host header

## 🎯 Complete Reverse Proxy Configuration

```nginx
server {
    listen 80;
    server_name example.com;
    
    # Increase timeouts for backend processing
    proxy_connect_timeout 60s;
    proxy_send_timeout 60s;
    proxy_read_timeout 60s;
    
    location / {
        proxy_pass http://127.0.0.1:3000;
        
        # Headers
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header X-Forwarded-Proto $scheme;
        proxy_set_header X-Forwarded-Host $host;
        
        # Buffering
        proxy_buffering on;
        proxy_buffer_size 4k;
        proxy_buffers 8 4k;
        proxy_busy_buffers_size 8k;
        
        # Don't pass proxy headers to backend
        proxy_set_header Connection "";
        
        # Enable keepalive to backend
        proxy_http_version 1.1;
    }
}
```

## 🔌 WebSocket Proxying

WebSocket connections require special handling:

```nginx
server {
    listen 80;
    server_name example.com;
    
    location / {
        proxy_pass http://backend:8080;
        
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header X-Forwarded-Proto $scheme;
    }
    
    # WebSocket location
    location /ws/ {
        proxy_pass http://backend:8080;
        
        # WebSocket headers
        proxy_http_version 1.1;
        proxy_set_header Upgrade $http_upgrade;
        proxy_set_header Connection "upgrade";
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        
        # WebSocket timeouts
        proxy_read_timeout 86400;
    }
}
```

## 🎨 Routing Based on URL Patterns

### Different Backends for Different Paths

```nginx
server {
    listen 80;
    server_name example.com;
    
    # API requests to API server
    location /api/ {
        proxy_pass http://api-server:8080;
        
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header X-Forwarded-Proto $scheme;
    }
    
    # Admin panel to admin server
    location /admin/ {
        proxy_pass http://admin-server:8081;
        
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
    }
    
    # All other requests to main app
    location / {
        proxy_pass http://app-server:3000;
        
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
    }
}
```

## 📊 Proxy Buffering

Buffering controls how NGINX handles responses from backend:

```nginx
location / {
    proxy_pass http://backend:8080;
    
    # Enable buffering
    proxy_buffering on;
    
    # Buffer sizes
    proxy_buffer_size 4k;           # First part of response
    proxy_buffers 8 4k;             # Number and size of buffers
    proxy_busy_buffers_size 8k;     # Buffers that can be busy
    proxy_max_temp_file_size 2048m; # Max temp file size
    proxy_temp_file_write_size 32k; # Write size to temp file
    
    # Disable buffering for streaming/SSE
    # proxy_buffering off;
}
```

**When to disable buffering:**
- Server-Sent Events (SSE)
- Real-time streaming
- Long polling
- WebSockets (handled differently)

## 🔒 HTTPS to HTTP Proxying (SSL Termination)

Terminate SSL at NGINX and forward HTTP to backend:

```nginx
# HTTPS frontend
server {
    listen 443 ssl http2;
    server_name example.com;
    
    ssl_certificate /etc/nginx/ssl/server.crt;
    ssl_certificate_key /etc/nginx/ssl/server.key;
    
    location / {
        # Proxy to HTTP backend
        proxy_pass http://127.0.0.1:8080;
        
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header X-Forwarded-Proto https;  # Important!
    }
}

# HTTP to HTTPS redirect
server {
    listen 80;
    server_name example.com;
    return 301 https://$server_name$request_uri;
}
```

## 🌐 Proxy to External Servers

```nginx
server {
    listen 80;
    server_name example.com;
    
    location / {
        # Proxy to external server
        proxy_pass http://external-server.com;
        
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
    }
}
```

## 🔍 Error Handling

### Custom Error Pages

```nginx
location / {
    proxy_pass http://backend:8080;
    
    # Handle backend errors
    proxy_intercept_errors on;
    
    error_page 502 503 504 /50x.html;
    location = /50x.html {
        root /usr/share/nginx/html;
    }
}
```

### Backend Health Checks

```nginx
location / {
    proxy_pass http://backend:8080;
    
    # Don't proxy if backend is down
    proxy_next_upstream error timeout invalid_header http_500 http_502 http_503;
    proxy_next_upstream_tries 3;
    proxy_next_upstream_timeout 10s;
}
```

## 📝 Practical Examples

### Example 1: Node.js Application

```nginx
server {
    listen 80;
    server_name myapp.com;
    
    location / {
        proxy_pass http://127.0.0.1:3000;
        
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header X-Forwarded-Proto $scheme;
        
        proxy_http_version 1.1;
        proxy_set_header Connection "";
        
        proxy_connect_timeout 60s;
        proxy_send_timeout 60s;
        proxy_read_timeout 60s;
    }
}
```

### Example 2: Python Django Application

```nginx
server {
    listen 80;
    server_name myapp.com;
    
    location / {
        proxy_pass http://127.0.0.1:8000;
        
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header X-Forwarded-Proto $scheme;
        
        # Required for Django
        proxy_redirect off;
    }
    
    # Serve static files directly
    location /static/ {
        alias /path/to/static/files/;
        expires 30d;
    }
    
    location /media/ {
        alias /path/to/media/files/;
        expires 30d;
    }
}
```

### Example 3: Multiple Services

```nginx
server {
    listen 80;
    server_name example.com;
    
    # Main application
    location / {
        proxy_pass http://127.0.0.1:3000;
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
    }
    
    # API service
    location /api/ {
        proxy_pass http://127.0.0.1:3001/;
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
    }
    
    # WebSocket service
    location /ws/ {
        proxy_pass http://127.0.0.1:3002;
        proxy_http_version 1.1;
        proxy_set_header Upgrade $http_upgrade;
        proxy_set_header Connection "upgrade";
        proxy_set_header Host $host;
        proxy_read_timeout 86400;
    }
    
    # Static files served directly
    location /static/ {
        root /var/www/static;
        expires 1y;
    }
}
```

## 🧪 Testing Reverse Proxy

### Test Proxy Configuration

```bash
# Test configuration
sudo nginx -t

# Reload NGINX
sudo systemctl reload nginx

# Test from command line
curl -I http://example.com

# Test with specific headers
curl -H "Host: example.com" http://your-server-ip
```

### Debug Proxy Headers

Add temporary headers to see what's being sent:

```nginx
location / {
    proxy_pass http://backend:8080;
    
    # Debug headers (remove in production)
    add_header X-Debug-Backend "backend:8080" always;
    add_header X-Debug-Host $host always;
}
```

## 📝 Exercises

1. Set up a basic reverse proxy to a backend application
2. Configure proxy headers (X-Real-IP, X-Forwarded-For, etc.)
3. Set up routing: different URL paths to different backends
4. Configure WebSocket proxying
5. Set up SSL termination (HTTPS frontend, HTTP backend)
6. Configure proxy buffering settings
7. Test error handling when backend is down
8. Combine static file serving with reverse proxy

## ✅ Checklist

- [ ] Understand what a reverse proxy is
- [ ] Can configure basic reverse proxy
- [ ] Understand proxy_pass directive
- [ ] Can set proper proxy headers
- [ ] Can configure WebSocket proxying
- [ ] Understand proxy buffering
- [ ] Can route requests based on URL patterns
- [ ] Can handle SSL termination

## ➡️ Next Steps

Proceed to [Module 3: Load Balancing](./03-load-balancing.md) to learn how to distribute traffic across multiple backend servers.

