# Advanced Level - Module 2: Security Hardening

## 📚 Learning Objectives

By the end of this module, you will:
- Hide NGINX version information
- Configure security headers
- Implement rate limiting
- Secure file permissions
- Protect against common attacks
- Configure access controls
- Understand SSL/TLS security

## 🔒 Security Overview

Security hardening involves:
- Hiding server information
- Setting security headers
- Rate limiting
- Access control
- File permissions
- SSL/TLS configuration
- DDoS protection

## 🎭 Hide Server Information

### Disable Server Tokens

```nginx
http {
    # Hide NGINX version
    server_tokens off;
}
```

**Before:** `Server: nginx/1.18.0`  
**After:** `Server: nginx`

### Custom Error Pages

```nginx
http {
    # Custom error pages (don't reveal server info)
    error_page 404 /404.html;
    error_page 500 502 503 504 /50x.html;
    
    server {
        location = /404.html {
            internal;
            root /usr/share/nginx/html;
        }
        
        location = /50x.html {
            internal;
            root /usr/share/nginx/html;
        }
    }
}
```

## 🛡️ Security Headers

### Comprehensive Security Headers

```nginx
server {
    listen 443 ssl http2;
    server_name example.com;
    
    # Hide version
    server_tokens off;
    
    # Security headers
    add_header X-Frame-Options "SAMEORIGIN" always;
    add_header X-Content-Type-Options "nosniff" always;
    add_header X-XSS-Protection "1; mode=block" always;
    add_header Referrer-Policy "no-referrer-when-downgrade" always;
    add_header Content-Security-Policy "default-src 'self' http: https: data: blob: 'unsafe-inline'" always;
    add_header Strict-Transport-Security "max-age=31536000; includeSubDomains" always;
    
    # Remove X-Powered-By (if proxying)
    proxy_hide_header X-Powered-By;
}
```

### Header Explanations

- **X-Frame-Options**: Prevents clickjacking
- **X-Content-Type-Options**: Prevents MIME sniffing
- **X-XSS-Protection**: Enables XSS filter
- **Strict-Transport-Security**: Forces HTTPS
- **Content-Security-Policy**: Controls resource loading
- **Referrer-Policy**: Controls referrer information

## 🚦 Rate Limiting

### Limit Requests

```nginx
http {
    # Define rate limit zones
    limit_req_zone $binary_remote_addr zone=general:10m rate=10r/s;
    limit_req_zone $binary_remote_addr zone=auth:10m rate=5r/m;
    limit_req_zone $binary_remote_addr zone=api:10m rate=20r/s;
    
    server {
        # General rate limit
        limit_req zone=general burst=20 nodelay;
        
        # Stricter limit for auth endpoints
        location /login {
            limit_req zone=auth burst=3 nodelay;
            # ...
        }
        
        # API rate limit
        location /api/ {
            limit_req zone=api burst=50 nodelay;
            # ...
        }
    }
}
```

### Limit Connections

```nginx
http {
    limit_conn_zone $binary_remote_addr zone=conn_limit:10m;
    
    server {
        # Limit connections per IP
        limit_conn conn_limit 10;
        
        # Limit connections per server
        limit_conn_zone $server_name zone=perserver:10m;
        limit_conn perserver 100;
    }
}
```

### Whitelist IPs

```nginx
http {
    geo $limit {
        default 1;
        127.0.0.1 0;  # Localhost
        192.168.1.0/24 0;  # Internal network
    }
    
    map $limit $limit_key {
        0 "";
        1 $binary_remote_addr;
    }
    
    limit_req_zone $limit_key zone=general:10m rate=10r/s;
}
```

## 🔐 Access Control

### IP-Based Access Control

```nginx
server {
    location /admin {
        # Allow specific IPs
        allow 192.168.1.100;
        allow 10.0.0.0/8;
        
        # Deny all others
        deny all;
    }
    
    location /internal {
        # Deny external access
        deny all;
        allow 127.0.0.1;
        allow 192.168.1.0/24;
    }
}
```

### HTTP Basic Authentication

```nginx
# Create password file
# htpasswd -c /etc/nginx/.htpasswd username

server {
    location /secure {
        auth_basic "Restricted Access";
        auth_basic_user_file /etc/nginx/.htpasswd;
    }
}
```

### Authentication with Subrequest

```nginx
location /private {
    auth_request /auth;
    auth_request_set $user $upstream_http_x_user;
    
    proxy_set_header X-User $user;
}

location = /auth {
    internal;
    proxy_pass http://auth-server/verify;
    proxy_pass_request_body off;
    proxy_set_header Content-Length "";
    proxy_set_header X-Original-URI $request_uri;
}
```

## 🚫 Protect Against Common Attacks

### SQL Injection Protection

```nginx
# Block SQL injection attempts
location / {
    if ($args ~* "union.*select.*\(|insert.*into|delete.*from|drop.*table") {
        return 403;
    }
    # ...
}
```

### XSS Protection

```nginx
# Block XSS attempts
location / {
    if ($args ~* "<script|javascript:|onerror=|onload=") {
        return 403;
    }
    # ...
}
```

### Path Traversal Protection

```nginx
# Block directory traversal
location / {
    if ($request_uri ~* "\.\.") {
        return 403;
    }
    # ...
}

# Block hidden files
location ~ /\. {
    deny all;
    access_log off;
    log_not_found off;
}
```

### Block Bad User Agents

```nginx
# Block malicious user agents
if ($http_user_agent ~* (libwww-perl|wget|python|nikto|curl|scan|java|winhttp|clshttp|loader)) {
    return 403;
}
```

### Block Invalid Methods

```nginx
# Only allow safe methods
if ($request_method !~ ^(GET|HEAD|POST|PUT|DELETE|OPTIONS)$) {
    return 405;
}
```

## 🔒 SSL/TLS Security

### Strong SSL Configuration

```nginx
server {
    listen 443 ssl http2;
    
    ssl_certificate /etc/nginx/ssl/server.crt;
    ssl_certificate_key /etc/nginx/ssl/server.key;
    
    # Protocols - only modern TLS
    ssl_protocols TLSv1.2 TLSv1.3;
    
    # Strong ciphers
    ssl_ciphers 'ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256:ECDHE-ECDSA-AES256-GCM-SHA384:ECDHE-RSA-AES256-GCM-SHA384:ECDHE-ECDSA-CHACHA20-POLY1305:ECDHE-RSA-CHACHA20-POLY1305';
    ssl_prefer_server_ciphers off;  # Let client choose for TLS 1.3
    
    # Session settings
    ssl_session_cache shared:SSL:10m;
    ssl_session_timeout 10m;
    ssl_session_tickets off;
    
    # OCSP Stapling
    ssl_stapling on;
    ssl_stapling_verify on;
    ssl_trusted_certificate /etc/nginx/ssl/chain.pem;
    resolver 8.8.8.8 8.8.4.4 valid=300s;
    resolver_timeout 5s;
    
    # Security headers
    add_header Strict-Transport-Security "max-age=31536000; includeSubDomains; preload" always;
}
```

## 📁 File Permissions

### Secure Configuration Files

```bash
# Configuration files
sudo chown root:root /etc/nginx/nginx.conf
sudo chmod 644 /etc/nginx/nginx.conf

# SSL certificates
sudo chmod 600 /etc/nginx/ssl/*.key
sudo chmod 644 /etc/nginx/ssl/*.crt

# Log files
sudo chown nginx:nginx /var/log/nginx/
sudo chmod 750 /var/log/nginx/
```

### Restrict File Access

```nginx
# Block access to sensitive files
location ~ /\.(htaccess|htpasswd|ini|log|sh|sql|conf)$ {
    deny all;
    return 404;
}

# Block access to backup files
location ~ ~$ {
    deny all;
    return 404;
}
```

## 🛡️ Complete Security Configuration

```nginx
user nginx;
worker_processes auto;

error_log /var/log/nginx/error.log warn;
pid /var/run/nginx.pid;

events {
    worker_connections 1024;
}

http {
    include /etc/nginx/mime.types;
    default_type application/octet-stream;
    
    # Hide version
    server_tokens off;
    
    # Rate limiting
    limit_req_zone $binary_remote_addr zone=general:10m rate=10r/s;
    limit_conn_zone $binary_remote_addr zone=conn_limit:10m;
    
    # Logging
    log_format main '$remote_addr - $remote_user [$time_local] "$request" '
                    '$status $body_bytes_sent "$http_referer" '
                    '"$http_user_agent" "$http_x_forwarded_for"';
    access_log /var/log/nginx/access.log main;
    
    # Performance
    sendfile on;
    tcp_nopush on;
    tcp_nodelay on;
    keepalive_timeout 65;
    
    # Compression
    gzip on;
    gzip_types text/plain text/css application/json application/javascript;
    
    # Default security headers
    add_header X-Frame-Options "SAMEORIGIN" always;
    add_header X-Content-Type-Options "nosniff" always;
    add_header X-XSS-Protection "1; mode=block" always;
    
    # HTTP to HTTPS redirect
    server {
        listen 80;
        server_name _;
        return 301 https://$host$request_uri;
    }
    
    # HTTPS server
    server {
        listen 443 ssl http2;
        server_name example.com;
        
        # SSL
        ssl_certificate /etc/nginx/ssl/server.crt;
        ssl_certificate_key /etc/nginx/ssl/server.key;
        ssl_protocols TLSv1.2 TLSv1.3;
        ssl_ciphers 'ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256';
        ssl_prefer_server_ciphers off;
        ssl_session_cache shared:SSL:10m;
        ssl_session_tickets off;
        
        # Security headers
        add_header Strict-Transport-Security "max-age=31536000; includeSubDomains" always;
        
        # Rate limiting
        limit_req zone=general burst=20 nodelay;
        limit_conn conn_limit 10;
        
        # Root
        root /var/www/html;
        index index.html;
        
        # Block hidden files
        location ~ /\. {
            deny all;
            access_log off;
            log_not_found off;
        }
        
        # Main location
        location / {
            try_files $uri $uri/ =404;
        }
        
        # Admin area with IP restriction
        location /admin {
            allow 192.168.1.100;
            deny all;
            
            auth_basic "Restricted";
            auth_basic_user_file /etc/nginx/.htpasswd;
        }
    }
}
```

## 🔍 Security Auditing

### Test SSL Configuration

```bash
# SSL Labs
# https://www.ssllabs.com/ssltest/

# Command line
openssl s_client -connect example.com:443 -servername example.com
```

### Security Headers Check

```bash
# Online tools
# https://securityheaders.com/
# https://observatory.mozilla.org/

# Command line
curl -I https://example.com | grep -i "x-\|strict-transport"
```

### Vulnerability Scanning

```bash
# Use tools like:
# - Nikto
# - Nmap
# - OpenVAS
```

## 📝 Exercises

1. Hide NGINX version information
2. Implement comprehensive security headers
3. Set up rate limiting for different endpoints
4. Configure IP-based access control
5. Set up HTTP basic authentication
6. Implement protection against common attacks
7. Secure SSL/TLS configuration
8. Audit your security configuration

## ✅ Checklist

- [ ] Server information hidden
- [ ] Security headers configured
- [ ] Rate limiting implemented
- [ ] Access controls configured
- [ ] Protection against common attacks
- [ ] SSL/TLS properly secured
- [ ] File permissions set correctly
- [ ] Security audit completed

## ➡️ Next Steps

Proceed to [Module 3: Troubleshooting](./03-troubleshooting.md) to learn debugging techniques.

