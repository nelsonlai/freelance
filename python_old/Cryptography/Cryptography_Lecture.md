# Cryptography – Comprehensive Lecture

## 🎯 Learning Objectives
- Understand the fundamental goals of cryptography: confidentiality, integrity, authentication, and non-repudiation
- Learn the historical evolution of cryptography from classical to modern systems
- Master the distinction between symmetric and asymmetric cryptography
- Understand cryptographic hashing, digital signatures, and message authentication codes
- Implement practical cryptographic solutions using Python
- Recognize common cryptographic attacks and security best practices
- Apply proper cryptographic protocols in real-world scenarios

---

## ⏱ Timing Breakdown
| Segment | Time |
|---|---|
| 0. Introduction & Historical Context | 15 min |
| 1. Cryptographic Goals & Adversarial Models | 10 min |
| 2. Classical Cryptography & Historical Ciphers | 20 min |
| 3. Cryptographic Hashing & Message Digests | 20 min |
| 4. Symmetric Cryptography | 25 min |
| 5. Asymmetric Cryptography & Digital Signatures | 25 min |
| 6. Cryptanalysis & Attack Methods | 15 min |
| 7. Modern Protocols & Hybrid Systems | 15 min |
| 8. Security Best Practices | 15 min |
| 9. Practical Exercises & Wrap-Up | 10 min |

---

## 0. Introduction & Historical Context (15 min)

### What is Cryptography?
**Cryptography** is the art and science of making ciphers - creating secure communication systems that protect information from unauthorized access.

**Cryptanalysis** is the art and science of breaking ciphers - analyzing and defeating cryptographic systems.

**Cryptology** encompasses both cryptography and cryptanalysis.

### Historical Timeline
- **Ancient Times**: Caesar cipher, substitution ciphers
- **World War I & II**: Enigma machine, codebreaking efforts
- **1970s**: DES (Data Encryption Standard), public key cryptography
- **1990s**: RSA, AES development
- **2000s**: Elliptic curve cryptography, SHA-3
- **Present**: Post-quantum cryptography, quantum-resistant algorithms

### Key Historical Figures
- **Julius Caesar**: Caesar cipher
- **Alan Turing**: Enigma codebreaking, computational theory
- **Whitfield Diffie & Martin Hellman**: Public key cryptography
- **Ron Rivest, Adi Shamir, Leonard Adleman**: RSA algorithm

---

## 1. Cryptographic Goals & Adversarial Models (10 min)

### The Four Pillars of Cryptography

#### 1. **Confidentiality**
- Keep information secret from unauthorized parties
- Only intended recipients can read the message
- Example: Encrypted email, secure messaging

#### 2. **Integrity**
- Detect if information has been tampered with
- Ensure data hasn't been modified in transit
- Example: File checksums, digital signatures

#### 3. **Authentication**
- Verify the identity of communicating parties
- Confirm who sent the message
- Example: Login systems, digital certificates

#### 4. **Non-repudiation**
- Prevent sender from denying they sent a message
- Provide proof of message origin
- Example: Digital signatures, audit trails

### Adversarial Models

#### **Eve (Eavesdropper)**
- Can observe communication but cannot modify it
- Passive attacker
- Threat: Confidentiality

#### **Mallory (Malicious Actor)**
- Can intercept, modify, inject, or delete messages
- Active attacker
- Threats: All four cryptographic goals

### Kerckhoffs' Principle
> "A cryptosystem should be secure even if everything about the system, except the key, is public knowledge."

**Why this matters:**
- Algorithm secrecy is fragile (people leave, algorithms leak)
- Public algorithms undergo extensive security analysis
- Key management is easier than algorithm secrecy

---

## 2. Classical Cryptography & Historical Ciphers (20 min)

### Types of Classical Ciphers

#### **Substitution Ciphers**
Replace each character with another character.

**Caesar Cipher**
```python
def caesar_cipher(text, shift):
    result = ""
    for char in text:
        if char.isalpha():
            ascii_offset = 65 if char.isupper() else 97
            shifted = (ord(char) - ascii_offset + shift) % 26
            result += chr(shifted + ascii_offset)
        else:
            result += char
    return result

# Example
plaintext = "ATTACKATDAWN"
ciphertext = caesar_cipher(plaintext, 5)
print(f"Plaintext: {plaintext}")
print(f"Ciphertext: {ciphertext}")
```

**Monoalphabetic Substitution**
```python
import random
import string

def monoalphabetic_substitution(text, key=None):
    if key is None:
        alphabet = list(string.ascii_uppercase)
        random.shuffle(alphabet)
        key = ''.join(alphabet)
    
    result = ""
    for char in text.upper():
        if char.isalpha():
            index = ord(char) - ord('A')
            result += key[index]
        else:
            result += char
    return result

# Example
plaintext = "ATTACKATDAWN"
ciphertext = monoalphabetic_substitution(plaintext)
print(f"Plaintext: {plaintext}")
print(f"Ciphertext: {ciphertext}")
```

#### **Transposition Ciphers**
Rearrange characters without changing them.

**Rail Fence Cipher**
```python
def rail_fence_encrypt(text, rails):
    fence = [[] for _ in range(rails)]
    rail = 0
    direction = 1
    
    for char in text:
        fence[rail].append(char)
        rail += direction
        if rail == rails - 1 or rail == 0:
            direction = -direction
    
    return ''.join([''.join(rail) for rail in fence])

# Example
plaintext = "WEAREDISCOVEREDFLEEATONCE"
ciphertext = rail_fence_encrypt(plaintext, 3)
print(f"Plaintext: {plaintext}")
print(f"Ciphertext: {ciphertext}")
```

### Breaking Classical Ciphers

#### **Frequency Analysis**
```python
from collections import Counter

def frequency_analysis(text):
    # Remove non-letters and convert to uppercase
    clean_text = ''.join(c.upper() for c in text if c.isalpha())
    
    # Count letter frequencies
    frequencies = Counter(clean_text)
    total_letters = len(clean_text)
    
    # Calculate percentages
    percentages = {letter: (count/total_letters)*100 
                  for letter, count in frequencies.items()}
    
    return sorted(percentages.items(), key=lambda x: x[1], reverse=True)

# English letter frequency (approximate)
english_freq = {
    'E': 12.7, 'T': 9.1, 'A': 8.2, 'O': 7.5, 'I': 7.0, 'N': 6.7,
    'S': 6.3, 'H': 6.1, 'R': 6.0, 'D': 4.3, 'L': 4.0, 'C': 2.8,
    'U': 2.8, 'M': 2.4, 'W': 2.4, 'F': 2.2, 'G': 2.0, 'Y': 2.0,
    'P': 1.9, 'B': 1.3, 'V': 1.0, 'K': 0.8, 'J': 0.15, 'X': 0.15,
    'Q': 0.10, 'Z': 0.07
}

# Example usage
sample_text = "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG"
freq_analysis = frequency_analysis(sample_text)
print("Letter frequencies:")
for letter, freq in freq_analysis:
    print(f"{letter}: {freq:.2f}%")
```

---

## 3. Cryptographic Hashing & Message Digests (20 min)

### Hash Function Properties

A cryptographic hash function H produces a hash from a message: H(m) = c

#### **Essential Properties:**
1. **Pre-image Resistance**: Given hash c, computationally infeasible to find m such that H(m) = c
2. **Second Pre-image Resistance**: Given m₁, computationally infeasible to find m₂ ≠ m₁ such that H(m₁) = H(m₂)
3. **Collision Resistance**: Computationally infeasible to find any m₁ ≠ m₂ such that H(m₁) = H(m₂)

### Common Hash Algorithms

#### **SHA Family**
```python
import hashlib

def demonstrate_hash_functions():
    message = b"Hello, World!"
    
    # SHA-1 (deprecated - collision attacks possible)
    sha1_hash = hashlib.sha1(message).hexdigest()
    print(f"SHA-1: {sha1_hash}")
    
    # SHA-256 (widely used)
    sha256_hash = hashlib.sha256(message).hexdigest()
    print(f"SHA-256: {sha256_hash}")
    
    # SHA-3 (newest standard)
    sha3_hash = hashlib.sha3_256(message).hexdigest()
    print(f"SHA-3: {sha3_hash}")
    
    # Demonstrate avalanche effect
    message2 = b"Hello, World?"
    sha256_hash2 = hashlib.sha256(message2).hexdigest()
    print(f"SHA-256 (changed): {sha256_hash2}")

demonstrate_hash_functions()
```

### Password Hashing with Salt

#### **Secure Password Storage**
```python
import os
import hashlib
import secrets

def hash_password(password: str, salt: bytes = None) -> tuple:
    """
    Hash a password with a random salt using PBKDF2.
    Returns (salt, hash) tuple.
    """
    if salt is None:
        salt = os.urandom(32)  # 256-bit salt
    
    # Use PBKDF2 with SHA-256
    hash_obj = hashlib.pbkdf2_hmac('sha256', 
                                  password.encode('utf-8'), 
                                  salt, 
                                  100000)  # 100,000 iterations
    
    return salt, hash_obj

def verify_password(password: str, salt: bytes, stored_hash: bytes) -> bool:
    """Verify a password against its stored hash."""
    _, computed_hash = hash_password(password, salt)
    return secrets.compare_digest(computed_hash, stored_hash)

# Example usage
password = "correct horse battery staple"
salt, password_hash = hash_password(password)

print(f"Salt: {salt.hex()}")
print(f"Hash: {password_hash.hex()}")

# Verify password
is_valid = verify_password(password, salt, password_hash)
print(f"Password verification: {is_valid}")

# Test with wrong password
is_invalid = verify_password("wrong password", salt, password_hash)
print(f"Wrong password verification: {is_invalid}")
```

### Message Authentication Codes (MACs)

#### **HMAC Implementation**
```python
import hmac
import hashlib

def create_hmac(message: bytes, key: bytes) -> bytes:
    """Create HMAC using SHA-256."""
    return hmac.new(key, message, hashlib.sha256).digest()

def verify_hmac(message: bytes, key: bytes, received_mac: bytes) -> bool:
    """Verify HMAC."""
    expected_mac = create_hmac(message, key)
    return hmac.compare_digest(expected_mac, received_mac)

# Example
message = b"Important message"
key = os.urandom(32)  # 256-bit key

mac = create_hmac(message, key)
print(f"HMAC: {mac.hex()}")

# Verify
is_valid = verify_hmac(message, key, mac)
print(f"HMAC verification: {is_valid}")
```

---

## 4. Symmetric Cryptography (25 min)

### Symmetric vs Asymmetric

**Symmetric Cryptography:**
- Same key for encryption and decryption
- Fast and efficient
- Key distribution problem
- Examples: AES, ChaCha20, DES

**Asymmetric Cryptography:**
- Different keys for encryption and decryption
- Slower but solves key distribution
- Examples: RSA, ECC, Diffie-Hellman

### Block Ciphers vs Stream Ciphers

#### **Block Ciphers**
- Process fixed-size blocks (e.g., 128 bits)
- Examples: AES, DES, Blowfish
- Modes: ECB, CBC, CFB, OFB, GCM

#### **Stream Ciphers**
- Process data bit-by-bit or byte-by-byte
- Examples: ChaCha20, RC4, A5/1

### AES (Advanced Encryption Standard)

#### **AES-GCM Implementation**
```python
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad, unpad

class AESCipher:
    def __init__(self, key_size=32):  # 256-bit key
        self.key = get_random_bytes(key_size)
    
    def encrypt(self, plaintext: bytes) -> tuple:
        """Encrypt using AES-GCM mode."""
        cipher = AES.new(self.key, AES.MODE_GCM)
        ciphertext, tag = cipher.encrypt_and_digest(plaintext)
        return cipher.nonce, ciphertext, tag
    
    def decrypt(self, nonce: bytes, ciphertext: bytes, tag: bytes) -> bytes:
        """Decrypt using AES-GCM mode."""
        cipher = AES.new(self.key, AES.MODE_GCM, nonce=nonce)
        return cipher.decrypt_and_verify(ciphertext, tag)

# Example usage
aes = AESCipher()
message = b"This is a secret message"

# Encrypt
nonce, ciphertext, tag = aes.encrypt(message)
print(f"Nonce: {nonce.hex()}")
print(f"Ciphertext: {ciphertext.hex()}")
print(f"Tag: {tag.hex()}")

# Decrypt
decrypted = aes.decrypt(nonce, ciphertext, tag)
print(f"Decrypted: {decrypted.decode()}")
```

#### **AES-CBC Implementation**
```python
def aes_cbc_encrypt(plaintext: bytes, key: bytes) -> tuple:
    """Encrypt using AES-CBC mode."""
    iv = get_random_bytes(16)  # 128-bit IV
    cipher = AES.new(key, AES.MODE_CBC, iv)
    
    # Pad the plaintext
    padded_plaintext = pad(plaintext, AES.block_size)
    ciphertext = cipher.encrypt(padded_plaintext)
    
    return iv, ciphertext

def aes_cbc_decrypt(iv: bytes, ciphertext: bytes, key: bytes) -> bytes:
    """Decrypt using AES-CBC mode."""
    cipher = AES.new(key, AES.MODE_CBC, iv)
    padded_plaintext = cipher.decrypt(ciphertext)
    return unpad(padded_plaintext, AES.block_size)

# Example
key = get_random_bytes(32)  # 256-bit key
message = b"Hello, World! This is a longer message."

# Encrypt
iv, ciphertext = aes_cbc_encrypt(message, key)
print(f"IV: {iv.hex()}")
print(f"Ciphertext: {ciphertext.hex()}")

# Decrypt
decrypted = aes_cbc_decrypt(iv, ciphertext, key)
print(f"Decrypted: {decrypted.decode()}")
```

### Modes of Operation

#### **ECB (Electronic Codebook) - INSECURE**
```python
def aes_ecb_encrypt(plaintext: bytes, key: bytes) -> bytes:
    """ECB mode - DO NOT USE for real applications!"""
    cipher = AES.new(key, AES.MODE_ECB)
    padded_plaintext = pad(plaintext, AES.block_size)
    return cipher.encrypt(padded_plaintext)

# ECB reveals patterns - demonstrate with image-like data
def demonstrate_ecb_weakness():
    # Create a pattern (like a simple image)
    pattern = b"AAAA" * 4 + b"BBBB" * 4  # 32 bytes total
    key = get_random_bytes(32)
    
    ecb_ciphertext = aes_ecb_encrypt(pattern, key)
    print(f"ECB ciphertext: {ecb_ciphertext.hex()}")
    print("Notice the repeating pattern!")

demonstrate_ecb_weakness()
```

---

## 5. Asymmetric Cryptography & Digital Signatures (25 min)

### Public Key Cryptography Concepts

#### **Key Pairs**
- **Public Key**: Can be shared with everyone
- **Private Key**: Must be kept secret
- **Mathematical Relationship**: Keys are mathematically related but computationally infeasible to derive one from the other

### RSA Implementation

#### **RSA Key Generation**
```python
from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP
from Crypto.Signature import pkcs1_15
from Crypto.Hash import SHA256

def generate_rsa_keypair(key_size=2048):
    """Generate RSA key pair."""
    key = RSA.generate(key_size)
    private_key = key.export_key()
    public_key = key.publickey().export_key()
    return private_key, public_key

def rsa_encrypt(message: bytes, public_key_bytes: bytes) -> bytes:
    """Encrypt message using RSA public key."""
    public_key = RSA.import_key(public_key_bytes)
    cipher = PKCS1_OAEP.new(public_key)
    # base64 encode
    return cipher.encrypt(message)

def rsa_decrypt(ciphertext: bytes, private_key_bytes: bytes) -> bytes:
    """Decrypt message using RSA private key."""
    private_key = RSA.import_key(private_key_bytes)
    # base64 decode
    cipher = PKCS1_OAEP.new(private_key)
    return cipher.decrypt(ciphertext)

# Example
private_key, public_key = generate_rsa_keypair()
message = b"Secret message for RSA encryption"

# Encrypt
ciphertext = rsa_encrypt(message, public_key)
print(f"Ciphertext: {ciphertext.hex()}")

# Decrypt
decrypted = rsa_decrypt(ciphertext, private_key)
print(f"Decrypted: {decrypted.decode()}")
```

#### **RSA Digital Signatures**
```python
def rsa_sign(message: bytes, private_key_bytes: bytes) -> bytes:
    """Sign message using RSA private key."""
    private_key = RSA.import_key(private_key_bytes)
    hash_obj = SHA256.new(message)
    signature = pkcs1_15.new(private_key).sign(hash_obj)
    return signature

def rsa_verify(message: bytes, signature: bytes, public_key_bytes: bytes) -> bool:
    """Verify RSA signature."""
    public_key = RSA.import_key(public_key_bytes)
    hash_obj = SHA256.new(message)
    try:
        pkcs1_15.new(public_key).verify(hash_obj, signature)
        return True
    except ValueError:
        return False

# Example
message = b"Important document to sign"
signature = rsa_sign(message, private_key)

# Verify signature
is_valid = rsa_verify(message, signature, public_key)
print(f"Signature valid: {is_valid}")

# Test with tampered message
tampered_message = b"Important document to sign (modified)"
is_invalid = rsa_verify(tampered_message, signature, public_key)
print(f"Tampered message signature valid: {is_invalid}")
```

### Elliptic Curve Cryptography (ECC)

#### **ECDSA Implementation**
```python
from cryptography.hazmat.primitives.asymmetric import ec
from cryptography.hazmat.primitives import hashes, serialization
from cryptography.hazmat.primitives.asymmetric.utils import encode_dss_signature, decode_dss_signature

def generate_ec_keypair():
    """Generate ECDSA key pair."""
    private_key = ec.generate_private_key(ec.SECP256R1())
    public_key = private_key.public_key()
    return private_key, public_key

def ecdsa_sign(message: bytes, private_key) -> bytes:
    """Sign message using ECDSA."""
    signature = private_key.sign(message, ec.ECDSA(hashes.SHA256()))
    return signature

def ecdsa_verify(message: bytes, signature: bytes, public_key) -> bool:
    """Verify ECDSA signature."""
    try:
        public_key.verify(signature, message, ec.ECDSA(hashes.SHA256()))
        return True
    except Exception:
        return False

# Example
private_key, public_key = generate_ec_keypair()
message = b"ECDSA signed message"

# Sign
signature = ecdsa_sign(message, private_key)
print(f"ECDSA signature: {signature.hex()}")

# Verify
is_valid = ecdsa_verify(message, signature, public_key)
print(f"ECDSA signature valid: {is_valid}")
```

### Diffie-Hellman Key Exchange

#### **DH Implementation**
```python
from cryptography.hazmat.primitives.asymmetric import dh
from cryptography.hazmat.primitives.kdf.hkdf import HKDF
from cryptography.hazmat.primitives import hashes

def generate_dh_parameters():
    """Generate DH parameters."""
    parameters = dh.generate_parameters(generator=2, key_size=2048)
    return parameters

def perform_dh_key_exchange():
    """Demonstrate DH key exchange."""
    # Generate parameters
    parameters = generate_dh_parameters()
    
    # Alice generates her key pair
    alice_private = parameters.generate_private_key()
    alice_public = alice_private.public_key()
    
    # Bob generates his key pair
    bob_private = parameters.generate_private_key()
    bob_public = bob_private.public_key()
    
    # Exchange public keys and compute shared secret
    alice_shared = alice_private.exchange(bob_public)
    bob_shared = bob_private.exchange(alice_public)
    
    # Derive symmetric key from shared secret
    derived_key = HKDF(
        algorithm=hashes.SHA256(),
        length=32,
        salt=None,
        info=b'handshake data',
    ).derive(alice_shared)
    
    print(f"Shared secret length: {len(alice_shared)} bytes")
    print(f"Derived key: {derived_key.hex()}")
    print(f"Keys match: {alice_shared == bob_shared}")

perform_dh_key_exchange()
```

---

## 6. Cryptanalysis & Attack Methods (15 min)

### Types of Attacks

#### **Ciphertext-Only Attack**
- Attacker has only ciphertext
- Example: Frequency analysis on substitution ciphers

#### **Known Plaintext Attack**
- Attacker has some plaintext-ciphertext pairs
- Example: Breaking Enigma with known message formats

#### **Chosen Plaintext Attack**
- Attacker can choose plaintexts to encrypt
- Example: Differential cryptanalysis

#### **Chosen Ciphertext Attack**
- Attacker can choose ciphertexts to decrypt
- Example: Padding oracle attacks

### Common Attack Techniques

#### **Frequency Analysis Attack**
```python
def frequency_attack_caesar(ciphertext: str):
    """Attempt to break Caesar cipher using frequency analysis."""
    # English letter frequencies
    english_freq = {
        'E': 12.7, 'T': 9.1, 'A': 8.2, 'O': 7.5, 'I': 7.0, 'N': 6.7,
        'S': 6.3, 'H': 6.1, 'R': 6.0, 'D': 4.3, 'L': 4.0, 'C': 2.8,
        'U': 2.8, 'M': 2.4, 'W': 2.4, 'F': 2.2, 'G': 2.0, 'Y': 2.0,
        'P': 1.9, 'B': 1.3, 'V': 1.0, 'K': 0.8, 'J': 0.15, 'X': 0.15,
        'Q': 0.10, 'Z': 0.07
    }
    
    best_shift = 0
    best_score = float('inf')
    
    for shift in range(26):
        # Decrypt with current shift
        decrypted = caesar_cipher(ciphertext, -shift)
        
        # Calculate frequency score
        freq_analysis = frequency_analysis(decrypted)
        score = 0
        
        for letter, freq in freq_analysis:
            expected_freq = english_freq.get(letter, 0)
            score += abs(freq - expected_freq)
        
        if score < best_score:
            best_score = score
            best_shift = shift
    
    return caesar_cipher(ciphertext, -best_shift), best_shift

# Example
original_message = "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG"
encrypted_message = caesar_cipher(original_message, 7)
print(f"Original: {original_message}")
print(f"Encrypted: {encrypted_message}")

decrypted_message, shift_used = frequency_attack_caesar(encrypted_message)
print(f"Decrypted: {decrypted_message}")
print(f"Shift used: {shift_used}")
```

#### **Padding Oracle Attack Simulation**
```python
def simulate_padding_oracle_attack():
    """
    Simulate a padding oracle attack on CBC mode.
    This is a simplified demonstration.
    """
    print("Padding Oracle Attack Simulation")
    print("=" * 40)
    
    # Generate random key and IV
    key = get_random_bytes(16)
    iv = get_random_bytes(16)
    
    # Encrypt a message
    message = b"Hello, World!"
    cipher = AES.new(key, AES.MODE_CBC, iv)
    padded_message = pad(message, AES.block_size)
    ciphertext = cipher.encrypt(padded_message)
    
    print(f"Original message: {message}")
    print(f"Ciphertext: {ciphertext.hex()}")
    
    # Simulate padding oracle (checks if padding is valid)
    def padding_oracle(ciphertext_bytes):
        try:
            cipher = AES.new(key, AES.MODE_CBC, iv)
            decrypted = cipher.decrypt(ciphertext_bytes)
            unpad(decrypted, AES.block_size)
            return True  # Valid padding
        except ValueError:
            return False  # Invalid padding
    
    # Attack: modify last byte of ciphertext and test padding oracle
    modified_ciphertext = bytearray(ciphertext)
    for i in range(256):
        modified_ciphertext[-1] = i
        if padding_oracle(bytes(modified_ciphertext)):
            print(f"Found valid padding with byte value: {i}")
            break

simulate_padding_oracle_attack()
```

---

## 7. Modern Protocols & Hybrid Systems (15 min)

### Hybrid Cryptography

**Why Hybrid Systems?**
- Symmetric encryption is fast but has key distribution problems
- Asymmetric encryption solves key distribution but is slow
- Solution: Use asymmetric for key exchange, symmetric for bulk data

#### **TLS/SSL Handshake Simulation**
```python
def simulate_tls_handshake():
    """Simulate a simplified TLS handshake."""
    print("TLS Handshake Simulation")
    print("=" * 30)
    
    # 1. Client generates random pre-master secret
    pre_master_secret = get_random_bytes(48)
    print(f"1. Client generates pre-master secret: {pre_master_secret.hex()[:16]}...")
    
    # 2. Server generates RSA key pair
    server_private, server_public = generate_rsa_keypair()
    print("2. Server generates RSA key pair")
    
    # 3. Client encrypts pre-master secret with server's public key
    encrypted_pre_master = rsa_encrypt(pre_master_secret, server_public)
    print(f"3. Client encrypts pre-master secret: {encrypted_pre_master.hex()[:16]}...")
    
    # 4. Server decrypts pre-master secret
    decrypted_pre_master = rsa_decrypt(encrypted_pre_master, server_private)
    print(f"4. Server decrypts pre-master secret: {decrypted_pre_master.hex()[:16]}...")
    
    # 5. Both parties derive session keys
    # (In real TLS, this involves more complex key derivation)
    session_key = hashlib.sha256(pre_master_secret).digest()[:32]
    print(f"5. Session key derived: {session_key.hex()[:16]}...")
    
    # 6. Use session key for symmetric encryption
    aes_cipher = AESCipher()
    aes_cipher.key = session_key  # Override with derived key
    
    message = b"Secure message using session key"
    nonce, ciphertext, tag = aes_cipher.encrypt(message)
    print(f"6. Message encrypted with session key: {ciphertext.hex()[:16]}...")
    
    decrypted_message = aes_cipher.decrypt(nonce, ciphertext, tag)
    print(f"7. Message decrypted: {decrypted_message.decode()}")

simulate_tls_handshake()
```

### Digital Certificates & PKI

#### **Certificate Verification Simulation**
```python
def simulate_certificate_verification():
    """Simulate certificate verification process."""
    print("Certificate Verification Simulation")
    print("=" * 40)
    
    # 1. CA generates root certificate
    ca_private, ca_public = generate_rsa_keypair()
    print("1. CA generates root certificate")
    
    # 2. Server generates certificate request
    server_private, server_public = generate_rsa_keypair()
    print("2. Server generates certificate request")
    
    # 3. CA signs server's public key
    server_cert_data = server_public  # Simplified
    server_cert_signature = rsa_sign(server_cert_data, ca_private)
    print("3. CA signs server certificate")
    
    # 4. Client verifies certificate
    is_valid = rsa_verify(server_cert_data, server_cert_signature, ca_public)
    print(f"4. Client verifies certificate: {is_valid}")
    
    if is_valid:
        print("5. Certificate is valid - proceeding with secure communication")
    else:
        print("5. Certificate verification failed - aborting connection")

simulate_certificate_verification()
```

---

## 8. Security Best Practices (15 min)

### ⚠️ Critical Security Rules

#### **1. NEVER Roll Your Own Crypto**
```python
# ❌ WRONG - Don't do this!
def bad_encryption(plaintext, key):
    result = ""
    for i, char in enumerate(plaintext):
        result += chr(ord(char) ^ ord(key[i % len(key)]))
    return result

# ✅ CORRECT - Use established libraries
from cryptography.fernet import Fernet

def good_encryption(plaintext, key):
    f = Fernet(key)
    return f.encrypt(plaintext)
```

#### **2. Use Appropriate Key Sizes**
```python
def demonstrate_key_sizes():
    """Demonstrate appropriate key sizes for different algorithms."""
    print("Recommended Key Sizes:")
    print("=" * 25)
    print("AES: 128-bit (minimum), 256-bit (recommended)")
    print("RSA: 2048-bit (minimum), 3072-bit (recommended)")
    print("ECC: 256-bit (equivalent to 3072-bit RSA)")
    print("Hash: SHA-256 (minimum), SHA-3 (recommended)")
    
    # Generate keys with appropriate sizes
    aes_key = get_random_bytes(32)  # 256-bit
    rsa_key = RSA.generate(2048)    # 2048-bit
    print(f"AES key length: {len(aes_key) * 8} bits")
    print(f"RSA key length: {rsa_key.size_in_bits()} bits")

demonstrate_key_sizes()
```

#### **3. Secure Random Number Generation**
```python
import secrets

def demonstrate_secure_randomness():
    """Demonstrate secure vs insecure random number generation."""
    print("Random Number Generation:")
    print("=" * 30)
    
    # ❌ Insecure - predictable
    import random
    random.seed(42)  # Fixed seed
    insecure_random = random.randint(0, 1000000)
    print(f"Insecure random: {insecure_random}")
    
    # ✅ Secure - cryptographically secure
    secure_random = secrets.randbelow(1000000)
    print(f"Secure random: {secure_random}")
    
    # Generate secure random bytes
    secure_bytes = secrets.token_bytes(32)
    print(f"Secure random bytes: {secure_bytes.hex()}")

demonstrate_secure_randomness()
```

#### **4. Proper Initialization Vectors (IVs)**
```python
def demonstrate_iv_usage():
    """Demonstrate proper IV usage."""
    print("Initialization Vector Usage:")
    print("=" * 30)
    
    key = get_random_bytes(32)
    message1 = b"First message"
    message2 = b"Second message"
    
    # ❌ WRONG - Reusing IV
    iv = get_random_bytes(16)
    cipher1 = AES.new(key, AES.MODE_CBC, iv)
    cipher2 = AES.new(key, AES.MODE_CBC, iv)  # Same IV!
    
    ct1 = cipher1.encrypt(pad(message1, AES.block_size))
    ct2 = cipher2.encrypt(pad(message2, AES.block_size))
    
    print("❌ Reusing IV reveals patterns")
    print(f"Message 1 ciphertext: {ct1.hex()[:32]}...")
    print(f"Message 2 ciphertext: {ct2.hex()[:32]}...")
    
    # ✅ CORRECT - Unique IV for each message
    iv1 = get_random_bytes(16)
    iv2 = get_random_bytes(16)
    
    cipher1 = AES.new(key, AES.MODE_CBC, iv1)
    cipher2 = AES.new(key, AES.MODE_CBC, iv2)
    
    ct1 = cipher1.encrypt(pad(message1, AES.block_size))
    ct2 = cipher2.encrypt(pad(message2, AES.block_size))
    
    print("\n✅ Unique IVs provide security")
    print(f"Message 1 ciphertext: {ct1.hex()[:32]}...")
    print(f"Message 2 ciphertext: {ct2.hex()[:32]}...")

demonstrate_iv_usage()
```

#### **5. Side-Channel Attack Prevention**
```python
import time

def vulnerable_timing_attack():
    """Demonstrate timing attack vulnerability."""
    def insecure_compare(a, b):
        """Vulnerable to timing attacks."""
        if len(a) != len(b):
            return False
        for i in range(len(a)):
            if a[i] != b[i]:
                return False
        return True
    
    def secure_compare(a, b):
        """Secure against timing attacks."""
        return secrets.compare_digest(a, b)
    
    # Test timing differences
    test_string = b"test string"
    wrong_string = b"wrong string"
    
    # Time insecure comparison
    start = time.time()
    insecure_compare(test_string, wrong_string)
    insecure_time = time.time() - start
    
    # Time secure comparison
    start = time.time()
    secure_compare(test_string, wrong_string)
    secure_time = time.time() - start
    
    print(f"Insecure compare time: {insecure_time:.6f}s")
    print(f"Secure compare time: {secure_time:.6f}s")

vulnerable_timing_attack()
```

### Security Checklist

#### **Before Implementing Crypto:**
- [ ] Use established, well-tested libraries
- [ ] Verify algorithm hasn't been broken
- [ ] Use appropriate key sizes
- [ ] Generate random numbers securely
- [ ] Use unique IVs/nonces
- [ ] Implement proper padding
- [ ] Protect against side-channel attacks
- [ ] Validate all inputs
- [ ] Use constant-time comparisons
- [ ] Keep keys secure in memory

---

## 9. Practical Exercises & Wrap-Up (10 min)

### Hands-On Exercises

#### **Exercise 1: Secure File Encryption**
```python
def encrypt_file(filename: str, password: str):
    """Encrypt a file with password-based encryption."""
    # Generate salt
    salt = os.urandom(32)
    
    # Derive key from password
    key = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    
    # Read file
    with open(filename, 'rb') as f:
        data = f.read()
    
    # Encrypt
    cipher = AES.new(key, AES.MODE_GCM)
    ciphertext, tag = cipher.encrypt_and_digest(data)
    
    # Save encrypted file
    with open(filename + '.enc', 'wb') as f:
        f.write(salt + cipher.nonce + tag + ciphertext)
    
    print(f"File {filename} encrypted to {filename}.enc")

def decrypt_file(filename: str, password: str):
    """Decrypt a password-encrypted file."""
    with open(filename, 'rb') as f:
        data = f.read()
    
    # Extract components
    salt = data[:32]
    nonce = data[32:48]
    tag = data[48:64]
    ciphertext = data[64:]
    
    # Derive key
    key = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    
    # Decrypt
    cipher = AES.new(key, AES.MODE_GCM, nonce=nonce)
    plaintext = cipher.decrypt_and_verify(ciphertext, tag)
    
    # Save decrypted file
    output_filename = filename.replace('.enc', '.dec')
    with open(output_filename, 'wb') as f:
        f.write(plaintext)
    
    print(f"File {filename} decrypted to {output_filename}")

# Example usage
# encrypt_file("document.txt", "my_secure_password")
# decrypt_file("document.txt.enc", "my_secure_password")
```

#### **Exercise 2: Secure Communication Protocol**
```python
class SecureMessaging:
    def __init__(self):
        self.private_key, self.public_key = generate_rsa_keypair()
        self.session_key = None
    
    def establish_session(self, peer_public_key):
        """Establish secure session using hybrid encryption."""
        # Generate session key
        self.session_key = get_random_bytes(32)
        
        # Encrypt session key with peer's public key
        encrypted_session_key = rsa_encrypt(self.session_key, peer_public_key)
        
        return encrypted_session_key
    
    def send_message(self, message: bytes, peer_public_key: bytes) -> tuple:
        """Send encrypted and signed message."""
        # Encrypt message with session key
        cipher = AES.new(self.session_key, AES.MODE_GCM)
        ciphertext, tag = cipher.encrypt_and_digest(message)
        
        # Sign the message
        signature = rsa_sign(message, self.private_key)
        
        return cipher.nonce, ciphertext, tag, signature
    
    def receive_message(self, nonce: bytes, ciphertext: bytes, tag: bytes, 
                       signature: bytes, sender_public_key: bytes) -> bytes:
        """Receive and verify encrypted message."""
        # Decrypt message
        cipher = AES.new(self.session_key, AES.MODE_GCM, nonce=nonce)
        message = cipher.decrypt_and_verify(ciphertext, tag)
        
        # Verify signature
        if not rsa_verify(message, signature, sender_public_key):
            raise ValueError("Invalid signature")
        
        return message

# Example usage
alice = SecureMessaging()
bob = SecureMessaging()

# Establish session
session_key_encrypted = alice.establish_session(bob.public_key)
bob.session_key = rsa_decrypt(session_key_encrypted, bob.private_key)

# Send message
message = b"Hello Bob, this is Alice!"
nonce, ciphertext, tag, signature = alice.send_message(message, bob.public_key)

# Receive message
received_message = bob.receive_message(nonce, ciphertext, tag, signature, alice.public_key)
print(f"Received message: {received_message.decode()}")
```

### Additional Exercises

1. **Implement a Caesar cipher breaker** using frequency analysis
2. **Create a password manager** with secure storage
3. **Build a simple TLS-like handshake** simulator
4. **Implement HMAC-based authentication** for API requests
5. **Create a digital signature system** for document verification

---

## ✅ Summary

### Key Takeaways

#### **Cryptographic Goals**
- **Confidentiality**: Keep data secret
- **Integrity**: Detect tampering
- **Authentication**: Verify identity
- **Non-repudiation**: Prevent denial

#### **Algorithm Categories**
- **Symmetric**: Fast, shared key (AES, ChaCha20)
- **Asymmetric**: Key exchange, signatures (RSA, ECC)
- **Hashing**: One-way functions (SHA-256, SHA-3)
- **MACs**: Authentication codes (HMAC)

#### **Security Principles**
- **Never roll your own crypto**
- **Use appropriate key sizes**
- **Generate randomness securely**
- **Use unique IVs/nonces**
- **Protect against side-channel attacks**

#### **Real-World Applications**
- **TLS/SSL**: Web security
- **Digital signatures**: Document authentication
- **Password hashing**: Secure storage
- **File encryption**: Data protection
- **Blockchain**: Cryptographic proofs

### Further Reading

- [NIST Cryptographic Standards](https://csrc.nist.gov/projects/cryptographic-standards-and-guidelines)
- [Cryptography Engineering](https://www.schneier.com/books/cryptography-engineering/)
- [Real-World Cryptography](https://www.manning.com/books/real-world-cryptography)
- [Applied Cryptography](https://www.schneier.com/books/applied-cryptography/)

### Remember: Security is a Process, Not a Product

Cryptography is just one tool in the security toolkit. Always consider:
- Threat modeling
- Defense in depth
- Regular security audits
- Keeping systems updated
- User education and training

---

*"The only secure system is one that is powered off, cast in a block of concrete and sealed in a lead-lined room with armed guards - and even then I have my doubts."* - Gene Spafford
