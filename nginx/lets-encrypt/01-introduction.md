# Let's Encrypt - Module 1: Introduction

## 📚 Learning Objectives

By the end of this module, you will:
- Understand what Let's Encrypt is
- Know the benefits of Let's Encrypt
- Understand how Let's Encrypt works
- Learn about Certbot
- Understand certificate validation methods

## 🔒 What is Let's Encrypt?

Let's Encrypt is a free, automated, and open Certificate Authority (CA) that provides SSL/TLS certificates for websites. It was launched in 2016 by the Internet Security Research Group (ISRG).

### Key Features

1. **Free**: No cost for certificates
2. **Automated**: Automated certificate issuance and renewal
3. **Trusted**: Certificates are trusted by all major browsers
4. **Open**: Transparent and auditable
5. **Secure**: Uses modern security practices

### Benefits

- **Cost**: Eliminates SSL certificate costs
- **Accessibility**: Makes HTTPS accessible to everyone
- **Automation**: Automated renewal reduces management overhead
- **Security**: Encourages HTTPS adoption
- **Standard**: Industry-standard certificates

## 🎯 How Let's Encrypt Works

### Certificate Lifecycle

1. **Request**: Request certificate for your domain
2. **Validation**: Prove domain ownership
3. **Issuance**: Receive signed certificate
4. **Installation**: Install certificate on server
5. **Renewal**: Automatically renew before expiration (90 days)

### Domain Validation Methods

Let's Encrypt validates domain ownership using one of these methods:

1. **HTTP-01 Challenge**: Place a file on your web server
2. **DNS-01 Challenge**: Add a TXT record to DNS
3. **TLS-ALPN-01 Challenge**: Use TLS handshake (advanced)

## 🤖 What is Certbot?

Certbot is the official client software for Let's Encrypt. It automates:
- Certificate issuance
- Certificate installation
- Certificate renewal
- Web server configuration

### Certbot Features

- **Easy Installation**: Simple installation process
- **Auto-Configuration**: Can configure NGINX/Apache automatically
- **Manual Mode**: Manual configuration options available
- **Renewal Automation**: Automatic renewal setup
- **Plugin Support**: Plugins for different web servers

## 🔑 Certificate Types

### Domain Validation (DV) Certificates

- Validates domain ownership only
- Fastest to obtain (minutes)
- Suitable for most websites
- Free with Let's Encrypt

### Wildcard Certificates

- Covers domain and all subdomains (*.example.com)
- Requires DNS-01 challenge
- Useful for multiple subdomains

### Single Domain Certificates

- Covers one domain (example.com)
- Can include www subdomain (example.com + www.example.com)

## 📋 Prerequisites

Before using Let's Encrypt, you need:

1. **Domain Name**: A registered domain name
2. **Server Access**: Root or sudo access to server
3. **Port 80/443 Open**: HTTP/HTTPS ports accessible
4. **DNS Configuration**: Domain pointing to your server IP
5. **Web Server**: NGINX, Apache, or ability to run standalone

## 🎓 Important Concepts

### Certificate Expiration

- Let's Encrypt certificates are valid for **90 days**
- Renewal should happen every **60-90 days**
- Automatic renewal is recommended

### Rate Limits

Let's Encrypt has rate limits to prevent abuse:

- **Certificates per Registered Domain**: 50 per week
- **Duplicate Certificate**: 5 per week
- **Failed Validations**: 5 per account, per hostname, per hour
- **New Accounts**: 10 per IP per 3 hours

### Validation Timing

- HTTP-01: Requires web server running
- DNS-01: Requires DNS access
- Validation typically takes seconds to minutes

## 🔒 Security Considerations

### Private Key Security

- Private keys must be kept secure
- Certbot handles key generation securely
- Back up certificates and keys

### Certificate Transparency

- All certificates are logged publicly
- Provides security and auditability
- Browsers check CT logs

## 📊 Let's Encrypt vs Commercial Certificates

| Feature | Let's Encrypt | Commercial |
|---------|---------------|------------|
| Cost | Free | $50-$500+/year |
| Validation | Automated | Manual/Automated |
| Duration | 90 days | 1-3 years |
| Renewal | Automated | Manual/Automated |
| Wildcard | Yes (DNS challenge) | Yes |
| Trust | All browsers | All browsers |
| Support | Community | Paid support |

## ✅ Advantages of Let's Encrypt

1. **Zero Cost**: Completely free
2. **Easy Setup**: Automated tools available
3. **Auto-Renewal**: Reduces maintenance
4. **Trusted**: Works everywhere
5. **Modern Standards**: Uses latest security practices

## ⚠️ Limitations

1. **Short Validity**: 90 days (mitigated by auto-renewal)
2. **DV Only**: No Extended Validation (EV) certificates
3. **Rate Limits**: Limits on certificate requests
4. **Domain Validation Only**: No organization validation

## 🚀 Getting Started

To get started with Let's Encrypt:

1. Install Certbot on your server
2. Ensure your domain points to your server
3. Run Certbot to obtain certificate
4. Configure auto-renewal
5. Test your HTTPS setup

## 📝 Summary

Let's Encrypt provides free, automated SSL/TLS certificates that make HTTPS accessible to everyone. Using Certbot, you can easily obtain and renew certificates automatically. While certificates expire every 90 days, automated renewal makes this a non-issue in practice.

## ➡️ Next Steps

Proceed to [Module 2: Certbot Installation](./02-certbot-installation.md) to learn how to install Certbot on different operating systems.

