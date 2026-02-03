"""
Problem: Maximum Non Negative Product in a Matrix
Difficulty: Medium
Tags: array, dp

Approach: DP - track both min and max product to handle negative numbers
Time Complexity: O(m * n) where m, n are matrix dimensions
Space Complexity: O(m * n) for DP table
"""

MOD = 10**9 + 7

class Solution:
    def maxProductPath(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        dp_min = [[0] * n for _ in range(m)]
        dp_max = [[0] * n for _ in range(m)]
        
        dp_min[0][0] = dp_max[0][0] = grid[0][0]
        
        for i in range(1, m):
            dp_min[i][0] = dp_max[i][0] = dp_min[i-1][0] * grid[i][0]
        
        for j in range(1, n):
            dp_min[0][j] = dp_max[0][j] = dp_min[0][j-1] * grid[0][j]
        
        for i in range(1, m):
            for j in range(1, n):
                val = grid[i][j]
                candidates = [
                    dp_min[i-1][j] * val,
                    dp_max[i-1][j] * val,
                    dp_min[i][j-1] * val,
                    dp_max[i][j-1] * val
                ]
                dp_min[i][j] = min(candidates)
                dp_max[i][j] = max(candidates)
        
        return dp_max[m-1][n-1] % MOD if dp_max[m-1][n-1] >= 0 else -1