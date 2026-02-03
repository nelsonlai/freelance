"""
Problem: Vowels of All Substrings
Difficulty: Medium
Tags: string, math, combinatorics

Approach: For each vowel at index i, count how many substrings contain it
Time Complexity: O(n) where n is string length
Space Complexity: O(1)
"""

class Solution:
    def countVowels(self, word: str) -> int:
        vowels = {'a', 'e', 'i', 'o', 'u'}
        n = len(word)
        result = 0
        
        for i, char in enumerate(word):
            if char in vowels:
                # Number of substrings containing this vowel
                # Left choices: i + 1, Right choices: n - i
                result += (i + 1) * (n - i)
        
        return result