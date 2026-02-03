"""
Problem: Check Whether Two Strings are Almost Equivalent
Difficulty: Easy
Tags: string, hash

Approach: Count character frequencies and check if difference <= 3 for all characters
Time Complexity: O(n + m) where n, m are string lengths
Space Complexity: O(26)
"""

from collections import Counter

class Solution:
    def checkAlmostEquivalent(self, word1: str, word2: str) -> bool:
        count1 = Counter(word1)
        count2 = Counter(word2)
        
        all_chars = set(count1.keys()) | set(count2.keys())
        
        for char in all_chars:
            diff = abs(count1[char] - count2[char])
            if diff > 3:
                return False
        
        return True