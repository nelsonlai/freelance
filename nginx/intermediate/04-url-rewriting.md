# Intermediate Level - Module 4: URL Rewriting and Redirects

## 📚 Learning Objectives

By the end of this module, you will:
- Understand URL rewriting vs redirects
- Use `rewrite` directive
- Configure permanent and temporary redirects
- Handle URL patterns with regex
- Set up clean URLs
- Understand rewrite flags

## 🔄 Rewrite vs Redirect

### Rewrite
- **Internal**: Changes URL internally, browser doesn't see change
- **Same Request**: Client makes one request
- **Use Case**: Clean URLs, routing

### Redirect
- **External**: Browser makes new request to new URL
- **Two Requests**: Client makes two requests
- **Use Case**: Moving pages, forcing HTTPS, www/non-www

## ✏️ Rewrite Directive

### Basic Syntax

```nginx
rewrite regex replacement [flag];
```

### Examples

```nginx
# Rewrite /old to /new (internal)
rewrite ^/old$ /new last;

# Rewrite with regex
rewrite ^/users/(.*)$ /profile.php?user=$1 last;
```

## 🚩 Rewrite Flags

### last
Stops processing and searches for new location matching rewritten URI:

```nginx
location / {
    rewrite ^/old$ /new last;
    # If /new matches another location, that location is used
}

location /new {
    # This location will handle the rewritten /new
}
```

### break
Stops processing rewrite directives but continues in current location:

```nginx
location / {
    rewrite ^/old$ /new break;
    # Processing stops here, no more rewrites
    # Continues with current location block
}
```

### redirect
Temporary redirect (HTTP 302):

```nginx
rewrite ^/old$ /new redirect;
```

### permanent
Permanent redirect (HTTP 301):

```nginx
rewrite ^/old$ /new permanent;
```

## 🔀 Common Redirect Patterns

### HTTP to HTTPS

```nginx
server {
    listen 80;
    server_name example.com;
    return 301 https://$server_name$request_uri;
}
```

Or using rewrite:

```nginx
server {
    listen 80;
    server_name example.com;
    rewrite ^(.*)$ https://$server_name$1 permanent;
}
```

### www to non-www

```nginx
server {
    listen 80;
    server_name www.example.com;
    return 301 http://example.com$request_uri;
}

server {
    listen 80;
    server_name example.com;
    # ... main configuration
}
```

### non-www to www

```nginx
server {
    listen 80;
    server_name example.com;
    return 301 http://www.example.com$request_uri;
}

server {
    listen 80;
    server_name www.example.com;
    # ... main configuration
}
```

### Trailing Slash

```nginx
# Remove trailing slash
rewrite ^/(.*)/$ /$1 permanent;

# Add trailing slash
rewrite ^/(.*[^/])$ /$1/ permanent;
```

### Force Trailing Slash for Directories

```nginx
location / {
    # Add trailing slash if missing and is directory
    rewrite ^([^.]*[^/])$ $1/ permanent;
}
```

## 🎯 URL Rewriting Examples

### Clean URLs (Remove .php extension)

```nginx
location / {
    # Remove .php extension
    rewrite ^/(.*)\.php$ /$1 permanent;
    
    # Add .php extension internally
    rewrite ^/(.*)$ /$1.php last;
}
```

### RESTful API Routing

```nginx
location /api/ {
    rewrite ^/api/users/(.*)$ /api/user.php?id=$1 last;
    rewrite ^/api/posts/(.*)$ /api/post.php?id=$1 last;
    rewrite ^/api/categories/(.*)$ /api/category.php?slug=$1 last;
}
```

### Query String to Path

```nginx
# Convert /page.php?id=123 to /page/123
location / {
    rewrite ^/page/(.*)$ /page.php?id=$1 last;
}
```

### Remove Query Strings

```nginx
location / {
    # Remove query string
    rewrite ^(.*)\?.*$ $1 permanent;
}
```

### Add Query Parameters

```nginx
location / {
    rewrite ^(.*)$ $1?source=nginx permanent;
}
```

## 📋 Complete Rewrite Examples

### Example 1: Clean URLs for PHP Application

```nginx
server {
    listen 80;
    server_name example.com;
    root /var/www/html;
    index index.php index.html;
    
    location / {
        # Try files first, then try with .php, then 404
        try_files $uri $uri/ @php;
    }
    
    location @php {
        # Add .php extension
        rewrite ^/(.*)$ /$1.php last;
    }
    
    location ~ \.php$ {
        fastcgi_pass unix:/var/run/php/php7.4-fpm.sock;
        fastcgi_index index.php;
        include fastcgi_params;
        fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
    }
}
```

### Example 2: Multiple Redirects

```nginx
server {
    listen 80;
    server_name example.com www.example.com;
    
    # Redirect www to non-www
    if ($host = www.example.com) {
        return 301 http://example.com$request_uri;
    }
    
    # Redirect HTTP to HTTPS
    return 301 https://$server_name$request_uri;
}

server {
    listen 443 ssl http2;
    server_name example.com;
    
    ssl_certificate /etc/nginx/ssl/server.crt;
    ssl_certificate_key /etc/nginx/ssl/server.key;
    
    root /var/www/html;
    index index.html;
    
    location / {
        try_files $uri $uri/ =404;
    }
}
```

### Example 3: Complex URL Rewriting

```nginx
server {
    listen 80;
    server_name example.com;
    root /var/www/html;
    
    # Old blog structure to new
    rewrite ^/blog/(\d{4})/(\d{2})/(.*)$ /posts/$3 permanent;
    
    # Product pages
    rewrite ^/product/(.*)$ /product.php?slug=$1 last;
    
    # User profiles
    rewrite ^/user/(.*)$ /profile.php?username=$1 last;
    
    # Category pages
    rewrite ^/category/(.*)$ /category.php?cat=$1 last;
    
    location / {
        try_files $uri $uri/ =404;
    }
}
```

## 🔍 Conditional Rewrites

### Using if Directive

```nginx
# Redirect based on condition
if ($request_method = POST) {
    return 405;
}

# Redirect old domain
if ($host = olddomain.com) {
    return 301 http://newdomain.com$request_uri;
}

# Redirect based on user agent
if ($http_user_agent ~* "bot") {
    return 403;
}
```

**Warning**: Use `if` directive carefully. It can cause unexpected behavior.

### Better Approach: Map Directive

```nginx
# Define map
map $host $new_host {
    default $host;
    olddomain.com newdomain.com;
    www.olddomain.com www.newdomain.com;
}

server {
    listen 80;
    server_name example.com;
    
    if ($new_host != $host) {
        return 301 http://$new_host$request_uri;
    }
    
    # ... rest of config
}
```

## 📝 Practical Examples

### Example 1: WordPress Clean URLs

```nginx
location / {
    try_files $uri $uri/ /index.php?$args;
}

location ~ \.php$ {
    fastcgi_pass unix:/var/run/php/php7.4-fpm.sock;
    fastcgi_index index.php;
    include fastcgi_params;
    fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
}
```

### Example 2: Multiple Domain Redirects

```nginx
# Redirect multiple old domains to new domain
server {
    listen 80;
    server_name old1.com old2.com old3.com;
    return 301 https://newdomain.com$request_uri;
}

server {
    listen 443 ssl http2;
    server_name newdomain.com;
    # ... main configuration
}
```

### Example 3: API Versioning

```nginx
location /api/ {
    # Rewrite v1 to v2
    rewrite ^/api/v1/(.*)$ /api/v2/$1 permanent;
    
    # Current API version
    rewrite ^/api/v2/(.*)$ /api/current/$1 last;
}
```

## 🧪 Testing Rewrites

### Test Configuration

```bash
# Test syntax
sudo nginx -t

# Show effective configuration
sudo nginx -T | grep -A 5 rewrite
```

### Test Rewrites

```bash
# Test redirect
curl -I http://example.com/old
# Should return 301 or 302

# Test rewrite (internal)
curl http://example.com/old
# Should show content from /new

# Follow redirects
curl -L http://example.com/old
```

## 🔒 Security Considerations

### Prevent Directory Traversal

```nginx
# Block attempts to access parent directories
if ($request_uri ~ "\.\./") {
    return 403;
}
```

### Block Specific Paths

```nginx
# Block access to admin
location /admin {
    deny all;
    return 403;
}

# Block .htaccess and config files
location ~ /\.(ht|git) {
    deny all;
    return 404;
}
```

## 📝 Exercises

1. Set up HTTP to HTTPS redirect
2. Configure www to non-www redirect
3. Create clean URLs by removing file extensions
4. Rewrite query strings to path parameters
5. Set up multiple domain redirects
6. Create RESTful URL routing
7. Test your rewrites and redirects
8. Implement conditional redirects

## ✅ Checklist

- [ ] Understand difference between rewrite and redirect
- [ ] Can use rewrite directive
- [ ] Understand rewrite flags (last, break, redirect, permanent)
- [ ] Can set up HTTP to HTTPS redirect
- [ ] Can configure www/non-www redirects
- [ ] Can create clean URLs
- [ ] Understand conditional rewrites
- [ ] Can test rewrites and redirects

## ➡️ Next Steps

Proceed to [Module 5: Caching](./05-caching.md) to learn about caching strategies with NGINX.

