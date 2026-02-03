"""
Problem: Out of Boundary Paths
Difficulty: Medium
Tags: dp

Approach: Dynamic programming with memoization or tabulation
Time Complexity: O(n * m) where n and m are problem dimensions
Space Complexity: O(n) or O(n * m) for DP table
"""

from functools import lru_cache

class Solution:
    def findPaths(self, m: int, n: int, maxMove: int, startRow: int, startColumn: int) -> int:
        MOD = 10**9 + 7
        
        @lru_cache(None)
        def dp(moves, row, col):
            if row < 0 or row >= m or col < 0 or col >= n:
                return 1
            if moves == 0:
                return 0
            
            result = 0
            for dx, dy in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
                result = (result + dp(moves - 1, row + dx, col + dy)) % MOD
            
            return result
        
        return dp(maxMove, startRow, startColumn)