"""
Problem: Substrings That Begin and End With the Same Letter
Difficulty: Medium
Tags: array, string, math, hash

Approach: Count substrings by tracking first and last occurrence of each character
Time Complexity: O(n) where n is string length
Space Complexity: O(1)
"""

from collections import defaultdict

class Solution:
    def numberOfSubstrings(self, s: str) -> int:
        count = defaultdict(int)
        result = 0
        
        for i, char in enumerate(s):
            # All substrings ending at i that start with same char
            # Count how many times this char appeared before
            result += count[char]
            count[char] += 1
        
        # Add single character substrings
        result += len(s)
        
        return result