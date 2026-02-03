"""
Problem: Count Negative Numbers in a Sorted Matrix
Difficulty: Easy
Tags: array, sort, search

Approach: Start from top-right, move left if negative, down if positive
Time Complexity: O(m + n) where m, n are matrix dimensions
Space Complexity: O(1)
"""

class Solution:
    def countNegatives(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        count = 0
        row, col = 0, n - 1
        
        while row < m and col >= 0:
            if grid[row][col] < 0:
                count += m - row
                col -= 1
            else:
                row += 1
        
        return count