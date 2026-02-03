"""
Problem: Change Minimum Characters to Satisfy One of Three Conditions
Difficulty: Medium
Tags: array, string, hash, prefix sum

Approach: Try all three conditions, find minimum changes needed
Time Complexity: O(n + m + 26) where n, m are lengths
Space Complexity: O(26)
"""

from collections import Counter

class Solution:
    def minCharacters(self, a: str, b: str) -> int:
        freq_a = Counter(a)
        freq_b = Counter(b)
        
        # Condition 3: All characters in a < all in b (or vice versa)
        result = float('inf')
        
        # Condition 1: Every char in a < every char in b
        for c in range(ord('a'), ord('z')):
            changes = sum(freq_a[chr(i)] for i in range(c + 1, ord('z') + 1))
            changes += sum(freq_b[chr(i)] for i in range(ord('a'), c + 1))
            result = min(result, changes)
        
        # Condition 2: Every char in b < every char in a
        for c in range(ord('a'), ord('z')):
            changes = sum(freq_b[chr(i)] for i in range(c + 1, ord('z') + 1))
            changes += sum(freq_a[chr(i)] for i in range(ord('a'), c + 1))
            result = min(result, changes)
        
        # Condition 3: All same character
        for c in range(ord('a'), ord('z') + 1):
            char = chr(c)
            changes = len(a) - freq_a[char] + len(b) - freq_b[char]
            result = min(result, changes)
        
        return result