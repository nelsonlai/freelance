# Beginner Level - Module 5: Server Blocks (Virtual Hosts)

## 📚 Learning Objectives

By the end of this module, you will:
- Understand what server blocks are
- Configure multiple websites on one server
- Understand server_name matching
- Set up default server blocks
- Handle different domains and ports
- Practice with practical examples

## 🎯 What are Server Blocks?

Server blocks (also called virtual hosts) allow you to host multiple websites on a single NGINX server. Each server block defines how NGINX should handle requests for a specific domain or IP address.

**Apache Equivalent**: Virtual Hosts  
**Nginx Term**: Server Blocks

## 📋 Basic Server Block Structure

```nginx
server {
    listen 80;
    server_name example.com www.example.com;
    
    root /var/www/example.com;
    index index.html;
    
    location / {
        try_files $uri $uri/ =404;
    }
}
```

### Key Components

1. **listen**: Port and optional IP address
2. **server_name**: Domain name(s) this server block handles
3. **root**: Document root directory
4. **location**: URL path matching and handling

## 🌐 Multiple Server Blocks

You can define multiple server blocks to host different websites:

```nginx
http {
    # First website
    server {
        listen 80;
        server_name example.com www.example.com;
        root /var/www/example.com;
        index index.html;
        
        location / {
            try_files $uri $uri/ =404;
        }
    }
    
    # Second website
    server {
        listen 80;
        server_name another-site.com;
        root /var/www/another-site.com;
        index index.html;
        
        location / {
            try_files $uri $uri/ =404;
        }
    }
    
    # Third website
    server {
        listen 80;
        server_name api.example.com;
        root /var/www/api;
        index index.html;
        
        location / {
            try_files $uri $uri/ =404;
        }
    }
}
```

## 🎯 Server Name Matching

NGINX matches requests to server blocks based on `server_name` in this order:

1. **Exact name match**
2. **Longest wildcard starting with asterisk** (e.g., `*.example.com`)
3. **Longest wildcard ending with asterisk** (e.g., `mail.*`)
4. **First matching regex** (indicated by `~` prefix)
5. **Default server** (first server block with `default_server` flag or first server block)

### Matching Examples

```nginx
# Exact match (highest priority)
server {
    listen 80;
    server_name example.com;
    # Handles: example.com
}

# Wildcard prefix
server {
    listen 80;
    server_name *.example.com;
    # Handles: www.example.com, mail.example.com, etc.
    # Does NOT handle: example.com
}

# Wildcard suffix
server {
    listen 80;
    server_name example.*;
    # Handles: example.com, example.org, example.net
}

# Regex match
server {
    listen 80;
    server_name ~^www\.(.+)$;
    # Matches any domain starting with www.
    # Captured group available as $1
}
```

## 🏠 Default Server Block

The default server block handles requests that don't match any `server_name`:

```nginx
# Default server (catches all unmatched requests)
server {
    listen 80 default_server;
    server_name _;  # Catch-all
    
    root /var/www/default;
    index index.html;
    
    location / {
        return 444;  # Close connection without response
        # Or serve a default page
        # try_files $uri $uri/ =404;
    }
}

# Specific website
server {
    listen 80;
    server_name example.com;
    root /var/www/example.com;
    # ...
}
```

**When to use default_server:**
- Block requests to IP address
- Serve a default page for unmatched domains
- Prevent information disclosure

## 🔌 Listening on Different Ports

### HTTP (Port 80)

```nginx
server {
    listen 80;
    server_name example.com;
    # ...
}
```

### HTTPS (Port 443)

```nginx
server {
    listen 443 ssl;
    server_name example.com;
    # SSL configuration here
    # ...
}
```

### Custom Port

```nginx
server {
    listen 8080;
    server_name example.com;
    # ...
}
```

### Specific IP and Port

```nginx
# Listen on specific IP and port
server {
    listen 192.168.1.100:80;
    server_name example.com;
    # ...
}

# Multiple IPs
server {
    listen 192.168.1.100:80;
    listen 192.168.1.101:80;
    server_name example.com;
    # ...
}
```

## 📁 Organizing Server Blocks

### Method 1: All in nginx.conf

```nginx
http {
    include /etc/nginx/mime.types;
    
    server {
        # Site 1
    }
    
    server {
        # Site 2
    }
}
```

### Method 2: Separate Files (Recommended)

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
    root /var/www/example.com;
    # ...
}
```

**/etc/nginx/conf.d/another-site.com.conf:**
```nginx
server {
    listen 80;
    server_name another-site.com;
    root /var/www/another-site.com;
    # ...
}
```

### Method 3: sites-available/sites-enabled (Debian/Ubuntu)

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
    root /var/www/example.com;
    # ...
}
```

**Enable the site:**
```bash
# Create symlink
sudo ln -s /etc/nginx/sites-available/example.com /etc/nginx/sites-enabled/

# Test and reload
sudo nginx -t
sudo systemctl reload nginx
```

**Disable the site:**
```bash
# Remove symlink
sudo rm /etc/nginx/sites-enabled/example.com

# Test and reload
sudo nginx -t
sudo systemctl reload nginx
```

## 🎯 Practical Examples

### Example 1: Basic Website

```nginx
server {
    listen 80;
    server_name mysite.com www.mysite.com;
    
    root /var/www/mysite.com;
    index index.html index.htm;
    
    access_log /var/log/nginx/mysite.com.access.log;
    error_log /var/log/nginx/mysite.com.error.log;
    
    location / {
        try_files $uri $uri/ =404;
    }
}
```

### Example 2: Multiple Domains

```nginx
# Main site
server {
    listen 80;
    server_name example.com www.example.com;
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
    root /var/www/api;
    index index.html;
    
    location / {
        try_files $uri $uri/ =404;
    }
}
```

### Example 3: Development and Production

```nginx
# Production server
server {
    listen 80;
    server_name example.com www.example.com;
    root /var/www/example.com/public;
    index index.html;
    
    location / {
        try_files $uri $uri/ =404;
    }
}

# Development server
server {
    listen 8080;
    server_name dev.example.com;
    root /var/www/example.com/dev;
    index index.html;
    
    location / {
        try_files $uri $uri/ =404;
    }
}
```

### Example 4: Redirect www to non-www

```nginx
# Redirect www to non-www
server {
    listen 80;
    server_name www.example.com;
    return 301 http://example.com$request_uri;
}

# Main server
server {
    listen 80;
    server_name example.com;
    root /var/www/example.com;
    index index.html;
    
    location / {
        try_files $uri $uri/ =404;
    }
}
```

### Example 5: Default Server with Catch-All

```nginx
# Default server - block unmatched requests
server {
    listen 80 default_server;
    server_name _;
    return 444;  # Close connection
}

# Real website
server {
    listen 80;
    server_name example.com;
    root /var/www/example.com;
    index index.html;
    
    location / {
        try_files $uri $uri/ =404;
    }
}
```

## 🔍 Debugging Server Blocks

### Check Which Server Block is Used

Add this to your server block temporarily:

```nginx
server {
    listen 80;
    server_name example.com;
    
    # Debug: Show which server block matched
    add_header X-Server-Name $server_name;
    add_header X-Host $host;
    
    # ... rest of config
}
```

Then check headers:
```bash
curl -I http://example.com
```

### Test Server Name Matching

```bash
# Test specific server_name
curl -H "Host: example.com" http://your-server-ip

# Test default server
curl -H "Host: unknown-domain.com" http://your-server-ip
```

### View Active Configuration

```bash
# Test and show effective configuration
sudo nginx -T

# Show only server blocks
sudo nginx -T | grep -A 20 "server {"
```

## 📝 Exercises

1. Create two server blocks for two different domains
2. Set up a default server block that returns 444
3. Create server blocks for subdomains (www, blog, api)
4. Configure a server block that redirects www to non-www
5. Organize server blocks using separate files in conf.d/
6. Test which server block matches different host headers
7. Set up a development server on port 8080

## ✅ Checklist

- [ ] Understand what server blocks are
- [ ] Can create multiple server blocks
- [ ] Understand server_name matching priority
- [ ] Can configure default server block
- [ ] Know how to listen on different ports
- [ ] Can organize server blocks in separate files
- [ ] Can debug server block matching

## ➡️ Next Steps

Congratulations! You've completed the Beginner Level. Proceed to [Intermediate Level - Module 1: SSL/TLS](../intermediate/01-ssl-tls.md) to learn about securing your websites with HTTPS.

