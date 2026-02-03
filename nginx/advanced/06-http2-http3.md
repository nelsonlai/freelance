# Advanced Level - Module 6: HTTP/2 and HTTP/3

## 📚 Learning Objectives

By the end of this module, you will:
- Understand HTTP/2 features and benefits
- Configure HTTP/2 in NGINX
- Understand HTTP/3 (QUIC) protocol
- Configure HTTP/3 support
- Optimize for HTTP/2
- Troubleshoot HTTP/2 issues

## 🚀 HTTP/2 Overview

HTTP/2 is a major revision of HTTP protocol with:
- **Multiplexing**: Multiple requests over single connection
- **Header Compression**: HPACK compression
- **Server Push**: Proactive resource delivery
- **Binary Protocol**: More efficient than text
- **Stream Prioritization**: Better resource loading

### Benefits

- Faster page loads
- Reduced latency
- Better bandwidth utilization
- Improved mobile performance
- Backward compatible

## 🔧 HTTP/2 Configuration

### Basic HTTP/2 Setup

```nginx
server {
    listen 443 ssl http2;
    server_name example.com;
    
    ssl_certificate /etc/nginx/ssl/server.crt;
    ssl_certificate_key /etc/nginx/ssl/server.key;
    
    # ... rest of configuration
}
```

**Requirements:**
- SSL/TLS (HTTP/2 requires HTTPS)
- NGINX 1.9.5+ with HTTP/2 support
- Modern browser

### HTTP/2 with HTTP/1.1 Fallback

```nginx
# HTTPS with HTTP/2
server {
    listen 443 ssl http2;
    server_name example.com;
    # ... HTTPS configuration
}

# HTTP redirect (still uses HTTP/1.1)
server {
    listen 80;
    server_name example.com;
    return 301 https://$server_name$request_uri;
}
```

## 📦 HTTP/2 Push

### Server Push Configuration

```nginx
http {
    # Enable HTTP/2 push
    http2_push_preload on;
    
    server {
        listen 443 ssl http2;
        server_name example.com;
        
        location / {
            # Push critical resources
            http2_push /style.css;
            http2_push /app.js;
            http2_push /logo.png;
            
            root /var/www/html;
            index index.html;
        }
    }
}
```

### Conditional Push

```nginx
location / {
    root /var/www/html;
    index index.html;
    
    # Push based on Link headers from backend
    proxy_http_version 1.1;
    proxy_set_header Connection "";
}
```

## ⚡ HTTP/2 Optimization

### Connection Settings

```nginx
http {
    # HTTP/2 settings
    http2_max_field_size 16k;
    http2_max_header_size 32k;
    http2_max_concurrent_streams 128;
    http2_recv_buffer_size 256k;
    
    server {
        listen 443 ssl http2;
        # ...
    }
}
```

### Stream Prioritization

```nginx
server {
    listen 443 ssl http2;
    
    # Critical resources loaded first
    location ~* \.(css)$ {
        add_header Link "</style.css>; rel=preload; as=style";
    }
    
    location ~* \.(js)$ {
        add_header Link "</app.js>; rel=preload; as=script";
    }
}
```

## 🔒 HTTP/2 Security

### Strong SSL/TLS for HTTP/2

```nginx
server {
    listen 443 ssl http2;
    server_name example.com;
    
    # Strong SSL configuration
    ssl_protocols TLSv1.2 TLSv1.3;
    ssl_ciphers 'ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256';
    ssl_prefer_server_ciphers off;
    
    # HTTP/2 specific
    http2_max_field_size 16k;
    http2_max_header_size 32k;
    
    # ... rest of configuration
}
```

## 🧪 Testing HTTP/2

### Browser Testing

1. Open browser developer tools
2. Check Network tab
3. Protocol column shows "h2" for HTTP/2

### Command Line Testing

```bash
# Check if HTTP/2 is enabled
curl -I --http2 https://example.com

# Test with nghttp2
nghttp -vn https://example.com

# Check ALPN negotiation
openssl s_client -alpn h2 -connect example.com:443
```

### Online Tools

- [HTTP/2 Test](https://tools.keycdn.com/http2-test)
- [WebPageTest](https://www.webpagetest.org/)

## 🌐 HTTP/3 (QUIC) Overview

HTTP/3 uses QUIC protocol over UDP:
- **Built-in Encryption**: TLS 1.3
- **Connection Migration**: Survives IP changes
- **Multiplexing**: No head-of-line blocking
- **Faster Handshakes**: 0-RTT and 1-RTT
- **Better Mobile**: Handles network switching

### HTTP/3 Status

- NGINX Plus supports HTTP/3
- Open source NGINX requires QUIC module
- Still evolving standard

## 🔧 HTTP/3 Configuration (NGINX Plus/QUIC Module)

### Basic HTTP/3 Setup

```nginx
server {
    listen 443 ssl http2;
    listen 443 quic reuseport;  # QUIC on same port
    
    server_name example.com;
    
    ssl_certificate /etc/nginx/ssl/server.crt;
    ssl_certificate_key /etc/nginx/ssl/server.key;
    
    # HTTP/3 specific
    add_header Alt-Svc 'h3=":443"; ma=86400';
    
    # ... rest of configuration
}
```

### HTTP/3 with Fallbacks

```nginx
server {
    # HTTP/2 and HTTP/1.1
    listen 443 ssl http2;
    
    # HTTP/3 (QUIC)
    listen 443 quic reuseport;
    
    server_name example.com;
    
    ssl_certificate /etc/nginx/ssl/server.crt;
    ssl_certificate_key /etc/nginx/ssl/server.key;
    
    # Announce HTTP/3 support
    add_header Alt-Svc 'h3=":443"; ma=86400, h3-29=":443"; ma=86400';
    
    # ... rest of configuration
}
```

## 📊 Performance Comparison

### HTTP/1.1 vs HTTP/2 vs HTTP/3

**HTTP/1.1:**
- One request per connection
- Text-based protocol
- No header compression
- Sequential loading

**HTTP/2:**
- Multiple requests per connection
- Binary protocol
- Header compression (HPACK)
- Server push support
- Requires TLS

**HTTP/3:**
- QUIC over UDP
- Built-in encryption
- Better multiplexing
- Connection migration
- Faster handshakes

## 🔍 Troubleshooting HTTP/2

### Check HTTP/2 Support

```bash
# Check NGINX version
nginx -v

# Check compilation options
nginx -V | grep http_v2

# Test connection
curl -I --http2 https://example.com
```

### Common Issues

**1. HTTP/2 Not Working**
- Check SSL certificate is valid
- Verify `http2` in listen directive
- Check browser support

**2. Push Not Working**
- Verify browser support
- Check resource paths
- Verify SSL connection

**3. Performance Issues**
- Adjust `http2_max_concurrent_streams`
- Optimize server push
- Check network conditions

## 📝 Complete HTTP/2 Configuration

```nginx
http {
    # HTTP/2 settings
    http2_max_field_size 16k;
    http2_max_header_size 32k;
    http2_max_concurrent_streams 128;
    http2_recv_buffer_size 256k;
    
    # SSL configuration
    ssl_protocols TLSv1.2 TLSv1.3;
    ssl_ciphers 'ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256';
    ssl_prefer_server_ciphers off;
    
    server {
        # HTTP/2
        listen 443 ssl http2;
        server_name example.com;
        
        ssl_certificate /etc/nginx/ssl/server.crt;
        ssl_certificate_key /etc/nginx/ssl/server.key;
        
        root /var/www/html;
        index index.html;
        
        location / {
            # HTTP/2 push
            http2_push /style.css;
            http2_push /app.js;
            
            try_files $uri $uri/ =404;
        }
        
        # Static assets
        location ~* \.(jpg|jpeg|png|gif|css|js)$ {
            expires 1y;
            add_header Cache-Control "public, immutable";
        }
    }
    
    # HTTP redirect
    server {
        listen 80;
        server_name example.com;
        return 301 https://$server_name$request_uri;
    }
}
```

## 📝 Exercises

1. Enable HTTP/2 on your NGINX server
2. Test HTTP/2 connection
3. Configure HTTP/2 server push
4. Optimize HTTP/2 settings
5. Compare performance HTTP/1.1 vs HTTP/2
6. Test HTTP/3 (if available)
7. Troubleshoot HTTP/2 issues
8. Monitor HTTP/2 usage

## ✅ Checklist

- [ ] Understand HTTP/2 features
- [ ] Can configure HTTP/2
- [ ] Understand HTTP/3 basics
- [ ] Can optimize for HTTP/2
- [ ] Can test HTTP/2 connections
- [ ] Can troubleshoot HTTP/2 issues
- [ ] Understand performance benefits
- [ ] Know browser compatibility

## ➡️ Next Steps

Proceed to [Module 7: Monitoring](./07-monitoring.md) to learn about monitoring and observability.

