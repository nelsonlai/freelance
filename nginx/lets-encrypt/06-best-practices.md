# Let's Encrypt - Module 6: Best Practices and Advanced Topics

## 📚 Learning Objectives

By the end of this module, you will:
- Follow Let's Encrypt best practices
- Set up wildcard certificates
- Configure multiple domains efficiently
- Implement certificate backup strategies
- Use advanced Certbot features
- Understand security considerations

## ✅ Best Practices

### 1. Use Auto-Renewal

Always set up automatic renewal:

```bash
# Verify auto-renewal is enabled
sudo systemctl status certbot.timer

# Test renewal regularly
sudo certbot renew --dry-run
```

### 2. Monitor Certificate Expiration

Set up monitoring:

```bash
# Create monitoring script
cat > /usr/local/bin/check-cert-expiry.sh << 'EOF'
#!/bin/bash
DOMAIN="example.com"
DAYS_WARNING=30
CERT_FILE="/etc/letsencrypt/live/$DOMAIN/cert.pem"

if [ -f "$CERT_FILE" ]; then
    EXPIRY=$(openssl x509 -in "$CERT_FILE" -noout -enddate | cut -d= -f2)
    EXPIRY_EPOCH=$(date -d "$EXPIRY" +%s)
    NOW_EPOCH=$(date +%s)
    DAYS_LEFT=$(( ($EXPIRY_EPOCH - $NOW_EPOCH) / 86400 ))
    
    if [ $DAYS_LEFT -lt $DAYS_WARNING ]; then
        echo "WARNING: Certificate expires in $DAYS_LEFT days"
    fi
fi
EOF

chmod +x /usr/local/bin/check-cert-expiry.sh

# Add to cron
sudo crontab -e
# Add: 0 9 * * * /usr/local/bin/check-cert-expiry.sh
```

### 3. Backup Certificates

Regular backups are essential:

```bash
# Backup script
cat > /usr/local/bin/backup-letsencrypt.sh << 'EOF'
#!/bin/bash
BACKUP_DIR="/backup/letsencrypt"
DATE=$(date +%Y%m%d)
BACKUP_PATH="$BACKUP_DIR/$DATE"

mkdir -p "$BACKUP_PATH"
cp -r /etc/letsencrypt "$BACKUP_PATH/"
tar -czf "$BACKUP_PATH.tar.gz" "$BACKUP_PATH"
rm -rf "$BACKUP_PATH"

# Keep only last 30 days
find "$BACKUP_DIR" -name "*.tar.gz" -mtime +30 -delete
EOF

chmod +x /usr/local/bin/backup-letsencrypt.sh

# Daily backup
sudo crontab -e
# Add: 0 2 * * * /usr/local/bin/backup-letsencrypt.sh
```

### 4. Use Strong SSL Configuration

Always use strong SSL settings:

```nginx
server {
    listen 443 ssl http2;
    
    ssl_certificate /etc/letsencrypt/live/example.com/fullchain.pem;
    ssl_certificate_key /etc/letsencrypt/live/example.com/privkey.pem;
    
    # Strong protocols
    ssl_protocols TLSv1.2 TLSv1.3;
    
    # Strong ciphers
    ssl_ciphers 'ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256:ECDHE-ECDSA-AES256-GCM-SHA384:ECDHE-RSA-AES256-GCM-SHA384';
    ssl_prefer_server_ciphers off;
    
    # Session cache
    ssl_session_cache shared:SSL:10m;
    ssl_session_timeout 10m;
    ssl_session_tickets off;
    
    # OCSP Stapling
    ssl_stapling on;
    ssl_stapling_verify on;
    ssl_trusted_certificate /etc/letsencrypt/live/example.com/chain.pem;
    
    # Security headers
    add_header Strict-Transport-Security "max-age=31536000; includeSubDomains" always;
}
```

### 5. Test in Staging First

Always test with staging server:

```bash
# Use staging for testing
sudo certbot --staging --nginx -d test.example.com

# Test renewal
sudo certbot renew --staging --dry-run
```

### 6. Keep Certbot Updated

Regularly update Certbot:

```bash
# Ubuntu/Debian
sudo apt update && sudo apt upgrade certbot

# CentOS/RHEL
sudo yum update certbot

# Check version
certbot --version
```

## 🌐 Wildcard Certificates

### Obtaining Wildcard Certificate

Wildcard certificates cover `*.example.com`:

```bash
# Manual DNS challenge
sudo certbot certonly --manual --preferred-challenges dns \
    -d example.com \
    -d *.example.com
```

### Automated DNS Challenge

**Cloudflare Example:**

```bash
# Install plugin
sudo apt install python3-certbot-dns-cloudflare -y

# Configure credentials
sudo mkdir -p /etc/letsencrypt
sudo nano /etc/letsencrypt/cloudflare.ini
# Add:
# dns_cloudflare_api_token = YOUR_API_TOKEN

sudo chmod 600 /etc/letsencrypt/cloudflare.ini

# Obtain wildcard certificate
sudo certbot certonly \
    --dns-cloudflare \
    --dns-cloudflare-credentials /etc/letsencrypt/cloudflare.ini \
    -d example.com \
    -d *.example.com
```

### NGINX Configuration for Wildcard

```nginx
server {
    listen 443 ssl http2;
    server_name *.example.com;
    
    ssl_certificate /etc/letsencrypt/live/example.com/fullchain.pem;
    ssl_certificate_key /etc/letsencrypt/live/example.com/privkey.pem;
    
    # ... SSL configuration ...
    
    root /var/www/html;
    index index.html;
    
    location / {
        try_files $uri $uri/ =404;
    }
}
```

## 🔄 Managing Multiple Domains

### Single Certificate for Multiple Domains

```bash
# One certificate, multiple domains
sudo certbot --nginx \
    -d example.com \
    -d www.example.com \
    -d api.example.com \
    -d blog.example.com
```

### Separate Certificates

```bash
# Different certificates for different domains
sudo certbot --nginx -d example.com
sudo certbot --nginx -d anotherdomain.com
```

### Certificate Management

```bash
# List all certificates
sudo certbot certificates

# Delete certificate
sudo certbot delete --cert-name example.com

# Revoke certificate
sudo certbot revoke --cert-path /etc/letsencrypt/live/example.com/cert.pem
```

## 🔒 Security Best Practices

### 1. Protect Private Keys

```bash
# Correct permissions
sudo chmod 600 /etc/letsencrypt/live/example.com/privkey.pem
sudo chmod 755 /etc/letsencrypt/live/example.com/
sudo chmod 644 /etc/letsencrypt/live/example.com/fullchain.pem

# Verify
sudo ls -la /etc/letsencrypt/live/example.com/
```

### 2. Use Strong SSL Configuration

Always use TLS 1.2+ and strong ciphers (see example above).

### 3. Enable HSTS

```nginx
add_header Strict-Transport-Security "max-age=31536000; includeSubDomains; preload" always;
```

### 4. Regular Updates

Keep Certbot and NGINX updated:

```bash
# Update Certbot
sudo apt update && sudo apt upgrade certbot

# Update NGINX
sudo apt update && sudo apt upgrade nginx
```

## 📊 Certificate Monitoring

### Comprehensive Monitoring Script

```bash
#!/bin/bash
# /usr/local/bin/cert-monitor.sh

DOMAINS=("example.com" "anotherdomain.com")
EMAIL="admin@example.com"
DAYS_WARNING=30

for domain in "${DOMAINS[@]}"; do
    CERT_FILE="/etc/letsencrypt/live/$domain/cert.pem"
    
    if [ -f "$CERT_FILE" ]; then
        EXPIRY=$(openssl x509 -in "$CERT_FILE" -noout -enddate | cut -d= -f2)
        EXPIRY_EPOCH=$(date -d "$EXPIRY" +%s)
        NOW_EPOCH=$(date +%s)
        DAYS_LEFT=$(( ($EXPIRY_EPOCH - $NOW_EPOCH) / 86400 ))
        
        if [ $DAYS_LEFT -lt $DAYS_WARNING ]; then
            echo "Certificate for $domain expires in $DAYS_LEFT days" | \
                mail -s "Certificate Expiry Warning" "$EMAIL"
        fi
    fi
done
```

## 🔧 Advanced Certbot Features

### Certificate Revocation

```bash
# Revoke certificate
sudo certbot revoke --cert-path /etc/letsencrypt/live/example.com/cert.pem

# Revoke with reason
sudo certbot revoke --cert-path /etc/letsencrypt/live/example.com/cert.pem \
    --reason keycompromise
```

### Account Management

```bash
# Show account information
sudo certbot show_account

# Update email
sudo certbot update_account --email newemail@example.com

# Unregister account
sudo certbot unregister
```

### Testing Configuration Changes

```bash
# Test renewal without making changes
sudo certbot renew --dry-run

# Test with specific options
sudo certbot renew --dry-run --nginx
```

## 📝 Complete Production Setup

### Example: Complete Secure Setup

```bash
# 1. Install Certbot
sudo apt install certbot python3-certbot-nginx

# 2. Obtain certificate
sudo certbot --nginx -d example.com -d www.example.com --redirect

# 3. Verify auto-renewal
sudo systemctl status certbot.timer
sudo certbot renew --dry-run

# 4. Set up monitoring
# (Use monitoring script from above)

# 5. Set up backups
# (Use backup script from above)

# 6. Verify SSL
# Visit: https://www.ssllabs.com/ssltest/
```

## 📋 Checklist for Production

- [ ] Certificates obtained and installed
- [ ] Auto-renewal configured and tested
- [ ] Strong SSL configuration applied
- [ ] Monitoring set up
- [ ] Backups configured
- [ ] Certbot updated
- [ ] Firewall configured
- [ ] Security headers set
- [ ] HSTS enabled
- [ ] SSL tested with SSL Labs

## 📝 Exercises

1. Set up certificate expiration monitoring
2. Create backup script for certificates
3. Obtain wildcard certificate
4. Configure multiple domains efficiently
5. Implement strong SSL configuration
6. Set up comprehensive monitoring
7. Test certificate revocation
8. Create production deployment checklist

## ✅ Best Practices Checklist

- [ ] Auto-renewal enabled and tested
- [ ] Monitoring set up
- [ ] Backups configured
- [ ] Strong SSL configuration
- [ ] Security headers enabled
- [ ] Certbot kept updated
- [ ] Documentation maintained
- [ ] Disaster recovery plan ready

## 🎓 Summary

Following these best practices ensures:
- Reliable certificate management
- Security compliance
- Minimal downtime
- Easy troubleshooting
- Scalable certificate management

## ➡️ Conclusion

Congratulations! You've completed the Let's Encrypt comprehensive guide. You now know how to:
- Install and use Certbot
- Obtain and manage certificates
- Set up automatic renewal
- Troubleshoot common issues
- Follow best practices
- Implement advanced configurations

Continue practicing and stay updated with Let's Encrypt documentation!

