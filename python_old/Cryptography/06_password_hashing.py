"""
Password Hashing - Secure Password Storage

This module demonstrates secure password hashing techniques using salt and
key derivation functions. Proper password hashing is crucial for security
as it prevents rainbow table attacks and makes brute force attacks much
more difficult.

Key Concepts:
- Salt: Random data added to passwords before hashing
- Key Derivation Functions: Slow hash functions designed for passwords
- PBKDF2: Password-Based Key Derivation Function 2
- Argon2: Modern password hashing algorithm (winner of Password Hashing Competition)

Security Principles:
- Never store plaintext passwords
- Always use salt (unique for each password)
- Use slow hash functions (not fast ones like SHA-256)
- Use sufficient iterations/work factor
- Use cryptographically secure random number generators

Author: Cryptography Lecture
Date: 2024
"""

import hashlib
import os
import secrets
import time
from typing import Tuple, Optional


def hash_password_basic(password: str, salt: Optional[bytes] = None) -> Tuple[bytes, bytes]:
    """
    Hash a password using PBKDF2 with SHA-256.
    
    This is a basic implementation for educational purposes. In production,
    use libraries like bcrypt, scrypt, or Argon2.
    
    Args:
        password (str): The password to hash
        salt (bytes, optional): Salt to use. If None, generates a random salt
    
    Returns:
        Tuple[bytes, bytes]: (salt, hash) tuple
        
    Example:
        >>> salt, hash_val = hash_password_basic("mypassword")
        >>> len(salt)
        32
        >>> len(hash_val)
        32
    """
    # Generate random salt if not provided
    if salt is None:
        salt = os.urandom(32)  # 256-bit salt
    
    # Convert password to bytes
    password_bytes = password.encode('utf-8')
    
    # Use PBKDF2 with SHA-256
    # PBKDF2 applies the hash function multiple times to slow down attacks
    hash_obj = hashlib.pbkdf2_hmac(
        'sha256',           # Hash algorithm
        password_bytes,     # Password
        salt,               # Salt
        100000             # Iterations (100,000 is a reasonable default)
    )
    
    return salt, hash_obj


def verify_password_basic(password: str, salt: bytes, stored_hash: bytes) -> bool:
    """
    Verify a password against its stored hash.
    
    Args:
        password (str): The password to verify
        salt (bytes): The salt used during hashing
        stored_hash (bytes): The stored hash to compare against
    
    Returns:
        bool: True if password is correct, False otherwise
        
    Example:
        >>> salt, hash_val = hash_password_basic("mypassword")
        >>> verify_password_basic("mypassword", salt, hash_val)
        True
        >>> verify_password_basic("wrongpassword", salt, hash_val)
        False
    """
    # Hash the provided password with the same salt
    _, computed_hash = hash_password_basic(password, salt)
    
    # Use constant-time comparison to prevent timing attacks
    return secrets.compare_digest(computed_hash, stored_hash)


def hash_password_advanced(password: str, salt: Optional[bytes] = None, 
                          iterations: int = 100000) -> Tuple[bytes, bytes, int]:
    """
    Advanced password hashing with configurable parameters.
    
    Args:
        password (str): The password to hash
        salt (bytes, optional): Salt to use. If None, generates a random salt
        iterations (int): Number of PBKDF2 iterations
    
    Returns:
        Tuple[bytes, bytes, int]: (salt, hash, iterations) tuple
    """
    if salt is None:
        salt = os.urandom(32)  # 256-bit salt
    
    password_bytes = password.encode('utf-8')
    
    # Use PBKDF2 with configurable iterations
    hash_obj = hashlib.pbkdf2_hmac(
        'sha256',
        password_bytes,
        salt,
        iterations
    )
    
    return salt, hash_obj, iterations


def verify_password_advanced(password: str, salt: bytes, stored_hash: bytes, 
                           iterations: int) -> bool:
    """
    Verify a password with advanced parameters.
    
    Args:
        password (str): The password to verify
        salt (bytes): The salt used during hashing
        stored_hash (bytes): The stored hash to compare against
        iterations (int): Number of iterations used during hashing
    
    Returns:
        bool: True if password is correct, False otherwise
    """
    _, computed_hash, _ = hash_password_advanced(password, salt, iterations)
    return secrets.compare_digest(computed_hash, stored_hash)


def demonstrate_password_hashing():
    """
    Demonstrate secure password hashing techniques.
    """
    print("=" * 60)
    print("SECURE PASSWORD HASHING DEMONSTRATION")
    print("=" * 60)
    
    # Example 1: Basic password hashing
    password = "correct horse battery staple"
    print(f"Password: {password}")
    
    # Hash the password
    salt, password_hash = hash_password_basic(password)
    
    print(f"Salt: {salt.hex()}")
    print(f"Hash: {password_hash.hex()}")
    print(f"Salt length: {len(salt) * 8} bits")
    print(f"Hash length: {len(password_hash) * 8} bits")
    
    # Verify the password
    is_valid = verify_password_basic(password, salt, password_hash)
    print(f"Password verification: {is_valid}")
    
    # Test with wrong password
    is_invalid = verify_password_basic("wrong password", salt, password_hash)
    print(f"Wrong password verification: {is_invalid}")
    
    print("\n" + "-" * 40)
    
    # Example 2: Same password, different salt
    print("Same password with different salt:")
    salt2, password_hash2 = hash_password_basic(password)
    
    print(f"Salt 1: {salt.hex()}")
    print(f"Hash 1: {password_hash.hex()}")
    print(f"Salt 2: {salt2.hex()}")
    print(f"Hash 2: {password_hash2.hex()}")
    print(f"Hashes are different: {password_hash != password_hash2}")
    
    print("\n" + "-" * 40)
    
    # Example 3: Different iterations
    print("Password hashing with different iteration counts:")
    
    iterations_list = [1000, 10000, 100000, 1000000]
    
    for iterations in iterations_list:
        start_time = time.time()
        salt_iter, hash_iter, _ = hash_password_advanced(password, iterations=iterations)
        end_time = time.time()
        
        print(f"Iterations: {iterations:7,}, Time: {end_time - start_time:.3f}s")
    
    print("\nNote: More iterations = more security but slower verification")


def demonstrate_salt_importance():
    """
    Demonstrate why salt is important for password security.
    """
    print("\n" + "=" * 60)
    print("SALT IMPORTANCE DEMONSTRATION")
    print("=" * 60)
    
    # Common passwords
    passwords = ["password", "123456", "admin", "letmein"]
    
    print("Hashing common passwords WITHOUT salt:")
    print("-" * 40)
    
    # Hash without salt (vulnerable to rainbow table attacks)
    for pwd in passwords:
        # Simple hash without salt (DON'T DO THIS IN REAL APPLICATIONS!)
        hash_no_salt = hashlib.sha256(pwd.encode()).hexdigest()
        print(f"{pwd:<10}: {hash_no_salt}")
    
    print("\nHashing common passwords WITH salt:")
    print("-" * 40)
    
    # Hash with salt (secure)
    for pwd in passwords:
        salt, hash_with_salt = hash_password_basic(pwd)
        print(f"{pwd:<10}: {hash_with_salt.hex()}")
        print(f"Salt: {salt.hex()}")
    
    print("\nKey differences:")
    print("• Without salt: Same password always produces same hash")
    print("• With salt: Same password produces different hash each time")
    print("• Salt prevents rainbow table attacks")
    print("• Salt prevents attackers from precomputing hashes")


def rainbow_table_attack_demo():
    """
    Demonstrate how rainbow table attacks work and why salt prevents them.
    """
    print("\n" + "=" * 60)
    print("RAINBOW TABLE ATTACK DEMONSTRATION")
    print("=" * 60)
    
    print("Rainbow Table Attack:")
    print("1. Attacker precomputes hashes of common passwords")
    print("2. When they get a password database, they can quickly look up hashes")
    print("3. Salt makes this attack impossible")
    
    # Simulate a rainbow table
    common_passwords = {
        "password": hashlib.sha256(b"password").hexdigest(),
        "123456": hashlib.sha256(b"123456").hexdigest(),
        "admin": hashlib.sha256(b"admin").hexdigest(),
        "letmein": hashlib.sha256(b"letmein").hexdigest(),
    }
    
    print("\nSimulated rainbow table:")
    for pwd, hash_val in common_passwords.items():
        print(f"{pwd:<10}: {hash_val}")
    
    # Simulate finding a hash in the database
    stolen_hash = hashlib.sha256(b"password").hexdigest()
    print(f"\nStolen hash from database: {stolen_hash}")
    
    # Check if it's in our rainbow table
    for pwd, hash_val in common_passwords.items():
        if hash_val == stolen_hash:
            print(f"FOUND! Password is: {pwd}")
            break
    else:
        print("Password not found in rainbow table")
    
    print("\nNow with salt:")
    # Hash with salt
    salt, salted_hash = hash_password_basic("password")
    print(f"Salted hash: {salted_hash.hex()}")
    print(f"Salt: {salt.hex()}")
    
    # Try to find in rainbow table
    found = False
    for pwd, hash_val in common_passwords.items():
        if hash_val == salted_hash.hex():
            print(f"FOUND! Password is: {pwd}")
            found = True
            break
    
    if not found:
        print("Password NOT found in rainbow table!")
        print("Salt prevents rainbow table attacks!")


def timing_attack_demo():
    """
    Demonstrate timing attacks and how constant-time comparison prevents them.
    """
    print("\n" + "=" * 60)
    print("TIMING ATTACK DEMONSTRATION")
    print("=" * 60)
    
    # Create a vulnerable comparison function
    def vulnerable_compare(a: bytes, b: bytes) -> bool:
        """Vulnerable to timing attacks."""
        if len(a) != len(b):
            return False
        for i in range(len(a)):
            if a[i] != b[i]:
                return False
        return True
    
    # Test data
    correct_hash = b"correct_hash_value"
    wrong_hash = b"wrong_hash_value_"
    
    # Measure timing differences
    print("Timing vulnerable comparison:")
    
    # Time correct comparison
    start_time = time.time()
    for _ in range(10000):
        vulnerable_compare(correct_hash, correct_hash)
    correct_time = time.time() - start_time
    
    # Time wrong comparison
    start_time = time.time()
    for _ in range(10000):
        vulnerable_compare(correct_hash, wrong_hash)
    wrong_time = time.time() - start_time
    
    print(f"Correct comparison time: {correct_time:.6f}s")
    print(f"Wrong comparison time: {wrong_time:.6f}s")
    print(f"Time difference: {abs(correct_time - wrong_time):.6f}s")
    
    print("\nTiming secure comparison:")
    
    # Time secure comparison
    start_time = time.time()
    for _ in range(10000):
        secrets.compare_digest(correct_hash, correct_hash)
    secure_correct_time = time.time() - start_time
    
    start_time = time.time()
    for _ in range(10000):
        secrets.compare_digest(correct_hash, wrong_hash)
    secure_wrong_time = time.time() - start_time
    
    print(f"Secure correct comparison time: {secure_correct_time:.6f}s")
    print(f"Secure wrong comparison time: {secure_wrong_time:.6f}s")
    print(f"Time difference: {abs(secure_correct_time - secure_wrong_time):.6f}s")
    
    print("\nNote: secrets.compare_digest() prevents timing attacks")


def password_strength_analysis():
    """
    Analyze password strength and demonstrate brute force resistance.
    """
    print("\n" + "=" * 60)
    print("PASSWORD STRENGTH ANALYSIS")
    print("=" * 60)
    
    # Test passwords of different strengths
    test_passwords = [
        "123",           # Very weak
        "password",      # Weak
        "Password123",   # Medium
        "P@ssw0rd123!",  # Strong
        "correct horse battery staple",  # Passphrase
    ]
    
    print("Password strength analysis:")
    print("-" * 40)
    
    for pwd in test_passwords:
        # Calculate entropy (simplified)
        charset_size = 0
        if any(c.islower() for c in pwd):
            charset_size += 26  # lowercase
        if any(c.isupper() for c in pwd):
            charset_size += 26  # uppercase
        if any(c.isdigit() for c in pwd):
            charset_size += 10  # digits
        if any(c in "!@#$%^&*()_+-=[]{}|;:,.<>?" for c in pwd):
            charset_size += 32  # special chars
        
        entropy = len(pwd) * (charset_size ** 0.5) if charset_size > 0 else 0
        
        print(f"Password: {pwd}")
        print(f"Length: {len(pwd)}, Charset: {charset_size}, Entropy: {entropy:.1f}")
        
        # Time to hash
        start_time = time.time()
        salt, hash_val = hash_password_basic(pwd)
        hash_time = time.time() - start_time
        
        print(f"Hash time: {hash_time:.4f}s")
        print()
    
    print("Brute force resistance:")
    print("• Weak passwords can be cracked quickly")
    print("• Strong passwords take much longer to crack")
    print("• Salt makes precomputed attacks impossible")
    print("• High iteration count slows down brute force")


def best_practices_summary():
    """
    Summarize best practices for password hashing.
    """
    print("\n" + "=" * 60)
    print("PASSWORD HASHING BEST PRACTICES")
    print("=" * 60)
    
    print("✓ DO:")
    print("  • Use salt (unique for each password)")
    print("  • Use slow hash functions (PBKDF2, bcrypt, scrypt, Argon2)")
    print("  • Use sufficient iterations/work factor")
    print("  • Use cryptographically secure random number generators")
    print("  • Use constant-time comparison for verification")
    print("  • Store salt alongside the hash")
    print("  • Use established libraries (don't implement yourself)")
    
    print("\n✗ DON'T:")
    print("  • Store plaintext passwords")
    print("  • Use fast hash functions (MD5, SHA-1, SHA-256)")
    print("  • Use the same salt for all passwords")
    print("  • Use predictable salts")
    print("  • Use too few iterations")
    print("  • Implement your own password hashing")
    
    print("\nRecommended algorithms:")
    print("  • Argon2 (winner of Password Hashing Competition)")
    print("  • bcrypt (widely used, battle-tested)")
    print("  • scrypt (memory-hard function)")
    print("  • PBKDF2 (if others not available)")
    
    print("\nIteration recommendations:")
    print("  • PBKDF2: 100,000+ iterations")
    print("  • bcrypt: cost factor 12+")
    print("  • scrypt: N=16384, r=8, p=1")
    print("  • Argon2: time=3, memory=65536, parallelism=4")


if __name__ == "__main__":
    # Run all demonstrations
    demonstrate_password_hashing()
    demonstrate_salt_importance()
    rainbow_table_attack_demo()
    timing_attack_demo()
    password_strength_analysis()
    best_practices_summary()
    
    print("\n" + "=" * 60)
    print("EDUCATIONAL SUMMARY")
    print("=" * 60)
    print("Password hashing is critical for application security:")
    print("• Prevents password theft even if database is compromised")
    print("• Salt prevents rainbow table attacks")
    print("• Slow hash functions prevent brute force attacks")
    print("• Constant-time comparison prevents timing attacks")
    print("\nAlways use established libraries and follow security best practices!")
    print("Never implement password hashing from scratch!")
