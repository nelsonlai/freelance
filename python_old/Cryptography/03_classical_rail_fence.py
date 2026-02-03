"""
Classical Cryptography - Rail Fence Cipher (Transposition Cipher)

This module demonstrates the Rail Fence cipher, a type of transposition cipher
where the plaintext is written in a zigzag pattern along multiple "rails" and
then read row by row to create the ciphertext.

Transposition ciphers rearrange the characters of the plaintext without
changing the characters themselves, unlike substitution ciphers which
replace characters with different ones.

Security Note: Transposition ciphers are generally more secure than simple
substitution ciphers but are still vulnerable to various attacks and should
not be used for real-world security applications.

Author: Cryptography Lecture
Date: 2024
"""

from typing import List


def rail_fence_encrypt(text: str, rails: int) -> str:
    """
    Encrypt text using the Rail Fence cipher.
    
    The Rail Fence cipher works by:
    1. Writing the plaintext in a zigzag pattern across multiple rails
    2. Reading the text row by row to create the ciphertext
    
    For example, with 3 rails and text "WEAREDISCOVEREDFLEEATONCE":
    
    W . . . E . . . C . . . R . . . L . . . T . . . E
    . E . R . D . S . O . E . E . F . E . A . O . C .
    . . A . . . I . . . V . . . D . . . E . . . N . .
    
    Reading row by row: WECRLTEERDSOEEFEAOCAIVDEN
    
    Args:
        text (str): The plaintext to encrypt
        rails (int): The number of rails (rows) to use (must be >= 2)
    
    Returns:
        str: The encrypted ciphertext
        
    Raises:
        ValueError: If rails < 2
        
    Example:
        >>> rail_fence_encrypt("HELLO", 3)
        'HOLEL'
    """
    if rails < 2:
        raise ValueError("Number of rails must be at least 2")
    
    # Remove spaces and convert to uppercase for consistency
    clean_text = text.replace(' ', '').upper()
    
    # Create a list of lists to represent the rails
    fence = [[] for _ in range(rails)]
    
    # Current rail position and direction
    rail = 0
    direction = 1  # 1 for down, -1 for up
    
    # Place each character in the appropriate rail
    for char in clean_text:
        fence[rail].append(char)
        
        # Move to the next rail
        rail += direction
        
        # Change direction when reaching the top or bottom rail
        if rail == rails - 1 or rail == 0:
            direction = -direction
    
    # Read the ciphertext by concatenating all rails
    ciphertext = ''.join([''.join(rail) for rail in fence])
    
    return ciphertext


def rail_fence_decrypt(ciphertext: str, rails: int) -> str:
    """
    Decrypt ciphertext using the Rail Fence cipher.
    
    Decryption works by:
    1. Determining the pattern of rail lengths
    2. Reconstructing the zigzag pattern
    3. Reading the characters in the original order
    
    Args:
        ciphertext (str): The encrypted message
        rails (int): The number of rails used for encryption
    
    Returns:
        str: The decrypted plaintext
        
    Example:
        >>> rail_fence_decrypt("HOLEL", 3)
        'HELLO'
    """
    if rails < 2:
        raise ValueError("Number of rails must be at least 2")
    
    # Calculate the length of each rail
    text_length = len(ciphertext)
    rail_lengths = [0] * rails
    
    # Simulate the encryption process to determine rail lengths
    rail = 0
    direction = 1
    
    for _ in range(text_length):
        rail_lengths[rail] += 1
        rail += direction
        if rail == rails - 1 or rail == 0:
            direction = -direction
    
    # Reconstruct the fence with the correct characters
    fence = [[] for _ in range(rails)]
    char_index = 0
    
    # Fill each rail with the appropriate characters
    for i in range(rails):
        fence[i] = list(ciphertext[char_index:char_index + rail_lengths[i]])
        char_index += rail_lengths[i]
    
    # Read the plaintext by following the zigzag pattern
    plaintext = ""
    rail = 0
    direction = 1
    
    for _ in range(text_length):
        if fence[rail]:
            plaintext += fence[rail].pop(0)
        rail += direction
        if rail == rails - 1 or rail == 0:
            direction = -direction
    
    return plaintext


def visualize_rail_fence(text: str, rails: int) -> str:
    """
    Create a visual representation of the Rail Fence pattern.
    
    Args:
        text (str): The text to visualize
        rails (int): The number of rails
    
    Returns:
        str: A string representation of the rail fence pattern
    """
    clean_text = text.replace(' ', '').upper()
    
    # Create a 2D grid to represent the pattern
    pattern = [['.' for _ in range(len(clean_text))] for _ in range(rails)]
    
    # Fill the pattern
    rail = 0
    direction = 1
    
    for i, char in enumerate(clean_text):
        pattern[rail][i] = char
        rail += direction
        if rail == rails - 1 or rail == 0:
            direction = -direction
    
    # Convert to string representation
    result = ""
    for row in pattern:
        result += ''.join(row) + '\n'
    
    return result


def demonstrate_rail_fence_cipher():
    """
    Demonstrate the Rail Fence cipher with various examples.
    """
    print("=" * 60)
    print("RAIL FENCE CIPHER DEMONSTRATION")
    print("=" * 60)
    
    # Example 1: Basic encryption/decryption
    plaintext = "WEAREDISCOVEREDFLEEATONCE"
    rails = 3
    
    print(f"Plaintext: {plaintext}")
    print(f"Number of rails: {rails}")
    
    # Show the visual pattern
    print("\nVisual pattern:")
    pattern = visualize_rail_fence(plaintext, rails)
    print(pattern)
    
    # Encrypt
    ciphertext = rail_fence_encrypt(plaintext, rails)
    print(f"Ciphertext: {ciphertext}")
    
    # Decrypt
    decrypted = rail_fence_decrypt(ciphertext, rails)
    print(f"Decrypted: {decrypted}")
    print(f"Encryption successful: {plaintext == decrypted}")
    
    print("\n" + "-" * 40)
    
    # Example 2: Different number of rails
    message = "HELLO WORLD"
    print(f"Message: {message}")
    
    for rails in [2, 3, 4, 5]:
        encrypted = rail_fence_encrypt(message, rails)
        decrypted = rail_fence_decrypt(encrypted, rails)
        print(f"Rails {rails}: {encrypted} -> {decrypted}")
    
    print("\n" + "-" * 40)
    
    # Example 3: Show pattern for different rails
    text = "CRYPTOGRAPHY"
    print(f"Text: {text}")
    
    for rails in [2, 3, 4]:
        print(f"\nPattern with {rails} rails:")
        pattern = visualize_rail_fence(text, rails)
        print(pattern)


def analyze_rail_fence_security():
    """
    Analyze the security properties of the Rail Fence cipher.
    """
    print("\n" + "=" * 60)
    print("RAIL FENCE CIPHER SECURITY ANALYSIS")
    print("=" * 60)
    
    print("Security Properties:")
    print("✓ Transposition: Characters are rearranged, not replaced")
    print("✓ Preserves character frequencies")
    print("✗ Vulnerable to pattern analysis")
    print("✗ Vulnerable to known plaintext attacks")
    print("✗ Limited key space (number of rails)")
    
    print("\nAttack Methods:")
    print("1. Brute Force:")
    print("   - Try all possible numbers of rails")
    print("   - For text of length n, try rails from 2 to n")
    print("   - Check if decrypted text makes sense")
    
    print("\n2. Pattern Analysis:")
    print("   - Look for common English patterns")
    print("   - Analyze character positions and relationships")
    print("   - Use statistical analysis of character distributions")
    
    print("\n3. Known Plaintext Attack:")
    print("   - If attacker knows some plaintext-ciphertext pairs")
    print("   - Can determine the number of rails used")
    print("   - Can break the entire cipher")
    
    print("\n4. Anagram Solving:")
    print("   - Rail Fence cipher creates anagrams")
    print("   - Use anagram-solving techniques")
    print("   - Combine with frequency analysis")


def brute_force_attack_demo():
    """
    Demonstrate a brute force attack on Rail Fence cipher.
    """
    print("\n" + "=" * 60)
    print("BRUTE FORCE ATTACK DEMONSTRATION")
    print("=" * 60)
    
    # Encrypt a message with unknown number of rails
    original_message = "ATTACKATDAWN"
    secret_rails = 4
    ciphertext = rail_fence_encrypt(original_message, secret_rails)
    
    print(f"Original message: {original_message}")
    print(f"Ciphertext: {ciphertext}")
    print(f"Secret number of rails: {secret_rails}")
    
    print("\nTrying all possible numbers of rails:")
    
    # Try all possible numbers of rails
    for rails in range(2, len(ciphertext) + 1):
        try:
            decrypted = rail_fence_decrypt(ciphertext, rails)
            print(f"Rails {rails:2d}: {decrypted}")
            
            # Check if this looks like English (simple heuristic)
            if decrypted == original_message:
                print(f"  *** FOUND CORRECT DECRYPTION! ***")
        except:
            print(f"Rails {rails:2d}: Error")


def combined_cipher_demo():
    """
    Demonstrate combining Rail Fence with substitution cipher.
    """
    print("\n" + "=" * 60)
    print("COMBINED CIPHER DEMONSTRATION")
    print("=" * 60)
    
    plaintext = "HELLO WORLD"
    
    # First apply Rail Fence cipher
    rail_ciphertext = rail_fence_encrypt(plaintext, 3)
    print(f"After Rail Fence: {rail_ciphertext}")
    
    # Then apply Caesar cipher
    caesar_ciphertext = ""
    for char in rail_ciphertext:
        if char.isalpha():
            caesar_ciphertext += chr((ord(char) - ord('A') + 5) % 26 + ord('A'))
        else:
            caesar_ciphertext += char
    
    print(f"After Caesar cipher: {caesar_ciphertext}")
    
    print("\nDecryption (reverse order):")
    
    # Decrypt Caesar cipher first
    caesar_decrypted = ""
    for char in caesar_ciphertext:
        if char.isalpha():
            caesar_decrypted += chr((ord(char) - ord('A') - 5) % 26 + ord('A'))
        else:
            caesar_decrypted += char
    
    print(f"After Caesar decryption: {caesar_decrypted}")
    
    # Then decrypt Rail Fence cipher
    final_decrypted = rail_fence_decrypt(caesar_decrypted, 3)
    print(f"Final decryption: {final_decrypted}")
    
    print(f"Combined cipher successful: {plaintext == final_decrypted}")


if __name__ == "__main__":
    # Run demonstrations
    demonstrate_rail_fence_cipher()
    analyze_rail_fence_security()
    brute_force_attack_demo()
    combined_cipher_demo()
    
    print("\n" + "=" * 60)
    print("EDUCATIONAL NOTE")
    print("=" * 60)
    print("The Rail Fence cipher is included here for educational purposes")
    print("to demonstrate transposition cipher concepts. While more secure")
    print("than simple substitution ciphers, it is still vulnerable to")
    print("various attacks and should NEVER be used for real-world")
    print("data protection!")
