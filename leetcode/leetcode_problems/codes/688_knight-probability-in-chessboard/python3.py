"""
Problem: Knight Probability in Chessboard
Difficulty: Medium
Tags: dp

Approach: Dynamic programming with memoization or tabulation
Time Complexity: O(n * m) where n and m are problem dimensions
Space Complexity: O(n) or O(n * m) for DP table
"""

from functools import lru_cache

class Solution:
    def knightProbability(self, n: int, k: int, row: int, column: int) -> float:
        @lru_cache(None)
        def dp(moves, r, c):
            if r < 0 or r >= n or c < 0 or c >= n:
                return 0
            if moves == 0:
                return 1
            
            directions = [(-2, -1), (-2, 1), (-1, -2), (-1, 2),
                         (1, -2), (1, 2), (2, -1), (2, 1)]
            
            total = 0
            for dr, dc in directions:
                total += dp(moves - 1, r + dr, c + dc)
            
            return total / 8.0
        
        return dp(k, row, column)