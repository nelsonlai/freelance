"""
Problem: Shift 2D Grid
Difficulty: Easy
Tags: array

Approach: Flatten grid, shift, then reshape
Time Complexity: O(m * n) where m, n are grid dimensions
Space Complexity: O(m * n) for result
"""

class Solution:
    def shiftGrid(self, grid: List[List[int]], k: int) -> List[List[int]]:
        m, n = len(grid), len(grid[0])
        total = m * n
        k %= total
        
        # Flatten grid
        flat = [grid[i][j] for i in range(m) for j in range(n)]
        
        # Shift
        flat = flat[-k:] + flat[:-k]
        
        # Reshape
        result = []
        for i in range(m):
            result.append(flat[i * n:(i + 1) * n])
        
        return result