# Beginner Level - Module 3: Basic Configuration

## 📚 Learning Objectives

By the end of this module, you will:
- Understand NGINX configuration file structure
- Learn about directives and contexts
- Understand the main configuration file
- Learn about include directives
- Practice editing configuration files

## 📄 Configuration File Structure

NGINX configuration files use a hierarchical, block-based structure similar to programming languages.

### Main Configuration File

**Linux**: `/etc/nginx/nginx.conf`  
**macOS**: `/usr/local/etc/nginx/nginx.conf` or `/opt/homebrew/etc/nginx/nginx.conf`

### Basic Structure

```nginx
# Global directives
user nginx;
worker_processes auto;
error_log /var/log/nginx/error.log warn;
pid /var/run/nginx.pid;

# Events block
events {
    worker_connections 1024;
}

# HTTP block
http {
    # HTTP-level directives
    
    # Server blocks
    server {
        # Server-level directives
    }
}
```

## 🔑 Key Concepts

### Directives

Directives are configuration instructions that control NGINX behavior:

```nginx
# Simple directive (key-value pair)
worker_processes auto;

# Block directive (contains other directives)
events {
    worker_connections 1024;
}
```

### Contexts (Blocks)

Contexts are containers for directives:

1. **main** - Top-level context (outside any block)
2. **events** - Event processing configuration
3. **http** - HTTP server configuration
4. **server** - Virtual host configuration
5. **location** - URL matching and handling
6. **upstream** - Backend server groups (load balancing)

```
main (global scope)
├── events { ... }
└── http {
    ├── server { ... }
    ├── server {
    │   └── location / { ... }
    │   └── location /api { ... }
    │   }
    └── upstream backend { ... }
}
```

## 📋 Main Configuration Sections

### 1. Main Context (Global Settings)

```nginx
# User and group for worker processes
user nginx;

# Number of worker processes (auto = number of CPU cores)
worker_processes auto;

# Error log file and level
error_log /var/log/nginx/error.log warn;

# PID file location
pid /var/run/nginx.pid;
```

**Key Directives:**
- `user`: User that runs worker processes
- `worker_processes`: Number of worker processes
- `error_log`: Error log location and level (debug, info, notice, warn, error)
- `pid`: Process ID file location

### 2. Events Block

```nginx
events {
    # Maximum connections per worker
    worker_connections 1024;
    
    # Connection processing method
    use epoll;  # Linux
    
    # Accept as many connections as possible
    multi_accept on;
}
```

**Key Directives:**
- `worker_connections`: Max simultaneous connections per worker
- `use`: Event processing method (epoll, kqueue, select, etc.)
- `multi_accept`: Accept all connections in the queue at once

### 3. HTTP Block

```nginx
http {
    # Include MIME types
    include /etc/nginx/mime.types;
    default_type application/octet-stream;
    
    # Logging format
    log_format main '$remote_addr - $remote_user [$time_local] "$request" '
                    '$status $body_bytes_sent "$http_referer" '
                    '"$http_user_agent" "$http_x_forwarded_for"';
    
    # Access log
    access_log /var/log/nginx/access.log main;
    
    # Performance settings
    sendfile on;
    tcp_nopush on;
    tcp_nodelay on;
    keepalive_timeout 65;
    types_hash_max_size 2048;
    
    # Gzip compression
    gzip on;
    
    # Include server configurations
    include /etc/nginx/conf.d/*.conf;
    include /etc/nginx/sites-enabled/*;
}
```

**Key Directives:**
- `include`: Include other configuration files
- `default_type`: Default MIME type
- `log_format`: Define log format
- `access_log`: Access log location
- `sendfile`: Efficient file transfer
- `keepalive_timeout`: Keep-alive timeout
- `gzip`: Enable compression

### 4. Server Block (Virtual Host)

```nginx
server {
    # Listen on port 80
    listen 80;
    
    # Server name (domain)
    server_name example.com www.example.com;
    
    # Document root
    root /var/www/html;
    
    # Default index files
    index index.html index.htm;
    
    # Location block
    location / {
        try_files $uri $uri/ =404;
    }
}
```

**Key Directives:**
- `listen`: Port and optional IP address
- `server_name`: Domain name(s) for this server
- `root`: Document root directory
- `index`: Default index files

### 5. Location Block

```nginx
location / {
    # Try files in order
    try_files $uri $uri/ /index.html;
}

location /images/ {
    # Serve from specific directory
    alias /var/www/images/;
    
    # Expires header
    expires 30d;
}

location ~ \.php$ {
    # Process PHP files
    fastcgi_pass unix:/var/run/php/php7.4-fpm.sock;
    fastcgi_index index.php;
    include fastcgi_params;
}
```

**Location Matching:**
- `=` - Exact match
- `^~` - Prefix match (longest match, no regex)
- `~` - Case-sensitive regex
- `~*` - Case-insensitive regex
- `/` - Prefix match (shortest match)

## 📝 Include Directive

The `include` directive allows you to organize configuration:

```nginx
# Include MIME types
include /etc/nginx/mime.types;

# Include all .conf files from a directory
include /etc/nginx/conf.d/*.conf;

# Include specific file
include /etc/nginx/ssl.conf;
```

## 🎯 Configuration Best Practices

### 1. Always Test Configuration

```bash
sudo nginx -t
```

### 2. Backup Before Changes

```bash
sudo cp /etc/nginx/nginx.conf /etc/nginx/nginx.conf.backup
```

### 3. Use Include for Organization

Separate configuration into logical files:
- `/etc/nginx/conf.d/general.conf`
- `/etc/nginx/conf.d/ssl.conf`
- `/etc/nginx/conf.d/security.conf`

### 4. Comment Your Config

```nginx
# This server block handles the main website
server {
    # Listen on HTTP port
    listen 80;
    # ... rest of config
}
```

## 📖 Common Directives Reference

### Logging
- `error_log`: Error log location and level
- `access_log`: Access log location and format
- `log_format`: Define custom log format

### Performance
- `sendfile`: Use kernel sendfile() for file transfer
- `tcp_nopush`: Enable TCP_NOPUSH socket option
- `tcp_nodelay`: Disable Nagle's algorithm
- `keepalive_timeout`: Timeout for keep-alive connections
- `client_max_body_size`: Maximum request body size

### Security
- `server_tokens`: Hide NGINX version
- `add_header`: Add custom headers

## 🔍 Understanding Default Configuration

Let's examine a typical default `nginx.conf`:

```nginx
user nginx;
worker_processes auto;
error_log /var/log/nginx/error.log;
pid /var/run/nginx.pid;

events {
    worker_connections 1024;
}

http {
    log_format main '$remote_addr - $remote_user [$time_local] "$request" '
                    '$status $body_bytes_sent "$http_referer" '
                    '"$http_user_agent" "$http_x_forwarded_for"';

    access_log /var/log/nginx/access.log main;

    sendfile on;
    tcp_nopush on;
    tcp_nodelay on;
    keepalive_timeout 65;
    types_hash_max_size 2048;

    include /etc/nginx/mime.types;
    default_type application/octet-stream;

    gzip on;

    include /etc/nginx/conf.d/*.conf;
}
```

## 🛠️ Practical Example

Create a simple server configuration:

```nginx
# /etc/nginx/conf.d/mysite.conf
server {
    listen 80;
    server_name mysite.local;
    
    root /var/www/mysite;
    index index.html;
    
    location / {
        try_files $uri $uri/ =404;
    }
    
    # Deny access to hidden files
    location ~ /\. {
        deny all;
    }
}
```

Test and reload:
```bash
sudo nginx -t
sudo systemctl reload nginx
```

## 📝 Exercises

1. Open your `nginx.conf` file and identify each context
2. Find the default server block configuration
3. Create a backup of your configuration file
4. Add a comment explaining what `worker_processes auto` does
5. Locate where server blocks are included
6. Check the log format definition
7. Test your configuration with `nginx -t`

## ✅ Checklist

- [ ] Understand configuration file structure
- [ ] Know the difference between directives and contexts
- [ ] Can identify main, events, http, server, and location blocks
- [ ] Understand the include directive
- [ ] Can test configuration syntax
- [ ] Know how to reload configuration

## ➡️ Next Steps

Proceed to [Module 4: Serving Static Files](./04-serving-static-files.md) to learn how to configure NGINX to serve static content.

