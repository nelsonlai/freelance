"""
Problem: First Unique Character in a String
Difficulty: Easy
Tags: string, hash, queue

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import Counter

class Solution:
    def firstUniqChar(self, s: str) -> int:
        count = Counter(s)
        for i, char in enumerate(s):
            if count[char] == 1:
                return i
        return -1