# Let's Encrypt - Module 5: Troubleshooting

## 📚 Learning Objectives

By the end of this module, you will:
- Troubleshoot common certificate issues
- Fix validation failures
- Resolve renewal problems
- Handle rate limit issues
- Debug NGINX configuration problems
- Use Certbot debugging options

## 🔍 Common Issues and Solutions

### Issue 1: Domain Validation Failed

**Symptoms:**
```
Failed to obtain certificate
The following errors were reported by the server:
```

**Causes:**
- Domain doesn't point to server
- Port 80 blocked by firewall
- DNS propagation delay
- Wrong server IP

**Solutions:**

1. **Check DNS Resolution:**
   ```bash
   # Check if domain points to your server
   nslookup example.com
   dig example.com
   
   # Compare with server IP
   curl ifconfig.me
   ```

2. **Check Port 80 Accessibility:**
   ```bash
   # Test from external machine
   curl -I http://example.com
   
   # Check firewall
   sudo ufw status
   sudo firewall-cmd --list-all
   ```

3. **Verify Web Server Running:**
   ```bash
   sudo systemctl status nginx
   sudo netstat -tlnp | grep :80
   ```

4. **Check NGINX Configuration:**
   ```bash
   # Ensure server block exists
   sudo nginx -t
   sudo cat /etc/nginx/sites-available/default
   ```

### Issue 2: Certificate Renewal Fails

**Symptoms:**
```
Attempting to renew cert...
Cert not yet due for renewal
```

Or renewal errors.

**Solutions:**

1. **Check Renewal Logs:**
   ```bash
   sudo tail -f /var/log/letsencrypt/letsencrypt.log
   sudo journalctl -u certbot.service
   ```

2. **Test Renewal:**
   ```bash
   # Dry run
   sudo certbot renew --dry-run
   
   # Verbose output
   sudo certbot renew --dry-run -v
   ```

3. **Force Renewal (if needed):**
   ```bash
   sudo certbot renew --force-renewal
   ```

4. **Check Timer Status:**
   ```bash
   sudo systemctl status certbot.timer
   sudo systemctl list-timers
   ```

### Issue 3: Rate Limit Exceeded

**Symptoms:**
```
There were too many requests of a given type :: Error creating new order :: too many certificates already issued for exact set of domains
```

**Solutions:**

1. **Wait for Rate Limit Reset:**
   - Certificates per domain: Resets after 7 days
   - Failed validations: Resets after 1 hour
   - Check rate limits: https://letsencrypt.org/docs/rate-limits/

2. **Use Staging Server for Testing:**
   ```bash
   sudo certbot --staging -d example.com
   ```

3. **Check Current Certificates:**
   ```bash
   sudo certbot certificates
   ```

4. **Remove Unused Certificates:**
   ```bash
   sudo certbot delete --cert-name olddomain.com
   ```

### Issue 4: Port 80 Already in Use

**Symptoms:**
```
Error binding to port 80: Could not bind to IPv4 or IPv6
```

**Solutions:**

1. **Find Process Using Port 80:**
   ```bash
   sudo lsof -i :80
   sudo netstat -tlnp | grep :80
   ```

2. **Stop Conflicting Service:**
   ```bash
   # If Apache
   sudo systemctl stop apache2
   
   # Use webroot mode instead
   sudo certbot certonly --webroot -w /var/www/html -d example.com
   ```

3. **Use Standalone with Port Option:**
   ```bash
   sudo certbot certonly --standalone --http-01-port 8080 -d example.com
   ```

### Issue 5: NGINX Configuration Error

**Symptoms:**
```
nginx: [error] invalid PID number "" in "/var/run/nginx.pid"
```

Or configuration test fails.

**Solutions:**

1. **Test NGINX Configuration:**
   ```bash
   sudo nginx -t
   ```

2. **Check Certificate Paths:**
   ```bash
   # Verify paths in config
   sudo grep -r "ssl_certificate" /etc/nginx/
   
   # Check if files exist
   sudo ls -la /etc/letsencrypt/live/example.com/
   ```

3. **Fix Certificate Paths:**
   ```nginx
   # Correct paths
   ssl_certificate /etc/letsencrypt/live/example.com/fullchain.pem;
   ssl_certificate_key /etc/letsencrypt/live/example.com/privkey.pem;
   ```

### Issue 6: Certificate Not Trusted by Browser

**Symptoms:**
Browser shows "Not Secure" or certificate error.

**Solutions:**

1. **Check Certificate Chain:**
   ```bash
   openssl s_client -connect example.com:443 -servername example.com
   ```

2. **Verify Certificate Files:**
   ```bash
   # Check fullchain includes intermediate
   sudo openssl x509 -in /etc/letsencrypt/live/example.com/fullchain.pem -text -noout
   ```

3. **Ensure Using fullchain.pem:**
   ```nginx
   # Correct
   ssl_certificate /etc/letsencrypt/live/example.com/fullchain.pem;
   
   # Incorrect (missing chain)
   ssl_certificate /etc/letsencrypt/live/example.com/cert.pem;
   ```

## 🔧 Debugging Commands

### Verbose Mode

```bash
# Verbose output
sudo certbot --nginx -d example.com -v

# Very verbose
sudo certbot --nginx -d example.com -vv
```

### Debug Logging

```bash
# Enable debug logging
sudo certbot --nginx -d example.com --debug

# View debug logs
sudo tail -f /var/log/letsencrypt/letsencrypt.log
```

### Test with Staging

```bash
# Use staging server (no rate limits)
sudo certbot --staging --nginx -d example.com

# Test renewal with staging
sudo certbot renew --staging --dry-run
```

## 📋 Diagnostic Checklist

Run through this checklist when troubleshooting:

### 1. Domain and DNS

- [ ] Domain resolves to correct IP
- [ ] DNS propagation complete
- [ ] No DNS caching issues

```bash
# Test DNS
nslookup example.com
dig example.com +short
```

### 2. Network Connectivity

- [ ] Port 80 accessible from internet
- [ ] Firewall allows HTTP/HTTPS
- [ ] No reverse proxy blocking

```bash
# Test from external
curl -I http://example.com

# Check firewall
sudo ufw status
```

### 3. Web Server

- [ ] NGINX/Apache running
- [ ] Web server accessible
- [ ] Configuration valid

```bash
# Check service
sudo systemctl status nginx

# Test config
sudo nginx -t
```

### 4. Certbot

- [ ] Certbot installed
- [ ] Plugins available
- [ ] Permissions correct

```bash
# Check Certbot
certbot --version
certbot plugins

# Check permissions
sudo ls -la /etc/letsencrypt/
```

### 5. Certificate Status

- [ ] Certificate exists
- [ ] Not expired
- [ ] Valid for domain

```bash
# List certificates
sudo certbot certificates

# Check expiration
sudo openssl x509 -in /etc/letsencrypt/live/example.com/cert.pem -noout -dates
```

## 🔍 Log File Locations

### Certbot Logs

```bash
# Main log file
/var/log/letsencrypt/letsencrypt.log

# View logs
sudo tail -f /var/log/letsencrypt/letsencrypt.log

# Search for errors
sudo grep -i error /var/log/letsencrypt/letsencrypt.log
```

### Systemd Logs

```bash
# Certbot service logs
sudo journalctl -u certbot.service

# Certbot timer logs
sudo journalctl -u certbot.timer

# Follow logs
sudo journalctl -u certbot.service -f
```

### NGINX Logs

```bash
# Error log
sudo tail -f /var/log/nginx/error.log

# Access log
sudo tail -f /var/log/nginx/access.log
```

## 🛠️ Advanced Troubleshooting

### Manual Certificate Request

If automated methods fail, try manual:

```bash
# Manual DNS challenge
sudo certbot certonly --manual --preferred-challenges dns -d example.com

# Follow prompts to add TXT record
```

### Certificate Verification

```bash
# Verify certificate
sudo openssl x509 -in /etc/letsencrypt/live/example.com/cert.pem -text -noout

# Check certificate chain
openssl s_client -connect example.com:443 -servername example.com -showcerts

# Test with SSL Labs
# Visit: https://www.ssllabs.com/ssltest/
```

### Reset Certbot

If Certbot is corrupted:

```bash
# Backup current config
sudo cp -r /etc/letsencrypt /etc/letsencrypt.backup

# Delete account (careful!)
# sudo rm -rf /etc/letsencrypt/accounts/

# Re-register
sudo certbot register --email youremail@example.com
```

## 📝 Common Error Messages

### "Failed to obtain certificate"

**Possible causes:**
- DNS not pointing to server
- Port 80 blocked
- Web server not running

### "Too many certificates already issued"

**Solution:**
- Wait for rate limit reset
- Use staging for testing
- Remove unused certificates

### "Connection refused"

**Possible causes:**
- Web server not running
- Firewall blocking
- Wrong port

### "Challenge failed"

**Possible causes:**
- Can't access validation file
- DNS challenge record incorrect
- Network issues

## 📝 Exercises

1. Simulate and fix a DNS resolution issue
2. Troubleshoot a port 80 conflict
3. Fix a certificate renewal failure
4. Handle a rate limit error
5. Debug NGINX configuration errors
6. Verify certificate chain is correct
7. Use verbose mode to diagnose issues
8. Create a troubleshooting checklist

## ✅ Troubleshooting Checklist

- [ ] Can identify common certificate issues
- [ ] Know how to check DNS resolution
- [ ] Can verify port accessibility
- [ ] Understand rate limits
- [ ] Can use debug mode
- [ ] Know log file locations
- [ ] Can verify certificate validity
- [ ] Have troubleshooting workflow

## ➡️ Next Steps

Proceed to [Module 6: Best Practices and Advanced Topics](./06-best-practices.md) to learn advanced techniques and best practices.

