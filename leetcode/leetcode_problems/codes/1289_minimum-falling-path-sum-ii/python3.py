"""
Problem: Minimum Falling Path Sum II
Difficulty: Hard
Tags: array, dp

Approach: DP - track min and second min from previous row to avoid same column
Time Complexity: O(n^2) where n is grid size
Space Complexity: O(n) using rolling array
"""

class Solution:
    def minFallingPathSum(self, grid: List[List[int]]) -> int:
        n = len(grid)
        prev = grid[0][:]
        
        for i in range(1, n):
            # Find min and second min in previous row
            min1, min2 = float('inf'), float('inf')
            idx1 = -1
            for j in range(n):
                if prev[j] < min1:
                    min2 = min1
                    min1 = prev[j]
                    idx1 = j
                elif prev[j] < min2:
                    min2 = prev[j]
            
            # Calculate current row
            curr = [0] * n
            for j in range(n):
                if j != idx1:
                    curr[j] = grid[i][j] + min1
                else:
                    curr[j] = grid[i][j] + min2
            prev = curr
        
        return min(prev)