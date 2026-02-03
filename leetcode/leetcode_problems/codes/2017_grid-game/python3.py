"""
Problem: Grid Game
Difficulty: Medium
Tags: array

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def gridGame(self, grid: List[List[int]]) -> int:
        n = len(grid[0])
        top_sum = sum(grid[0])
        bottom_sum = 0
        result = float('inf')
        
        for i in range(n):
            top_sum -= grid[0][i]
            result = min(result, max(top_sum, bottom_sum))
            bottom_sum += grid[1][i]
        
        return result