# Intermediate Level - Module 6: Virtual Hosting

## 📚 Learning Objectives

By the end of this module, you will:
- Understand advanced virtual hosting concepts
- Configure name-based virtual hosting
- Set up IP-based virtual hosting
- Handle default servers
- Configure wildcard domains
- Set up subdomain management

## 🌐 Virtual Hosting Types

### 1. Name-Based Virtual Hosting
Multiple domains on one IP address (most common)

### 2. IP-Based Virtual Hosting
Different IP addresses for each domain

### 3. Port-Based Virtual Hosting
Different ports for different services

## 📋 Name-Based Virtual Hosting

Multiple domains share the same IP address:

```nginx
# First domain
server {
    listen 80;
    server_name example.com www.example.com;
    root /var/www/example.com;
    index index.html;
    
    location / {
        try_files $uri $uri/ =404;
    }
}

# Second domain
server {
    listen 80;
    server_name another-site.com;
    root /var/www/another-site.com;
    index index.html;
    
    location / {
        try_files $uri $uri/ =404;
    }
}
```

**How it works:**
- NGINX matches requests based on `Host` header
- Same IP, different server_name values

## 🔌 IP-Based Virtual Hosting

Different IP addresses for different domains:

```nginx
# Domain 1 on IP 192.168.1.10
server {
    listen 192.168.1.10:80;
    server_name example.com;
    root /var/www/example.com;
    # ...
}

# Domain 2 on IP 192.168.1.11
server {
    listen 192.168.1.11:80;
    server_name another-site.com;
    root /var/www/another-site.com;
    # ...
}
```

**When to use:**
- SSL certificates requiring specific IPs
- Legacy applications
- Isolation requirements

## 🔢 Port-Based Virtual Hosting

Different ports for different services:

```nginx
# Main website on port 80
server {
    listen 80;
    server_name example.com;
    root /var/www/example.com;
    # ...
}

# Development site on port 8080
server {
    listen 8080;
    server_name dev.example.com;
    root /var/www/dev;
    # ...
}

# Admin panel on port 8081
server {
    listen 8081;
    server_name admin.example.com;
    root /var/www/admin;
    # ...
}
```

## 🎯 Wildcard Domains

### Subdomain Wildcard

```nginx
server {
    listen 80;
    server_name *.example.com;
    root /var/www/wildcard;
    
    # Use the subdomain in config
    set $subdomain $1;
    if ($host ~* ^([^.]+)\.example\.com$) {
        set $subdomain $1;
    }
    
    location / {
        try_files $uri $uri/ =404;
    }
}
```

### Catch-All Subdomain

```nginx
server {
    listen 80;
    server_name *.example.com;
    root /var/www/subdomains;
    
    # Extract subdomain
    if ($host ~* ^([^.]+)\.example\.com$) {
        set $subdomain $1;
        rewrite ^(.*)$ /$subdomain$1 break;
    }
}
```

## 🏠 Default Server Blocks

### Catch-All Default Server

```nginx
# Default server - catches all unmatched requests
server {
    listen 80 default_server;
    server_name _;
    
    # Return 444 (close connection)
    return 444;
    
    # Or serve default page
    # root /var/www/default;
    # index index.html;
}

# Real websites
server {
    listen 80;
    server_name example.com;
    root /var/www/example.com;
    # ...
}
```

### Multiple Default Servers

```nginx
# Default for IPv4
server {
    listen 80 default_server;
    server_name _;
    return 444;
}

# Default for IPv6
server {
    listen [::]:80 default_server;
    server_name _;
    return 444;
}
```

## 📁 Organizing Virtual Hosts

### Method 1: Separate Files

**nginx.conf:**
```nginx
http {
    include /etc/nginx/mime.types;
    include /etc/nginx/conf.d/*.conf;
}
```

**/etc/nginx/conf.d/example.com.conf:**
```nginx
server {
    listen 80;
    server_name example.com;
    # ...
}
```

### Method 2: sites-available/sites-enabled

**nginx.conf:**
```nginx
http {
    include /etc/nginx/mime.types;
    include /etc/nginx/sites-enabled/*;
}
```

**/etc/nginx/sites-available/example.com:**
```nginx
server {
    listen 80;
    server_name example.com;
    # ...
}
```

**Enable site:**
```bash
sudo ln -s /etc/nginx/sites-available/example.com /etc/nginx/sites-enabled/
sudo nginx -t
sudo systemctl reload nginx
```

## 🌍 Subdomain Management

### Individual Subdomain Configs

```nginx
# Main domain
server {
    listen 80;
    server_name example.com;
    root /var/www/example.com;
    # ...
}

# www subdomain
server {
    listen 80;
    server_name www.example.com;
    return 301 http://example.com$request_uri;
}

# Blog subdomain
server {
    listen 80;
    server_name blog.example.com;
    root /var/www/blog;
    # ...
}

# API subdomain
server {
    listen 80;
    server_name api.example.com;
    
    location / {
        proxy_pass http://127.0.0.1:3000;
        # ...
    }
}

# Mail subdomain
server {
    listen 80;
    server_name mail.example.com;
    root /var/www/mail;
    # ...
}
```

### Dynamic Subdomain Handling

```nginx
server {
    listen 80;
    server_name ~^(?<subdomain>.+)\.example\.com$;
    
    # Use subdomain variable
    root /var/www/subdomains/$subdomain;
    
    location / {
        try_files $uri $uri/ =404;
    }
}
```

## 🔒 Secure Virtual Hosting

### HTTPS Virtual Hosts

```nginx
# HTTP redirect
server {
    listen 80;
    server_name example.com;
    return 301 https://$server_name$request_uri;
}

# HTTPS main
server {
    listen 443 ssl http2;
    server_name example.com;
    
    ssl_certificate /etc/nginx/ssl/example.com.crt;
    ssl_certificate_key /etc/nginx/ssl/example.com.key;
    
    root /var/www/example.com;
    # ...
}
```

### Multiple HTTPS Domains

```nginx
# Domain 1
server {
    listen 443 ssl http2;
    server_name example.com;
    
    ssl_certificate /etc/nginx/ssl/example.com.crt;
    ssl_certificate_key /etc/nginx/ssl/example.com.key;
    # ...
}

# Domain 2
server {
    listen 443 ssl http2;
    server_name another-site.com;
    
    ssl_certificate /etc/nginx/ssl/another-site.com.crt;
    ssl_certificate_key /etc/nginx/ssl/another-site.com.key;
    # ...
}
```

## 📝 Practical Examples

### Example 1: Complete Multi-Domain Setup

```nginx
# Default server
server {
    listen 80 default_server;
    server_name _;
    return 444;
}

# Main website
server {
    listen 80;
    server_name example.com www.example.com;
    
    # Redirect www to non-www
    if ($host = www.example.com) {
        return 301 http://example.com$request_uri;
    }
    
    root /var/www/example.com;
    index index.html;
    
    location / {
        try_files $uri $uri/ =404;
    }
}

# Blog subdomain
server {
    listen 80;
    server_name blog.example.com;
    root /var/www/blog;
    index index.html;
    
    location / {
        try_files $uri $uri/ =404;
    }
}

# API subdomain
server {
    listen 80;
    server_name api.example.com;
    
    location / {
        proxy_pass http://127.0.0.1:3000;
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
    }
}
```

### Example 2: Development and Production

```nginx
# Production
server {
    listen 80;
    server_name example.com;
    root /var/www/example.com/production;
    # ...
}

# Staging
server {
    listen 80;
    server_name staging.example.com;
    root /var/www/example.com/staging;
    # ...
}

# Development
server {
    listen 8080;
    server_name dev.example.com;
    root /var/www/example.com/development;
    # ...
}
```

### Example 3: User Subdomains

```nginx
server {
    listen 80;
    server_name ~^(?<username>[a-z0-9-]+)\.example\.com$;
    
    root /var/www/users/$username;
    
    # Check if directory exists
    if (!-d $document_root) {
        return 404;
    }
    
    location / {
        try_files $uri $uri/ =404;
    }
}
```

## 🔍 Debugging Virtual Hosts

### Test Server Name Matching

```bash
# Test specific host
curl -H "Host: example.com" http://your-server-ip

# Test default server
curl -H "Host: unknown.com" http://your-server-ip
```

### Check Active Configuration

```bash
# Show all server blocks
sudo nginx -T | grep -A 10 "server {"

# Check which server block will match
sudo nginx -T | grep server_name
```

### Debug with Headers

```nginx
server {
    listen 80;
    server_name example.com;
    
    # Debug headers
    add_header X-Server-Name $server_name always;
    add_header X-Host $host always;
    # ...
}
```

## 📝 Exercises

1. Set up name-based virtual hosting for 3 domains
2. Configure IP-based virtual hosting
3. Set up port-based virtual hosting
4. Create a default server block
5. Configure wildcard subdomain handling
6. Set up multiple subdomains (www, blog, api)
7. Organize virtual hosts using separate files
8. Test server name matching

## ✅ Checklist

- [ ] Understand virtual hosting types
- [ ] Can configure name-based virtual hosting
- [ ] Can set up IP-based virtual hosting
- [ ] Can configure port-based virtual hosting
- [ ] Understand default server blocks
- [ ] Can handle wildcard domains
- [ ] Can manage subdomains
- [ ] Can organize virtual host configurations

## ➡️ Next Steps

Congratulations! You've completed the Intermediate Level. Proceed to [Advanced Level - Module 1: Performance Tuning](../advanced/01-performance-tuning.md) to learn about optimizing NGINX performance.

