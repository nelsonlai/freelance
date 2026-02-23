# C Socket Examples

Minimal TCP, UDP, and HTTPS client examples matching the Python versions in `../python/`.

## Build

**TCP/UDP (no extra deps):**
```bash
cc -o 01-basic-tcp-server 01-basic-tcp-server.c
cc -o 02-basic-tcp-client 02-basic-tcp-client.c
cc -o 03-basic-udp-server 03-basic-udp-server.c
cc -o 04-basic-udp-client 04-basic-udp-client.c
cc -o 06-domain-to-ip 06-domain-to-ip.c
cc -o 07-ioctl-link-layer 07-ioctl-link-layer.c
```

**HTTPS client** (requires OpenSSL):
```bash
cc -o 05-https-client 05-https-client.c -lssl -lcrypto
```
On macOS with Homebrew OpenSSL, you may need:
```bash
cc -I$(brew --prefix openssl)/include -L$(brew --prefix openssl)/lib \
   -o 05-https-client 05-https-client.c -lssl -lcrypto
```

Or build all at once (TCP/UDP only; HTTPS needs the OpenSSL flags above):
```bash
for f in 0*.c; do cc -o "${f%.c}" "$f"; done
```

## Run

**TCP (run server first, then client in another terminal):**
```bash
./01-basic-tcp-server    # Terminal 1
./02-basic-tcp-client    # Terminal 2
```

**UDP (run server first, then client):**
```bash
./03-basic-udp-server    # Terminal 1
./04-basic-udp-client    # Terminal 2
```

**HTTPS client** (no server needed; talks to real HTTPS sites):
```bash
./05-https-client www.example.com
./05-https-client www.example.com /
```

**Domain name to IP** (DNS lookup):
```bash
./06-domain-to-ip www.example.com
./06-domain-to-ip localhost
```

**ioctl link-layer** (query network interfaces; Linux-oriented):
```bash
./07-ioctl-link-layer              # list all interfaces
./07-ioctl-link-layer eth0         # single interface
```

TCP/UDP examples use `127.0.0.1:8080` by default. Requires a POSIX environment (macOS, Linux, etc.). See `10-security/02-https-how-it-works.md` for how HTTPS communication works.
