# Let's Encrypt - Module 4: Auto-Renewal

## 📚 Learning Objectives

By the end of this module, you will:
- Understand certificate expiration
- Set up automatic renewal
- Test renewal process
- Configure renewal hooks
- Troubleshoot renewal issues
- Monitor certificate expiration

## ⏰ Certificate Expiration

### Let's Encrypt Certificate Lifecycle

- **Validity Period**: 90 days
- **Recommended Renewal**: Every 60 days
- **Automatic Renewal**: Set up to run automatically

### Why Auto-Renewal?

- Certificates expire every 90 days
- Manual renewal is error-prone
- Prevents service interruption
- Ensures continuous HTTPS

## 🔄 Setting Up Auto-Renewal

### Automatic Setup (NGINX Plugin)

If you used `certbot --nginx`, auto-renewal is usually configured automatically:

```bash
# Check renewal timer status
sudo systemctl status certbot.timer

# Check renewal service
sudo systemctl status certbot.service
```

### Manual Setup

Certbot creates a systemd timer for automatic renewal:

```bash
# Check if timer exists
sudo systemctl list-timers | grep certbot

# Enable and start timer (if not running)
sudo systemctl enable certbot.timer
sudo systemctl start certbot.timer
```

### Verify Timer Configuration

```bash
# View timer file
sudo cat /lib/systemd/system/certbot.timer

# Check timer status
sudo systemctl status certbot.timer
sudo systemctl list-timers certbot.timer
```

## 🧪 Testing Renewal

### Dry Run (Test Without Renewing)

```bash
# Test renewal without actually renewing
sudo certbot renew --dry-run

# Test specific certificate
sudo certbot renew --dry-run --cert-name example.com
```

**Expected Output:**
```
The dry run was successful.
```

### Force Renewal (For Testing)

```bash
# Force renewal (even if not expired)
sudo certbot renew --force-renewal

# Renew specific certificate
sudo certbot renew --cert-name example.com --force-renewal
```

**Warning**: Don't do this too often - respect rate limits!

## ⚙️ Renewal Configuration

### Renewal Configuration Files

Certbot stores renewal configuration in:
```
/etc/letsencrypt/renewal/
```

### View Renewal Configuration

```bash
# List renewal configs
sudo ls -la /etc/letsencrypt/renewal/

# View specific renewal config
sudo cat /etc/letsencrypt/renewal/example.com.conf
```

Example renewal configuration:
```ini
# renew_before_expiry = 30 days
version = 2.0.0
archive_dir = /etc/letsencrypt/archive/example.com
cert = /etc/letsencrypt/live/example.com/cert.pem
privkey = /etc/letsencrypt/live/example.com/privkey.pem
chain = /etc/letsencrypt/live/example.com/chain.pem
fullchain = /etc/letsencrypt/live/example.com/fullchain.pem

# Options used in the renewal request
renew_hook = systemctl reload nginx
```

## 🔧 Renewal Hooks

### Pre-Hook (Before Renewal)

Runs before certificate renewal:

```ini
# In renewal config file
pre_hook = systemctl stop nginx
```

### Renewal Hook (After Renewal)

Runs after successful renewal:

```ini
# In renewal config file
renew_hook = systemctl reload nginx
```

### Post-Hook (Always Runs)

Runs after renewal attempt (success or failure):

```ini
# In renewal config file
post_hook = systemctl start nginx
```

### Configure Hooks via Command Line

```bash
# Add renewal hook
sudo certbot renew --renew-hook "systemctl reload nginx"

# Add pre-hook (for standalone mode)
sudo certbot renew --pre-hook "systemctl stop nginx" --post-hook "systemctl start nginx"
```

### Example: Standalone Mode with Hooks

```bash
# Renewal command with hooks
sudo certbot renew \
    --pre-hook "systemctl stop nginx" \
    --post-hook "systemctl start nginx" \
    --renew-hook "systemctl reload nginx"
```

## 📅 Scheduling Renewal

### Systemd Timer (Default)

Certbot uses systemd timer that runs twice daily:

```bash
# Check timer schedule
sudo systemctl list-timers certbot.timer

# View timer details
sudo systemctl cat certbot.timer
```

### Cron Job (Alternative)

If systemd isn't available, use cron:

```bash
# Edit crontab
sudo crontab -e

# Add renewal check (runs twice daily)
0 0,12 * * * certbot renew --quiet --renew-hook "systemctl reload nginx"
```

**Cron Schedule Explanation:**
- `0 0,12 * * *`: Run at 00:00 and 12:00 every day
- `--quiet`: Only output on errors
- `--renew-hook`: Reload NGINX after renewal

## 🔍 Monitoring Certificate Expiration

### Check Certificate Expiration

```bash
# List all certificates with expiration
sudo certbot certificates

# Check specific certificate
sudo certbot certificates --cert-name example.com

# Check expiration date
sudo openssl x509 -in /etc/letsencrypt/live/example.com/cert.pem -noout -dates
```

### Automated Expiration Check Script

Create a monitoring script:

```bash
#!/bin/bash
# /usr/local/bin/check-cert-expiry.sh

DOMAIN="example.com"
DAYS_BEFORE_EXPIRY=30

CERT_FILE="/etc/letsencrypt/live/$DOMAIN/cert.pem"
EXPIRY_DATE=$(openssl x509 -in "$CERT_FILE" -noout -enddate | cut -d= -f2)
EXPIRY_TIMESTAMP=$(date -d "$EXPIRY_DATE" +%s)
CURRENT_TIMESTAMP=$(date +%s)
DAYS_UNTIL_EXPIRY=$(( ($EXPIRY_TIMESTAMP - $CURRENT_TIMESTAMP) / 86400 ))

if [ $DAYS_UNTIL_EXPIRY -lt $DAYS_BEFORE_EXPIRY ]; then
    echo "WARNING: Certificate for $DOMAIN expires in $DAYS_UNTIL_EXPIRY days"
    # Send alert (email, notification, etc.)
fi
```

Add to cron:
```bash
# Run daily
0 9 * * * /usr/local/bin/check-cert-expiry.sh
```

## 📧 Email Notifications

### Renewal Reminders

Let's Encrypt sends email reminders:
- 20 days before expiration
- 10 days before expiration
- 1 day before expiration

### Update Email Address

```bash
# Update email for account
sudo certbot update_account --email newemail@example.com

# Register new account with email
sudo certbot register --email youremail@example.com --agree-tos
```

## 🔧 Advanced Renewal Options

### Renewal for Specific Certificates

```bash
# Renew specific certificate
sudo certbot renew --cert-name example.com

# Renew certificates for specific domains
sudo certbot renew --cert-path /etc/letsencrypt/live/example.com
```

### Quiet Mode

```bash
# Only output on errors (for cron)
sudo certbot renew --quiet
```

### Non-Interactive Renewal

```bash
# Run without user interaction
sudo certbot renew --quiet --non-interactive
```

### Renewal with Specific Plugin

```bash
# Renew using NGINX plugin
sudo certbot renew --nginx

# Renew using standalone
sudo certbot renew --standalone
```

## 🚨 Troubleshooting Renewal

### Issue: Renewal Fails

**Check logs:**
```bash
# Certbot logs
sudo tail -f /var/log/letsencrypt/letsencrypt.log

# System logs
sudo journalctl -u certbot.timer
sudo journalctl -u certbot.service
```

**Common causes:**
- Domain DNS changed
- Port 80 blocked
- NGINX configuration error
- Rate limit exceeded

### Issue: Timer Not Running

```bash
# Check timer status
sudo systemctl status certbot.timer

# Enable and start timer
sudo systemctl enable certbot.timer
sudo systemctl start certbot.timer

# Check if timer is scheduled
sudo systemctl list-timers
```

### Issue: NGINX Not Reloading

```bash
# Manually reload after renewal
sudo certbot renew --renew-hook "systemctl reload nginx"

# Test NGINX config first
sudo nginx -t
```

### Issue: Rate Limit Exceeded

```bash
# Check rate limit status
# Visit: https://letsencrypt.org/docs/rate-limits/

# Wait before retrying
# Use staging server for testing
sudo certbot renew --staging
```

## 📊 Renewal Best Practices

1. **Test Regularly**: Run `--dry-run` monthly
2. **Monitor Logs**: Check renewal logs regularly
3. **Use Hooks**: Configure renewal hooks properly
4. **Backup Certificates**: Backup certificate files
5. **Monitor Expiration**: Set up expiration alerts
6. **Document Process**: Document your renewal setup

## 📝 Complete Renewal Setup Example

### Systemd Timer Setup

```bash
# Enable timer
sudo systemctl enable certbot.timer
sudo systemctl start certbot.timer

# Verify
sudo systemctl status certbot.timer
sudo systemctl list-timers certbot.timer
```

### Renewal Configuration

```bash
# Test renewal
sudo certbot renew --dry-run

# Configure renewal hooks (if needed)
# Edit /etc/letsencrypt/renewal/example.com.conf
# Add: renew_hook = systemctl reload nginx
```

### Monitoring Script

Create monitoring and alerting for certificate expiration.

## 📝 Exercises

1. Check if auto-renewal is enabled
2. Test renewal with `--dry-run`
3. Verify renewal timer is scheduled
4. Configure renewal hooks
5. Check certificate expiration dates
6. Create expiration monitoring script
7. Test forced renewal (with caution)
8. Review renewal logs

## ✅ Checklist

- [ ] Auto-renewal enabled and working
- [ ] Renewal timer scheduled
- [ ] Tested renewal with `--dry-run`
- [ ] Renewal hooks configured
- [ ] Monitoring expiration dates
- [ ] Email notifications set up
- [ ] Documented renewal process
- [ ] Tested renewal process

## ➡️ Next Steps

Proceed to [Module 5: Troubleshooting](./05-troubleshooting.md) to learn how to troubleshoot common Let's Encrypt issues.

