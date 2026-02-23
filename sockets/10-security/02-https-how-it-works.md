# How HTTPS Talks: Client and Server Communication

HTTPS is **HTTP over TLS** (Transport Layer Security). The application data (HTTP) is unchanged; the difference is that it is sent over an **encrypted, authenticated** channel. This module explains how that channel is set up and how HTTP runs on top of it.

## Overview: HTTP vs HTTPS

| Aspect | HTTP | HTTPS |
|--------|------|-------|
| **Port** | 80 | 443 |
| **Data** | Plain text | Encrypted |
| **Server identity** | Not verified | Verified via certificate |
| **Layer** | Application (HTTP) over TCP | Application (HTTP) over TLS over TCP |

Conceptually:

```
HTTP:   [Client] ---- TCP ---- [Server]   (bytes visible to anyone on the path)
HTTPS:  [Client] ---- TCP ---- TLS (encrypt/decrypt) ---- [Server]   (bytes are ciphertext)
```

So "how HTTPS talks" is really two parts:

1. **How TLS sets up the secure channel** (handshake, then encrypted record layer).
2. **How HTTP runs on top of that channel** (same as HTTP over TCP, but the TCP stream is replaced by the TLS "application data" stream).

---

## The Layered Picture

```
+------------------+
|  HTTP (request/   |   Same as normal HTTP: GET /path, headers, body...
|  response)        |
+------------------+
|  TLS (record +   |   Encryption, integrity, optional client auth
|  handshake)      |
+------------------+
|  TCP             |   Reliable stream: connect, stream of bytes, close
+------------------+
|  IP / link       |
+------------------+
```

- **TCP** gives a reliable byte stream between client and server.
- **TLS** runs on that stream: first a **handshake** (authenticate server, agree keys), then **application data** (encrypted HTTP).
- **HTTP** is the same protocol as on port 80; it just runs over the TLS application-data stream instead of the raw TCP stream.

So when we say "how HTTPS talks," we mean: first TCP and TLS talk (handshake + encrypted records), then HTTP talks exactly as usual over that protected pipe.

---

## Step 1: TCP Connection

The client opens a normal TCP connection to the server:

- **Server address**: hostname (e.g. `www.example.com`) or IP.
- **Port**: **443** for HTTPS (by convention).

Same as any TCP client: `socket()`, `connect()` to `host:443`. Until the next step, this is just a plain TCP connection.

---

## Step 2: TLS Handshake (Over That TCP Connection)

Once TCP is connected, the **TLS handshake** runs on top of it. This is how the two sides agree on keys and (optionally) prove identity.

### 2.1 What the Handshake Does

- **Negotiate parameters**: TLS version (e.g. 1.2 or 1.3), cipher suite (encryption and integrity).
- **Server authentication**: Server sends a **certificate**; the client checks it (signature, chain, hostname).
- **Key agreement**: Client and server derive shared **session keys** (no one else can derive them).
- **Optional client authentication**: Less common for HTTPS; server can ask for a client certificate.

### 2.2 Simplified Handshake Flow (TLS 1.2 style)

```
Client                              Server
  |                                    |
  |-------- TCP connect (443) -------->|
  |                                    |
  |-------- ClientHello --------------->|   (supported versions, ciphers, random)
  |                                    |
  |<------- ServerHello -----------------|   (chosen version, cipher, random)
  |<------- Certificate ------------------|   (server's cert + chain)
  |<------- ServerKeyExchange (optional) -|   (e.g. DH params)
  |<------- ServerHelloDone -------------|   (end of server hello)
  |                                    |
  |-------- ClientKeyExchange ---------->|   (client's key share / pre-master)
  |-------- ChangeCipherSpec ------------>|   (switch to new keys)
  |-------- Finished ------------------->|   (encrypted, integrity check)
  |                                    |
  |<------- ChangeCipherSpec -------------|   (switch to new keys)
  |<------- Finished ----------------------|   (encrypted, integrity check)
  |                                    |
  |===== Encrypted application data =====|   (HTTP here)
```

- **ClientHello / ServerHello**: Agree TLS version and cipher suite; exchange random values.
- **Certificate**: Server sends its certificate; client verifies it (trusted CA, hostname, validity).
- **Key exchange**: Both sides compute the same session keys from the exchanged data.
- **Finished**: First messages encrypted with the new keys; proves handshake was not tampered with.

After the handshake, all application data (e.g. HTTP) is sent as **TLS Application Data** records: encrypted and integrity-protected.

### 2.3 Hostname Verification (Important for HTTPS)

The client must check that the server’s certificate is **for the hostname it is connecting to** (e.g. `www.example.com`). Otherwise a different server could present its own valid certificate and the client would still accept it. In code this is done by:

- Setting the expected hostname (e.g. for SNI and for verification).
- Using the TLS library’s verification API so it checks the certificate’s subject/common name or SAN against that hostname.

---

## Step 3: HTTP Over the TLS Channel

After the handshake, the **application** sees a reliable byte stream. It does not see TLS headers or ciphertext; the TLS library decrypts and returns plaintext.

So from the application’s point of view:

1. **Send**: HTTP request (e.g. `GET / HTTP/1.1`, headers, body) as bytes.
2. **Receive**: HTTP response (status line, headers, body) as bytes.

The only difference from plain HTTP over TCP is that **send** and **receive** go through the TLS library (e.g. `SSL_write` / `SSL_read`) instead of `send()` / `recv()` on the raw socket. The HTTP format is unchanged.

### Example: One HTTPS Request

```
Client sends (over TLS, so encrypted on the wire):
  GET / HTTP/1.1
  Host: www.example.com
  Connection: close

  (optional body)

Server sends (over TLS, so encrypted on the wire):
  HTTP/1.1 200 OK
  Content-Type: text/html
  ...

  <html>...</html>
```

So "how HTTPS talks" at the application layer is: **exactly like HTTP**, but the bytes are carried inside TLS application-data records instead of raw TCP segments.

---

## Summary: How HTTPS "Talks"

1. **TCP**: Client connects to `host:443` (same as any TCP client).
2. **TLS handshake**: Over that TCP connection, client and server do the handshake (authenticate server, agree keys). After this, the connection is "secure."
3. **HTTP**: Client sends HTTP request using the TLS "send" API; server sends HTTP response using the TLS "send" API. Format and semantics are standard HTTP; only the transport is TLS instead of raw TCP.

So **HTTPS = TCP + TLS + HTTP**: same HTTP protocol, on top of a TLS-protected TCP connection.

---

## What the C Example Does

The C example in `examples/c/05-https-client.c` demonstrates this:

1. Resolve the hostname to an IP address (`getaddrinfo`).
2. Open a TCP connection to port 443 (`socket`, `connect`).
3. Create an OpenSSL TLS client context and attach it to that socket (`SSL_CTX`, `SSL`, `SSL_set_fd`).
4. Set the hostname for SNI and certificate verification (`SSL_set_tlsext_host_name`, `SSL_set1_host`).
5. Run the TLS handshake (`SSL_connect`).
6. Send an HTTP GET request over TLS (`SSL_write`).
7. Read the HTTP response over TLS (`SSL_read`) and print it.
8. Shut down TLS and close the connection.

That is the full path of "how HTTPS talks" in one small program: TCP → TLS handshake → HTTP over TLS.
