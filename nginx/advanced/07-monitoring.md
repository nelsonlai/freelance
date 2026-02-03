# Advanced Level - Module 7: Monitoring and Observability

## 📚 Learning Objectives

By the end of this module, you will:
- Set up NGINX status monitoring
- Configure comprehensive logging
- Use monitoring tools
- Set up alerts
- Monitor performance metrics
- Understand key performance indicators
- Create monitoring dashboards

## 📊 NGINX Status Module

### Basic Status Endpoint

```nginx
location /nginx_status {
    stub_status on;
    access_log off;
    allow 127.0.0.1;
    allow 192.168.1.0/24;
    deny all;
}
```

**Output:**
```
Active connections: 3
server accepts handled requests
 45 45 123
Reading: 0 Writing: 1 Waiting: 2
```

**Metrics:**
- `Active connections`: Current connections
- `accepts`: Total accepted connections
- `handled`: Total handled connections
- `requests`: Total requests
- `Reading`: Reading request headers
- `Writing`: Writing response
- `Waiting`: Keepalive connections

### Status with Extended Information (NGINX Plus)

```nginx
location /api {
    api write=on;
    allow 127.0.0.1;
    deny all;
}
```

## 📝 Comprehensive Logging

### Extended Log Format

```nginx
http {
    # Extended log format
    log_format detailed '$remote_addr - $remote_user [$time_local] '
                        '"$request" $status $body_bytes_sent '
                        '"$http_referer" "$http_user_agent" '
                        '$request_time $upstream_response_time '
                        '$upstream_addr $upstream_status';
    
    access_log /var/log/nginx/access.log detailed;
    error_log /var/log/nginx/error.log warn;
}
```

### Log Rotation

```nginx
# /etc/logrotate.d/nginx
/var/log/nginx/*.log {
    daily
    missingok
    rotate 52
    compress
    delaycompress
    notifempty
    create 0640 nginx adm
    sharedscripts
    postrotate
        if [ -f /var/run/nginx.pid ]; then
            kill -USR1 `cat /var/run/nginx.pid`
        fi
    endscript
}
```

### Separate Log Files

```nginx
server {
    server_name example.com;
    
    # Per-server logs
    access_log /var/log/nginx/example.com.access.log;
    error_log /var/log/nginx/example.com.error.log warn;
    
    # Different log levels
    error_log /var/log/nginx/example.com.error.log debug;
}
```

## 🔍 Key Metrics to Monitor

### Connection Metrics

- Active connections
- Connections per second
- Connection accept rate
- Connection handling rate

### Request Metrics

- Requests per second
- Request processing time
- Request size
- Response size

### Upstream Metrics

- Upstream response time
- Upstream status codes
- Upstream failures
- Upstream availability

### Error Metrics

- 4xx errors
- 5xx errors
- Timeouts
- Connection errors

## 📊 Monitoring Tools

### Prometheus + Grafana

**NGINX Exporter Setup:**

```nginx
location /nginx_status {
    stub_status on;
    allow 127.0.0.1;
    deny all;
}
```

**Prometheus Configuration:**
```yaml
scrape_configs:
  - job_name: 'nginx'
    static_configs:
      - targets: ['nginx-exporter:9113']
```

### ELK Stack (Elasticsearch, Logstash, Kibana)

**Logstash Configuration:**
```ruby
input {
  file {
    path => "/var/log/nginx/access.log"
    type => "nginx-access"
  }
}

filter {
  grok {
    match => { "message" => "%{NGINXACCESS}" }
  }
}

output {
  elasticsearch {
    hosts => ["localhost:9200"]
  }
}
```

### Datadog

Install Datadog agent and configure NGINX integration.

### New Relic

Install New Relic agent and configure NGINX monitoring.

## 🎯 Custom Metrics

### Add Custom Headers

```nginx
location / {
    proxy_pass http://backend;
    
    # Custom metrics headers
    add_header X-Response-Time $request_time;
    add_header X-Upstream-Time $upstream_response_time;
    add_header X-Cache-Status $upstream_cache_status;
    add_header X-Upstream-Addr $upstream_addr;
}
```

### Custom Log Format for Metrics

```nginx
log_format metrics '$remote_addr $time_local "$request" $status '
                   '$request_time $upstream_response_time '
                   '$upstream_addr $upstream_status '
                   '$body_bytes_sent "$http_user_agent"';
```

## 📈 Performance Monitoring

### Request Time Monitoring

```nginx
http {
    log_format timing '$remote_addr - $remote_user [$time_local] '
                      '"$request" $status $body_bytes_sent '
                      'rt=$request_time uct="$upstream_connect_time" '
                      'uht="$upstream_header_time" urt="$upstream_response_time"';
    
    access_log /var/log/nginx/timing.log timing;
}
```

### Slow Request Logging

```nginx
map $request_time $slow_request {
    default 0;
    "~^[1-9]\." 1;  # > 1 second
    "~^[1-9][0-9]" 1;  # > 10 seconds
}

access_log /var/log/nginx/slow.log combined if=$slow_request;
```

## 🚨 Alerting

### Setup Alerts Based on Logs

**Script to check error rate:**
```bash
#!/bin/bash
ERROR_COUNT=$(tail -1000 /var/log/nginx/error.log | grep -c error)
if [ $ERROR_COUNT -gt 50 ]; then
    echo "High error rate detected: $ERROR_COUNT errors"
    # Send alert
fi
```

### Monitor with Nagios/Icinga

Configure checks for:
- NGINX process status
- Response time
- Error rate
- Upstream availability

### Prometheus Alerts

```yaml
groups:
  - name: nginx_alerts
    rules:
      - alert: HighErrorRate
        expr: rate(nginx_http_requests_total{status=~"5.."}[5m]) > 0.05
        for: 5m
        annotations:
          summary: "High error rate detected"
```

## 📊 Dashboard Creation

### Grafana Dashboard

**Key Panels:**
- Requests per second
- Response time
- Error rate
- Active connections
- Upstream health
- Cache hit ratio

### Custom Dashboard Queries

```promql
# Requests per second
rate(nginx_http_requests_total[5m])

# Average response time
rate(nginx_http_request_duration_seconds_sum[5m]) / rate(nginx_http_request_duration_seconds_count[5m])

# Error rate
rate(nginx_http_requests_total{status=~"5.."}[5m])
```

## 🔧 Real-Time Monitoring

### Real-Time Log Monitoring

```bash
# Watch access log
sudo tail -f /var/log/nginx/access.log

# Watch error log
sudo tail -f /var/log/nginx/error.log

# Watch with filtering
sudo tail -f /var/log/nginx/access.log | grep "500"
```

### Real-Time Metrics

```bash
# Watch connections
watch -n 1 'curl -s http://localhost/nginx_status'

# Monitor specific metrics
watch -n 1 'netstat -an | grep :80 | wc -l'
```

## 📋 Complete Monitoring Setup

```nginx
http {
    # Status endpoint
    server {
        listen 8080;
        server_name localhost;
        
        location /nginx_status {
            stub_status on;
            access_log off;
            allow 127.0.0.1;
            deny all;
        }
    }
    
    # Extended logging
    log_format detailed '$remote_addr - $remote_user [$time_local] '
                        '"$request" $status $body_bytes_sent '
                        '"$http_referer" "$http_user_agent" '
                        'rt=$request_time uct="$upstream_connect_time" '
                        'uht="$upstream_header_time" urt="$upstream_response_time" '
                        'cache=$upstream_cache_status';
    
    access_log /var/log/nginx/access.log detailed;
    error_log /var/log/nginx/error.log warn;
    
    # Slow request logging
    map $request_time $slow_request {
        default 0;
        "~^[1-9]\." 1;
    }
    
    access_log /var/log/nginx/slow.log detailed if=$slow_request;
    
    server {
        listen 443 ssl http2;
        server_name example.com;
        
        # Add metrics headers
        add_header X-Response-Time $request_time;
        add_header X-Upstream-Time $upstream_response_time;
        add_header X-Cache-Status $upstream_cache_status;
        
        # ... rest of configuration
    }
}
```

## 📝 Exercises

1. Set up NGINX status endpoint
2. Configure extended logging
3. Set up log rotation
4. Create custom metrics
5. Set up Prometheus monitoring (if possible)
6. Create monitoring alerts
7. Build a monitoring dashboard
8. Analyze performance metrics

## ✅ Checklist

- [ ] Can set up status monitoring
- [ ] Understand key metrics
- [ ] Can configure comprehensive logging
- [ ] Can set up monitoring tools
- [ ] Can create alerts
- [ ] Can monitor performance
- [ ] Understand observability concepts
- [ ] Can analyze metrics

## 🎓 Congratulations!

You've completed all Advanced Level modules! You now have comprehensive knowledge of NGINX including:
- Performance optimization
- Security hardening
- Troubleshooting
- Rate limiting
- Advanced caching
- HTTP/2 and HTTP/3
- Monitoring and observability

Continue practicing and exploring NGINX to master these concepts!

