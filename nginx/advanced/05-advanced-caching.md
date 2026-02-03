# Advanced Level - Module 5: Advanced Caching

## 📚 Learning Objectives

By the end of this module, you will:
- Understand advanced caching strategies
- Configure cache purging
- Implement cache segmentation
- Set up cache warming
- Configure cache revalidation
- Understand cache locking
- Monitor cache performance

## 🎯 Advanced Caching Concepts

Advanced caching involves:
- Cache purging and invalidation
- Cache segmentation
- Conditional caching
- Cache warming
- Cache revalidation
- Cache locking

## 🔄 Cache Purging

### Manual Cache Purging

```nginx
# Allow purge from specific IPs
location ~ /purge(/.*) {
    allow 127.0.0.1;
    allow 192.168.1.0/24;
    deny all;
    
    proxy_cache_purge cache_zone $scheme$request_method$host$1;
}
```

### Purge by Pattern

```nginx
# Purge all cache for a domain
location ~ /purge_all {
    allow 127.0.0.1;
    deny all;
    
    # Custom Lua script or module needed
    # Or use external tool
}
```

### Automatic Cache Invalidation

```nginx
http {
    proxy_cache_path /var/cache/nginx levels=1:2 keys_zone=my_cache:10m 
                     max_size=1g inactive=60m use_temp_path=off;
    
    # Map cache keys
    map $request_method $purge_method {
        PURGE 1;
        default 0;
    }
    
    server {
        location / {
            proxy_pass http://backend;
            proxy_cache my_cache;
            
            # Handle PURGE method
            proxy_cache_bypass $purge_method;
            proxy_no_cache $purge_method;
            
            # Purge on POST/PUT/DELETE
            proxy_cache_bypass $request_method;
            proxy_no_cache $request_method;
        }
    }
}
```

## 📊 Cache Segmentation

### Separate Cache Zones

```nginx
http {
    # Cache for static content
    proxy_cache_path /var/cache/nginx/static levels=1:2 
                     keys_zone=static_cache:50m max_size=5g 
                     inactive=7d use_temp_path=off;
    
    # Cache for dynamic content
    proxy_cache_path /var/cache/nginx/dynamic levels=1:2 
                     keys_zone=dynamic_cache:50m max_size=2g 
                     inactive=1h use_temp_path=off;
    
    # Cache for API responses
    proxy_cache_path /var/cache/nginx/api levels=1:2 
                     keys_zone=api_cache:10m max_size=500m 
                     inactive=10m use_temp_path=off;
    
    server {
        # Static content - long cache
        location ~* \.(jpg|jpeg|png|gif|css|js)$ {
            proxy_pass http://backend;
            proxy_cache static_cache;
            proxy_cache_valid 200 7d;
        }
        
        # Dynamic content - short cache
        location / {
            proxy_pass http://backend;
            proxy_cache dynamic_cache;
            proxy_cache_valid 200 1h;
        }
        
        # API - very short cache
        location /api/ {
            proxy_pass http://backend;
            proxy_cache api_cache;
            proxy_cache_valid 200 10m;
        }
    }
}
```

### Cache by User Role

```nginx
http {
    proxy_cache_path /var/cache/nginx levels=1:2 
                     keys_zone=my_cache:10m max_size=1g;
    
    map $http_authorization $cache_key {
        default $scheme$request_method$host$request_uri;
        "~Bearer.*" $scheme$request_method$host$request_uri$http_authorization;
    }
    
    server {
        location / {
            proxy_pass http://backend;
            proxy_cache my_cache;
            proxy_cache_key $cache_key;
        }
    }
}
```

## ⏰ Cache Revalidation

### Stale-While-Revalidate

```nginx
location / {
    proxy_pass http://backend;
    proxy_cache my_cache;
    
    # Serve stale content while revalidating
    proxy_cache_use_stale error timeout updating http_500 http_502 http_503 http_504;
    proxy_cache_background_update on;
    proxy_cache_revalidate on;
}
```

**How it works:**
- Serves stale content immediately
- Updates cache in background
- Next request gets fresh content

### Conditional Requests (ETag/Last-Modified)

```nginx
location / {
    proxy_pass http://backend;
    proxy_cache my_cache;
    
    # Use ETag and Last-Modified
    proxy_cache_revalidate on;
    
    # Pass conditional headers to backend
    proxy_set_header If-None-Match $http_if_none_match;
    proxy_set_header If-Modified-Since $http_if_modified_since;
}
```

## 🔒 Cache Locking

### Prevent Cache Stampede

```nginx
http {
    proxy_cache_path /var/cache/nginx levels=1:2 
                     keys_zone=my_cache:10m max_size=1g 
                     use_temp_path=off;
    
    proxy_cache_lock on;          # Enable cache locking
    proxy_cache_lock_timeout 5s;  # Lock timeout
    proxy_cache_lock_age 10s;     # Lock age
}
```

**Benefits:**
- Prevents multiple requests for same resource
- Reduces backend load
- First request fetches, others wait

## 🔥 Cache Warming

### Pre-populate Cache

```bash
# Warm cache by requesting common pages
curl http://example.com/
curl http://example.com/about
curl http://example.com/products
curl http://example.com/contact

# Or with script
#!/bin/bash
URLS=(
    "http://example.com/"
    "http://example.com/about"
    "http://example.com/products"
)

for url in "${URLS[@]}"; do
    curl -s "$url" > /dev/null
done
```

### Scheduled Cache Warming

```bash
# Add to crontab
*/5 * * * * /usr/local/bin/warm_cache.sh
```

## 📋 Advanced Cache Configuration

### Complete Advanced Setup

```nginx
http {
    # Main cache zone
    proxy_cache_path /var/cache/nginx/main levels=1:2 
                     keys_zone=main_cache:100m max_size=10g 
                     inactive=24h use_temp_path=off;
    
    # Static cache zone
    proxy_cache_path /var/cache/nginx/static levels=1:2 
                     keys_zone=static_cache:50m max_size=5g 
                     inactive=7d use_temp_path=off;
    
    # API cache zone
    proxy_cache_path /var/cache/nginx/api levels=1:2 
                     keys_zone=api_cache:10m max_size=500m 
                     inactive=10m use_temp_path=off;
    
    # Cache key variables
    map $request_method $cache_method {
        GET HEAD "";
        default "no_cache";
    }
    
    map $http_authorization $is_authenticated {
        default "";
        "~Bearer.*" "authenticated";
    }
    
    server {
        listen 80;
        server_name example.com;
        
        # Static content
        location ~* \.(jpg|jpeg|png|gif|ico|css|js|svg|woff|woff2)$ {
            proxy_pass http://backend;
            
            proxy_cache static_cache;
            proxy_cache_key "$scheme$request_method$host$request_uri";
            proxy_cache_valid 200 7d;
            proxy_cache_valid 404 1h;
            
            # Headers
            add_header X-Cache-Status $upstream_cache_status;
            add_header X-Cache-Key $request_uri;
            
            # Stale content
            proxy_cache_use_stale error timeout updating;
            proxy_cache_background_update on;
        }
        
        # API endpoints
        location /api/ {
            proxy_pass http://backend;
            
            proxy_cache api_cache;
            proxy_cache_key "$scheme$request_method$host$request_uri$is_authenticated";
            proxy_cache_valid 200 10m;
            proxy_cache_valid 404 1m;
            
            # Cache locking
            proxy_cache_lock on;
            proxy_cache_lock_timeout 5s;
            
            # Conditional requests
            proxy_cache_revalidate on;
            
            # Bypass cache for authenticated requests
            proxy_cache_bypass $is_authenticated;
            proxy_no_cache $is_authenticated;
            
            # Headers
            add_header X-Cache-Status $upstream_cache_status;
        }
        
        # Dynamic content
        location / {
            proxy_pass http://backend;
            
            proxy_cache main_cache;
            proxy_cache_key "$scheme$request_method$host$request_uri";
            proxy_cache_valid 200 1h;
            proxy_cache_valid 302 10m;
            proxy_cache_valid 404 5m;
            
            # Method-based caching
            proxy_cache_bypass $cache_method;
            proxy_no_cache $cache_method;
            
            # Stale while revalidate
            proxy_cache_use_stale error timeout updating http_500 http_502 http_503;
            proxy_cache_background_update on;
            proxy_cache_revalidate on;
            
            # Cache locking
            proxy_cache_lock on;
            proxy_cache_lock_timeout 5s;
            
            # Headers
            add_header X-Cache-Status $upstream_cache_status;
            add_header X-Cache-Key $request_uri;
            add_header Cache-Control "public, max-age=3600";
        }
        
        # Cache purge endpoint
        location ~ /purge(/.*) {
            allow 127.0.0.1;
            allow 192.168.1.0/24;
            deny all;
            
            proxy_cache_purge main_cache $scheme$request_method$host$1;
        }
    }
}
```

## 📊 Cache Monitoring

### Cache Statistics

```nginx
# Custom log format with cache info
log_format cache_log '$remote_addr - $remote_user [$time_local] '
                     '"$request" $status $body_bytes_sent '
                     'cache: $upstream_cache_status '
                     'time: $request_time';
```

### Monitor Cache Hit Ratio

```bash
# Count cache hits vs misses
sudo awk '{print $NF}' /var/log/nginx/access.log | grep cache | sort | uniq -c

# Calculate hit ratio
hits=$(sudo grep -c "cache: HIT" /var/log/nginx/access.log)
misses=$(sudo grep -c "cache: MISS" /var/log/nginx/access.log)
total=$((hits + misses))
ratio=$(echo "scale=2; $hits * 100 / $total" | bc)
echo "Cache hit ratio: ${ratio}%"
```

### Cache Size Monitoring

```bash
# Check cache directory size
du -sh /var/cache/nginx

# Count cached files
find /var/cache/nginx -type f | wc -l

# Find largest cache files
find /var/cache/nginx -type f -exec ls -lh {} \; | awk '{print $5, $9}' | sort -hr | head
```

## 🔍 Cache Debugging

### Enable Cache Debugging

```nginx
error_log /var/log/nginx/cache.log debug;
```

### Debug Headers

```nginx
location / {
    proxy_pass http://backend;
    proxy_cache my_cache;
    
    # Debug headers
    add_header X-Cache-Status $upstream_cache_status;
    add_header X-Cache-Key $request_uri;
    add_header X-Cache-Valid $upstream_cache_valid;
}
```

## 📝 Exercises

1. Set up cache purging mechanism
2. Create separate cache zones for different content types
3. Implement stale-while-revalidate
4. Enable cache locking
5. Set up cache warming script
6. Monitor cache hit ratio
7. Configure conditional cache revalidation
8. Test cache invalidation

## ✅ Checklist

- [ ] Understand advanced caching concepts
- [ ] Can configure cache purging
- [ ] Can segment caches
- [ ] Understand cache revalidation
- [ ] Can implement cache locking
- [ ] Can set up cache warming
- [ ] Can monitor cache performance
- [ ] Can debug cache issues

## ➡️ Next Steps

Proceed to [Module 6: HTTP/2 and HTTP/3](./06-http2-http3.md) to learn about modern HTTP protocols.

