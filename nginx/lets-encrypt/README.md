# Let's Encrypt Comprehensive Guide

Welcome to the comprehensive Let's Encrypt learning guide! This section provides step-by-step instructions for obtaining, managing, and maintaining free SSL/TLS certificates using Let's Encrypt and Certbot.

## 📚 Guide Overview

This guide is organized into six comprehensive modules:

### Module 1: Introduction
- What is Let's Encrypt?
- Benefits and features
- How Let's Encrypt works
- Understanding Certbot
- Certificate types and validation methods

### Module 2: Certbot Installation
- Installing Certbot on Linux distributions
- Installing on macOS and Windows
- Verifying installation
- Understanding plugins
- Pre-installation checklist

### Module 3: Obtaining Certificates
- Using NGINX plugin (easiest method)
- Standalone mode
- Webroot mode
- DNS challenge method
- Wildcard certificates
- Multiple domain certificates

### Module 4: Auto-Renewal
- Understanding certificate expiration
- Setting up automatic renewal
- Testing renewal process
- Configuring renewal hooks
- Monitoring certificate expiration
- Email notifications

### Module 5: Troubleshooting
- Common issues and solutions
- Debugging commands
- Diagnostic checklist
- Log file locations
- Advanced troubleshooting techniques
- Error message resolution

### Module 6: Best Practices
- Security best practices
- Certificate backup strategies
- Monitoring and alerting
- Wildcard certificate setup
- Advanced Certbot features
- Production deployment checklist

## 🎯 Learning Path

1. **Start with Module 1** to understand Let's Encrypt fundamentals
2. **Follow Module 2** to install Certbot on your system
3. **Use Module 3** to obtain your first certificate
4. **Set up Module 4** for automatic renewal
5. **Refer to Module 5** when encountering issues
6. **Implement Module 6** best practices for production

## 📋 Prerequisites

Before starting, ensure you have:
- A registered domain name
- Root or sudo access to your server
- NGINX or another web server installed
- Domain DNS pointing to your server IP
- Port 80 (and optionally 443) accessible from internet

## 🔑 Key Concepts

### Certificate Lifecycle
- Let's Encrypt certificates are valid for **90 days**
- Renewal should happen every **60-90 days**
- Automatic renewal is essential for production

### Validation Methods
- **HTTP-01**: Validates via web server (most common)
- **DNS-01**: Validates via DNS TXT record (for wildcards)
- **TLS-ALPN-01**: Advanced TLS handshake method

### Rate Limits
Let's Encrypt has rate limits:
- 50 certificates per registered domain per week
- 5 duplicate certificates per week
- 5 failed validations per hour per hostname

## 🚀 Quick Start

### Fastest Way to Get Started

1. **Install Certbot:**
   ```bash
   sudo apt install certbot python3-certbot-nginx
   ```

2. **Obtain Certificate:**
   ```bash
   sudo certbot --nginx -d example.com
   ```

3. **Verify Auto-Renewal:**
   ```bash
   sudo certbot renew --dry-run
   ```

That's it! Your certificate is installed and auto-renewal is configured.

## 📁 Module Files

- [Module 1: Introduction](./01-introduction.md)
- [Module 2: Certbot Installation](./02-certbot-installation.md)
- [Module 3: Obtaining Certificates](./03-obtaining-certificates.md)
- [Module 4: Auto-Renewal](./04-auto-renewal.md)
- [Module 5: Troubleshooting](./05-troubleshooting.md)
- [Module 6: Best Practices](./06-best-practices.md)

## 💡 Tips for Success

1. **Always test first**: Use `--dry-run` before making changes
2. **Monitor expiration**: Set up alerts for certificate expiration
3. **Keep Certbot updated**: Regular updates ensure compatibility
4. **Backup certificates**: Regular backups prevent data loss
5. **Use staging server**: Test with `--staging` flag first

## 🔗 Integration with NGINX Course

This Let's Encrypt guide complements the NGINX course materials:
- Works seamlessly with [Intermediate Module 1: SSL/TLS](../intermediate/01-ssl-tls.md)
- Examples use NGINX configuration
- Follows NGINX best practices

## 📖 Additional Resources

- [Let's Encrypt Official Website](https://letsencrypt.org/)
- [Certbot Documentation](https://certbot.eff.org/)
- [Let's Encrypt Community](https://community.letsencrypt.org/)
- [SSL Labs SSL Test](https://www.ssllabs.com/ssltest/)

## 🎓 Learning Objectives

By completing this guide, you will:
- Understand Let's Encrypt and how it works
- Install and configure Certbot
- Obtain SSL certificates for your domains
- Set up automatic certificate renewal
- Troubleshoot common certificate issues
- Implement best practices for production

## ➡️ Getting Started

Begin with [Module 1: Introduction](./01-introduction.md) to learn about Let's Encrypt.

Happy learning! 🔒

