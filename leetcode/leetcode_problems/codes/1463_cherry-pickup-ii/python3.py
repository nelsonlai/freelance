"""
Problem: Cherry Pickup II
Difficulty: Hard
Tags: array, dp

Approach: DP - dp[row][col1][col2] = max cherries with robots at (row, col1) and (row, col2)
Time Complexity: O(rows * cols^2) where rows, cols are grid dimensions
Space Complexity: O(rows * cols^2) for DP table
"""

class Solution:
    def cherryPickup(self, grid: List[List[int]]) -> int:
        rows, cols = len(grid), len(grid[0])
        dp = [[[float('-inf')] * cols for _ in range(cols)] for _ in range(rows)]
        dp[0][0][cols-1] = grid[0][0] + grid[0][cols-1]
        
        for row in range(1, rows):
            for col1 in range(cols):
                for col2 in range(cols):
                    for d1 in [-1, 0, 1]:
                        for d2 in [-1, 0, 1]:
                            prev_col1 = col1 - d1
                            prev_col2 = col2 - d2
                            if 0 <= prev_col1 < cols and 0 <= prev_col2 < cols:
                                cherries = grid[row][col1]
                                if col1 != col2:
                                    cherries += grid[row][col2]
                                dp[row][col1][col2] = max(
                                    dp[row][col1][col2],
                                    dp[row-1][prev_col1][prev_col2] + cherries
                                )
        
        return max(max(row) for row in dp[rows-1])