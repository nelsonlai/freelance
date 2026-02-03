"""
Problem: Count Fertile Pyramids in a Land
Difficulty: Hard
Tags: array, dp

Approach: DP to count pyramids (both normal and inverted)
Time Complexity: O(m * n) where m, n are grid dimensions
Space Complexity: O(m * n)
"""

class Solution:
    def countPyramids(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        
        def countPyramidType(is_inverted):
            dp = [[0] * n for _ in range(m)]
            result = 0
            
            if is_inverted:
                # Inverted pyramids: start from top
                for i in range(m):
                    for j in range(n):
                        if grid[i][j] == 1:
                            if i == 0:
                                dp[i][j] = 1
                            else:
                                if j > 0 and j < n - 1:
                                    dp[i][j] = min(dp[i-1][j-1], dp[i-1][j], dp[i-1][j+1]) + 1
                                else:
                                    dp[i][j] = 1
                            if dp[i][j] > 1:
                                result += dp[i][j] - 1
            else:
                # Normal pyramids: start from bottom
                for i in range(m - 1, -1, -1):
                    for j in range(n):
                        if grid[i][j] == 1:
                            if i == m - 1:
                                dp[i][j] = 1
                            else:
                                if j > 0 and j < n - 1:
                                    dp[i][j] = min(dp[i+1][j-1], dp[i+1][j], dp[i+1][j+1]) + 1
                                else:
                                    dp[i][j] = 1
                            if dp[i][j] > 1:
                                result += dp[i][j] - 1
            
            return result
        
        return countPyramidType(False) + countPyramidType(True)