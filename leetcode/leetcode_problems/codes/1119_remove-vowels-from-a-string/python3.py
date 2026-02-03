"""
Problem: Remove Vowels from a String
Difficulty: Easy
Tags: string

Approach: Filter out vowels using set lookup
Time Complexity: O(n) where n is the length of the string
Space Complexity: O(n) for the result string
"""

class Solution:
    def removeVowels(self, s: str) -> str:
        vowels = {'a', 'e', 'i', 'o', 'u'}
        return ''.join(char for char in s if char not in vowels)