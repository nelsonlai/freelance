# Intermediate Level - Module 5: Caching

## 📚 Learning Objectives

By the end of this module, you will:
- Understand caching concepts
- Configure proxy caching
- Set cache keys and zones
- Configure cache expiration
- Handle cache purging
- Understand browser caching

## 🗄️ What is Caching?

Caching stores frequently accessed data in faster storage to improve performance:
- **Faster Response Times**: Serve from cache instead of backend
- **Reduced Backend Load**: Fewer requests to backend servers
- **Better User Experience**: Faster page loads
- **Lower Bandwidth**: Reduced data transfer

## 🎯 Types of Caching in NGINX

1. **Proxy Cache**: Cache backend responses
2. **Browser Cache**: Cache directives for clients
3. **FastCGI Cache**: Cache FastCGI responses
4. **uwsgi Cache**: Cache uWSGI responses
5. **SCGI Cache**: Cache SCGI responses

## 🔧 Proxy Caching Configuration

### Basic Cache Setup

```nginx
http {
    # Define cache zone
    proxy_cache_path /var/cache/nginx levels=1:2 keys_zone=my_cache:10m 
                     max_size=1g inactive=60m use_temp_path=off;
    
    server {
        listen 80;
        server_name example.com;
        
        location / {
            proxy_pass http://backend;
            
            # Enable caching
            proxy_cache my_cache;
            
            # Cache key
            proxy_cache_key "$scheme$request_method$host$request_uri";
            
            # Cache valid responses
            proxy_cache_valid 200 302 10m;
            proxy_cache_valid 404 1m;
        }
    }
}
```

### Cache Zone Parameters

```nginx
proxy_cache_path /var/cache/nginx
    levels=1:2                    # Directory levels for cache files
    keys_zone=my_cache:10m        # Zone name and size (metadata)
    max_size=1g                   # Maximum cache size
    inactive=60m                  # Remove files not accessed in 60m
    use_temp_path=off;            # Store files directly in cache path
```

**Directory Levels:**
- `levels=1:2` creates: `/var/cache/nginx/a/bc/abcdef...`
- Helps avoid too many files in one directory

## 📋 Cache Directives

### Basic Cache Directives

```nginx
location / {
    proxy_pass http://backend;
    
    # Enable cache
    proxy_cache my_cache;
    
    # Cache key (unique identifier)
    proxy_cache_key "$scheme$request_method$host$request_uri";
    
    # Cache methods (GET and HEAD by default)
    proxy_cache_methods GET HEAD;
    
    # Cache valid status codes
    proxy_cache_valid 200 302 10m;    # Cache 200 and 302 for 10 minutes
    proxy_cache_valid 404 1m;         # Cache 404 for 1 minute
    proxy_cache_valid any 5m;         # Cache all others for 5 minutes
    
    # Bypass cache conditions
    proxy_cache_bypass $http_pragma $http_authorization;
    
    # Don't cache conditions
    proxy_no_cache $http_pragma $http_authorization;
}
```

### Cache Headers

```nginx
location / {
    proxy_pass http://backend;
    proxy_cache my_cache;
    
    # Add cache status header
    add_header X-Cache-Status $upstream_cache_status;
    
    # Cache control
    proxy_cache_use_stale error timeout updating http_500 http_502 http_503 http_504;
    proxy_cache_background_update on;
    proxy_cache_revalidate on;
}
```

**Cache Status Values:**
- `MISS`: Not in cache
- `HIT`: Served from cache
- `EXPIRED`: Expired, fetching new
- `STALE`: Serving stale (if configured)
- `UPDATING`: Currently updating
- `REVALIDATED`: Revalidated with backend
- `BYPASS`: Cache bypassed

## ⏰ Cache Expiration

### Time-Based Expiration

```nginx
location / {
    proxy_pass http://backend;
    proxy_cache my_cache;
    
    # Cache for specific times
    proxy_cache_valid 200 302 10m;     # 10 minutes
    proxy_cache_valid 404 1m;          # 1 minute
    proxy_cache_valid 5m;              # All others: 5 minutes
}
```

### Header-Based Expiration

```nginx
location / {
    proxy_pass http://backend;
    proxy_cache my_cache;
    
    # Use backend Cache-Control header
    proxy_cache_valid 200 302 10m;
    proxy_ignore_headers Cache-Control;
    
    # Or respect backend headers
    proxy_cache_use_stale error timeout http_500 http_502 http_503;
}
```

## 🔄 Cache Purging

### Manual Cache Purging

Delete cache files manually:

```bash
# Delete entire cache
sudo rm -rf /var/cache/nginx/*

# Delete specific cache (need to know hash)
sudo find /var/cache/nginx -name "*hash*" -delete
```

### Cache Purge Module (nginx-module-http-purge)

```nginx
# Allow purge from localhost only
location ~ /purge(/.*) {
    allow 127.0.0.1;
    deny all;
    proxy_cache_purge my_cache $scheme$request_method$host$1;
}
```

**Usage:**
```bash
curl -X PURGE http://example.com/purge/page.html
```

## 🌐 Browser Caching (Client-Side)

### Cache-Control Headers

```nginx
location ~* \.(jpg|jpeg|png|gif|ico|css|js)$ {
    expires 1y;
    add_header Cache-Control "public, immutable";
}

location / {
    expires 1h;
    add_header Cache-Control "public, must-revalidate";
}
```

### Expires Directive

```nginx
location / {
    expires 24h;              # 24 hours
    expires 30d;              # 30 days
    expires 1y;               # 1 year
    expires epoch;            # No expiration
    expires max;              # Maximum (10 years)
    expires off;              # No Expires header
}
```

### ETag Support

```nginx
location / {
    etag on;                  # Enable ETag
    # ETag is on by default
}
```

## 📊 Complete Caching Configuration

### Example 1: Static Files

```nginx
server {
    listen 80;
    server_name example.com;
    
    root /var/www/html;
    
    # Cache static assets
    location ~* \.(jpg|jpeg|png|gif|ico|css|js|svg|woff|woff2)$ {
        expires 1y;
        add_header Cache-Control "public, immutable";
        access_log off;
    }
    
    # HTML files - shorter cache
    location ~* \.html$ {
        expires 1h;
        add_header Cache-Control "public, must-revalidate";
    }
}
```

### Example 2: Proxy Cache

```nginx
http {
    # Cache zone
    proxy_cache_path /var/cache/nginx levels=1:2 keys_zone=backend_cache:10m 
                     max_size=1g inactive=60m use_temp_path=off;
    
    server {
        listen 80;
        server_name example.com;
        
        location / {
            proxy_pass http://backend;
            
            # Caching
            proxy_cache backend_cache;
            proxy_cache_key "$scheme$request_method$host$request_uri";
            proxy_cache_valid 200 302 10m;
            proxy_cache_valid 404 1m;
            
            # Headers
            proxy_set_header Host $host;
            proxy_set_header X-Real-IP $remote_addr;
            
            # Cache status
            add_header X-Cache-Status $upstream_cache_status;
        }
        
        # Don't cache API endpoints
        location /api/ {
            proxy_pass http://backend;
            proxy_cache_bypass 1;
            proxy_no_cache 1;
        }
    }
}
```

### Example 3: Advanced Caching

```nginx
http {
    proxy_cache_path /var/cache/nginx levels=1:2 keys_zone=my_cache:50m 
                     max_size=10g inactive=24h use_temp_path=off;
    
    # Split cache by request method
    map $request_method $cache_method {
        GET HEAD "";
        default "no_cache";
    }
    
    server {
        listen 80;
        server_name example.com;
        
        location / {
            proxy_pass http://backend;
            
            proxy_cache my_cache;
            proxy_cache_key "$scheme$request_method$host$request_uri$is_args$args";
            
            # Conditional caching
            proxy_cache_bypass $cache_method;
            proxy_no_cache $cache_method;
            
            # Cache validation
            proxy_cache_valid 200 302 1h;
            proxy_cache_valid 404 5m;
            proxy_cache_valid any 10m;
            
            # Stale cache
            proxy_cache_use_stale error timeout updating http_500 http_502 http_503 http_504;
            proxy_cache_background_update on;
            proxy_cache_revalidate on;
            
            # Headers
            add_header X-Cache-Status $upstream_cache_status;
            add_header X-Cache-Key $request_uri;
            
            proxy_set_header Host $host;
            proxy_set_header X-Real-IP $remote_addr;
        }
    }
}
```

## 🔍 Cache Debugging

### Enable Cache Logging

```nginx
http {
    log_format cache_log '$remote_addr - $remote_user [$time_local] '
                         '"$request" $status $body_bytes_sent '
                         '"$http_referer" "$http_user_agent" '
                         'cache: $upstream_cache_status';
    
    access_log /var/log/nginx/cache.log cache_log;
}
```

### Check Cache Status

```bash
# Check cache directory size
du -sh /var/cache/nginx

# Count cached files
find /var/cache/nginx -type f | wc -l

# Check cache headers in response
curl -I http://example.com | grep -i cache

# Test cache hit
curl -v http://example.com 2>&1 | grep -i cache
```

## 🎯 Cache Best Practices

### 1. Cache Static Content Aggressively

```nginx
location ~* \.(jpg|jpeg|png|gif|ico|css|js|svg|woff|woff2)$ {
    expires 1y;
    add_header Cache-Control "public, immutable";
}
```

### 2. Cache Dynamic Content Carefully

```nginx
location / {
    proxy_cache my_cache;
    proxy_cache_valid 200 5m;  # Short cache for dynamic content
}
```

### 3. Don't Cache Personalized Content

```nginx
location /user/ {
    proxy_pass http://backend;
    proxy_cache_bypass 1;
    proxy_no_cache 1;
}
```

### 4. Use Cache Purging for Updates

Set up purge mechanism for immediate cache invalidation.

### 5. Monitor Cache Performance

Monitor cache hit ratio and adjust accordingly.

## 📝 Exercises

1. Set up basic proxy cache
2. Configure cache expiration times
3. Set up browser caching for static files
4. Configure cache bypass for specific paths
5. Add cache status headers
6. Test cache hits and misses
7. Set up cache purging (if module available)
8. Monitor cache performance

## ✅ Checklist

- [ ] Understand caching concepts
- [ ] Can configure proxy cache zones
- [ ] Understand cache directives
- [ ] Can set cache expiration
- [ ] Can configure browser caching
- [ ] Understand cache purging
- [ ] Can debug cache issues
- [ ] Know cache best practices

## ➡️ Next Steps

Proceed to [Module 6: Virtual Hosting](./06-virtual-hosting.md) to learn advanced virtual hosting techniques.

