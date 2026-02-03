# Beginner Level - Module 4: Serving Static Files

## 📚 Learning Objectives

By the end of this module, you will:
- Configure NGINX to serve static files
- Understand the `root` and `alias` directives
- Set up proper file permissions
- Configure directory listings
- Handle different file types
- Set up caching for static content

## 🌐 What are Static Files?

Static files are files that don't change based on user input:
- HTML files
- CSS stylesheets
- JavaScript files
- Images (JPG, PNG, GIF, SVG)
- Fonts
- PDFs
- Videos

## 📂 Basic Static File Serving

### Simple Server Block

```nginx
server {
    listen 80;
    server_name example.com;
    
    # Document root directory
    root /var/www/example.com;
    
    # Default index files (checked in order)
    index index.html index.htm;
    
    # Location block for all requests
    location / {
        # Try to serve the requested file, or directory, or return 404
        try_files $uri $uri/ =404;
    }
}
```

### Understanding `root` Directive

The `root` directive sets the document root for the server:

```nginx
root /var/www/example.com;
```

If a request comes for `http://example.com/images/logo.png`, NGINX will look for:
```
/var/www/example.com/images/logo.png
```

## 🔄 Root vs Alias

### `root` Directive

Appends the full URI path to the root:

```nginx
location /images/ {
    root /var/www/example.com;
}
```

Request: `http://example.com/images/photo.jpg`  
File served: `/var/www/example.com/images/photo.jpg`

### `alias` Directive

Replaces the location path with the alias path:

```nginx
location /images/ {
    alias /var/www/photos/;
}
```

Request: `http://example.com/images/photo.jpg`  
File served: `/var/www/photos/photo.jpg`

**Note:** `alias` path must end with `/` when used in location blocks.

## 📋 Complete Static File Server Configuration

```nginx
server {
    listen 80;
    server_name example.com www.example.com;
    
    # Document root
    root /var/www/example.com/public;
    index index.html index.htm;
    
    # Logging
    access_log /var/log/nginx/example.com.access.log;
    error_log /var/log/nginx/example.com.error.log;
    
    # Main location block
    location / {
        try_files $uri $uri/ =404;
    }
    
    # Serve static assets with caching
    location ~* \.(jpg|jpeg|png|gif|ico|css|js|svg|woff|woff2|ttf|eot)$ {
        expires 1y;
        add_header Cache-Control "public, immutable";
        access_log off;
    }
    
    # Deny access to hidden files
    location ~ /\. {
        deny all;
        access_log off;
        log_not_found off;
    }
    
    # Custom error pages
    error_page 404 /404.html;
    error_page 500 502 503 504 /50x.html;
    
    location = /50x.html {
        root /usr/share/nginx/html;
    }
}
```

## 🗂️ Directory Listings

### Enable Directory Listings

```nginx
location /downloads/ {
    alias /var/www/downloads/;
    
    # Enable directory listing
    autoindex on;
    
    # Show file sizes in human-readable format
    autoindex_exact_size off;
    
    # Show local time instead of GMT
    autoindex_localtime on;
}
```

### Disable Directory Listings (Default)

```nginx
location / {
    # Directory listing is off by default
    autoindex off;
    try_files $uri $uri/ =404;
}
```

## 📁 File Permissions

Ensure proper file permissions:

```bash
# Set ownership
sudo chown -R www-data:www-data /var/www/example.com

# Set directory permissions (755 = rwxr-xr-x)
sudo find /var/www/example.com -type d -exec chmod 755 {} \;

# Set file permissions (644 = rw-r--r--)
sudo find /var/www/example.com -type f -exec chmod 644 {} \;
```

**Permission Breakdown:**
- **755** for directories: Owner (rwx), Group (rx), Others (rx)
- **644** for files: Owner (rw), Group (r), Others (r)

## ⚡ Performance Optimization for Static Files

### 1. Enable Sendfile

```nginx
http {
    sendfile on;
    tcp_nopush on;
    tcp_nodelay on;
}
```

### 2. Enable Gzip Compression

```nginx
http {
    gzip on;
    gzip_vary on;
    gzip_proxied any;
    gzip_comp_level 6;
    gzip_types text/plain text/css text/xml text/javascript 
               application/json application/javascript application/xml+rss 
               application/rss+xml font/truetype font/opentype 
               application/vnd.ms-fontobject image/svg+xml;
    gzip_disable "msie6";
}
```

### 3. Set Expires Headers

```nginx
# Cache static assets for 1 year
location ~* \.(jpg|jpeg|png|gif|ico|css|js)$ {
    expires 1y;
    add_header Cache-Control "public, immutable";
}

# Cache fonts
location ~* \.(woff|woff2|ttf|eot)$ {
    expires 1y;
    add_header Cache-Control "public, immutable";
    add_header Access-Control-Allow-Origin *;
}
```

## 🎯 Serving Different File Types

### HTML Files

```nginx
location / {
    root /var/www/html;
    index index.html index.htm;
    try_files $uri $uri/ =404;
}
```

### CSS and JavaScript

```nginx
location ~* \.(css|js)$ {
    root /var/www/static;
    expires 30d;
    add_header Cache-Control "public";
}
```

### Images

```nginx
location ~* \.(jpg|jpeg|png|gif|ico|svg|webp)$ {
    root /var/www/images;
    expires 365d;
    add_header Cache-Control "public, immutable";
    
    # Optional: Image optimization
    image_filter resize 800 600;
}
```

### PDF Files

```nginx
location ~* \.pdf$ {
    root /var/www/documents;
    add_header Content-Disposition 'attachment';
    expires 7d;
}
```

### Font Files (with CORS)

```nginx
location ~* \.(woff|woff2|ttf|eot)$ {
    root /var/www/fonts;
    expires 1y;
    add_header Cache-Control "public, immutable";
    add_header Access-Control-Allow-Origin *;
}
```

## 🔒 Security Considerations

### 1. Deny Access to Hidden Files

```nginx
location ~ /\. {
    deny all;
    access_log off;
    log_not_found off;
}
```

### 2. Deny Access to Backup Files

```nginx
location ~* \.(bak|backup|old|orig|save|swp|tmp)$ {
    deny all;
    access_log off;
    log_not_found off;
}
```

### 3. Prevent Directory Traversal

```nginx
location / {
    # This is handled automatically by NGINX
    # But you can add explicit checks
    try_files $uri $uri/ =404;
}
```

### 4. Limit File Upload Size

```nginx
http {
    client_max_body_size 10M;
}

# Or per server
server {
    client_max_body_size 5M;
}
```

## 📝 Practical Example: Complete Static Site

```nginx
server {
    listen 80;
    server_name mysite.local;
    
    root /var/www/mysite;
    index index.html;
    
    # Enable gzip
    gzip on;
    gzip_types text/plain text/css application/json application/javascript text/xml application/xml application/xml+rss text/javascript;
    
    # Main location
    location / {
        try_files $uri $uri/ =404;
    }
    
    # Cache static assets
    location ~* \.(jpg|jpeg|png|gif|ico|css|js|svg|woff|woff2)$ {
        expires 1y;
        add_header Cache-Control "public, immutable";
    }
    
    # Deny hidden files
    location ~ /\. {
        deny all;
    }
    
    # Custom 404 page
    error_page 404 /404.html;
    
    # Logging
    access_log /var/log/nginx/mysite.access.log;
    error_log /var/log/nginx/mysite.error.log;
}
```

## 🧪 Testing Your Configuration

### 1. Create Test Files

```bash
# Create directory
sudo mkdir -p /var/www/mysite

# Create index.html
sudo tee /var/www/mysite/index.html > /dev/null <<EOF
<!DOCTYPE html>
<html>
<head>
    <title>My Site</title>
</head>
<body>
    <h1>Welcome to My Site!</h1>
    <img src="/images/logo.png" alt="Logo">
</body>
</html>
EOF

# Create images directory and test image
sudo mkdir -p /var/www/mysite/images
# (Add an image file here)
```

### 2. Set Permissions

```bash
sudo chown -R www-data:www-data /var/www/mysite
sudo chmod -R 755 /var/www/mysite
```

### 3. Test and Reload

```bash
sudo nginx -t
sudo systemctl reload nginx
```

### 4. Test in Browser

Visit `http://mysite.local` or `http://localhost`

## 📝 Exercises

1. Create a directory `/var/www/test-site` with an `index.html` file
2. Configure NGINX to serve files from this directory
3. Add a location block to cache images for 30 days
4. Enable directory listings for a `/files` location
5. Configure proper file permissions
6. Test serving different file types (HTML, CSS, JS, images)
7. Add security rules to deny access to hidden files

## ✅ Checklist

- [ ] Understand `root` and `alias` directives
- [ ] Can configure basic static file serving
- [ ] Know how to enable/disable directory listings
- [ ] Understand file permissions
- [ ] Can set up caching for static assets
- [ ] Know how to serve different file types
- [ ] Understand security considerations

## ➡️ Next Steps

Proceed to [Module 5: Server Blocks](./05-server-blocks.md) to learn about virtual hosting with NGINX.

