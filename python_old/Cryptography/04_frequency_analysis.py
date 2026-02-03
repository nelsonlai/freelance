"""
Classical Cryptography - Frequency Analysis Tools

This module provides tools for analyzing letter frequencies in text, which is
a fundamental technique for breaking classical substitution ciphers. Frequency
analysis exploits the fact that different letters appear with different
frequencies in natural language.

Frequency analysis is one of the oldest and most effective methods for
breaking monoalphabetic substitution ciphers, as it reveals the underlying
statistical patterns in the encrypted text.

Author: Cryptography Lecture
Date: 2024
"""

from collections import Counter
from typing import Dict, List, Tuple
import matplotlib.pyplot as plt
import numpy as np


# Standard English letter frequencies (approximate percentages)
ENGLISH_FREQUENCIES = {
    'E': 12.7, 'T': 9.1, 'A': 8.2, 'O': 7.5, 'I': 7.0, 'N': 6.7,
    'S': 6.3, 'H': 6.1, 'R': 6.0, 'D': 4.3, 'L': 4.0, 'C': 2.8,
    'U': 2.8, 'M': 2.4, 'W': 2.4, 'F': 2.2, 'G': 2.0, 'Y': 2.0,
    'P': 1.9, 'B': 1.3, 'V': 1.0, 'K': 0.8, 'J': 0.15, 'X': 0.15,
    'Q': 0.10, 'Z': 0.07
}


def clean_text(text: str) -> str:
    """
    Clean text for frequency analysis by removing non-alphabetic characters
    and converting to uppercase.
    
    Args:
        text (str): The input text to clean
    
    Returns:
        str: Cleaned text containing only uppercase letters
        
    Example:
        >>> clean_text("Hello, World! 123")
        'HELLOWORLD'
    """
    # Remove all non-alphabetic characters and convert to uppercase
    return ''.join(char.upper() for char in text if char.isalpha())


def calculate_frequencies(text: str) -> Dict[str, float]:
    """
    Calculate the frequency of each letter in the given text.
    
    Args:
        text (str): The text to analyze
    
    Returns:
        Dict[str, float]: Dictionary mapping letters to their frequency percentages
        
    Example:
        >>> freqs = calculate_frequencies("HELLO")
        >>> freqs['L']
        40.0
    """
    # Clean the text first
    clean = clean_text(text)
    
    if not clean:
        return {}
    
    # Count occurrences of each letter
    letter_counts = Counter(clean)
    total_letters = len(clean)
    
    # Calculate percentages
    frequencies = {}
    for letter, count in letter_counts.items():
        frequencies[letter] = (count / total_letters) * 100
    
    return frequencies


def get_sorted_frequencies(text: str) -> List[Tuple[str, float]]:
    """
    Get letter frequencies sorted by frequency (highest first).
    
    Args:
        text (str): The text to analyze
    
    Returns:
        List[Tuple[str, float]]: List of (letter, frequency) tuples sorted by frequency
        
    Example:
        >>> freqs = get_sorted_frequencies("HELLO")
        >>> freqs[0]
        ('L', 40.0)
    """
    frequencies = calculate_frequencies(text)
    return sorted(frequencies.items(), key=lambda x: x[1], reverse=True)


def frequency_analysis(text: str) -> List[Tuple[str, float]]:
    """
    Perform frequency analysis on the given text.
    
    This is an alias for get_sorted_frequencies() for compatibility
    with the lecture examples.
    
    Args:
        text (str): The text to analyze
    
    Returns:
        List[Tuple[str, float]]: List of (letter, frequency) tuples sorted by frequency
    """
    return get_sorted_frequencies(text)


def compare_with_english(text: str) -> Dict[str, Tuple[float, float]]:
    """
    Compare the letter frequencies in the text with standard English frequencies.
    
    Args:
        text (str): The text to analyze
    
    Returns:
        Dict[str, Tuple[float, float]]: Dictionary mapping letters to (text_freq, english_freq) tuples
        
    Example:
        >>> comparison = compare_with_english("HELLO")
        >>> comparison['E']
        (0.0, 12.7)  # E appears 0% in "HELLO" but 12.7% in English
    """
    text_frequencies = calculate_frequencies(text)
    comparison = {}
    
    # Compare frequencies for all letters that appear in the text
    for letter in text_frequencies:
        comparison[letter] = (
            text_frequencies[letter],
            ENGLISH_FREQUENCIES.get(letter, 0.0)
        )
    
    return comparison


def chi_squared_test(text: str) -> float:
    """
    Perform a chi-squared test to measure how well the text matches English letter frequencies.
    
    The chi-squared test measures the difference between observed and expected frequencies.
    Lower values indicate better match with English.
    
    Args:
        text (str): The text to test
    
    Returns:
        float: The chi-squared statistic
        
    Example:
        >>> chi_squared_test("HELLO WORLD")
        45.2  # Higher values indicate less English-like text
    """
    text_frequencies = calculate_frequencies(text)
    clean = clean_text(text)
    total_letters = len(clean)
    
    chi_squared = 0.0
    
    # Calculate chi-squared for each letter
    for letter in ENGLISH_FREQUENCIES:
        observed = text_frequencies.get(letter, 0.0)
        expected = ENGLISH_FREQUENCIES[letter]
        
        # Convert percentages to counts
        observed_count = (observed / 100.0) * total_letters
        expected_count = (expected / 100.0) * total_letters
        
        if expected_count > 0:
            chi_squared += ((observed_count - expected_count) ** 2) / expected_count
    
    return chi_squared


def frequency_attack_caesar(ciphertext: str) -> Tuple[str, int]:
    """
    Attempt to break a Caesar cipher using frequency analysis.
    
    This function tries all possible shifts and selects the one that produces
    text most similar to English based on letter frequencies.
    
    Args:
        ciphertext (str): The encrypted message
    
    Returns:
        Tuple[str, int]: (decrypted_text, shift_used)
        
    Example:
        >>> ciphertext = "KHOOR ZRUOG"
        >>> decrypted, shift = frequency_attack_caesar(ciphertext)
        >>> print(f"Decrypted: {decrypted}, Shift: {shift}")
        Decrypted: HELLO WORLD, Shift: 3
    """
    best_decryption = ""
    best_shift = 0
    best_score = float('inf')
    
    # Try all possible shifts (0-25)
    for shift in range(26):
        # Decrypt with current shift
        decrypted = ""
        for char in ciphertext.upper():
            if char.isalpha():
                # Apply inverse Caesar shift
                ascii_offset = ord('A')
                shifted = (ord(char) - ascii_offset - shift) % 26
                decrypted += chr(shifted + ascii_offset)
            else:
                decrypted += char
        
        # Calculate chi-squared score (lower is better)
        score = chi_squared_test(decrypted)
        
        if score < best_score:
            best_score = score
            best_shift = shift
            best_decryption = decrypted
    
    return best_decryption, best_shift


def frequency_attack_monoalphabetic(ciphertext: str) -> Dict[str, str]:
    """
    Attempt to break a monoalphabetic substitution cipher using frequency analysis.
    
    This function maps the most frequent ciphertext letters to the most frequent
    English letters based on statistical analysis.
    
    Args:
        ciphertext (str): The encrypted message
    
    Returns:
        Dict[str, str]: Dictionary mapping ciphertext letters to likely plaintext letters
        
    Example:
        >>> ciphertext = "ITSSG"
        >>> mapping = frequency_attack_monoalphabetic(ciphertext)
        >>> print(mapping)
        {'I': 'H', 'T': 'E', 'S': 'L', 'G': 'O'}
    """
    # Get ciphertext frequencies
    cipher_frequencies = get_sorted_frequencies(ciphertext)
    
    # Get English frequencies sorted by frequency
    english_frequencies = sorted(ENGLISH_FREQUENCIES.items(), key=lambda x: x[1], reverse=True)
    
    # Create mapping based on frequency matching
    mapping = {}
    min_length = min(len(cipher_frequencies), len(english_frequencies))
    
    for i in range(min_length):
        cipher_letter = cipher_frequencies[i][0]
        english_letter = english_frequencies[i][0]
        mapping[cipher_letter] = english_letter
    
    return mapping


def apply_substitution_mapping(text: str, mapping: Dict[str, str]) -> str:
    """
    Apply a substitution mapping to decrypt text.
    
    Args:
        text (str): The text to decrypt
        mapping (Dict[str, str]): Dictionary mapping ciphertext to plaintext letters
    
    Returns:
        str: The decrypted text
        
    Example:
        >>> mapping = {'I': 'H', 'T': 'E', 'S': 'L', 'G': 'O'}
        >>> apply_substitution_mapping("ITSSG", mapping)
        'HELLO'
    """
    result = ""
    for char in text.upper():
        if char.isalpha():
            result += mapping.get(char, char)  # Use mapping or keep original if not found
        else:
            result += char
    return result


def plot_frequency_comparison(text: str, title: str = "Letter Frequency Analysis"):
    """
    Create a bar chart comparing text frequencies with English frequencies.
    
    Args:
        text (str): The text to analyze
        title (str): Title for the plot
    """
    text_frequencies = calculate_frequencies(text)
    
    # Get all letters that appear in either text or English
    all_letters = set(text_frequencies.keys()) | set(ENGLISH_FREQUENCIES.keys())
    all_letters = sorted(all_letters)
    
    # Prepare data for plotting
    text_freqs = [text_frequencies.get(letter, 0) for letter in all_letters]
    english_freqs = [ENGLISH_FREQUENCIES.get(letter, 0) for letter in all_letters]
    
    # Create the plot
    x = np.arange(len(all_letters))
    width = 0.35
    
    fig, ax = plt.subplots(figsize=(12, 6))
    bars1 = ax.bar(x - width/2, text_freqs, width, label='Text Frequencies', alpha=0.8)
    bars2 = ax.bar(x + width/2, english_freqs, width, label='English Frequencies', alpha=0.8)
    
    ax.set_xlabel('Letters')
    ax.set_ylabel('Frequency (%)')
    ax.set_title(title)
    ax.set_xticks(x)
    ax.set_xticklabels(all_letters)
    ax.legend()
    
    plt.tight_layout()
    plt.show()


def demonstrate_frequency_analysis():
    """
    Demonstrate frequency analysis with various examples.
    """
    print("=" * 60)
    print("FREQUENCY ANALYSIS DEMONSTRATION")
    print("=" * 60)
    
    # Example 1: Analyze a simple text
    sample_text = "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG"
    print(f"Sample text: {sample_text}")
    
    frequencies = get_sorted_frequencies(sample_text)
    print("\nLetter frequencies:")
    for letter, freq in frequencies:
        print(f"{letter}: {freq:5.2f}%")
    
    print("\n" + "-" * 40)
    
    # Example 2: Compare with English
    comparison = compare_with_english(sample_text)
    print("Comparison with English frequencies:")
    print("Letter | Text % | English % | Difference")
    print("-" * 40)
    for letter, (text_freq, english_freq) in sorted(comparison.items()):
        diff = abs(text_freq - english_freq)
        print(f"{letter:6s} | {text_freq:6.2f} | {english_freq:8.2f} | {diff:8.2f}")
    
    print("\n" + "-" * 40)
    
    # Example 3: Chi-squared test
    chi_squared = chi_squared_test(sample_text)
    print(f"Chi-squared test result: {chi_squared:.2f}")
    print("(Lower values indicate better match with English)")
    
    print("\n" + "-" * 40)
    
    # Example 4: Frequency attack on Caesar cipher
    print("Frequency attack on Caesar cipher:")
    original = "HELLO WORLD"
    encrypted = ""
    shift = 7
    
    # Encrypt
    for char in original:
        if char.isalpha():
            encrypted += chr((ord(char.upper()) - ord('A') + shift) % 26 + ord('A'))
        else:
            encrypted += char
    
    print(f"Original: {original}")
    print(f"Encrypted (shift {shift}): {encrypted}")
    
    # Attack
    decrypted, found_shift = frequency_attack_caesar(encrypted)
    print(f"Decrypted: {decrypted}")
    print(f"Found shift: {found_shift}")
    print(f"Attack successful: {original == decrypted}")


def demonstrate_monoalphabetic_attack():
    """
    Demonstrate frequency attack on monoalphabetic substitution.
    """
    print("\n" + "=" * 60)
    print("MONOALPHABETIC SUBSTITUTION ATTACK")
    print("=" * 60)
    
    # Create a simple substitution cipher
    plaintext = "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG"
    substitution_key = "QWERTYUIOPASDFGHJKLZXCVBNM"
    
    # Encrypt
    ciphertext = ""
    for char in plaintext.upper():
        if char.isalpha():
            index = ord(char) - ord('A')
            ciphertext += substitution_key[index]
        else:
            ciphertext += char
    
    print(f"Plaintext: {plaintext}")
    print(f"Ciphertext: {ciphertext}")
    
    # Perform frequency attack
    mapping = frequency_attack_monoalphabetic(ciphertext)
    print(f"\nFrequency-based mapping:")
    for cipher_char, plain_char in mapping.items():
        print(f"{cipher_char} -> {plain_char}")
    
    # Apply mapping
    decrypted = apply_substitution_mapping(ciphertext, mapping)
    print(f"\nDecrypted: {decrypted}")
    
    # Show accuracy
    correct_mappings = 0
    total_mappings = len(mapping)
    for cipher_char, plain_char in mapping.items():
        original_index = ord(cipher_char) - ord('A')
        if substitution_key[original_index] == cipher_char:
            expected_plain = chr(original_index + ord('A'))
            if plain_char == expected_plain:
                correct_mappings += 1
    
    accuracy = (correct_mappings / total_mappings) * 100 if total_mappings > 0 else 0
    print(f"Mapping accuracy: {accuracy:.1f}%")


if __name__ == "__main__":
    # Run demonstrations
    demonstrate_frequency_analysis()
    demonstrate_monoalphabetic_attack()
    
    print("\n" + "=" * 60)
    print("EDUCATIONAL NOTE")
    print("=" * 60)
    print("Frequency analysis is a powerful tool for breaking classical")
    print("substitution ciphers. It exploits the statistical properties")
    print("of natural language and demonstrates why classical ciphers are")
    print("insecure for modern cryptographic applications.")
    print("\nModern ciphers use techniques like confusion and diffusion")
    print("to prevent frequency analysis attacks.")
