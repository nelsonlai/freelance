# Let's Encrypt - Module 3: Obtaining Certificates

## 📚 Learning Objectives

By the end of this module, you will:
- Obtain your first SSL certificate
- Use Certbot with NGINX plugin
- Use standalone mode
- Use webroot mode
- Understand different validation methods
- Handle certificate renewal

## 🎯 Prerequisites

Before obtaining a certificate:

1. Domain points to your server IP
2. NGINX is installed and running
3. Port 80 (and optionally 443) is accessible
4. Certbot is installed with NGINX plugin

## 🚀 Method 1: Using NGINX Plugin (Easiest)

### Automatic Configuration

The NGINX plugin automatically:
- Obtains certificate
- Configures NGINX for HTTPS
- Sets up automatic renewal

```bash
# Obtain certificate for single domain
sudo certbot --nginx -d example.com

# Obtain certificate for multiple domains
sudo certbot --nginx -d example.com -d www.example.com

# Obtain certificate and configure automatically
sudo certbot --nginx -d example.com --redirect
```

### Step-by-Step Process

1. **Run Certbot:**
   ```bash
   sudo certbot --nginx -d example.com
   ```

2. **Enter Email Address:**
   - Used for renewal reminders and security notices
   - Enter a valid email address

3. **Agree to Terms of Service:**
   - Read and accept the Let's Encrypt Terms of Service

4. **Choose Redirect Option:**
   - Option 1: No redirect (keep HTTP)
   - Option 2: Redirect HTTP to HTTPS (recommended)

5. **Certificate Obtained:**
   - Certificate saved to `/etc/letsencrypt/live/example.com/`
   - NGINX configuration automatically updated

### Verify Certificate

```bash
# Check certificate files
sudo ls -la /etc/letsencrypt/live/example.com/

# Files created:
# - fullchain.pem (certificate + chain)
# - privkey.pem (private key)
# - cert.pem (certificate only)
# - chain.pem (chain only)

# Test certificate
sudo certbot certificates

# Test in browser
# Visit: https://example.com
```

## 🔧 Method 2: Standalone Mode

Use when NGINX plugin isn't available or you want manual control:

```bash
# Stop NGINX temporarily
sudo systemctl stop nginx

# Obtain certificate
sudo certbot certonly --standalone -d example.com -d www.example.com

# Start NGINX
sudo systemctl start nginx
```

**When to use:**
- NGINX plugin not available
- Manual configuration preferred
- Testing certificate issuance

## 🌐 Method 3: Webroot Mode

Use when you can't stop NGINX or want zero downtime:

### Step 1: Configure NGINX for Validation

```nginx
server {
    listen 80;
    server_name example.com www.example.com;
    
    root /var/www/html;
    index index.html;
    
    # Allow Let's Encrypt validation
    location /.well-known/acme-challenge/ {
        root /var/www/html;
    }
    
    location / {
        try_files $uri $uri/ =404;
    }
}
```

### Step 2: Obtain Certificate

```bash
# Obtain certificate using webroot
sudo certbot certonly --webroot \
    -w /var/www/html \
    -d example.com \
    -d www.example.com
```

**Benefits:**
- No downtime
- NGINX continues running
- Validation happens via HTTP

## 🔐 Method 4: DNS Challenge

Use for wildcard certificates or when HTTP validation isn't possible:

```bash
# DNS challenge (manual)
sudo certbot certonly --manual --preferred-challenges dns -d example.com -d *.example.com
```

Certbot will prompt you to add a TXT record to DNS.

### Automated DNS Plugins

**Cloudflare:**
```bash
# Install plugin
sudo apt install python3-certbot-dns-cloudflare -y

# Configure credentials
sudo mkdir -p /etc/letsencrypt
sudo nano /etc/letsencrypt/cloudflare.ini
# Add:
# dns_cloudflare_api_token = YOUR_API_TOKEN

# Set permissions
sudo chmod 600 /etc/letsencrypt/cloudflare.ini

# Obtain certificate
sudo certbot certonly \
    --dns-cloudflare \
    --dns-cloudflare-credentials /etc/letsencrypt/cloudflare.ini \
    -d example.com -d *.example.com
```

## 📋 Complete Certificate Examples

### Example 1: Single Domain

```bash
# Basic single domain
sudo certbot --nginx -d example.com

# With automatic redirect
sudo certbot --nginx -d example.com --redirect
```

### Example 2: Multiple Domains

```bash
# Multiple domains in one certificate
sudo certbot --nginx \
    -d example.com \
    -d www.example.com \
    -d api.example.com \
    -d blog.example.com
```

### Example 3: Wildcard Certificate

```bash
# Wildcard certificate (requires DNS challenge)
sudo certbot certonly --manual --preferred-challenges dns \
    -d example.com \
    -d *.example.com
```

### Example 4: Staging/Testing

```bash
# Use staging server for testing
sudo certbot --nginx --staging -d example.com

# Staging certificates aren't trusted but help test
```

## 🔍 Verification Process

### What Happens During Validation

1. **Request Certificate**: Certbot requests certificate from Let's Encrypt
2. **Validation**: Let's Encrypt validates domain ownership
   - HTTP-01: Accesses `http://example.com/.well-known/acme-challenge/`
   - DNS-01: Checks DNS TXT record
3. **Issuance**: Certificate issued if validation succeeds
4. **Installation**: Certificate installed (if using plugin)

### Verify Certificate Files

```bash
# List certificate files
sudo ls -la /etc/letsencrypt/live/example.com/

# View certificate details
sudo openssl x509 -in /etc/letsencrypt/live/example.com/cert.pem -text -noout

# Check certificate expiration
sudo openssl x509 -in /etc/letsencrypt/live/example.com/cert.pem -noout -dates
```

### Test HTTPS

```bash
# Test with curl
curl -I https://example.com

# Test certificate chain
openssl s_client -connect example.com:443 -servername example.com
```

## 📝 NGINX Configuration After Certbot

After running Certbot with NGINX plugin, your configuration will look like:

```nginx
server {
    listen 80;
    server_name example.com www.example.com;
    return 301 https://$server_name$request_uri;
}

server {
    listen 443 ssl http2;
    server_name example.com www.example.com;
    
    ssl_certificate /etc/letsencrypt/live/example.com/fullchain.pem;
    ssl_certificate_key /etc/letsencrypt/live/example.com/privkey.pem;
    include /etc/letsencrypt/options-ssl-nginx.conf;
    ssl_dhparam /etc/letsencrypt/ssl-dhparams.pem;
    
    root /var/www/html;
    index index.html;
    
    location / {
        try_files $uri $uri/ =404;
    }
}
```

## 🔄 Manual Configuration (If Not Using Plugin)

If you obtained certificate manually, configure NGINX:

```nginx
server {
    listen 443 ssl http2;
    server_name example.com;
    
    # Certificate paths
    ssl_certificate /etc/letsencrypt/live/example.com/fullchain.pem;
    ssl_certificate_key /etc/letsencrypt/live/example.com/privkey.pem;
    
    # SSL configuration
    ssl_protocols TLSv1.2 TLSv1.3;
    ssl_ciphers 'ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256';
    ssl_prefer_server_ciphers off;
    
    root /var/www/html;
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

Then test and reload:
```bash
sudo nginx -t
sudo systemctl reload nginx
```

## 🧪 Testing Certificate

### Online Tools

- [SSL Labs SSL Test](https://www.ssllabs.com/ssltest/)
- [SSL Checker](https://www.sslshopper.com/ssl-checker.html)

### Command Line

```bash
# Check certificate details
echo | openssl s_client -connect example.com:443 -servername example.com 2>/dev/null | openssl x509 -noout -dates

# Test HTTPS
curl -vI https://example.com

# Check certificate chain
openssl s_client -connect example.com:443 -servername example.com -showcerts
```

## 📝 Exercises

1. Obtain certificate for your domain using NGINX plugin
2. Obtain certificate using standalone mode
3. Obtain certificate using webroot mode
4. Verify certificate files exist
5. Test HTTPS in browser
6. Check certificate expiration date
7. View certificate details with openssl
8. Test certificate with SSL Labs

## ✅ Checklist

- [ ] Certificate obtained successfully
- [ ] Certificate files in `/etc/letsencrypt/live/`
- [ ] NGINX configured for HTTPS (if using plugin)
- [ ] HTTPS working in browser
- [ ] Certificate expiration date verified
- [ ] SSL test passed
- [ ] HTTP to HTTPS redirect working (if configured)

## ➡️ Next Steps

Proceed to [Module 4: Auto-Renewal](./04-auto-renewal.md) to learn how to set up automatic certificate renewal.

