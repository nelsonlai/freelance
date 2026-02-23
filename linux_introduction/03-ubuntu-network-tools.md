# Ubuntu Linux Built-in Network Tools (Run from Shell)

This guide covers common Ubuntu/Linux command-line tools for networking: DNS, firewall, interfaces, connectivity, and related tasks. All commands are run from the shell (terminal).

---

## Table of Contents

1. [DNS Tools](#dns-tools)
2. [Firewall (UFW)](#firewall-ufw)
3. [Network Interfaces and IP](#network-interfaces-and-ip)
4. [Connectivity and Diagnostics](#connectivity-and-diagnostics)
5. [SSH and Remote Access](#ssh-and-remote-access)
6. [Network Manager (CLI)](#network-manager-cli)

---

## DNS Tools

### dig — Domain Information Groper

Query DNS records. Often not installed by default; install with: `sudo apt install dnsutils`

```bash
# Basic A record lookup
dig example.com

# Short output
dig +short example.com

# Specific record types
dig example.com A
dig example.com MX
dig example.com NS
dig example.com TXT
dig example.com SOA

# Use a specific DNS server (e.g. Google 8.8.8.8)
dig @8.8.8.8 example.com

# Reverse DNS (PTR)
dig -x 8.8.8.8

# Trace delegation path
dig +trace example.com
```

### nslookup

Interactive or one-off DNS lookup (part of `dnsutils`).

```bash
# Simple lookup
nslookup example.com

# Use specific server
nslookup example.com 8.8.8.8

# Query type
nslookup -type=MX example.com

# Interactive mode (then type domain names, then exit)
nslookup
> example.com
> google.com
> exit
```

### host

Simple DNS lookup (part of `dnsutils`).

```bash
# A record
host example.com

# All record types
host -a example.com

# Specific type
host -t MX example.com
host -t NS example.com

# Use specific DNS server
host example.com 8.8.8.8

# Reverse lookup
host 8.8.8.8
```

### resolvectl / systemd-resolve (systemd DNS)

Ubuntu uses **systemd-resolved** for DNS. Inspect and test resolution:

```bash
# Show DNS configuration and statistics
resolvectl status

# Query via system resolver (respects /etc/resolv.conf)
resolvectl query example.com

# Flush DNS cache (if caching is enabled)
sudo resolvectl flush-caches
```

### /etc/resolv.conf

Shows which DNS servers the system uses (often managed by systemd-resolved or NetworkManager).

```bash
# View current DNS servers
cat /etc/resolv.conf
```

---

## Firewall (UFW)

**UFW** (Uncomplicated Firewall) is the default firewall front-end on Ubuntu. It configures **iptables**/nftables.

### Enable and status

```bash
# Check status
sudo ufw status

# Verbose status (with rules)
sudo ufw status verbose

# Numbered rules (useful for delete)
sudo ufw status numbered

# Enable firewall (will prompt if SSH might be blocked)
sudo ufw enable

# Disable firewall
sudo ufw disable

# Reset to defaults
sudo ufw reset
```

### Allow and deny

```bash
# Allow port (default: incoming)
sudo ufw allow 22        # SSH
sudo ufw allow 80        # HTTP
sudo ufw allow 443       # HTTPS
sudo ufw allow 8080/tcp  # specify protocol

# Allow from specific IP
sudo ufw allow from 192.168.1.100

# Allow from subnet
sudo ufw allow from 192.168.1.0/24

# Allow port from specific IP only
sudo ufw allow from 192.168.1.100 to any port 22

# Deny
sudo ufw deny 3306       # block MySQL port
sudo ufw deny from 10.0.0.50

# Delete rule (by rule text or number)
sudo ufw delete allow 80
sudo ufw status numbered
sudo ufw delete 2
```

### Default policy and reload

```bash
# Default incoming: deny; outgoing: allow
sudo ufw default deny incoming
sudo ufw default allow outgoing

# Reload after changes (usually automatic)
sudo ufw reload
```

### Application profiles

```bash
# List application profiles
sudo ufw app list

# Allow by app name
sudo ufw allow 'Nginx Full'
sudo ufw allow 'OpenSSH'
```

---

## Network Interfaces and IP

### ip — Modern replacement for ifconfig

```bash
# List all interfaces with addresses
ip addr show
# or short:
ip a

# List only one interface
ip addr show eth0

# Bring interface up/down
sudo ip link set eth0 up
sudo ip link set eth0 down

# Add/remove IP address
sudo ip addr add 192.168.1.10/24 dev eth0
sudo ip addr del 192.168.1.10/24 dev eth0

# Show routing table
ip route show
ip route

# Add default gateway
sudo ip route add default via 192.168.1.1

# Show link (layer 2) info
ip link show

# Show ARP table
ip neigh show
```

### ss — Socket statistics (replacement for netstat)

```bash
# All listening sockets
ss -tuln

# -t TCP, -u UDP, -l listening, -n numeric (no DNS)
ss -tln    # TCP listening
ss -uln    # UDP listening

# Show processes using sockets
ss -tulnp

# All connections (including established)
ss -tun
```

### nmcli — NetworkManager (see [Network Manager](#network-manager-cli))

---

## Connectivity and Diagnostics

### ping

```bash
# Basic ping (ICMP)
ping -c 4 example.com
ping -c 4 8.8.8.8

# Specify interval (seconds)
ping -i 2 8.8.8.8

# Only print summary
ping -c 4 -q 8.8.8.8
```

### traceroute / tracepath

Show path (hops) to destination.

```bash
# Install if needed: sudo apt install traceroute
traceroute example.com
traceroute -n 8.8.8.8   # no DNS lookup for hops

# tracepath (often installed by default, no root)
tracepath example.com
tracepath -n 8.8.8.8
```

### curl — HTTP(s) and more

```bash
# GET and print body
curl https://example.com

# Show response headers
curl -I https://example.com

# Follow redirects
curl -L https://example.com

# Verbose
curl -v https://example.com

# Save to file
curl -o page.html https://example.com

# Custom request
curl -X POST -d "key=value" https://api.example.com/endpoint
curl -H "Authorization: Bearer TOKEN" https://api.example.com
```

### wget — Download files

```bash
# Download file
wget https://example.com/file.zip

# Save with custom name
wget -O myfile.zip https://example.com/file.zip

# Continue partial download
wget -c https://example.com/largefile.iso

# Background
wget -b https://example.com/file.zip
```

### netcat (nc) — Read/write over network

```bash
# Test if port is open (connect)
nc -zv hostname 22
nc -zv 192.168.1.1 80

# Listen on port (simple server)
nc -l -p 9999

# Send data
echo "hello" | nc hostname 9999
```

### telnet — Test TCP connectivity (optional)

```bash
# Install: sudo apt install telnet
telnet example.com 80
# Then type HTTP request or quit with Ctrl+] then quit
```

### openssl — TLS/SSL and certificates

```bash
# Test HTTPS connectivity
openssl s_client -connect example.com:443 -servername example.com

# Check certificate expiry
echo | openssl s_client -connect example.com:443 -servername example.com 2>/dev/null | openssl x509 -noout -dates
```

---

## SSH and Remote Access

### ssh — Secure Shell client

```bash
# Basic login
ssh user@hostname
ssh user@192.168.1.10

# Specify port
ssh -p 2222 user@hostname

# Run single command
ssh user@hostname "ls -la /tmp"

# Copy files (use scp or rsync)
scp file.txt user@hostname:/remote/path/
scp user@hostname:/remote/file.txt ./
```

### ssh-keygen and ssh-copy-id

```bash
# Generate key pair (default: ED25519)
ssh-keygen -t ed25519 -C "your_email@example.com"

# Copy public key to server (for passwordless login)
ssh-copy-id user@hostname
```

---

## Network Manager (CLI)

**NetworkManager** is the default network stack on Ubuntu desktop and many servers. Use **nmcli** to manage connections from the shell.

### General

```bash
# General status
nmcli general status

# Show all connections
nmcli connection show

# Show active connection
nmcli connection show --active

# Show devices (interfaces)
nmcli device status
nmcli device show
```

### WiFi (if supported)

```bash
# List WiFi networks
nmcli device wifi list

# Connect to WiFi (by SSID)
nmcli device wifi connect "MyNetwork" password "mypassword"

# Connect using existing saved connection
nmcli connection up "MyNetwork"

# Disconnect
nmcli device disconnect wlan0
```

### Wired and static IP

```bash
# Bring connection up/down by name
nmcli connection up "Wired connection 1"
nmcli connection down "Wired connection 1"

# Add a new connection (example: static IP)
nmcli connection add type ethernet con-name "MyStatic" ifname eth0 ipv4.addresses 192.168.1.10/24 ipv4.gateway 192.168.1.1 ipv4.dns "8.8.8.8" ipv4.method manual

# Modify existing connection
nmcli connection modify "MyStatic" ipv4.addresses 192.168.1.20/24
nmcli connection modify "MyStatic" ipv4.dns "8.8.8.8 8.8.4.4"
```

### Reload DNS

After changing DNS in NetworkManager:

```bash
# Restart NetworkManager (use with care on remote systems)
sudo systemctl restart NetworkManager

# Or just trigger reconnect
nmcli connection down "connection-name"; nmcli connection up "connection-name"
```

---

## Quick Reference: Common Tasks

| Task | Command(s) |
|------|------------|
| Resolve hostname to IP | `dig +short example.com`, `host example.com` |
| Check DNS server used | `cat /etc/resolv.conf`, `resolvectl status` |
| Firewall status | `sudo ufw status` |
| Allow SSH | `sudo ufw allow 22` or `sudo ufw allow OpenSSH` |
| List listening ports | `ss -tuln` |
| Show IP addresses | `ip a` |
| Show default gateway | `ip route` |
| Test connectivity | `ping -c 4 8.8.8.8` |
| Test HTTP | `curl -I https://example.com` |
| Test port open | `nc -zv host 22` |
| WiFi list/connect | `nmcli device wifi list`, `nmcli device wifi connect "SSID" password "pass"` |

---

## See Also

- [01-introduction-to-linux.md](01-introduction-to-linux.md) — Linux overview
- [02-linux-bash-and-shell-scripting.md](02-linux-bash-and-shell-scripting.md) — Bash and shell scripting
