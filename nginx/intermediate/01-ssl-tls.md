# Intermediate Level - Module 1: SSL/TLS Configuration

## 📚 Learning Objectives

By the end of this module, you will:
- Understand SSL/TLS basics
- Generate SSL certificates
- Configure NGINX for HTTPS
- Set up Let's Encrypt certificates
- Configure certificate auto-renewal
- Understand SSL best practices

## 🔒 What is SSL/TLS?

SSL (Secure Sockets Layer) and TLS (Transport Layer Security) are cryptographic protocols that provide secure communication over the internet. They encrypt data between the client and server.

**Current Standard**: TLS (SSL is deprecated, but the term "SSL" is still commonly used)

### Benefits
- **Encryption**: Data is encrypted in transit
- **Authentication**: Verifies server identity
- **Data Integrity**: Ensures data hasn't been tampered with
- **SEO**: Google favors HTTPS sites
- **Trust**: Shows security badge in browsers

## 📜 SSL Certificate Types

### 1. Self-Signed Certificate
- Free, quick to generate
- Not trusted by browsers (shows warning)
- Good for development/testing

### 2. Let's Encrypt (Free)
- Free, trusted by browsers
- Valid for 90 days
- Auto-renewal available

### 3. Commercial Certificates
- Paid certificates
- Extended validation options
- Longer validity periods

## 🔑 Generating Self-Signed Certificate

### Step 1: Create Certificate Directory

```bash
sudo mkdir -p /etc/nginx/ssl
```

### Step 2: Generate Private Key

```bash
sudo openssl genrsa -out /etc/nginx/ssl/server.key 2048
```

### Step 3: Generate Certificate Signing Request (CSR)

```bash
sudo openssl req -new -key /etc/nginx/ssl/server.key -out /etc/nginx/ssl/server.csr
```

You'll be prompted for:
- Country Name
- State/Province
- City
- Organization Name
- Common Name (your domain): **example.com**

### Step 4: Generate Self-Signed Certificate

```bash
sudo openssl x509 -req -days 365 -in /etc/nginx/ssl/server.csr \
    -signkey /etc/nginx/ssl/server.key -out /etc/nginx/ssl/server.crt
```

### Step 5: Set Permissions

```bash
sudo chmod 600 /etc/nginx/ssl/server.key
sudo chmod 644 /etc/nginx/ssl/server.crt
```

### One-Line Command

```bash
sudo openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
    -keyout /etc/nginx/ssl/server.key \
    -out /etc/nginx/ssl/server.crt \
    -subj "/C=US/ST=State/L=City/O=Organization/CN=example.com"
```

## 🔧 Basic HTTPS Configuration

### Minimal HTTPS Server Block

```nginx
server {
    listen 443 ssl;
    server_name example.com;
    
    # SSL Certificate paths
    ssl_certificate /etc/nginx/ssl/server.crt;
    ssl_certificate_key /etc/nginx/ssl/server.key;
    
    root /var/www/example.com;
    index index.html;
    
    location / {
        try_files $uri $uri/ =404;
    }
}
```

### HTTP to HTTPS Redirect

```nginx
# Redirect HTTP to HTTPS
server {
    listen 80;
    server_name example.com;
    return 301 https://$server_name$request_uri;
}

# HTTPS server
server {
    listen 443 ssl;
    server_name example.com;
    
    ssl_certificate /etc/nginx/ssl/server.crt;
    ssl_certificate_key /etc/nginx/ssl/server.key;
    
    root /var/www/example.com;
    index index.html;
    
    location / {
        try_files $uri $uri/ =404;
    }
}
```

## ✅ Let's Encrypt Setup

Let's Encrypt provides free, trusted SSL certificates.

### Step 1: Install Certbot

**Ubuntu/Debian:**
```bash
sudo apt update
sudo apt install certbot python3-certbot-nginx -y
```

**CentOS/RHEL:**
```bash
sudo yum install certbot python3-certbot-nginx -y
```

**macOS:**
```bash
brew install certbot
```

### Step 2: Basic NGINX Configuration

First, set up a basic HTTP server block:

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

### Step 3: Obtain Certificate

```bash
sudo certbot --nginx -d example.com -d www.example.com
```

Certbot will:
- Automatically obtain certificates
- Configure NGINX for HTTPS
- Set up auto-renewal

### Step 4: Verify Auto-Renewal

```bash
# Test renewal (dry run)
sudo certbot renew --dry-run

# Check renewal timer
sudo systemctl status certbot.timer
```

### Manual Certificate Renewal

```bash
sudo certbot renew
sudo systemctl reload nginx
```

## 🔐 SSL/TLS Best Practices

### Strong SSL Configuration

```nginx
server {
    listen 443 ssl http2;
    server_name example.com;
    
    # Certificate paths
    ssl_certificate /etc/letsencrypt/live/example.com/fullchain.pem;
    ssl_certificate_key /etc/letsencrypt/live/example.com/privkey.pem;
    
    # SSL Protocols (disable old, insecure versions)
    ssl_protocols TLSv1.2 TLSv1.3;
    
    # SSL Ciphers (strong, modern ciphers)
    ssl_ciphers 'ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256:ECDHE-ECDSA-AES256-GCM-SHA384:ECDHE-RSA-AES256-GCM-SHA384';
    ssl_prefer_server_ciphers off;
    
    # Session caching
    ssl_session_cache shared:SSL:10m;
    ssl_session_timeout 10m;
    ssl_session_tickets off;
    
    # OCSP Stapling
    ssl_stapling on;
    ssl_stapling_verify on;
    ssl_trusted_certificate /etc/letsencrypt/live/example.com/chain.pem;
    resolver 8.8.8.8 8.8.4.4 valid=300s;
    resolver_timeout 5s;
    
    # Security Headers
    add_header Strict-Transport-Security "max-age=31536000; includeSubDomains" always;
    add_header X-Frame-Options "SAMEORIGIN" always;
    add_header X-Content-Type-Options "nosniff" always;
    add_header X-XSS-Protection "1; mode=block" always;
    
    root /var/www/example.com;
    index index.html;
    
    location / {
        try_files $uri $uri/ =404;
    }
}

# HTTP to HTTPS redirect
server {
    listen 80;
    server_name example.com;
    return 301 https://$server_name$request_uri;
}
```

## 🔄 HTTP/2 Support

HTTP/2 improves performance over HTTPS:

```nginx
server {
    listen 443 ssl http2;  # Add http2
    server_name example.com;
    
    ssl_certificate /etc/nginx/ssl/server.crt;
    ssl_certificate_key /etc/nginx/ssl/server.key;
    
    # ... rest of config
}
```

## 🌍 Multiple Domains with SSL

### Separate Certificates

```nginx
# Domain 1
server {
    listen 443 ssl http2;
    server_name example.com;
    
    ssl_certificate /etc/nginx/ssl/example.com.crt;
    ssl_certificate_key /etc/nginx/ssl/example.com.key;
    
    root /var/www/example.com;
    # ...
}

# Domain 2
server {
    listen 443 ssl http2;
    server_name another-site.com;
    
    ssl_certificate /etc/nginx/ssl/another-site.com.crt;
    ssl_certificate_key /etc/nginx/ssl/another-site.com.key;
    
    root /var/www/another-site.com;
    # ...
}
```

### SAN (Subject Alternative Names) Certificate

A single certificate for multiple domains:

```nginx
server {
    listen 443 ssl http2;
    server_name example.com www.example.com api.example.com;
    
    ssl_certificate /etc/nginx/ssl/multi-domain.crt;
    ssl_certificate_key /etc/nginx/ssl/multi-domain.key;
    
    # ...
}
```

## 🔍 SSL Certificate Testing

### Test SSL Configuration

```bash
# Online tools
# https://www.ssllabs.com/ssltest/
# https://observatory.mozilla.org/

# Command line
openssl s_client -connect example.com:443 -servername example.com
```

### Check Certificate Validity

```bash
# View certificate details
openssl x509 -in /etc/nginx/ssl/server.crt -text -noout

# Check expiration date
openssl x509 -in /etc/nginx/ssl/server.crt -noout -dates
```

### Verify NGINX SSL Configuration

```bash
# Test configuration
sudo nginx -t

# Check if SSL is working
curl -I https://example.com
```

## 📝 Practical Example: Complete HTTPS Setup

```nginx
# HTTP to HTTPS redirect
server {
    listen 80;
    listen [::]:80;
    server_name example.com www.example.com;
    return 301 https://$server_name$request_uri;
}

# HTTPS server
server {
    listen 443 ssl http2;
    listen [::]:443 ssl http2;
    server_name example.com www.example.com;
    
    # SSL Certificate
    ssl_certificate /etc/letsencrypt/live/example.com/fullchain.pem;
    ssl_certificate_key /etc/letsencrypt/live/example.com/privkey.pem;
    
    # SSL Configuration
    ssl_protocols TLSv1.2 TLSv1.3;
    ssl_ciphers 'ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256:ECDHE-ECDSA-AES256-GCM-SHA384:ECDHE-RSA-AES256-GCM-SHA384';
    ssl_prefer_server_ciphers off;
    ssl_session_cache shared:SSL:10m;
    ssl_session_timeout 10m;
    ssl_session_tickets off;
    
    # OCSP Stapling
    ssl_stapling on;
    ssl_stapling_verify on;
    ssl_trusted_certificate /etc/letsencrypt/live/example.com/chain.pem;
    resolver 8.8.8.8 valid=300s;
    resolver_timeout 5s;
    
    # Security Headers
    add_header Strict-Transport-Security "max-age=31536000; includeSubDomains" always;
    add_header X-Frame-Options "SAMEORIGIN" always;
    add_header X-Content-Type-Options "nosniff" always;
    add_header X-XSS-Protection "1; mode=block" always;
    
    # Root and index
    root /var/www/example.com;
    index index.html;
    
    # Logging
    access_log /var/log/nginx/example.com.access.log;
    error_log /var/log/nginx/example.com.error.log;
    
    location / {
        try_files $uri $uri/ =404;
    }
    
    # Cache static files
    location ~* \.(jpg|jpeg|png|gif|ico|css|js)$ {
        expires 1y;
        add_header Cache-Control "public, immutable";
    }
}
```

## 🔧 Troubleshooting

### Certificate Not Found

```bash
# Check certificate file exists
sudo ls -la /etc/nginx/ssl/

# Check file permissions
sudo chmod 644 /etc/nginx/ssl/server.crt
sudo chmod 600 /etc/nginx/ssl/server.key
```

### SSL Handshake Failed

- Verify certificate is valid
- Check certificate and key match
- Ensure firewall allows port 443
- Verify SSL protocols are supported

### Browser Shows "Not Secure"

- Certificate may be self-signed
- Certificate may be expired
- Certificate may not match domain
- Mixed content (HTTP resources on HTTPS page)

## 📝 Exercises

1. Generate a self-signed certificate for testing
2. Configure NGINX to serve HTTPS with your certificate
3. Set up Let's Encrypt certificate using Certbot
4. Configure HTTP to HTTPS redirect
5. Implement SSL best practices (TLS 1.2+, strong ciphers)
6. Enable HTTP/2
7. Set up auto-renewal for Let's Encrypt certificates
8. Test your SSL configuration using SSL Labs

## ✅ Checklist

- [ ] Understand SSL/TLS basics
- [ ] Can generate self-signed certificates
- [ ] Can set up Let's Encrypt certificates
- [ ] Can configure HTTPS in NGINX
- [ ] Understand SSL best practices
- [ ] Can set up HTTP to HTTPS redirect
- [ ] Can enable HTTP/2
- [ ] Understand certificate renewal

## ➡️ Next Steps

Proceed to [Module 2: Reverse Proxy](./02-reverse-proxy.md) to learn how to use NGINX as a reverse proxy.

