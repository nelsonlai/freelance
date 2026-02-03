"""
Problem: Can I Win
Difficulty: Medium
Tags: dp, math

Approach: Dynamic programming with memoization or tabulation
Time Complexity: O(n * m) where n and m are problem dimensions
Space Complexity: O(n) or O(n * m) for DP table
"""

from functools import lru_cache

class Solution:
    def canIWin(self, maxChoosableInteger: int, desiredTotal: int) -> bool:
        if desiredTotal <= maxChoosableInteger:
            return True
        if sum(range(1, maxChoosableInteger + 1)) < desiredTotal:
            return False
        
        @lru_cache(None)
        def can_win(used, remaining):
            for i in range(1, maxChoosableInteger + 1):
                if not (used & (1 << i)):
                    if i >= remaining or not can_win(used | (1 << i), remaining - i):
                        return True
            return False
        
        return can_win(0, desiredTotal)