"""
Problem: Scramble String
Difficulty: Hard
Tags: string, tree, dp

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

from functools import lru_cache

class Solution:
    @lru_cache(maxsize=None)
    def isScramble(self, s1: str, s2: str) -> bool:
        if s1 == s2:
            return True
        if len(s1) != len(s2) or sorted(s1) != sorted(s2):
            return False
        
        n = len(s1)
        for i in range(1, n):
            if (self.isScramble(s1[:i], s2[:i]) and self.isScramble(s1[i:], s2[i:])) or \
               (self.isScramble(s1[:i], s2[n-i:]) and self.isScramble(s1[i:], s2[:n-i])):
                return True
        
        return False