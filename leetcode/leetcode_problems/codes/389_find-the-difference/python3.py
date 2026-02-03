"""
Problem: Find the Difference
Difficulty: Easy
Tags: string, hash, sort

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import Counter

class Solution:
    def findTheDifference(self, s: str, t: str) -> str:
        s_count = Counter(s)
        t_count = Counter(t)
        
        for char in t_count:
            if t_count[char] > s_count[char]:
                return char
        return ""