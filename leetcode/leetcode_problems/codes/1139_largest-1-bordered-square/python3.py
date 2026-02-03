"""
Problem: Largest 1-Bordered Square
Difficulty: Medium
Tags: array, dp

Approach: DP - precompute horizontal and vertical consecutive 1s, check all possible squares
Time Complexity: O(m * n * min(m, n)) where m, n are grid dimensions
Space Complexity: O(m * n) for DP tables
"""

class Solution:
    def largest1BorderedSquare(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        hor = [[0] * n for _ in range(m)]
        ver = [[0] * n for _ in range(m)]
        
        # Precompute horizontal and vertical consecutive 1s
        for i in range(m):
            for j in range(n):
                if grid[i][j] == 1:
                    hor[i][j] = hor[i][j-1] + 1 if j > 0 else 1
                    ver[i][j] = ver[i-1][j] + 1 if i > 0 else 1
        
        max_size = 0
        for i in range(m):
            for j in range(n):
                if grid[i][j] == 1:
                    size = min(hor[i][j], ver[i][j])
                    while size > max_size:
                        if hor[i-size+1][j] >= size and ver[i][j-size+1] >= size:
                            max_size = size
                            break
                        size -= 1
        
        return max_size * max_size