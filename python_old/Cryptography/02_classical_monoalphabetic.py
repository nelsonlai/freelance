"""
Classical Cryptography - Monoalphabetic Substitution Cipher

This module demonstrates monoalphabetic substitution ciphers, where each
letter in the plaintext is replaced by exactly one other letter throughout
the entire message. This is more secure than the Caesar cipher but still
vulnerable to frequency analysis.

Security Note: While more secure than Caesar cipher, monoalphabetic substitution
ciphers are still extremely weak and vulnerable to frequency analysis attacks.
They should NEVER be used for real-world security applications.

Author: Cryptography Lecture
Date: 2024
"""

import random
import string
from typing import Optional


def generate_random_key() -> str:
    """
    Generate a random monoalphabetic substitution key.
    
    This function creates a random permutation of the alphabet by:
    1. Creating a list of all uppercase letters
    2. Shuffling the list randomly
    3. Joining the shuffled letters into a string
    
    Returns:
        str: A 26-character string representing the substitution key
        
    Example:
        >>> key = generate_random_key()
        >>> len(key)
        26
        >>> set(key) == set(string.ascii_uppercase)
        True
    """
    # Create a list of all uppercase letters
    alphabet = list(string.ascii_uppercase)
    
    # Shuffle the alphabet randomly
    random.shuffle(alphabet)
    
    # Join the shuffled letters into a substitution key
    return ''.join(alphabet)


def generate_key_from_passphrase(passphrase: str) -> str:
    """
    Generate a substitution key from a memorable passphrase.
    
    This method creates a substitution key by:
    1. Taking unique letters from the passphrase
    2. Filling in remaining letters in alphabetical order
    
    Args:
        passphrase (str): A memorable phrase to generate the key from
    
    Returns:
        str: A 26-character substitution key
        
    Example:
        >>> generate_key_from_passphrase("PREMATURE OPTIMIZATION")
        'PREMATUOIZNSHFLVBCDGJKQWXY'
    """
    # Convert to uppercase and remove spaces
    clean_phrase = passphrase.upper().replace(' ', '')
    
    # Get unique letters in order of first appearance
    unique_letters = []
    seen = set()
    for char in clean_phrase:
        if char.isalpha() and char not in seen:
            unique_letters.append(char)
            seen.add(char)
    
    # Add remaining letters in alphabetical order
    for char in string.ascii_uppercase:
        if char not in seen:
            unique_letters.append(char)
    
    return ''.join(unique_letters)


def monoalphabetic_substitution(text: str, key: Optional[str] = None) -> str:
    """
    Encrypt text using monoalphabetic substitution.
    
    Each letter in the plaintext is replaced by the corresponding letter
    in the substitution key. For example, if the key is "QWERTYUIOPASDFGHJKLZXCVBNM":
    - A becomes Q
    - B becomes W
    - C becomes E
    - etc.
    
    Args:
        text (str): The plaintext to encrypt
        key (str, optional): The substitution key (26 letters). If None,
                            a random key will be generated
    
    Returns:
        str: The encrypted ciphertext
        
    Example:
        >>> key = "QWERTYUIOPASDFGHJKLZXCVBNM"
        >>> monoalphabetic_substitution("HELLO", key)
        'ITSSG'
    """
    # Generate a random key if none provided
    if key is None:
        key = generate_random_key()
    
    # Validate key length
    if len(key) != 26:
        raise ValueError("Substitution key must be exactly 26 characters long")
    
    # Validate that key contains all letters
    if set(key.upper()) != set(string.ascii_uppercase):
        raise ValueError("Substitution key must contain all 26 letters exactly once")
    
    result = ""
    
    # Process each character in the input text
    for char in text.upper():
        if char.isalpha():
            # Find the position of the character in the alphabet (0-25)
            alphabet_position = ord(char) - ord('A')
            
            # Replace with the corresponding character from the key
            result += key[alphabet_position]
        else:
            # Keep non-alphabetic characters unchanged
            result += char
    
    return result


def monoalphabetic_decrypt(ciphertext: str, key: str) -> str:
    """
    Decrypt ciphertext using monoalphabetic substitution.
    
    This function reverses the substitution by finding each ciphertext
    character in the key and replacing it with the corresponding alphabet letter.
    
    Args:
        ciphertext (str): The encrypted message
        key (str): The substitution key used for encryption
    
    Returns:
        str: The decrypted plaintext
        
    Example:
        >>> key = "QWERTYUIOPASDFGHJKLZXCVBNM"
        >>> ciphertext = "ITSSG"
        >>> monoalphabetic_decrypt(ciphertext, key)
        'HELLO'
    """
    result = ""
    
    # Process each character in the ciphertext
    for char in ciphertext.upper():
        if char.isalpha():
            # Find the position of the character in the key
            key_position = key.find(char)
            
            if key_position != -1:
                # Replace with the corresponding alphabet letter
                result += chr(key_position + ord('A'))
            else:
                # Character not found in key (shouldn't happen with valid key)
                result += char
        else:
            # Keep non-alphabetic characters unchanged
            result += char
    
    return result


def demonstrate_monoalphabetic_cipher():
    """
    Demonstrate monoalphabetic substitution with various examples.
    """
    print("=" * 60)
    print("MONOALPHABETIC SUBSTITUTION CIPHER DEMONSTRATION")
    print("=" * 60)
    
    # Example 1: Random key
    plaintext = "ATTACKATDAWN"
    random_key = generate_random_key()
    
    print(f"Plaintext: {plaintext}")
    print(f"Random key: {random_key}")
    
    ciphertext = monoalphabetic_substitution(plaintext, random_key)
    print(f"Ciphertext: {ciphertext}")
    
    decrypted = monoalphabetic_decrypt(ciphertext, random_key)
    print(f"Decrypted: {decrypted}")
    print(f"Encryption successful: {plaintext == decrypted}")
    
    print("\n" + "-" * 40)
    
    # Example 2: Passphrase-based key
    passphrase = "PREMATURE OPTIMIZATION IS THE ROOT OF ALL EVIL"
    passphrase_key = generate_key_from_passphrase(passphrase)
    
    print(f"Passphrase: {passphrase}")
    print(f"Generated key: {passphrase_key}")
    
    message = "HELLO WORLD"
    encrypted = monoalphabetic_substitution(message, passphrase_key)
    print(f"Message: {message}")
    print(f"Encrypted: {encrypted}")
    
    decrypted_message = monoalphabetic_decrypt(encrypted, passphrase_key)
    print(f"Decrypted: {decrypted_message}")
    
    print("\n" + "-" * 40)
    
    # Example 3: Show substitution mapping
    print("Substitution mapping:")
    print("Plaintext alphabet:  ABCDEFGHIJKLMNOPQRSTUVWXYZ")
    print(f"Substitution key:    {passphrase_key}")
    
    # Show a few examples
    examples = ["A", "B", "C", "Z"]
    print("\nExample substitutions:")
    for letter in examples:
        encrypted_letter = monoalphabetic_substitution(letter, passphrase_key)
        print(f"{letter} -> {encrypted_letter}")


def analyze_monoalphabetic_security():
    """
    Analyze the security properties of monoalphabetic substitution.
    """
    print("\n" + "=" * 60)
    print("MONOALPHABETIC SUBSTITUTION SECURITY ANALYSIS")
    print("=" * 60)
    
    print("Security Properties:")
    print("✓ Confusion: Each letter maps to exactly one other letter")
    print("✗ Diffusion: Letter frequencies are preserved")
    print("✗ Key space: Only 26! ≈ 4 × 10²⁶ possible keys")
    print("✗ Vulnerable to frequency analysis")
    print("✗ Vulnerable to known plaintext attacks")
    print("✗ Vulnerable to pattern analysis")
    
    print("\nAttack Methods:")
    print("1. Frequency Analysis:")
    print("   - Compare letter frequencies in ciphertext to English")
    print("   - Most frequent ciphertext letter likely corresponds to 'E'")
    print("   - Use statistical analysis to break the cipher")
    
    print("\n2. Known Plaintext Attack:")
    print("   - If attacker knows some plaintext-ciphertext pairs")
    print("   - Can directly determine parts of the substitution key")
    
    print("\n3. Pattern Analysis:")
    print("   - Look for common English patterns (THE, AND, etc.)")
    print("   - Use word length patterns and common letter combinations")
    
    print("\n4. Brute Force:")
    print("   - Try all possible substitution keys")
    print("   - Computationally feasible for short messages")


def frequency_analysis_demo():
    """
    Demonstrate how frequency analysis can break monoalphabetic substitution.
    """
    print("\n" + "=" * 60)
    print("FREQUENCY ANALYSIS DEMONSTRATION")
    print("=" * 60)
    
    # English letter frequencies (approximate percentages)
    english_frequencies = {
        'E': 12.7, 'T': 9.1, 'A': 8.2, 'O': 7.5, 'I': 7.0, 'N': 6.7,
        'S': 6.3, 'H': 6.1, 'R': 6.0, 'D': 4.3, 'L': 4.0, 'C': 2.8,
        'U': 2.8, 'M': 2.4, 'W': 2.4, 'F': 2.2, 'G': 2.0, 'Y': 2.0,
        'P': 1.9, 'B': 1.3, 'V': 1.0, 'K': 0.8, 'J': 0.15, 'X': 0.15,
        'Q': 0.10, 'Z': 0.07
    }
    
    print("English letter frequencies:")
    for letter, freq in sorted(english_frequencies.items(), key=lambda x: x[1], reverse=True):
        print(f"{letter}: {freq:5.1f}%")
    
    print("\nNote: Frequency analysis works best with longer texts")
    print("Short messages may not follow typical frequency patterns")


if __name__ == "__main__":
    # Run demonstrations
    demonstrate_monoalphabetic_cipher()
    analyze_monoalphabetic_security()
    frequency_analysis_demo()
    
    print("\n" + "=" * 60)
    print("EDUCATIONAL NOTE")
    print("=" * 60)
    print("Monoalphabetic substitution ciphers are included here for")
    print("educational purposes only. While more secure than Caesar cipher,")
    print("they are still extremely vulnerable to frequency analysis and")
    print("should NEVER be used for real-world data protection!")
