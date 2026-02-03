"""
Modern Cryptographic Protocols - TLS Handshake Simulation

This module demonstrates the TLS (Transport Layer Security) handshake protocol,
which is used to establish secure connections between clients and servers.
TLS provides confidentiality, integrity, and authentication for network
communications.

Key Concepts:
- TLS Handshake: Process of establishing secure connection
- Key Exchange: Secure distribution of symmetric keys
- Digital Certificates: Public key authentication
- Hybrid Cryptography: Combining symmetric and asymmetric encryption
- Forward Secrecy: Protection against future key compromise

Security Properties:
- Confidentiality: Data is encrypted in transit
- Integrity: Data cannot be modified without detection
- Authentication: Parties can verify each other's identity
- Forward Secrecy: Past communications remain secure

Author: Cryptography Lecture
Date: 2024
"""

import os
import time
import hashlib
from typing import Tuple, Optional
from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP, AES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad, unpad


class TLSCertificate:
    """
    A simplified TLS certificate for demonstration purposes.
    
    In real TLS, certificates are complex structures containing
    public keys, identity information, and digital signatures.
    """
    
    def __init__(self, subject: str, public_key: bytes, issuer: str = "CA"):
        """
        Initialize a TLS certificate.
        
        Args:
            subject (str): The subject (entity) the certificate identifies
            public_key (bytes): The public key in the certificate
            issuer (str): The certificate authority that issued the certificate
        """
        self.subject = subject
        self.public_key = public_key
        self.issuer = issuer
        self.serial_number = os.urandom(4).hex()
        self.valid_from = int(time.time())
        self.valid_to = self.valid_from + (365 * 24 * 60 * 60)  # 1 year
    
    def verify(self, ca_public_key: bytes) -> bool:
        """
        Verify the certificate (simplified).
        
        In real TLS, this would involve verifying the CA's digital signature.
        
        Args:
            ca_public_key (bytes): The CA's public key
        
        Returns:
            bool: True if certificate is valid
        """
        # Simplified verification - in reality, this would verify the CA's signature
        return self.issuer == "CA" and self.valid_to > int(time.time())
    
    def get_info(self) -> dict:
        """
        Get certificate information.
        
        Returns:
            dict: Certificate information
        """
        return {
            'subject': self.subject,
            'issuer': self.issuer,
            'serial_number': self.serial_number,
            'valid_from': self.valid_from,
            'valid_to': self.valid_to,
            'public_key': self.public_key.hex()
        }


class TLSServer:
    """
    A simplified TLS server for demonstration purposes.
    """
    
    def __init__(self, hostname: str):
        """
        Initialize the TLS server.
        
        Args:
            hostname (str): The server's hostname
        """
        self.hostname = hostname
        self.private_key, self.public_key = self._generate_key_pair()
        self.certificate = TLSCertificate(hostname, self.public_key)
        self.session_key = None
        self.cipher_suite = None
    
    def _generate_key_pair(self) -> Tuple[bytes, bytes]:
        """
        Generate RSA key pair for the server.
        
        Returns:
            Tuple[bytes, bytes]: (private_key, public_key)
        """
        key = RSA.generate(2048)
        private_key = key.export_key()
        public_key = key.publickey().export_key()
        return private_key, public_key
    
    def send_certificate(self) -> TLSCertificate:
        """
        Send the server certificate to the client.
        
        Returns:
            TLSCertificate: The server's certificate
        """
        return self.certificate
    
    def receive_pre_master_secret(self, encrypted_pre_master: bytes) -> bytes:
        """
        Receive and decrypt the pre-master secret from the client.
        
        Args:
            encrypted_pre_master (bytes): The encrypted pre-master secret
        
        Returns:
            bytes: The decrypted pre-master secret
        """
        # Decrypt the pre-master secret
        private_key = RSA.import_key(self.private_key)
        cipher = PKCS1_OAEP.new(private_key)
        pre_master_secret = cipher.decrypt(encrypted_pre_master)
        
        return pre_master_secret
    
    def derive_session_key(self, pre_master_secret: bytes, 
                          client_random: bytes, server_random: bytes) -> bytes:
        """
        Derive the session key from the pre-master secret and random values.
        
        Args:
            pre_master_secret (bytes): The pre-master secret
            client_random (bytes): Client's random value
            server_random (bytes): Server's random value
        
        Returns:
            bytes: The derived session key
        """
        # Simplified key derivation - in reality, this uses PRF
        key_material = pre_master_secret + client_random + server_random
        session_key = hashlib.sha256(key_material).digest()[:32]  # 256-bit key
        
        self.session_key = session_key
        return session_key
    
    def send_finished(self, handshake_messages: bytes) -> bytes:
        """
        Send the Finished message to complete the handshake.
        
        Args:
            handshake_messages (bytes): All handshake messages so far
        
        Returns:
            bytes: The Finished message
        """
        # Create Finished message (simplified)
        finished_data = b"Finished" + handshake_messages
        finished_hash = hashlib.sha256(finished_data).digest()
        
        return finished_hash
    
    def encrypt_data(self, data: bytes) -> Tuple[bytes, bytes, bytes]:
        """
        Encrypt data using the session key.
        
        Args:
            data (bytes): The data to encrypt
        
        Returns:
            Tuple[bytes, bytes, bytes]: (iv, ciphertext, tag)
        """
        if self.session_key is None:
            raise ValueError("Session key not established")
        
        # Encrypt using AES-GCM
        iv = get_random_bytes(16)
        cipher = AES.new(self.session_key, AES.MODE_GCM, nonce=iv)
        ciphertext, tag = cipher.encrypt_and_digest(data)
        
        return iv, ciphertext, tag
    
    def decrypt_data(self, iv: bytes, ciphertext: bytes, tag: bytes) -> bytes:
        """
        Decrypt data using the session key.
        
        Args:
            iv (bytes): The initialization vector
            ciphertext (bytes): The encrypted data
            tag (bytes): The authentication tag
        
        Returns:
            bytes: The decrypted data
        """
        if self.session_key is None:
            raise ValueError("Session key not established")
        
        # Decrypt using AES-GCM
        cipher = AES.new(self.session_key, AES.MODE_GCM, nonce=iv)
        plaintext = cipher.decrypt_and_verify(ciphertext, tag)
        
        return plaintext


class TLSClient:
    """
    A simplified TLS client for demonstration purposes.
    """
    
    def __init__(self, hostname: str):
        """
        Initialize the TLS client.
        
        Args:
            hostname (str): The server's hostname to connect to
        """
        self.hostname = hostname
        self.session_key = None
        self.cipher_suite = None
        self.server_certificate = None
    
    def send_client_hello(self) -> bytes:
        """
        Send ClientHello message to the server.
        
        Returns:
            bytes: The ClientHello message
        """
        # Create ClientHello message (simplified)
        client_random = get_random_bytes(32)
        client_hello = b"ClientHello" + client_random
        
        return client_hello
    
    def receive_server_hello(self, server_hello: bytes) -> bytes:
        """
        Receive ServerHello message from the server.
        
        Args:
            server_hello (bytes): The ServerHello message
        
        Returns:
            bytes: The server's random value
        """
        # Extract server random from ServerHello (simplified)
        server_random = server_hello[-32:]  # Last 32 bytes
        
        return server_random
    
    def receive_certificate(self, certificate: TLSCertificate) -> bool:
        """
        Receive and verify the server certificate.
        
        Args:
            certificate (TLSCertificate): The server's certificate
        
        Returns:
            bool: True if certificate is valid
        """
        self.server_certificate = certificate
        
        # Verify certificate (simplified)
        if certificate.subject != self.hostname:
            return False
        
        if not certificate.verify(b"CA_PUBLIC_KEY"):  # Simplified CA verification
            return False
        
        return True
    
    def send_pre_master_secret(self, server_public_key: bytes) -> bytes:
        """
        Generate and send the pre-master secret to the server.
        
        Args:
            server_public_key (bytes): The server's public key
        
        Returns:
            bytes: The encrypted pre-master secret
        """
        # Generate pre-master secret
        pre_master_secret = get_random_bytes(48)  # 384 bits
        
        # Encrypt with server's public key
        public_key = RSA.import_key(server_public_key)
        cipher = PKCS1_OAEP.new(public_key)
        encrypted_pre_master = cipher.encrypt(pre_master_secret)
        
        return encrypted_pre_master
    
    def derive_session_key(self, pre_master_secret: bytes, 
                          client_random: bytes, server_random: bytes) -> bytes:
        """
        Derive the session key from the pre-master secret and random values.
        
        Args:
            pre_master_secret (bytes): The pre-master secret
            client_random (bytes): Client's random value
            server_random (bytes): Server's random value
        
        Returns:
            bytes: The derived session key
        """
        # Simplified key derivation - in reality, this uses PRF
        key_material = pre_master_secret + client_random + server_random
        session_key = hashlib.sha256(key_material).digest()[:32]  # 256-bit key
        
        self.session_key = session_key
        return session_key
    
    def send_finished(self, handshake_messages: bytes) -> bytes:
        """
        Send the Finished message to complete the handshake.
        
        Args:
            handshake_messages (bytes): All handshake messages so far
        
        Returns:
            bytes: The Finished message
        """
        # Create Finished message (simplified)
        finished_data = b"Finished" + handshake_messages
        finished_hash = hashlib.sha256(finished_data).digest()
        
        return finished_hash
    
    def encrypt_data(self, data: bytes) -> Tuple[bytes, bytes, bytes]:
        """
        Encrypt data using the session key.
        
        Args:
            data (bytes): The data to encrypt
        
        Returns:
            Tuple[bytes, bytes, bytes]: (iv, ciphertext, tag)
        """
        if self.session_key is None:
            raise ValueError("Session key not established")
        
        # Encrypt using AES-GCM
        iv = get_random_bytes(16)
        cipher = AES.new(self.session_key, AES.MODE_GCM, nonce=iv)
        ciphertext, tag = cipher.encrypt_and_digest(data)
        
        return iv, ciphertext, tag
    
    def decrypt_data(self, iv: bytes, ciphertext: bytes, tag: bytes) -> bytes:
        """
        Decrypt data using the session key.
        
        Args:
            iv (bytes): The initialization vector
            ciphertext (bytes): The encrypted data
            tag (bytes): The authentication tag
        
        Returns:
            bytes: The decrypted data
        """
        if self.session_key is None:
            raise ValueError("Session key not established")
        
        # Decrypt using AES-GCM
        cipher = AES.new(self.session_key, AES.MODE_GCM, nonce=iv)
        plaintext = cipher.decrypt_and_verify(ciphertext, tag)
        
        return plaintext


def demonstrate_tls_handshake():
    """
    Demonstrate a complete TLS handshake process.
    """
    print("=" * 60)
    print("TLS HANDSHAKE DEMONSTRATION")
    print("=" * 60)
    
    # Create server and client
    server = TLSServer("example.com")
    client = TLSClient("example.com")
    
    print(f"Server: {server.hostname}")
    print(f"Client connecting to: {client.hostname}")
    
    print("\n" + "-" * 40)
    
    # Step 1: ClientHello
    print("Step 1: ClientHello")
    client_hello = client.send_client_hello()
    print(f"ClientHello: {client_hello.hex()}")
    
    print("\n" + "-" * 40)
    
    # Step 2: ServerHello
    print("Step 2: ServerHello")
    server_random = get_random_bytes(32)
    server_hello = b"ServerHello" + server_random
    print(f"ServerHello: {server_hello.hex()}")
    
    # Client receives ServerHello
    client_server_random = client.receive_server_hello(server_hello)
    print(f"Client received server random: {client_server_random.hex()}")
    
    print("\n" + "-" * 40)
    
    # Step 3: Certificate
    print("Step 3: Certificate")
    server_certificate = server.send_certificate()
    print(f"Server certificate: {server_certificate.get_info()}")
    
    # Client verifies certificate
    certificate_valid = client.receive_certificate(server_certificate)
    print(f"Certificate verification: {certificate_valid}")
    
    if not certificate_valid:
        print("ERROR: Certificate verification failed!")
        return
    
    print("\n" + "-" * 40)
    
    # Step 4: Pre-Master Secret
    print("Step 4: Pre-Master Secret")
    encrypted_pre_master = client.send_pre_master_secret(server.public_key)
    print(f"Encrypted pre-master secret: {encrypted_pre_master.hex()}")
    
    # Server receives and decrypts pre-master secret
    pre_master_secret = server.receive_pre_master_secret(encrypted_pre_master)
    print(f"Server decrypted pre-master secret: {pre_master_secret.hex()}")
    
    print("\n" + "-" * 40)
    
    # Step 5: Session Key Derivation
    print("Step 5: Session Key Derivation")
    client_random = client_hello[-32:]  # Extract from ClientHello
    
    # Both parties derive session key
    client_session_key = client.derive_session_key(
        pre_master_secret, client_random, client_server_random
    )
    server_session_key = server.derive_session_key(
        pre_master_secret, client_random, client_server_random
    )
    
    print(f"Client session key: {client_session_key.hex()}")
    print(f"Server session key: {server_session_key.hex()}")
    print(f"Session keys match: {client_session_key == server_session_key}")
    
    print("\n" + "-" * 40)
    
    # Step 6: Finished Messages
    print("Step 6: Finished Messages")
    handshake_messages = client_hello + server_hello + encrypted_pre_master
    
    client_finished = client.send_finished(handshake_messages)
    server_finished = server.send_finished(handshake_messages)
    
    print(f"Client Finished: {client_finished.hex()}")
    print(f"Server Finished: {server_finished.hex()}")
    print(f"Finished messages match: {client_finished == server_finished}")
    
    print("\n" + "-" * 40)
    
    # Step 7: Secure Communication
    print("Step 7: Secure Communication")
    
    # Client sends encrypted message
    message = b"Hello, this is a secure message!"
    print(f"Original message: {message.decode()}")
    
    iv, ciphertext, tag = client.encrypt_data(message)
    print(f"Encrypted message: {ciphertext.hex()}")
    
    # Server decrypts message
    decrypted_message = server.decrypt_data(iv, ciphertext, tag)
    print(f"Decrypted message: {decrypted_message.decode()}")
    print(f"Decryption successful: {message == decrypted_message}")
    
    print("\n" + "-" * 40)
    
    # Server sends encrypted response
    response = b"Hello back! This is a secure response."
    print(f"Original response: {response.decode()}")
    
    iv, ciphertext, tag = server.encrypt_data(response)
    print(f"Encrypted response: {ciphertext.hex()}")
    
    # Client decrypts response
    decrypted_response = client.decrypt_data(iv, ciphertext, tag)
    print(f"Decrypted response: {decrypted_response.decode()}")
    print(f"Decryption successful: {response == decrypted_response}")


def demonstrate_tls_security():
    """
    Demonstrate TLS security properties.
    """
    print("\n" + "=" * 60)
    print("TLS SECURITY PROPERTIES")
    print("=" * 60)
    
    print("TLS provides the following security properties:")
    print("-" * 40)
    
    print("1. Confidentiality:")
    print("   • All data is encrypted using symmetric encryption")
    print("   • Session keys are derived from pre-master secret")
    print("   • Pre-master secret is encrypted with server's public key")
    print("   • Only parties with session key can decrypt data")
    
    print("\n2. Integrity:")
    print("   • All messages are authenticated using MAC")
    print("   • Finished messages verify handshake integrity")
    print("   • Any modification is detected")
    print("   • Replay attacks are prevented")
    
    print("\n3. Authentication:")
    print("   • Server identity is verified through certificates")
    print("   • Certificate chain is validated")
    print("   • Public key is bound to server identity")
    print("   • Certificate revocation is checked")
    
    print("\n4. Forward Secrecy:")
    print("   • Session keys are derived from random values")
    print("   • Pre-master secret is ephemeral")
    print("   • Past communications remain secure")
    print("   • Future key compromise doesn't affect past sessions")
    
    print("\n" + "-" * 40)
    
    print("TLS Security Features:")
    print("• Perfect Forward Secrecy (PFS)")
    print("• Certificate Pinning")
    print("• HSTS (HTTP Strict Transport Security)")
    print("• Certificate Transparency")
    print("• OCSP Stapling")
    print("• SNI (Server Name Indication)")
    
    print("\n" + "-" * 40)
    
    print("TLS Versions:")
    print("• TLS 1.0: Deprecated")
    print("• TLS 1.1: Deprecated")
    print("• TLS 1.2: Widely used")
    print("• TLS 1.3: Latest version, improved security")


def demonstrate_tls_vulnerabilities():
    """
    Demonstrate common TLS vulnerabilities and attacks.
    """
    print("\n" + "=" * 60)
    print("TLS VULNERABILITIES AND ATTACKS")
    print("=" * 60)
    
    print("Common TLS Vulnerabilities:")
    print("-" * 40)
    
    print("1. Weak Cipher Suites:")
    print("   • RC4: Vulnerable to statistical attacks")
    print("   • DES: Weak encryption")
    print("   • MD5: Weak hash function")
    print("   • SHA-1: Weak hash function")
    
    print("\n2. Protocol Vulnerabilities:")
    print("   • BEAST: Browser Exploit Against SSL/TLS")
    print("   • CRIME: Compression Ratio Info-leak Made Easy")
    print("   • BREACH: Browser Reconnaissance and Exfiltration")
    print("   • POODLE: Padding Oracle On Downgraded Legacy Encryption")
    
    print("\n3. Implementation Vulnerabilities:")
    print("   • Heartbleed: OpenSSL buffer overflow")
    print("   • Shellshock: Bash vulnerability")
    print("   • FREAK: Factoring RSA Export Keys")
    print("   • Logjam: Diffie-Hellman parameter reuse")
    
    print("\n4. Certificate Vulnerabilities:")
    print("   • Weak RSA keys")
    print("   • Certificate authority compromise")
    print("   • Certificate misissuance")
    print("   • Certificate transparency bypass")
    
    print("\n" + "-" * 40)
    
    print("Attack Vectors:")
    print("• Man-in-the-Middle (MITM)")
    print("• Certificate Authority (CA) compromise")
    print("• Weak random number generation")
    print("• Side-channel attacks")
    print("• Timing attacks")
    print("• Power analysis attacks")
    
    print("\n" + "-" * 40)
    
    print("Mitigation Strategies:")
    print("• Use strong cipher suites")
    print("• Implement certificate pinning")
    print("• Use HSTS")
    print("• Regular security updates")
    print("• Certificate transparency monitoring")
    print("• Strong random number generation")


def demonstrate_tls_best_practices():
    """
    Demonstrate TLS best practices.
    """
    print("\n" + "=" * 60)
    print("TLS BEST PRACTICES")
    print("=" * 60)
    
    print("Configuration Best Practices:")
    print("-" * 40)
    
    print("1. Cipher Suite Selection:")
    print("   • Use AES-GCM for encryption")
    print("   • Use SHA-256 or SHA-384 for hashing")
    print("   • Use ECDHE for key exchange")
    print("   • Avoid weak algorithms (RC4, DES, MD5)")
    
    print("\n2. Certificate Management:")
    print("   • Use strong RSA keys (2048+ bits)")
    print("   • Use ECDSA certificates")
    print("   • Implement certificate pinning")
    print("   • Monitor certificate expiration")
    
    print("\n3. Protocol Configuration:")
    print("   • Use TLS 1.2 or TLS 1.3")
    print("   • Disable SSL 2.0 and 3.0")
    print("   • Disable TLS 1.0 and 1.1")
    print("   • Implement HSTS")
    
    print("\n4. Security Headers:")
    print("   • HSTS: HTTP Strict Transport Security")
    print("   • CSP: Content Security Policy")
    print("   • X-Frame-Options")
    print("   • X-Content-Type-Options")
    
    print("\n" + "-" * 40)
    
    print("Implementation Best Practices:")
    print("• Use established TLS libraries")
    print("• Implement proper error handling")
    print("• Use secure random number generation")
    print("• Implement certificate validation")
    print("• Monitor for security updates")
    print("• Regular security audits")
    
    print("\n" + "-" * 40)
    
    print("Monitoring and Maintenance:")
    print("• Certificate expiration monitoring")
    print("• Security vulnerability scanning")
    print("• Performance monitoring")
    print("• Log analysis")
    print("• Regular security updates")
    print("• Incident response planning")


def practical_tls_examples():
    """
    Show practical examples of TLS usage.
    """
    print("\n" + "=" * 60)
    print("PRACTICAL TLS EXAMPLES")
    print("=" * 60)
    
    print("Real-World TLS Applications:")
    print("-" * 40)
    
    print("1. Web Browsing (HTTPS):")
    print("   • Secure web pages")
    print("   • Online banking")
    print("   • E-commerce")
    print("   • Social media")
    
    print("\n2. Email (SMTPS, IMAPS, POP3S):")
    print("   • Secure email transmission")
    print("   • Email server communication")
    print("   • Email client connections")
    
    print("\n3. VPN (OpenVPN, IPSec):")
    print("   • Secure remote access")
    print("   • Site-to-site connections")
    print("   • Mobile device security")
    
    print("\n4. API Communication:")
    print("   • REST API security")
    print("   • Microservice communication")
    print("   • Cloud service integration")
    
    print("\n" + "-" * 40)
    
    # Demonstrate HTTPS simulation
    print("HTTPS Simulation:")
    
    # Create server and client
    server = TLSServer("api.example.com")
    client = TLSClient("api.example.com")
    
    # Simulate HTTPS request
    print("\n1. Establishing TLS connection...")
    
    # ClientHello
    client_hello = client.send_client_hello()
    
    # ServerHello
    server_random = get_random_bytes(32)
    server_hello = b"ServerHello" + server_random
    
    # Certificate
    server_certificate = server.send_certificate()
    certificate_valid = client.receive_certificate(server_certificate)
    
    if not certificate_valid:
        print("ERROR: Certificate verification failed!")
        return
    
    # Pre-Master Secret
    encrypted_pre_master = client.send_pre_master_secret(server.public_key)
    pre_master_secret = server.receive_pre_master_secret(encrypted_pre_master)
    
    # Session Key Derivation
    client_random = client_hello[-32:]
    client_session_key = client.derive_session_key(
        pre_master_secret, client_random, server_random
    )
    server_session_key = server.derive_session_key(
        pre_master_secret, client_random, server_random
    )
    
    print("TLS connection established!")
    
    # Simulate HTTPS request/response
    print("\n2. Sending HTTPS request...")
    
    request = b"GET /api/data HTTP/1.1\r\nHost: api.example.com\r\n\r\n"
    print(f"HTTP request: {request.decode()}")
    
    # Encrypt request
    iv, ciphertext, tag = client.encrypt_data(request)
    print(f"Encrypted request: {ciphertext.hex()}")
    
    # Server decrypts request
    decrypted_request = server.decrypt_data(iv, ciphertext, tag)
    print(f"Decrypted request: {decrypted_request.decode()}")
    
    # Server sends response
    print("\n3. Sending HTTPS response...")
    
    response = b"HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{\"data\": \"secret\"}"
    print(f"HTTP response: {response.decode()}")
    
    # Encrypt response
    iv, ciphertext, tag = server.encrypt_data(response)
    print(f"Encrypted response: {ciphertext.hex()}")
    
    # Client decrypts response
    decrypted_response = client.decrypt_data(iv, ciphertext, tag)
    print(f"Decrypted response: {decrypted_response.decode()}")
    
    print("\nHTTPS communication completed successfully!")


if __name__ == "__main__":
    # Run all demonstrations
    demonstrate_tls_handshake()
    demonstrate_tls_security()
    demonstrate_tls_vulnerabilities()
    demonstrate_tls_best_practices()
    practical_tls_examples()
    
    print("\n" + "=" * 60)
    print("EDUCATIONAL SUMMARY")
    print("=" * 60)
    print("TLS provides secure communication over networks:")
    print("• Establishes secure connections between clients and servers")
    print("• Provides confidentiality, integrity, and authentication")
    print("• Uses hybrid cryptography (asymmetric + symmetric)")
    print("• Supports forward secrecy")
    print("\nKey components:")
    print("• Handshake protocol")
    print("• Certificate validation")
    print("• Key exchange")
    print("• Session key derivation")
    print("• Secure data transmission")
    print("\nTLS is essential for secure internet communication!")
