"""
Problem: Number of Different Integers in a String
Difficulty: Easy
Tags: string, hash

Approach: Extract all integers, remove leading zeros, count unique
Time Complexity: O(n) where n is length
Space Complexity: O(n)
"""

import re

class Solution:
    def numDifferentIntegers(self, word: str) -> int:
        integers = re.findall(r'\d+', word)
        normalized = set(int(num) for num in integers)
        return len(normalized)