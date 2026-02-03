# IP Addresses and Ports

## IP Addresses

An **IP (Internet Protocol) address** uniquely identifies a device on a network. It's like a postal address for your computer.

### IPv4 Addresses

- **Format**: Four numbers separated by dots (dotted decimal notation)
- **Range**: 0.0.0.0 to 255.255.255.255
- **Example**: `192.168.1.100`
- **Size**: 32 bits (4 bytes)
- **Total addresses**: ~4.3 billion

#### IPv4 Address Classes

- **Class A**: 1.0.0.0 to 126.255.255.255 (large networks)
- **Class B**: 128.0.0.0 to 191.255.255.255 (medium networks)
- **Class C**: 192.0.0.0 to 223.255.255.255 (small networks)
- **Private ranges** (used in LANs):
  - 10.0.0.0/8
  - 172.16.0.0/12
  - 192.168.0.0/16

### IPv6 Addresses

- **Format**: Eight groups of four hexadecimal digits
- **Example**: `2001:0db8:85a3:0000:0000:8a2e:0370:7334`
- **Size**: 128 bits (16 bytes)
- **Total addresses**: ~340 undecillion (virtually unlimited)
- **Simplified**: Leading zeros can be omitted, consecutive zeros can be `::`

Example: `2001:db8:85a3::8a2e:370:7334`

### Special IP Addresses

- **127.0.0.1 (localhost)**: Your own computer (loopback)
- **0.0.0.0**: All interfaces, any address
- **255.255.255.255**: Broadcast address (all devices on network)

### IP Address Types

1. **Public IP**: Unique on the Internet, routable
2. **Private IP**: Used within LAN, not routable on Internet
3. **Static IP**: Permanently assigned
4. **Dynamic IP**: Assigned by DHCP (changes periodically)

## Ports

A **port** is a 16-bit number (0-65535) that identifies a specific process or application on a host. Think of it as an apartment number in a building (the building is the IP address).

### Port Ranges

- **Well-known ports (0-1023)**: Reserved for system services
  - Port 80: HTTP
  - Port 443: HTTPS
  - Port 22: SSH
  - Port 25: SMTP
  - Port 53: DNS
  - Port 21: FTP

- **Registered ports (1024-49151)**: For registered applications
  - Port 3306: MySQL
  - Port 5432: PostgreSQL
  - Port 8080: HTTP (alternative)

- **Dynamic/Private ports (49152-65535)**: For temporary use, client-side

### Common Ports for Socket Programming

| Port | Protocol | Purpose |
|------|----------|---------|
| 80 | HTTP | Web browsing |
| 443 | HTTPS | Secure web browsing |
| 22 | SSH | Secure shell |
| 25 | SMTP | Email sending |
| 53 | DNS | Domain name resolution |
| 3306 | MySQL | Database |
| 5432 | PostgreSQL | Database |
| 27017 | MongoDB | Database |

### Port Binding

- **Server**: Binds to a specific port (listens on that port)
- **Client**: Uses an ephemeral (temporary) port assigned by OS
- **Multiple sockets**: Can't bind to the same port on the same interface simultaneously

## Socket Address

A **socket address** combines IP address and port number:
- Format: `IP_ADDRESS:PORT`
- Example: `192.168.1.100:8080`
- Example: `127.0.0.1:3000`

This uniquely identifies an endpoint for network communication.

## Network Address Translation (NAT)

NAT allows multiple devices with private IPs to share a public IP:
- Router has public IP (visible to Internet)
- Devices on LAN have private IPs
- Router translates between private and public IPs
- Important for socket programming when connecting through routers

## Domain Names vs IP Addresses

- **Domain name**: Human-readable (e.g., `www.google.com`)
- **IP address**: Machine-readable (e.g., `142.250.191.14`)
- **DNS (Domain Name System)**: Translates domain names to IP addresses
- Socket programming often uses IPs directly, but can use domain names (DNS resolution happens automatically)

## In Socket Programming

### When Creating a Server

```python
# Bind to all interfaces on port 8080
server.bind(('0.0.0.0', 8080))

# Bind to localhost only
server.bind(('127.0.0.1', 8080))

# Bind to specific interface
server.bind(('192.168.1.100', 8080))
```

### When Creating a Client

```python
# Connect to server at specific IP and port
client.connect(('192.168.1.100', 8080))

# Connect using domain name
client.connect(('example.com', 80))
```

## Checking Your Network Information

### Linux/macOS
```bash
# Show IP addresses
ifconfig
# or
ip addr show

# Show listening ports
netstat -tuln
# or
ss -tuln
```

### Windows
```bash
# Show IP addresses
ipconfig

# Show listening ports
netstat -ano
```

## Common Issues

1. **"Address already in use"**
   - Port is already bound by another process
   - Solution: Choose different port or stop the other process

2. **"Connection refused"**
   - Nothing listening on that port
   - Solution: Start the server first

3. **Firewall blocking**
   - Firewall prevents connections
   - Solution: Configure firewall rules

4. **Wrong IP address**
   - Using private IP to connect from outside LAN
   - Solution: Use public IP or use port forwarding

---

**Key Takeaway**: IP addresses identify devices, ports identify applications. Together they form a socket address that uniquely identifies a network endpoint.

