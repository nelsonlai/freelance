# Advanced Level - Module 4: Rate Limiting

## 📚 Learning Objectives

By the end of this module, you will:
- Understand rate limiting concepts
- Configure request rate limiting
- Set up connection limiting
- Implement IP-based limiting
- Configure burst and delay
- Handle rate limit whitelisting
- Monitor rate limiting effectiveness

## 🚦 Rate Limiting Overview

Rate limiting protects your server by:
- Preventing DDoS attacks
- Reducing server load
- Preventing abuse
- Ensuring fair resource usage
- Protecting against brute force attacks

## 📊 Request Rate Limiting

### Basic Rate Limiting

```nginx
http {
    # Define rate limit zone
    limit_req_zone $binary_remote_addr zone=general:10m rate=10r/s;
    
    server {
        location / {
            # Apply rate limit
            limit_req zone=general;
            
            proxy_pass http://backend;
        }
    }
}
```

**Explanation:**
- `$binary_remote_addr`: Key (client IP)
- `zone=general:10m`: Zone name and memory size (10MB)
- `rate=10r/s`: 10 requests per second

### Rate Limit with Burst

```nginx
http {
    limit_req_zone $binary_remote_addr zone=general:10m rate=10r/s;
    
    server {
        location / {
            # Allow burst of 20 requests
            limit_req zone=general burst=20;
            
            proxy_pass http://backend;
        }
    }
}
```

**How burst works:**
- Normal rate: 10 requests/second
- Burst: Allows 20 extra requests in queue
- Excess requests are delayed

### Burst with No Delay

```nginx
location / {
    # Burst without delay (up to burst limit)
    limit_req zone=general burst=20 nodelay;
    
    proxy_pass http://backend;
}
```

**Difference:**
- `burst=20`: Queues requests, applies delay
- `burst=20 nodelay`: Allows burst, rejects after limit

## 🔢 Multiple Rate Limits

### Different Limits for Different Paths

```nginx
http {
    # General limit
    limit_req_zone $binary_remote_addr zone=general:10m rate=10r/s;
    
    # Stricter limit for API
    limit_req_zone $binary_remote_addr zone=api:10m rate=5r/s;
    
    # Very strict for auth
    limit_req_zone $binary_remote_addr zone=auth:10m rate=1r/s;
    
    server {
        location / {
            limit_req zone=general burst=20;
            # ...
        }
        
        location /api/ {
            limit_req zone=api burst=10;
            # ...
        }
        
        location /login {
            limit_req zone=auth burst=3 nodelay;
            # ...
        }
    }
}
```

### Nested Rate Limits

```nginx
http {
    limit_req_zone $binary_remote_addr zone=global:10m rate=100r/s;
    limit_req_zone $binary_remote_addr zone=per_location:10m rate=10r/s;
    
    server {
        # Global limit
        limit_req zone=global burst=50;
        
        location / {
            # Additional per-location limit
            limit_req zone=per_location burst=20;
            # ...
        }
    }
}
```

## 🔌 Connection Limiting

### Limit Connections per IP

```nginx
http {
    # Connection limit zone
    limit_conn_zone $binary_remote_addr zone=conn_limit:10m;
    
    server {
        # Limit to 10 connections per IP
        limit_conn conn_limit 10;
        
        location / {
            # ...
        }
    }
}
```

### Limit Connections per Server

```nginx
http {
    limit_conn_zone $server_name zone=perserver:10m;
    
    server {
        server_name example.com;
        
        # Limit to 100 connections per server
        limit_conn perserver 100;
        
        location / {
            # ...
        }
    }
}
```

### Multiple Connection Limits

```nginx
http {
    limit_conn_zone $binary_remote_addr zone=perip:10m;
    limit_conn_zone $server_name zone=perserver:10m;
    
    server {
        # Both limits apply
        limit_conn perip 10;
        limit_conn perserver 100;
        
        location / {
            # ...
        }
    }
}
```

## 🌐 Advanced Rate Limiting

### Whitelist Specific IPs

```nginx
http {
    # Geo block for whitelisting
    geo $limit {
        default 1;
        127.0.0.1 0;           # Localhost
        192.168.1.0/24 0;      # Internal network
        10.0.0.0/8 0;          # VPN network
    }
    
    map $limit $limit_key {
        0 "";
        1 $binary_remote_addr;
    }
    
    limit_req_zone $limit_key zone=general:10m rate=10r/s;
    
    server {
        limit_req zone=general burst=20;
        # Whitelisted IPs bypass rate limit
    }
}
```

### Rate Limiting by Location

```nginx
http {
    geo $country_code {
        default US;
        # Add country mappings
    }
    
    map $country_code $rate_limit {
        default "10r/s";
        "CN" "5r/s";
        "RU" "5r/s";
    }
    
    limit_req_zone $binary_remote_addr zone=dynamic:10m rate=10r/s;
    
    server {
        # Use dynamic rate based on location
        limit_req zone=dynamic burst=20;
    }
}
```

### Rate Limiting by User Agent

```nginx
http {
    map $http_user_agent $limit_bots {
        default "";
        ~*bot "1";
        ~*crawler "1";
        ~*spider "1";
    }
    
    map $limit_bots $limit_key {
        default $binary_remote_addr;
        "1" "";
    }
    
    limit_req_zone $limit_key zone=general:10m rate=10r/s;
    
    server {
        # Bots bypass rate limit (or create separate limit)
        limit_req zone=general burst=20;
    }
}
```

## 📝 Custom Error Responses

### Custom Rate Limit Error Page

```nginx
http {
    limit_req_zone $binary_remote_addr zone=general:10m rate=10r/s;
    
    server {
        limit_req zone=general burst=20;
        
        # Custom error page
        error_page 429 /rate_limit.html;
        
        location = /rate_limit.html {
            root /usr/share/nginx/html;
            internal;
        }
        
        location / {
            # ...
        }
    }
}
```

### Custom Error Response

```nginx
location / {
    limit_req zone=general burst=20;
    
    # Return JSON for API
    error_page 429 = @ratelimit;
    
    location @ratelimit {
        default_type application/json;
        return 429 '{"error":"Too many requests","retry_after":60}';
    }
}
```

## 📊 Rate Limit Status Headers

### Add Rate Limit Headers

```nginx
http {
    limit_req_zone $binary_remote_addr zone=general:10m rate=10r/s;
    
    server {
        location / {
            limit_req zone=general burst=20;
            
            # Add rate limit status headers
            add_header X-RateLimit-Limit "10" always;
            add_header X-RateLimit-Remaining "$limit_req_status" always;
            
            # ...
        }
    }
}
```

## 🔍 Monitoring Rate Limits

### Log Rate Limit Events

```nginx
http {
    log_format rate_limit '$remote_addr - $remote_user [$time_local] '
                          '"$request" $status $body_bytes_sent '
                          '"$http_referer" "$http_user_agent" '
                          'rate_limit: $limit_req_status';
    
    access_log /var/log/nginx/rate_limit.log rate_limit;
    
    limit_req_zone $binary_remote_addr zone=general:10m rate=10r/s;
    
    server {
        limit_req zone=general burst=20;
        # ...
    }
}
```

### Analyze Rate Limit Logs

```bash
# Count rate limit hits
sudo grep "PASSED\|REJECTED\|DELAYED" /var/log/nginx/rate_limit.log | wc -l

# Find IPs hitting limits
sudo awk '/REJECTED/ {print $1}' /var/log/nginx/rate_limit.log | sort | uniq -c | sort -rn
```

## 📋 Complete Rate Limiting Configuration

```nginx
http {
    # Rate limit zones
    limit_req_zone $binary_remote_addr zone=general:10m rate=10r/s;
    limit_req_zone $binary_remote_addr zone=api:10m rate=20r/s;
    limit_req_zone $binary_remote_addr zone=auth:10m rate=1r/m;
    
    # Connection limit zones
    limit_conn_zone $binary_remote_addr zone=conn_limit:10m;
    limit_conn_zone $server_name zone=perserver:10m;
    
    # Whitelist
    geo $whitelist {
        default 1;
        127.0.0.1 0;
        192.168.1.0/24 0;
    }
    
    map $whitelist $limit_key {
        0 "";
        1 $binary_remote_addr;
    }
    
    limit_req_zone $limit_key zone=general:10m rate=10r/s;
    
    server {
        listen 80;
        server_name example.com;
        
        # Connection limits
        limit_conn conn_limit 10;
        limit_conn perserver 100;
        
        # General rate limit
        limit_req zone=general burst=20 nodelay;
        
        # Custom error page
        error_page 429 /rate_limit.html;
        location = /rate_limit.html {
            root /usr/share/nginx/html;
            internal;
        }
        
        # Main location
        location / {
            proxy_pass http://backend;
        }
        
        # API with higher limit
        location /api/ {
            limit_req zone=api burst=50 nodelay;
            proxy_pass http://backend;
        }
        
        # Auth with strict limit
        location ~ ^/(login|register) {
            limit_req zone=auth burst=3 nodelay;
            proxy_pass http://backend;
        }
    }
}
```

## 🧪 Testing Rate Limits

### Test with curl

```bash
# Single request
curl http://example.com

# Multiple rapid requests
for i in {1..30}; do curl http://example.com; done

# Test with delay
for i in {1..30}; do curl http://example.com; sleep 0.1; done
```

### Test with Apache Bench

```bash
# 1000 requests, 100 concurrent
ab -n 1000 -c 100 http://example.com/
```

### Monitor in Real-Time

```bash
# Watch error log
sudo tail -f /var/log/nginx/error.log | grep "limiting requests"

# Watch access log
sudo tail -f /var/log/nginx/access.log
```

## 📝 Exercises

1. Set up basic rate limiting (10 requests/second)
2. Configure burst handling
3. Implement different limits for different paths
4. Set up connection limiting
5. Create IP whitelist for rate limits
6. Configure custom error pages for rate limits
7. Monitor rate limit effectiveness
8. Test rate limits under load

## ✅ Checklist

- [ ] Understand rate limiting concepts
- [ ] Can configure request rate limiting
- [ ] Understand burst and nodelay options
- [ ] Can set up connection limiting
- [ ] Can whitelist IPs
- [ ] Can configure custom error responses
- [ ] Can monitor rate limiting
- [ ] Can test rate limits

## ➡️ Next Steps

Proceed to [Module 5: Advanced Caching](./05-advanced-caching.md) to learn advanced caching strategies.

