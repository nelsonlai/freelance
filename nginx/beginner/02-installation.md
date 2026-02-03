# Beginner Level - Module 2: Installation

## 📚 Learning Objectives

By the end of this module, you will:
- Install NGINX on different Linux distributions
- Install NGINX on macOS
- Verify the installation
- Start, stop, and restart NGINX
- Understand basic service management

## 🐧 Installation on Linux

### Ubuntu/Debian

#### Method 1: Using Package Manager (Recommended for Beginners)

```bash
# Update package list
sudo apt update

# Install NGINX
sudo apt install nginx -y

# Check version
nginx -v
```

#### Method 2: Using Official NGINX Repository (Latest Version)

```bash
# Install prerequisites
sudo apt install curl gnupg2 ca-certificates lsb-release

# Add NGINX signing key
curl -fsSL https://nginx.org/keys/nginx_signing.key | sudo apt-key add -

# Add stable repository
echo "deb http://nginx.org/packages/ubuntu $(lsb_release -cs) nginx" | \
    sudo tee /etc/apt/sources.list.d/nginx.list

# Update and install
sudo apt update
sudo apt install nginx -y
```

### CentOS/RHEL/Rocky Linux

#### Method 1: Using Package Manager

```bash
# Install EPEL repository
sudo yum install epel-release -y

# Install NGINX
sudo yum install nginx -y

# Check version
nginx -v
```

#### Method 2: Using Official NGINX Repository

```bash
# Add NGINX repository
sudo vi /etc/yum.repos.d/nginx.repo
```

Add the following content:
```ini
[nginx-stable]
name=nginx stable repo
baseurl=http://nginx.org/packages/centos/$releasever/$basearch/
gpgcheck=1
enabled=1
gpgkey=https://nginx.org/keys/nginx_signing.key
module_hotfixes=true
```

Then install:
```bash
sudo yum install nginx -y
```

### Fedora

```bash
# Install NGINX
sudo dnf install nginx -y

# Check version
nginx -v
```

### Arch Linux

```bash
# Install NGINX
sudo pacman -S nginx

# Check version
nginx -v
```

## 🍎 Installation on macOS

### Using Homebrew (Recommended)

```bash
# Install Homebrew if not already installed
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install NGINX
brew install nginx

# Check version
nginx -v
```

### Using MacPorts

```bash
# Install NGINX
sudo port install nginx

# Check version
nginx -v
```

## 🪟 Installation on Windows

### Download Binary

1. Visit [NGINX Download Page](https://nginx.org/en/download.html)
2. Download the Windows version (Mainline or Stable)
3. Extract the ZIP file to `C:\nginx` (or your preferred location)
4. Open Command Prompt as Administrator
5. Navigate to NGINX directory:
   ```cmd
   cd C:\nginx
   ```
6. Start NGINX:
   ```cmd
   start nginx
   ```

## ✅ Verifying Installation

### Check Version

```bash
nginx -v          # Short version
nginx -V          # Detailed version with compile options
```

### Check Installation Status

```bash
# Linux (systemd)
sudo systemctl status nginx

# macOS
brew services list | grep nginx

# Or check if process is running
ps aux | grep nginx
```

### Test Default Configuration

```bash
# Start NGINX
sudo systemctl start nginx      # Linux
sudo nginx                       # macOS/Manual

# Check if it's listening on port 80
sudo netstat -tlnp | grep :80
# or
sudo ss -tlnp | grep :80

# Open browser and visit
# http://localhost or http://your-server-ip
```

You should see the NGINX welcome page!

## 🔧 Service Management

### Linux (systemd)

```bash
# Start NGINX
sudo systemctl start nginx

# Stop NGINX
sudo systemctl stop nginx

# Restart NGINX
sudo systemctl restart nginx

# Reload configuration (without dropping connections)
sudo systemctl reload nginx

# Enable NGINX to start on boot
sudo systemctl enable nginx

# Disable auto-start on boot
sudo systemctl disable nginx

# Check status
sudo systemctl status nginx
```

### macOS (Homebrew)

```bash
# Start NGINX
brew services start nginx

# Stop NGINX
brew services stop nginx

# Restart NGINX
brew services restart nginx

# Check status
brew services list
```

### Manual Control (All Platforms)

```bash
# Start NGINX
sudo nginx

# Stop NGINX (graceful shutdown)
sudo nginx -s quit

# Stop NGINX (immediate shutdown)
sudo nginx -s stop

# Reload configuration
sudo nginx -s reload

# Reopen log files
sudo nginx -s reopen

# Test configuration file syntax
sudo nginx -t

# Test configuration and show files
sudo nginx -T
```

## 📁 Important Directories

### Linux

- **Configuration**: `/etc/nginx/`
- **Main Config**: `/etc/nginx/nginx.conf`
- **Site Configs**: `/etc/nginx/conf.d/` or `/etc/nginx/sites-available/`
- **Document Root**: `/usr/share/nginx/html/` or `/var/www/html/`
- **Logs**: `/var/log/nginx/`
- **Binary**: `/usr/sbin/nginx` or `/usr/bin/nginx`

### macOS (Homebrew)

- **Configuration**: `/usr/local/etc/nginx/` or `/opt/homebrew/etc/nginx/`
- **Main Config**: `/usr/local/etc/nginx/nginx.conf` or `/opt/homebrew/etc/nginx/nginx.conf`
- **Document Root**: `/usr/local/var/www/` or `/opt/homebrew/var/www/`
- **Logs**: `/usr/local/var/log/nginx/` or `/opt/homebrew/var/log/nginx/`

### Windows

- **Configuration**: `C:\nginx\conf\`
- **Document Root**: `C:\nginx\html\`
- **Logs**: `C:\nginx\logs\`

## 🔍 Testing Configuration

Always test your configuration before reloading:

```bash
# Test configuration syntax
sudo nginx -t

# Successful output:
# nginx: the configuration file /etc/nginx/nginx.conf syntax is ok
# nginx: configuration file /etc/nginx/nginx.conf test is successful
```

## 🚨 Common Installation Issues

### Port 80 Already in Use

```bash
# Check what's using port 80
sudo lsof -i :80
# or
sudo netstat -tlnp | grep :80

# Stop conflicting service (e.g., Apache)
sudo systemctl stop apache2
```

### Permission Denied

NGINX needs root privileges to bind to ports 80 and 443:

```bash
# Always use sudo for nginx commands
sudo nginx
sudo nginx -t
```

### Firewall Blocking

```bash
# Ubuntu/Debian (UFW)
sudo ufw allow 'Nginx Full'
# or
sudo ufw allow 80/tcp
sudo ufw allow 443/tcp

# CentOS/RHEL (firewalld)
sudo firewall-cmd --permanent --add-service=http
sudo firewall-cmd --permanent --add-service=https
sudo firewall-cmd --reload
```

## 📝 Exercises

1. Install NGINX on your system
2. Verify the installation with `nginx -v`
3. Start NGINX and verify it's running
4. Access the default page in your browser
5. Test the configuration with `nginx -t`
6. Stop and restart NGINX
7. Find the location of your nginx.conf file

## ✅ Checklist

- [ ] NGINX installed successfully
- [ ] Version verified
- [ ] Service can start and stop
- [ ] Default page accessible
- [ ] Configuration test passes
- [ ] Know location of config files

## ➡️ Next Steps

Proceed to [Module 3: Basic Configuration](./03-basic-configuration.md) to learn about NGINX configuration structure.

