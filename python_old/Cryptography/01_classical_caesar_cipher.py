"""
Classical Cryptography - Caesar Cipher Implementation

This module demonstrates the Caesar cipher, one of the oldest and simplest
encryption techniques. The Caesar cipher is a type of substitution cipher
where each letter in the plaintext is shifted by a fixed number of positions
down the alphabet.

Security Note: This cipher is extremely weak and should NEVER be used for
real-world security applications. It's included here for educational purposes
only to demonstrate basic cryptographic concepts.

Author: Cryptography Lecture
Date: 2024
"""

def caesar_cipher(text: str, shift: int) -> str:
    """
    Encrypt or decrypt text using the Caesar cipher.
    
    The Caesar cipher works by shifting each letter in the alphabet by a
    fixed number of positions. For example, with a shift of 3:
    - A becomes D
    - B becomes E
    - C becomes F
    - etc.
    
    Args:
        text (str): The plaintext to encrypt or ciphertext to decrypt
        shift (int): The number of positions to shift each letter
                    - Positive values encrypt (shift right)
                    - Negative values decrypt (shift left)
    
    Returns:
        str: The encrypted or decrypted text
        
    Example:
        >>> caesar_cipher("HELLO", 3)
        'KHOOR'
        >>> caesar_cipher("KHOOR", -3)
        'HELLO'
    """
    result = ""
    
    # Iterate through each character in the input text
    for char in text:
        # Only process alphabetic characters
        if char.isalpha():
            # Determine the ASCII offset based on case
            # ASCII 'A' = 65, ASCII 'a' = 97
            ascii_offset = 65 if char.isupper() else 97
            
            # Calculate the new character position
            # ord(char) gets the ASCII value of the character
            # Subtract the offset to get position in alphabet (0-25)
            # Add the shift and use modulo 26 to wrap around the alphabet
            # Add the offset back to get the new ASCII value
            shifted = (ord(char) - ascii_offset + shift) % 26
            result += chr(shifted + ascii_offset)
        else:
            # Keep non-alphabetic characters unchanged
            result += char
    
    return result


def caesar_encrypt(plaintext: str, key: int) -> str:
    """
    Encrypt plaintext using Caesar cipher.
    
    Args:
        plaintext (str): The message to encrypt
        key (int): The encryption key (shift value)
    
    Returns:
        str: The encrypted ciphertext
    """
    return caesar_cipher(plaintext, key)


def caesar_decrypt(ciphertext: str, key: int) -> str:
    """
    Decrypt ciphertext using Caesar cipher.
    
    Args:
        ciphertext (str): The encrypted message
        key (int): The decryption key (shift value)
    
    Returns:
        str: The decrypted plaintext
    """
    return caesar_cipher(ciphertext, -key)


def demonstrate_caesar_cipher():
    """
    Demonstrate the Caesar cipher with various examples.
    """
    print("=" * 50)
    print("CAESAR CIPHER DEMONSTRATION")
    print("=" * 50)
    
    # Example 1: Basic encryption
    plaintext = "ATTACKATDAWN"
    key = 5
    
    print(f"Plaintext: {plaintext}")
    print(f"Key (shift): {key}")
    
    ciphertext = caesar_encrypt(plaintext, key)
    print(f"Ciphertext: {ciphertext}")
    
    decrypted = caesar_decrypt(ciphertext, key)
    print(f"Decrypted: {decrypted}")
    print(f"Encryption successful: {plaintext == decrypted}")
    
    print("\n" + "-" * 30)
    
    # Example 2: Case sensitivity
    mixed_case = "Hello World!"
    print(f"Mixed case plaintext: {mixed_case}")
    encrypted_mixed = caesar_encrypt(mixed_case, 7)
    print(f"Encrypted: {encrypted_mixed}")
    decrypted_mixed = caesar_decrypt(encrypted_mixed, 7)
    print(f"Decrypted: {decrypted_mixed}")
    
    print("\n" + "-" * 30)
    
    # Example 3: Different keys
    message = "SECRET MESSAGE"
    keys = [1, 13, 25]
    
    print(f"Original message: {message}")
    for key in keys:
        encrypted = caesar_encrypt(message, key)
        print(f"Key {key:2d}: {encrypted}")


def analyze_caesar_security():
    """
    Analyze the security weaknesses of the Caesar cipher.
    """
    print("\n" + "=" * 50)
    print("CAESAR CIPHER SECURITY ANALYSIS")
    print("=" * 50)
    
    print("Security Weaknesses:")
    print("1. Only 25 possible keys (shift 0-25)")
    print("2. Vulnerable to brute force attack")
    print("3. Vulnerable to frequency analysis")
    print("4. No confusion or diffusion properties")
    print("5. Preserves letter patterns and word boundaries")
    
    print("\nBrute Force Attack Demonstration:")
    ciphertext = "KHOOR ZRUOG"
    print(f"Ciphertext: {ciphertext}")
    print("Trying all possible keys:")
    
    for key in range(26):
        decrypted = caesar_decrypt(ciphertext, key)
        print(f"Key {key:2d}: {decrypted}")


if __name__ == "__main__":
    # Run demonstrations
    demonstrate_caesar_cipher()
    analyze_caesar_security()
    
    print("\n" + "=" * 50)
    print("EDUCATIONAL NOTE")
    print("=" * 50)
    print("The Caesar cipher is included here for educational purposes only.")
    print("It demonstrates basic substitution cipher concepts but is")
    print("completely insecure for real-world applications.")
    print("Never use this cipher for actual data protection!")
