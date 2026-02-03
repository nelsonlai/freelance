"""
Cryptanalysis - Timing Attack

This module demonstrates timing attacks, which exploit timing differences
in cryptographic operations to recover secret information. Timing attacks
are a type of side-channel attack that can be used to break cryptographic
systems even when the underlying algorithms are secure.

Key Concepts:
- Timing Attack: Exploits timing differences in operations
- Side-Channel Attack: Uses information leaked through system behavior
- Constant-Time Implementation: Operations that take the same time regardless of input
- Timing Analysis: Statistical analysis of timing differences
- Power Analysis: Related side-channel attack using power consumption

Security Implications:
- Can break cryptographic systems with timing vulnerabilities
- Exploits implementation flaws, not algorithm weaknesses
- Demonstrates importance of constant-time implementations
- Shows why secure coding practices are essential

Author: Cryptography Lecture
Date: 2024
"""

import time
import secrets
import statistics
import random
from typing import List, Tuple, Optional


class VulnerableComparison:
    """
    A vulnerable comparison function that leaks timing information.
    
    This function compares two strings byte by byte and returns False
    as soon as it finds a difference. This creates timing differences
    that can be exploited by attackers.
    """
    
    @staticmethod
    def insecure_compare(a: bytes, b: bytes) -> bool:
        """
        Insecure string comparison that leaks timing information.
        
        This function is vulnerable to timing attacks because it returns
        False as soon as it finds a difference, making comparisons with
        more matching bytes take longer.
        
        Args:
            a (bytes): First string to compare
            b (bytes): Second string to compare
        
        Returns:
            bool: True if strings are equal, False otherwise
        """
        if len(a) != len(b):
            return False
        
        for i in range(len(a)):
            if a[i] != b[i]:
                return False
        
        return True


class SecureComparison:
    """
    A secure comparison function that doesn't leak timing information.
    
    This function uses constant-time comparison to prevent timing attacks.
    """
    
    @staticmethod
    def secure_compare(a: bytes, b: bytes) -> bool:
        """
        Secure string comparison that doesn't leak timing information.
        
        This function uses constant-time comparison to prevent timing
        attacks by always performing the same operations regardless
        of the input values.
        
        Args:
            a (bytes): First string to compare
            b (bytes): Second string to compare
        
        Returns:
            bool: True if strings are equal, False otherwise
        """
        return secrets.compare_digest(a, b)


class TimingAttacker:
    """
    An attacker that exploits timing vulnerabilities.
    
    This class implements timing attack techniques to recover secret
    information by analyzing timing differences.
    """
    
    def __init__(self, comparison_function):
        """
        Initialize the attacker with a comparison function.
        
        Args:
            comparison_function: The comparison function to attack
        """
        self.comparison_function = comparison_function
    
    def measure_comparison_time(self, target: bytes, guess: bytes, 
                               iterations: int = 1000) -> float:
        """
        Measure the average time for a comparison operation.
        
        Args:
            target (bytes): The target string
            guess (bytes): The guess string
            iterations (int): Number of iterations to average
        
        Returns:
            float: Average comparison time in seconds
        """
        times = []
        
        for _ in range(iterations):
            start_time = time.perf_counter()
            self.comparison_function(target, guess)
            end_time = time.perf_counter()
            times.append(end_time - start_time)
        
        return statistics.mean(times)
    
    def attack_byte(self, target: bytes, known_bytes: bytes, 
                   byte_position: int, iterations: int = 1000) -> int:
        """
        Attack a single byte using timing analysis.
        
        Args:
            target (bytes): The target string
            known_bytes (bytes): Bytes already known
            byte_position (int): Position of the byte to attack
            iterations (int): Number of iterations for timing
        
        Returns:
            int: The recovered byte value
        """
        best_byte = 0
        best_time = 0
        
        # Try all possible byte values
        for byte_value in range(256):
            # Create guess with known bytes and current guess
            guess = bytearray(len(target))
            for i in range(len(known_bytes)):
                guess[i] = known_bytes[i]
            guess[byte_position] = byte_value
            
            # Measure comparison time
            avg_time = self.measure_comparison_time(target, bytes(guess), iterations)
            
            # Keep track of the byte with the longest comparison time
            if avg_time > best_time:
                best_time = avg_time
                best_byte = byte_value
        
        return best_byte
    
    def attack_string(self, target: bytes, iterations: int = 1000) -> bytes:
        """
        Attack a complete string using timing analysis.
        
        Args:
            target (bytes): The target string to recover
            iterations (int): Number of iterations for timing
        
        Returns:
            bytes: The recovered string
        """
        recovered = bytearray(len(target))
        
        # Attack each byte from left to right
        for byte_position in range(len(target)):
            print(f"Attacking byte {byte_position}...")
            
            # Attack this byte
            recovered_byte = self.attack_byte(target, bytes(recovered), 
                                            byte_position, iterations)
            recovered[byte_position] = recovered_byte
            
            print(f"Recovered byte {byte_position}: 0x{recovered_byte:02x} "
                  f"('{chr(recovered_byte) if 32 <= recovered_byte <= 126 else '.'}')")
        
        return bytes(recovered)


def demonstrate_timing_attack():
    """
    Demonstrate a timing attack on vulnerable string comparison.
    """
    print("=" * 60)
    print("TIMING ATTACK DEMONSTRATION")
    print("=" * 60)
    
    # Create a secret string
    secret = b"SecretPassword123"
    print(f"Secret string: {secret.decode()}")
    print(f"Secret length: {len(secret)} bytes")
    
    print("\n" + "-" * 40)
    
    # Demonstrate timing differences
    print("Timing Differences:")
    
    # Test with different numbers of matching bytes
    test_strings = [
        b"X",  # 0 matching bytes
        b"S",  # 1 matching byte
        b"Se",  # 2 matching bytes
        b"Sec",  # 3 matching bytes
        b"Secr",  # 4 matching bytes
        b"Secret",  # 6 matching bytes
    ]
    
    print("String | Matching Bytes | Average Time (ms)")
    print("-" * 40)
    
    for test_string in test_strings:
        times = []
        for _ in range(1000):
            start_time = time.perf_counter()
            VulnerableComparison.insecure_compare(secret, test_string)
            end_time = time.perf_counter()
            times.append(end_time - start_time)
        
        avg_time = statistics.mean(times) * 1000  # Convert to milliseconds
        matching_bytes = sum(1 for i in range(min(len(secret), len(test_string)))
                            if secret[i] == test_string[i])
        
        print(f"{test_string.decode():<6} | {matching_bytes:13d} | {avg_time:15.4f}")
    
    print("\nNotice: More matching bytes = longer comparison time!")
    
    print("\n" + "-" * 40)
    
    # Perform the attack
    print("Performing Timing Attack:")
    
    attacker = TimingAttacker(VulnerableComparison.insecure_compare)
    
    start_time = time.time()
    recovered = attacker.attack_string(secret, iterations=500)
    attack_time = time.time() - start_time
    
    print(f"\nAttack completed in {attack_time:.2f} seconds")
    print(f"Recovered string: {recovered.decode()}")
    print(f"Attack successful: {secret == recovered}")


def demonstrate_secure_comparison():
    """
    Demonstrate secure comparison that prevents timing attacks.
    """
    print("\n" + "=" * 60)
    print("SECURE COMPARISON DEMONSTRATION")
    print("=" * 60)
    
    # Test secure comparison
    secret = b"SecretPassword123"
    test_strings = [
        b"X",  # 0 matching bytes
        b"S",  # 1 matching byte
        b"Se",  # 2 matching bytes
        b"Sec",  # 3 matching bytes
        b"Secr",  # 4 matching bytes
        b"Secret",  # 6 matching bytes
    ]
    
    print("String | Matching Bytes | Average Time (ms)")
    print("-" * 40)
    
    for test_string in test_strings:
        times = []
        for _ in range(1000):
            start_time = time.perf_counter()
            SecureComparison.secure_compare(secret, test_string)
            end_time = time.perf_counter()
            times.append(end_time - start_time)
        
        avg_time = statistics.mean(times) * 1000  # Convert to milliseconds
        matching_bytes = sum(1 for i in range(min(len(secret), len(test_string)))
                            if secret[i] == test_string[i])
        
        print(f"{test_string.decode():<6} | {matching_bytes:13d} | {avg_time:15.4f}")
    
    print("\nNotice: All comparisons take approximately the same time!")
    print("No timing information is leaked.")
    
    print("\n" + "-" * 40)
    
    # Try to attack secure comparison
    print("Attempting Timing Attack on Secure Comparison:")
    
    attacker = TimingAttacker(SecureComparison.secure_compare)
    
    # Try to attack just the first byte
    print("Attacking first byte...")
    
    best_byte = 0
    best_time = 0
    
    for byte_value in range(256):
        guess = bytes([byte_value])
        avg_time = attacker.measure_comparison_time(secret, guess, iterations=1000)
        
        if avg_time > best_time:
            best_time = avg_time
            best_byte = byte_value
    
    print(f"Best guess for first byte: 0x{best_byte:02x} "
          f"('{chr(best_byte) if 32 <= best_byte <= 126 else '.'}')")
    print(f"Actual first byte: 0x{secret[0]:02x} "
          f"('{chr(secret[0]) if 32 <= secret[0] <= 126 else '.'}')")
    print(f"Attack successful: {best_byte == secret[0]}")
    
    if best_byte != secret[0]:
        print("Secure comparison prevented the timing attack!")


def demonstrate_timing_attack_variations():
    """
    Demonstrate different variations of timing attacks.
    """
    print("\n" + "-" * 40)
    print("TIMING ATTACK VARIATIONS")
    print("-" * 40)
    
    print("1. Password Verification Attack:")
    print("   • Attack password verification systems")
    print("   • Exploit timing differences in password comparison")
    print("   • Can recover passwords character by character")
    
    print("\n2. HMAC Verification Attack:")
    print("   • Attack HMAC verification in web applications")
    print("   • Exploit timing differences in MAC comparison")
    print("   • Can recover HMAC keys")
    
    print("\n3. RSA Decryption Attack:")
    print("   • Attack RSA decryption implementations")
    print("   • Exploit timing differences in modular exponentiation")
    print("   • Can recover RSA private keys")
    
    print("\n4. AES Key Schedule Attack:")
    print("   • Attack AES key schedule generation")
    print("   • Exploit timing differences in key expansion")
    print("   • Can recover AES keys")
    
    print("\n" + "-" * 40)
    
    # Demonstrate HMAC timing attack
    print("HMAC Timing Attack Simulation:")
    
    import hmac
    import hashlib
    
    secret_key = b"secret_hmac_key"
    message = b"important_message"
    
    # Create HMAC
    correct_hmac = hmac.new(secret_key, message, hashlib.sha256).digest()
    print(f"Correct HMAC: {correct_hmac.hex()}")
    
    # Simulate vulnerable HMAC verification
    def vulnerable_hmac_verify(message: bytes, received_hmac: bytes) -> bool:
        """Vulnerable HMAC verification that leaks timing information."""
        expected_hmac = hmac.new(secret_key, message, hashlib.sha256).digest()
        return VulnerableComparison.insecure_compare(expected_hmac, received_hmac)
    
    # Test timing differences
    test_hmacs = [
        b"X" * 32,  # Wrong HMAC
        correct_hmac[:1] + b"X" * 31,  # 1 byte correct
        correct_hmac[:2] + b"X" * 30,  # 2 bytes correct
        correct_hmac[:4] + b"X" * 28,  # 4 bytes correct
        correct_hmac[:8] + b"X" * 24,  # 8 bytes correct
    ]
    
    print("\nHMAC | Correct Bytes | Average Time (ms)")
    print("-" * 40)
    
    for test_hmac in test_hmacs:
        times = []
        for _ in range(1000):
            start_time = time.perf_counter()
            vulnerable_hmac_verify(message, test_hmac)
            end_time = time.perf_counter()
            times.append(end_time - start_time)
        
        avg_time = statistics.mean(times) * 1000
        correct_bytes = sum(1 for i in range(min(len(correct_hmac), len(test_hmac)))
                          if correct_hmac[i] == test_hmac[i])
        
        print(f"{test_hmac.hex()[:8]}... | {correct_bytes:11d} | {avg_time:15.4f}")
    
    print("\nNotice: More correct bytes = longer verification time!")


def demonstrate_timing_attack_prevention():
    """
    Demonstrate how to prevent timing attacks.
    """
    print("\n" + "=" * 60)
    print("TIMING ATTACK PREVENTION")
    print("=" * 60)
    
    print("Prevention Strategies:")
    print("-" * 40)
    
    print("1. Constant-Time Implementations:")
    print("   • Always perform the same operations")
    print("   • Use constant-time comparison functions")
    print("   • Avoid early termination on errors")
    print("   • Use lookup tables instead of conditional branches")
    
    print("\n2. Random Delays:")
    print("   • Add random delays to operations")
    print("   • Make timing differences unpredictable")
    print("   • Use exponential backoff")
    print("   • Add noise to timing measurements")
    
    print("\n3. Rate Limiting:")
    print("   • Limit the number of attempts")
    print("   • Implement exponential backoff")
    print("   • Monitor for suspicious patterns")
    print("   • Use CAPTCHAs for repeated failures")
    
    print("\n4. Hardware Solutions:")
    print("   • Use hardware security modules")
    print("   • Use constant-time hardware instructions")
    print("   • Use secure enclaves")
    print("   • Use dedicated cryptographic hardware")
    
    print("\n" + "-" * 40)
    
    # Demonstrate constant-time implementation
    print("Constant-Time Implementation Example:")
    
    def constant_time_compare(a: bytes, b: bytes) -> bool:
        """
        Constant-time string comparison.
        """
        if len(a) != len(b):
            return False
        
        result = 0
        for i in range(len(a)):
            result |= a[i] ^ b[i]
        
        return result == 0
    
    # Test constant-time comparison
    secret = b"SecretPassword123"
    test_strings = [
        b"X",  # 0 matching bytes
        b"S",  # 1 matching byte
        b"Se",  # 2 matching bytes
        b"Sec",  # 3 matching bytes
        b"Secr",  # 4 matching bytes
        b"Secret",  # 6 matching bytes
    ]
    
    print("\nString | Matching Bytes | Average Time (ms)")
    print("-" * 40)
    
    for test_string in test_strings:
        times = []
        for _ in range(1000):
            start_time = time.perf_counter()
            constant_time_compare(secret, test_string)
            end_time = time.perf_counter()
            times.append(end_time - start_time)
        
        avg_time = statistics.mean(times) * 1000
        matching_bytes = sum(1 for i in range(min(len(secret), len(test_string)))
                            if secret[i] == test_string[i])
        
        print(f"{test_string.decode():<6} | {matching_bytes:13d} | {avg_time:15.4f}")
    
    print("\nNotice: All comparisons take approximately the same time!")
    
    print("\n" + "-" * 40)
    
    # Demonstrate random delays
    print("Random Delay Example:")
    
    def delayed_compare(a: bytes, b: bytes) -> bool:
        """
        Comparison with random delay to prevent timing attacks.
        """
        # Add random delay
        delay = random.uniform(0.001, 0.005)  # 1-5ms delay
        time.sleep(delay)
        
        # Perform comparison
        return secrets.compare_digest(a, b)
    
    # Test delayed comparison
    secret = b"SecretPassword123"
    test_strings = [b"X", b"S", b"Se", b"Sec", b"Secr", b"Secret"]
    
    print("\nString | Matching Bytes | Average Time (ms)")
    print("-" * 40)
    
    for test_string in test_strings:
        times = []
        for _ in range(100):  # Fewer iterations due to delays
            start_time = time.perf_counter()
            delayed_compare(secret, test_string)
            end_time = time.perf_counter()
            times.append(end_time - start_time)
        
        avg_time = statistics.mean(times) * 1000
        matching_bytes = sum(1 for i in range(min(len(secret), len(test_string)))
                            if secret[i] == test_string[i])
        
        print(f"{test_string.decode():<6} | {matching_bytes:13d} | {avg_time:15.4f}")
    
    print("\nNotice: Random delays make timing differences unpredictable!")


def practical_timing_attack_examples():
    """
    Show practical examples of timing attacks.
    """
    print("\n" + "=" * 60)
    print("PRACTICAL TIMING ATTACK EXAMPLES")
    print("=" * 60)
    
    print("Real-World Examples:")
    print("-" * 40)
    
    print("1. Web Application Login:")
    print("   • Attack password verification systems")
    print("   • Exploit timing differences in password comparison")
    print("   • Can recover user passwords")
    
    print("\n2. API Authentication:")
    print("   • Attack HMAC verification in APIs")
    print("   • Exploit timing differences in signature verification")
    print("   • Can recover API keys")
    
    print("\n3. Database Encryption:")
    print("   • Attack encrypted database queries")
    print("   • Exploit timing differences in key validation")
    print("   • Can recover encryption keys")
    
    print("\n4. File System Encryption:")
    print("   • Attack encrypted file systems")
    print("   • Exploit timing differences in key derivation")
    print("   • Can recover file encryption keys")
    
    print("\n" + "-" * 40)
    
    # Simulate a vulnerable web application
    print("Vulnerable Web Application Simulation:")
    
    def vulnerable_login(username: str, password: str) -> bool:
        """
        Simulate a vulnerable login system.
        """
        # Simulate database lookup
        stored_password = b"user_password_123"
        
        # Vulnerable password comparison
        return VulnerableComparison.insecure_compare(
            password.encode(), stored_password
        )
    
    # Test timing differences
    test_passwords = [
        "X",  # 0 matching bytes
        "u",  # 1 matching byte
        "us",  # 2 matching bytes
        "use",  # 3 matching bytes
        "user",  # 4 matching bytes
        "user_",  # 5 matching bytes
    ]
    
    print("\nPassword | Matching Bytes | Average Time (ms)")
    print("-" * 40)
    
    for test_password in test_passwords:
        times = []
        for _ in range(1000):
            start_time = time.perf_counter()
            vulnerable_login("user", test_password)
            end_time = time.perf_counter()
            times.append(end_time - start_time)
        
        avg_time = statistics.mean(times) * 1000
        stored_password = b"user_password_123"
        matching_bytes = sum(1 for i in range(min(len(stored_password), len(test_password)))
                            if stored_password[i] == test_password.encode()[i])
        
        print(f"{test_password:<8} | {matching_bytes:13d} | {avg_time:15.4f}")
    
    print("\nWARNING: This login system is vulnerable to timing attacks!")
    print("An attacker could recover the password character by character.")


if __name__ == "__main__":
    # Run all demonstrations
    demonstrate_timing_attack()
    demonstrate_secure_comparison()
    demonstrate_timing_attack_variations()
    demonstrate_timing_attack_prevention()
    practical_timing_attack_examples()
    
    print("\n" + "=" * 60)
    print("EDUCATIONAL SUMMARY")
    print("=" * 60)
    print("Timing attacks exploit implementation vulnerabilities:")
    print("• Not algorithm weaknesses, but implementation flaws")
    print("• Exploit timing differences in operations")
    print("• Can recover secret information")
    print("• Demonstrate importance of constant-time implementations")
    print("\nPrevention strategies:")
    print("• Use constant-time comparison functions")
    print("• Implement random delays")
    print("• Use rate limiting")
    print("• Use hardware security modules")
    print("• Monitor for suspicious patterns")
    print("\nTiming attacks show why secure coding practices are essential!")
