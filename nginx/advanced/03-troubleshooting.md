# Advanced Level - Module 3: Troubleshooting

## 📚 Learning Objectives

By the end of this module, you will:
- Understand logging and log analysis
- Test configuration files
- Debug common errors
- Monitor NGINX performance
- Troubleshoot connection issues
- Fix configuration problems
- Use debugging tools

## 📊 Logging and Analysis

### Error Log

```nginx
http {
    # Error log with different levels
    error_log /var/log/nginx/error.log warn;
    
    # Per-server error log
    server {
        error_log /var/log/nginx/example.com.error.log debug;
    }
}
```

**Log Levels:**
- `debug`: Detailed debugging information
- `info`: Informational messages
- `notice`: Normal but significant events
- `warn`: Warning messages
- `error`: Error messages
- `crit`: Critical conditions
- `alert`: Action must be taken immediately
- `emerg`: System is unusable

### Access Log

```nginx
http {
    # Standard log format
    log_format main '$remote_addr - $remote_user [$time_local] "$request" '
                    '$status $body_bytes_sent "$http_referer" '
                    '"$http_user_agent" "$http_x_forwarded_for"';
    
    access_log /var/log/nginx/access.log main;
    
    # Extended log format
    log_format detailed '$remote_addr - $remote_user [$time_local] "$request" '
                        '$status $body_bytes_sent "$http_referer" '
                        '"$http_user_agent" "$http_x_forwarded_for" '
                        'rt=$request_time uct="$upstream_connect_time" '
                        'uht="$upstream_header_time" urt="$upstream_response_time"';
    
    access_log /var/log/nginx/access.log detailed;
}
```

### Log Analysis

```bash
# View recent errors
sudo tail -f /var/log/nginx/error.log

# Search for specific errors
sudo grep -i error /var/log/nginx/error.log

# Count errors by type
sudo grep error /var/log/nginx/error.log | awk '{print $NF}' | sort | uniq -c

# View access log
sudo tail -f /var/log/nginx/access.log

# Find most accessed files
sudo awk '{print $7}' /var/log/nginx/access.log | sort | uniq -c | sort -rn | head

# Find requests by status code
sudo awk '{print $9}' /var/log/nginx/access.log | sort | uniq -c | sort -rn

# Find slow requests
sudo awk '$NF > 1 {print $NF, $7}' /var/log/nginx/access.log | sort -rn | head
```

## ✅ Configuration Testing

### Test Configuration Syntax

```bash
# Test configuration
sudo nginx -t

# Test and show configuration
sudo nginx -T

# Test with specific config file
sudo nginx -t -c /path/to/nginx.conf

# Show effective configuration
sudo nginx -T | less
```

### Common Configuration Errors

**1. Missing Semicolon**
```nginx
# Wrong
worker_processes auto

# Correct
worker_processes auto;
```

**2. Unmatched Braces**
```nginx
# Wrong
server {
    location / {
    # Missing closing brace

# Correct
server {
    location / {
        # ...
    }
}
```

**3. Invalid Directive**
```nginx
# Wrong
server {
    invalid_directive value;
}

# Check available directives in documentation
```

**4. Port Already in Use**
```nginx
# Error: bind() to 0.0.0.0:80 failed (98: Address already in use)
# Solution: Check what's using port 80
sudo lsof -i :80
sudo netstat -tlnp | grep :80
```

## 🐛 Common Issues and Solutions

### 502 Bad Gateway

**Causes:**
- Backend server is down
- Backend server not responding
- Firewall blocking connection
- Wrong upstream address/port

**Debugging:**
```bash
# Check if backend is running
curl http://backend:port

# Check error log
sudo tail -f /var/log/nginx/error.log

# Test backend connectivity
telnet backend port
```

**Solution:**
```nginx
# Increase timeouts
proxy_connect_timeout 60s;
proxy_send_timeout 60s;
proxy_read_timeout 60s;

# Check upstream configuration
upstream backend {
    server 127.0.0.1:8080;
}
```

### 504 Gateway Timeout

**Causes:**
- Backend taking too long to respond
- Timeout values too low

**Solution:**
```nginx
# Increase timeouts
proxy_connect_timeout 300s;
proxy_send_timeout 300s;
proxy_read_timeout 300s;

# Or in FastCGI
fastcgi_connect_timeout 300s;
fastcgi_send_timeout 300s;
fastcgi_read_timeout 300s;
```

### 413 Request Entity Too Large

**Causes:**
- File upload too large
- `client_max_body_size` too small

**Solution:**
```nginx
http {
    client_max_body_size 50M;  # Increase limit
}

# Or per server
server {
    client_max_body_size 100M;
}
```

### 403 Forbidden

**Causes:**
- File permissions
- Directory listing disabled
- Access control rules

**Debugging:**
```bash
# Check file permissions
ls -la /var/www/html

# Check directory permissions
ls -ld /var/www/html

# Check SELinux (if enabled)
getenforce
```

**Solution:**
```bash
# Fix permissions
sudo chown -R nginx:nginx /var/www/html
sudo chmod -R 755 /var/www/html
sudo find /var/www/html -type f -exec chmod 644 {} \;
```

### 404 Not Found

**Causes:**
- File doesn't exist
- Wrong root directory
- Wrong index file

**Debugging:**
```nginx
# Add debug logging
error_log /var/log/nginx/error.log debug;

# Check root path
location / {
    # Log the path being checked
    try_files $uri $uri/ =404;
}
```

### Permission Denied

**Causes:**
- NGINX user doesn't have access
- SELinux restrictions
- Directory permissions

**Solution:**
```bash
# Check NGINX user
ps aux | grep nginx

# Fix permissions
sudo chown -R nginx:nginx /var/www/html
sudo chmod -R 755 /var/www/html

# Check SELinux
sudo setenforce 0  # Temporarily disable
# Or set proper context
sudo chcon -R -t httpd_sys_content_t /var/www/html
```

## 🔍 Debugging Techniques

### Enable Debug Mode

```nginx
# In nginx.conf
error_log /var/log/nginx/error.log debug;

# Or per server
server {
    error_log /var/log/nginx/server.error.log debug;
}
```

### Debug Specific Modules

```nginx
# Debug rewrite module
error_log /var/log/nginx/error.log notice;
rewrite_log on;
```

### Add Debug Headers

```nginx
location / {
    # Debug headers
    add_header X-Debug-Uri $uri;
    add_header X-Debug-Args $args;
    add_header X-Debug-Host $host;
    add_header X-Debug-Remote $remote_addr;
}
```

### Test with curl

```bash
# Basic request
curl -I http://example.com

# With specific host header
curl -H "Host: example.com" http://server-ip

# Verbose output
curl -v http://example.com

# Follow redirects
curl -L http://example.com

# Test specific path
curl http://example.com/path
```

## 📊 Monitoring and Performance

### Check NGINX Status

```bash
# Process status
ps aux | grep nginx

# Check if running
sudo systemctl status nginx

# Check listening ports
sudo netstat -tlnp | grep nginx
sudo ss -tlnp | grep nginx

# Check connections
sudo netstat -an | grep :80 | wc -l
```

### Monitor Connections

```bash
# Watch active connections
watch -n 1 'netstat -an | grep :80 | wc -l'

# Monitor specific IPs
sudo netstat -an | grep :80 | awk '{print $5}' | cut -d: -f1 | sort | uniq -c | sort -rn
```

### Resource Usage

```bash
# Check memory usage
ps aux | grep nginx

# Check open files
sudo lsof -p $(cat /var/run/nginx.pid) | wc -l

# Check file descriptor limit
ulimit -n
```

## 🛠️ Useful Commands

### Configuration Management

```bash
# Test configuration
sudo nginx -t

# Reload configuration
sudo systemctl reload nginx

# Restart NGINX
sudo systemctl restart nginx

# Stop NGINX
sudo systemctl stop nginx

# Start NGINX
sudo systemctl start nginx
```

### Log Management

```bash
# View logs in real-time
sudo tail -f /var/log/nginx/access.log
sudo tail -f /var/log/nginx/error.log

# Search logs
sudo grep "error" /var/log/nginx/error.log
sudo grep "404" /var/log/nginx/access.log

# Rotate logs (if logrotate configured)
sudo logrotate -f /etc/logrotate.d/nginx
```

### Network Debugging

```bash
# Check port
sudo lsof -i :80
sudo netstat -tlnp | grep :80

# Test connectivity
curl -I http://localhost
curl -I https://localhost

# Test DNS resolution
nslookup example.com
dig example.com
```

## 📝 Common Troubleshooting Workflow

1. **Check Error Logs**
   ```bash
   sudo tail -f /var/log/nginx/error.log
   ```

2. **Test Configuration**
   ```bash
   sudo nginx -t
   ```

3. **Check Service Status**
   ```bash
   sudo systemctl status nginx
   ```

4. **Verify Ports**
   ```bash
   sudo netstat -tlnp | grep nginx
   ```

5. **Test Connectivity**
   ```bash
   curl -I http://example.com
   ```

6. **Check Permissions**
   ```bash
   ls -la /var/www/html
   ```

7. **Review Configuration**
   ```bash
   sudo nginx -T | less
   ```

## 📝 Exercises

1. Enable debug logging and analyze error logs
2. Test configuration syntax before applying
3. Troubleshoot a 502 Bad Gateway error
4. Fix a 403 Forbidden error
5. Analyze access logs for patterns
6. Monitor NGINX performance
7. Debug a connection timeout issue
8. Create a troubleshooting checklist

## ✅ Checklist

- [ ] Understand log levels and formats
- [ ] Can test configuration syntax
- [ ] Know how to debug common errors
- [ ] Can analyze access and error logs
- [ ] Understand troubleshooting workflow
- [ ] Can monitor NGINX performance
- [ ] Know debugging tools and commands
- [ ] Can fix permission issues

## ➡️ Next Steps

Proceed to [Module 4: Rate Limiting](./04-rate-limiting.md) to learn advanced rate limiting techniques.

