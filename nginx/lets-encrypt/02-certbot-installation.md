# Let's Encrypt - Module 2: Certbot Installation

## 📚 Learning Objectives

By the end of this module, you will:
- Install Certbot on different Linux distributions
- Install Certbot on macOS
- Verify Certbot installation
- Understand Certbot plugins
- Configure Certbot for NGINX

## 🐧 Installation on Linux

### Ubuntu/Debian

#### Method 1: Using apt (Recommended)

```bash
# Update package list
sudo apt update

# Install Certbot and NGINX plugin
sudo apt install certbot python3-certbot-nginx -y

# Verify installation
certbot --version
```

#### Method 2: Using snapd (Latest Version)

```bash
# Install snapd if not installed
sudo apt update
sudo apt install snapd -y

# Install Certbot via snap
sudo snap install core; sudo snap refresh core
sudo snap install --classic certbot

# Create symlink
sudo ln -s /snap/bin/certbot /usr/bin/certbot

# Verify installation
certbot --version
```

### CentOS/RHEL/Rocky Linux

#### Using yum/dnf

```bash
# Install EPEL repository
sudo yum install epel-release -y
# or for RHEL 8+
sudo dnf install epel-release -y

# Install Certbot
sudo yum install certbot python3-certbot-nginx -y
# or
sudo dnf install certbot python3-certbot-nginx -y

# Verify installation
certbot --version
```

#### Using snapd (Alternative)

```bash
# Install snapd
sudo yum install snapd -y
sudo systemctl enable --now snapd.socket
sudo ln -s /var/lib/snapd/snap /snap

# Install Certbot
sudo snap install core; sudo snap refresh core
sudo snap install --classic certbot
```

### Fedora

```bash
# Install Certbot
sudo dnf install certbot python3-certbot-nginx -y

# Verify installation
certbot --version
```

### Arch Linux

```bash
# Install Certbot
sudo pacman -S certbot certbot-nginx

# Verify installation
certbot --version
```

### Amazon Linux 2

```bash
# Install Certbot
sudo yum install certbot python3-certbot-nginx -y

# Verify installation
certbot --version
```

## 🍎 Installation on macOS

### Using Homebrew

```bash
# Install Homebrew if not already installed
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install Certbot
brew install certbot

# Verify installation
certbot --version
```

### Using MacPorts

```bash
# Install Certbot
sudo port install py39-certbot

# Verify installation
certbot --version
```

## 🪟 Installation on Windows

### Using WSL (Windows Subsystem for Linux)

1. Install WSL (Ubuntu recommended)
2. Follow Ubuntu installation instructions above

### Using Docker

```bash
# Run Certbot via Docker
docker run -it --rm \
  -v /etc/letsencrypt:/etc/letsencrypt \
  -v /var/lib/letsencrypt:/var/lib/letsencrypt \
  certbot/certbot certonly --standalone
```

## ✅ Verify Installation

### Check Certbot Version

```bash
certbot --version
```

Expected output:
```
certbot 2.x.x
```

### Check Certbot Help

```bash
certbot --help
```

### List Available Plugins

```bash
certbot plugins
```

Common plugins:
- `nginx`: Auto-configure NGINX
- `apache`: Auto-configure Apache
- `standalone`: Run standalone web server
- `webroot`: Use webroot for validation
- `dns-cloudflare`: DNS challenge with Cloudflare
- `dns-route53`: DNS challenge with Route53

## 🔌 Certbot Plugins for NGINX

### NGINX Plugin

The NGINX plugin automatically:
- Obtains certificates
- Configures NGINX for HTTPS
- Sets up automatic renewal

**Installation:**
```bash
# Ubuntu/Debian
sudo apt install python3-certbot-nginx -y

# CentOS/RHEL
sudo yum install python3-certbot-nginx -y

# Fedora
sudo dnf install python3-certbot-nginx -y
```

**Verify Plugin:**
```bash
certbot plugins
```

Look for `nginx` in the output.

## 🔧 Pre-Installation Checklist

Before installing Certbot, ensure:

1. **Domain Points to Server**
   ```bash
   # Check DNS resolution
   nslookup yourdomain.com
   dig yourdomain.com
   ```

2. **Port 80 is Open**
   ```bash
   # Check if port 80 is accessible
   sudo netstat -tlnp | grep :80
   sudo ss -tlnp | grep :80
   ```

3. **Firewall Allows HTTP/HTTPS**
   ```bash
   # Ubuntu/Debian (UFW)
   sudo ufw allow 80/tcp
   sudo ufw allow 443/tcp
   
   # CentOS/RHEL (firewalld)
   sudo firewall-cmd --permanent --add-service=http
   sudo firewall-cmd --permanent --add-service=https
   sudo firewall-cmd --reload
   ```

4. **NGINX is Installed and Running**
   ```bash
   # Check NGINX status
   sudo systemctl status nginx
   
   # Start if not running
   sudo systemctl start nginx
   sudo systemctl enable nginx
   ```

5. **Basic NGINX Configuration Exists**
   ```bash
   # Check configuration
   sudo nginx -t
   
   # Ensure server block exists for your domain
   sudo cat /etc/nginx/sites-available/default
   ```

## 📋 Installation Methods Comparison

### System Package Manager (apt/yum/dnf)

**Pros:**
- Easy installation
- Automatic updates with system
- Integrated with package manager

**Cons:**
- May not be latest version
- Dependent on distribution updates

### Snap Package

**Pros:**
- Always latest version
- Automatic updates
- Works across distributions

**Cons:**
- Requires snapd
- Additional abstraction layer

### pip (Python Package Manager)

```bash
# Install via pip
pip install certbot certbot-nginx
```

**Pros:**
- Latest version
- Python environment control

**Cons:**
- May conflict with system packages
- Requires Python environment management

## 🧪 Post-Installation Testing

### Test Certbot Command

```bash
# Test Certbot without making changes
sudo certbot --dry-run --nginx -d yourdomain.com
```

### Check Certbot Configuration

```bash
# View Certbot configuration
sudo certbot show_account

# View certificate directories
ls -la /etc/letsencrypt/
```

## 🔍 Troubleshooting Installation

### Issue: Command Not Found

```bash
# Check if Certbot is in PATH
which certbot

# Check installation location
whereis certbot

# Add to PATH if needed
export PATH=$PATH:/usr/local/bin
```

### Issue: Permission Denied

```bash
# Certbot requires root/sudo for most operations
sudo certbot --version

# Check sudo access
sudo -v
```

### Issue: Plugin Not Found

```bash
# Reinstall plugin
# Ubuntu/Debian
sudo apt install --reinstall python3-certbot-nginx

# Verify plugin
certbot plugins
```

### Issue: Port 80 Already in Use

```bash
# Check what's using port 80
sudo lsof -i :80
sudo netstat -tlnp | grep :80

# Stop conflicting service
sudo systemctl stop apache2  # If Apache is running
```

## 📝 Exercises

1. Install Certbot on your system
2. Verify Certbot installation with `--version`
3. Check available Certbot plugins
4. Verify NGINX plugin is installed
5. Check if your domain points to your server
6. Ensure port 80 is accessible
7. Test Certbot in dry-run mode
8. Review Certbot configuration directory

## ✅ Checklist

- [ ] Certbot installed successfully
- [ ] Certbot version verified
- [ ] NGINX plugin installed (if using NGINX)
- [ ] Domain DNS configured correctly
- [ ] Port 80 accessible
- [ ] Firewall configured
- [ ] NGINX installed and running
- [ ] Ready to obtain certificates

## ➡️ Next Steps

Proceed to [Module 3: Obtaining Your First Certificate](./03-obtaining-certificates.md) to learn how to obtain SSL certificates for your domain.

