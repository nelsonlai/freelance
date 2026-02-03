"""
Problem: Integer Replacement
Difficulty: Medium
Tags: dp, greedy

Approach: Dynamic programming with memoization or tabulation
Time Complexity: O(n * m) where n and m are problem dimensions
Space Complexity: O(n) or O(n * m) for DP table
"""

from functools import lru_cache

class Solution:
    @lru_cache(None)
    def integerReplacement(self, n: int) -> int:
        if n == 1:
            return 0
        if n % 2 == 0:
            return 1 + self.integerReplacement(n // 2)
        return 1 + min(self.integerReplacement(n + 1), self.integerReplacement(n - 1))