# Intermediate Level - Module 3: Load Balancing

## 📚 Learning Objectives

By the end of this module, you will:
- Understand load balancing concepts
- Configure different load balancing methods
- Set up health checks
- Configure session persistence
- Understand upstream blocks
- Handle failures and failover

## ⚖️ What is Load Balancing?

Load balancing distributes incoming network traffic across multiple backend servers to:
- **Improve Performance**: Distribute workload
- **Increase Availability**: Redundancy
- **Scale Horizontally**: Add more servers
- **Handle Failures**: Automatic failover

## 🔧 Basic Load Balancing Setup

### Upstream Block

Define a group of backend servers:

```nginx
http {
    # Define upstream group
    upstream backend {
        server 127.0.0.1:3000;
        server 127.0.0.1:3001;
        server 127.0.0.1:3002;
    }
    
    server {
        listen 80;
        server_name example.com;
        
        location / {
            proxy_pass http://backend;
            
            proxy_set_header Host $host;
            proxy_set_header X-Real-IP $remote_addr;
            proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        }
    }
}
```

## 🎯 Load Balancing Methods

### 1. Round Robin (Default)

Distributes requests evenly across all servers:

```nginx
upstream backend {
    # Round robin is default
    server 127.0.0.1:3000;
    server 127.0.0.1:3001;
    server 127.0.0.1:3002;
}
```

### 2. Weighted Round Robin

Assign weights to servers (higher weight = more requests):

```nginx
upstream backend {
    server 127.0.0.1:3000 weight=3;  # 3x more requests
    server 127.0.0.1:3001 weight=2;  # 2x requests
    server 127.0.0.1:3002 weight=1;  # Normal weight
}
```

### 3. Least Connections

Routes to server with fewest active connections:

```nginx
upstream backend {
    least_conn;
    
    server 127.0.0.1:3000;
    server 127.0.0.1:3001;
    server 127.0.0.1:3002;
}
```

### 4. IP Hash

Routes same client IP to same server (session persistence):

```nginx
upstream backend {
    ip_hash;
    
    server 127.0.0.1:3000;
    server 127.0.0.1:3001;
    server 127.0.0.1:3002;
}
```

### 5. Generic Hash

Routes based on custom key (e.g., user ID):

```nginx
upstream backend {
    hash $request_uri consistent;
    
    server 127.0.0.1:3000;
    server 127.0.0.1:3001;
    server 127.0.0.1:3002;
}
```

### 6. Random

Randomly selects server with optional two-choice method:

```nginx
upstream backend {
    random two;
    
    server 127.0.0.1:3000;
    server 127.0.0.1:3001;
    server 127.0.0.1:3002;
}
```

## 🔍 Server Parameters

### Basic Parameters

```nginx
upstream backend {
    server 127.0.0.1:3000 weight=3 max_fails=3 fail_timeout=30s;
    server 127.0.0.1:3001 backup;  # Only used if others are down
    server 127.0.0.1:3002 down;    # Marked as down
}
```

### Parameter Options

- **weight=number**: Server weight (default: 1)
- **max_fails=number**: Max failures before marking down (default: 1)
- **fail_timeout=time**: Time server is considered down (default: 10s)
- **backup**: Use only if other servers are unavailable
- **down**: Mark server as permanently down
- **slow_start=time**: Gradually increase weight after recovery

## ❤️ Health Checks

### Passive Health Checks (Default)

```nginx
upstream backend {
    server 127.0.0.1:3000 max_fails=3 fail_timeout=30s;
    server 127.0.0.1:3001 max_fails=3 fail_timeout=30s;
    server 127.0.0.1:3002 max_fails=3 fail_timeout=30s;
}
```

**How it works:**
- If server fails to respond, it's marked as unavailable
- After `fail_timeout`, NGINX tries again
- After `max_fails` consecutive failures, server is marked down

### Active Health Checks (NGINX Plus)

NGINX Plus (commercial) supports active health checks:

```nginx
upstream backend {
    zone backend_zone 64k;
    
    server 127.0.0.1:3000;
    server 127.0.0.1:3001;
    server 127.0.0.1:3002;
    
    # Active health checks
    health_check;
}
```

### Custom Health Check Endpoint

```nginx
location /health {
    access_log off;
    return 200 "healthy\n";
    add_header Content-Type text/plain;
}
```

## 🔒 Session Persistence

### IP Hash Method

```nginx
upstream backend {
    ip_hash;  # Same IP always goes to same server
    
    server 127.0.0.1:3000;
    server 127.0.0.1:3001;
    server 127.0.0.1:3002;
}
```

### Cookie-Based Persistence (NGINX Plus)

```nginx
upstream backend {
    sticky cookie srv_id expires=1h domain=.example.com path=/;
    
    server 127.0.0.1:3000;
    server 127.0.0.1:3001;
}
```

### Application-Level Session Management

Use application sessions stored in shared storage (Redis, database).

## 📊 Complete Load Balancer Configuration

```nginx
http {
    # Upstream definition
    upstream backend {
        # Load balancing method
        least_conn;  # or ip_hash, hash, etc.
        
        # Backend servers
        server 127.0.0.1:3000 weight=3 max_fails=3 fail_timeout=30s;
        server 127.0.0.1:3001 weight=2 max_fails=3 fail_timeout=30s;
        server 127.0.0.1:3002 weight=1 max_fails=3 fail_timeout=30s;
        
        # Backup server
        server 127.0.0.1:3003 backup;
    }
    
    server {
        listen 80;
        server_name example.com;
        
        location / {
            proxy_pass http://backend;
            
            # Proxy headers
            proxy_set_header Host $host;
            proxy_set_header X-Real-IP $remote_addr;
            proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
            proxy_set_header X-Forwarded-Proto $scheme;
            
            # Timeouts
            proxy_connect_timeout 5s;
            proxy_send_timeout 60s;
            proxy_read_timeout 60s;
            
            # Next upstream on failure
            proxy_next_upstream error timeout http_500 http_502 http_503 http_504;
            proxy_next_upstream_tries 3;
            proxy_next_upstream_timeout 10s;
        }
    }
}
```

## 🌐 Multiple Upstream Groups

### Different Services

```nginx
http {
    # Web application servers
    upstream web_app {
        server 127.0.0.1:3000;
        server 127.0.0.1:3001;
    }
    
    # API servers
    upstream api_servers {
        least_conn;
        server 127.0.0.1:4000;
        server 127.0.0.1:4001;
        server 127.0.0.1:4002;
    }
    
    # Static file servers
    upstream static_files {
        server 127.0.0.1:5000;
        server 127.0.0.1:5001;
    }
    
    server {
        listen 80;
        server_name example.com;
        
        # Web application
        location / {
            proxy_pass http://web_app;
            # ...
        }
        
        # API
        location /api/ {
            proxy_pass http://api_servers;
            # ...
        }
        
        # Static files
        location /static/ {
            proxy_pass http://static_files;
            # ...
        }
    }
}
```

## 🔐 HTTPS Upstream Servers

```nginx
upstream backend {
    server 192.168.1.10:443;
    server 192.168.1.11:443;
}

server {
    location / {
        proxy_pass https://backend;
        
        # SSL verification (optional)
        proxy_ssl_verify off;
        proxy_ssl_trusted_certificate /path/to/ca.crt;
    }
}
```

## 📝 Practical Examples

### Example 1: Simple Load Balancer

```nginx
upstream app_servers {
    server 192.168.1.10:8080;
    server 192.168.1.11:8080;
    server 192.168.1.12:8080;
}

server {
    listen 80;
    server_name example.com;
    
    location / {
        proxy_pass http://app_servers;
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
    }
}
```

### Example 2: Weighted with Health Checks

```nginx
upstream backend {
    server 192.168.1.10:8080 weight=5 max_fails=3 fail_timeout=30s;
    server 192.168.1.11:8080 weight=3 max_fails=3 fail_timeout=30s;
    server 192.168.1.12:8080 weight=2 max_fails=3 fail_timeout=30s;
    server 192.168.1.13:8080 backup;  # Backup server
}

server {
    listen 80;
    server_name example.com;
    
    location / {
        proxy_pass http://backend;
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        
        proxy_next_upstream error timeout http_500 http_502 http_503;
    }
}
```

### Example 3: Session Persistence

```nginx
upstream backend {
    ip_hash;  # Session persistence by IP
    
    server 192.168.1.10:8080;
    server 192.168.1.11:8080;
    server 192.168.1.12:8080;
}

server {
    listen 80;
    server_name example.com;
    
    location / {
        proxy_pass http://backend;
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
    }
}
```

### Example 4: Multi-Tier Architecture

```nginx
# Frontend servers
upstream frontend {
    least_conn;
    server 192.168.1.10:3000;
    server 192.168.1.11:3000;
}

# Backend API servers
upstream backend_api {
    ip_hash;
    server 192.168.1.20:8080;
    server 192.168.1.21:8080;
}

server {
    listen 80;
    server_name example.com;
    
    # Frontend
    location / {
        proxy_pass http://frontend;
        proxy_set_header Host $host;
    }
    
    # Backend API
    location /api/ {
        proxy_pass http://backend_api;
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
    }
}
```

## 🧪 Testing Load Balancing

### Test Distribution

```bash
# Send multiple requests and check which server handles each
for i in {1..10}; do
    curl http://example.com
done

# Check server logs to see distribution
```

### Test Failover

```bash
# Stop one backend server
sudo systemctl stop backend-service-1

# Send requests - should automatically use other servers
curl http://example.com

# Restart server - should automatically rejoin pool
sudo systemctl start backend-service-1
```

### Monitor Upstream Status

Add status endpoint (requires NGINX Plus or third-party module):

```nginx
location /upstream_status {
    upstream_status;
    access_log off;
}
```

## 📝 Exercises

1. Set up a basic load balancer with 3 backend servers
2. Configure weighted load balancing
3. Implement least connections method
4. Set up IP hash for session persistence
5. Configure health checks with max_fails and fail_timeout
6. Add a backup server
7. Test failover behavior
8. Set up multiple upstream groups for different services

## ✅ Checklist

- [ ] Understand load balancing concepts
- [ ] Can create upstream blocks
- [ ] Understand different load balancing methods
- [ ] Can configure weighted load balancing
- [ ] Can set up health checks
- [ ] Understand session persistence
- [ ] Can handle server failures
- [ ] Can configure backup servers

## ➡️ Next Steps

Proceed to [Module 4: URL Rewriting](./04-url-rewriting.md) to learn about rewriting and redirecting URLs.

