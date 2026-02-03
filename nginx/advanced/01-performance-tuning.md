# Advanced Level - Module 1: Performance Tuning

## 📚 Learning Objectives

By the end of this module, you will:
- Optimize worker processes and connections
- Tune buffer sizes
- Configure keepalive connections
- Optimize file handling
- Understand connection limits
- Monitor and benchmark performance

## ⚡ Performance Optimization Overview

Performance tuning involves optimizing:
- Worker processes and connections
- Buffer sizes
- Connection handling
- File operations
- Caching strategies
- Compression

## 👷 Worker Processes and Connections

### Worker Processes

```nginx
# Main context
worker_processes auto;  # Auto = number of CPU cores

# Or specify explicitly
worker_processes 4;  # For 4-core system
```

**Recommendation:** Set to number of CPU cores or `auto`.

### Worker Connections

```nginx
events {
    worker_connections 1024;  # Connections per worker
    
    # Optimal event method
    use epoll;  # Linux
    # use kqueue;  # FreeBSD/macOS
    
    # Accept multiple connections at once
    multi_accept on;
}
```

**Calculation:**
- Max connections = `worker_processes × worker_connections`
- Example: 4 workers × 1024 = 4,096 max connections

### Optimize Event Processing

```nginx
events {
    worker_connections 2048;
    use epoll;  # Linux - efficient for high connections
    multi_accept on;
    accept_mutex off;  # Disable for better performance
}
```

## 📦 Buffer Optimization

### Client Body Buffers

```nginx
http {
    # Maximum body size
    client_max_body_size 10M;
    
    # Buffer sizes
    client_body_buffer_size 128k;
    client_header_buffer_size 1k;
    large_client_header_buffers 4 16k;
}
```

### Proxy Buffers

```nginx
location / {
    proxy_pass http://backend;
    
    # Proxy buffer settings
    proxy_buffer_size 4k;
    proxy_buffers 8 4k;
    proxy_busy_buffers_size 8k;
    proxy_temp_file_write_size 64k;
    proxy_max_temp_file_size 2048m;
}
```

## 🔗 Keepalive Connections

### HTTP Keepalive

```nginx
http {
    # Enable keepalive
    keepalive_timeout 65;
    keepalive_requests 100;
    
    # Keepalive to upstream
    upstream backend {
        server 127.0.0.1:8080;
        
        keepalive 32;  # Connection pool size
        keepalive_requests 100;
        keepalive_timeout 60s;
    }
    
    server {
        location / {
            proxy_pass http://backend;
            proxy_http_version 1.1;
            proxy_set_header Connection "";
        }
    }
}
```

## 📁 File Handling Optimization

### Sendfile

```nginx
http {
    # Use kernel sendfile() for efficient file transfer
    sendfile on;
    
    # Optimize packet transmission
    tcp_nopush on;   # Send headers and beginning of file together
    tcp_nodelay on;  # Disable Nagle's algorithm
}
```

### Open File Cache

```nginx
http {
    # Cache file descriptors
    open_file_cache max=10000 inactive=30s;
    open_file_cache_valid 60s;
    open_file_cache_min_uses 2;
    open_file_cache_errors on;
}
```

**Benefits:**
- Faster file access
- Reduced disk I/O
- Better performance for static files

## 🗜️ Compression Optimization

### Gzip Configuration

```nginx
http {
    gzip on;
    gzip_vary on;
    gzip_proxied any;
    gzip_comp_level 6;  # 1-9, 6 is good balance
    
    # Compress these types
    gzip_types
        text/plain
        text/css
        text/xml
        text/javascript
        application/json
        application/javascript
        application/xml+rss
        application/rss+xml
        font/truetype
        font/opentype
        application/vnd.ms-fontobject
        image/svg+xml;
    
    # Don't compress small files
    gzip_min_length 1000;
    
    # Disable for old browsers
    gzip_disable "msie6";
}
```

### Brotli Compression (if module available)

```nginx
http {
    brotli on;
    brotli_comp_level 6;
    brotli_types text/plain text/css application/json application/javascript text/xml application/xml;
}
```

## 🚦 Connection Limiting

### Limit Connections

```nginx
http {
    # Define limit zones
    limit_conn_zone $binary_remote_addr zone=conn_limit_per_ip:10m;
    limit_req_zone $binary_remote_addr zone=req_limit_per_ip:10m rate=10r/s;
    
    server {
        # Limit connections per IP
        limit_conn conn_limit_per_ip 10;
        
        # Limit requests per IP
        limit_req zone=req_limit_per_ip burst=20 nodelay;
        
        location / {
            # ...
        }
    }
}
```

## 📊 Complete Performance Configuration

```nginx
user nginx;
worker_processes auto;
worker_rlimit_nofile 65535;  # Increase file descriptor limit

error_log /var/log/nginx/error.log warn;
pid /var/run/nginx.pid;

events {
    worker_connections 2048;
    use epoll;
    multi_accept on;
}

http {
    include /etc/nginx/mime.types;
    default_type application/octet-stream;
    
    # Logging
    log_format main '$remote_addr - $remote_user [$time_local] "$request" '
                    '$status $body_bytes_sent "$http_referer" '
                    '"$http_user_agent" "$http_x_forwarded_for"';
    access_log /var/log/nginx/access.log main;
    
    # Performance settings
    sendfile on;
    tcp_nopush on;
    tcp_nodelay on;
    keepalive_timeout 65;
    keepalive_requests 100;
    types_hash_max_size 2048;
    server_tokens off;
    
    # Client settings
    client_max_body_size 10M;
    client_body_buffer_size 128k;
    client_header_buffer_size 1k;
    large_client_header_buffers 4 16k;
    
    # File cache
    open_file_cache max=10000 inactive=30s;
    open_file_cache_valid 60s;
    open_file_cache_min_uses 2;
    open_file_cache_errors on;
    
    # Compression
    gzip on;
    gzip_vary on;
    gzip_proxied any;
    gzip_comp_level 6;
    gzip_types text/plain text/css text/xml text/javascript 
               application/json application/javascript application/xml+rss 
               application/rss+xml font/truetype font/opentype 
               application/vnd.ms-fontobject image/svg+xml;
    gzip_min_length 1000;
    gzip_disable "msie6";
    
    # Rate limiting
    limit_conn_zone $binary_remote_addr zone=conn_limit_per_ip:10m;
    limit_req_zone $binary_remote_addr zone=req_limit_per_ip:10m rate=10r/s;
    
    include /etc/nginx/conf.d/*.conf;
}
```

## 🔍 Performance Monitoring

### Status Module (if available)

```nginx
location /nginx_status {
    stub_status on;
    access_log off;
    allow 127.0.0.1;
    deny all;
}
```

**Access:** `http://localhost/nginx_status`

### Key Metrics to Monitor

- Active connections
- Requests per second
- Bytes sent/received
- Worker processes status
- Cache hit ratio
- Upstream response times

### Benchmarking Tools

```bash
# Apache Bench
ab -n 10000 -c 100 http://example.com/

# wrk
wrk -t4 -c100 -d30s http://example.com/

# h2load (for HTTP/2)
h2load -n 10000 -c 100 -m 10 https://example.com/
```

## 🎯 Specific Optimizations

### Static File Serving

```nginx
location ~* \.(jpg|jpeg|png|gif|ico|css|js|svg|woff|woff2)$ {
    expires 1y;
    add_header Cache-Control "public, immutable";
    access_log off;
    
    # Direct I/O for large files
    sendfile on;
    tcp_nopush on;
}
```

### Reverse Proxy Optimization

```nginx
upstream backend {
    server 127.0.0.1:8080;
    keepalive 32;
}

location / {
    proxy_pass http://backend;
    proxy_http_version 1.1;
    proxy_set_header Connection "";
    
    # Optimize buffers
    proxy_buffer_size 4k;
    proxy_buffers 8 4k;
    proxy_busy_buffers_size 8k;
    
    # Timeouts
    proxy_connect_timeout 5s;
    proxy_send_timeout 60s;
    proxy_read_timeout 60s;
}
```

### FastCGI Optimization

```nginx
location ~ \.php$ {
    fastcgi_pass unix:/var/run/php/php7.4-fpm.sock;
    
    fastcgi_buffer_size 128k;
    fastcgi_buffers 4 256k;
    fastcgi_busy_buffers_size 256k;
    
    fastcgi_cache_path /var/cache/nginx/fastcgi levels=1:2 keys_zone=fcgi_cache:10m;
    fastcgi_cache fcgi_cache;
    fastcgi_cache_valid 200 60m;
}
```

## 🔧 System-Level Optimizations

### Increase File Descriptor Limit

```bash
# Edit /etc/security/limits.conf
* soft nofile 65535
* hard nofile 65535

# Or in systemd service file
[Service]
LimitNOFILE=65535
```

### Network Tuning

```bash
# Increase connection tracking
echo 'net.netfilter.nf_conntrack_max = 262144' >> /etc/sysctl.conf

# Optimize TCP
echo 'net.ipv4.tcp_fin_timeout = 30' >> /etc/sysctl.conf
echo 'net.ipv4.tcp_keepalive_time = 300' >> /etc/sysctl.conf

# Apply changes
sysctl -p
```

## 📝 Exercises

1. Optimize worker processes and connections for your system
2. Configure buffer sizes appropriately
3. Enable and tune keepalive connections
4. Optimize file handling (sendfile, open_file_cache)
5. Configure compression (gzip)
6. Set up connection limiting
7. Monitor performance metrics
8. Benchmark before and after optimizations

## ✅ Checklist

- [ ] Understand performance factors
- [ ] Can optimize worker processes
- [ ] Can tune buffer sizes
- [ ] Understand keepalive connections
- [ ] Can optimize file handling
- [ ] Can configure compression
- [ ] Can monitor performance
- [ ] Know system-level optimizations

## ➡️ Next Steps

Proceed to [Module 2: Security Hardening](./02-security-hardening.md) to learn about securing NGINX.

