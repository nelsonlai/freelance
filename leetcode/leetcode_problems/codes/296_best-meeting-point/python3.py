"""
Problem: Best Meeting Point
Difficulty: Hard
Tags: array, math, sort

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def minTotalDistance(self, grid: List[List[int]]) -> int:
        rows = []
        cols = []
        
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] == 1:
                    rows.append(i)
                    cols.append(j)
        
        cols.sort()
        row_median = rows[len(rows) // 2]
        col_median = cols[len(cols) // 2]
        
        distance = 0
        for row in rows:
            distance += abs(row - row_median)
        for col in cols:
            distance += abs(col - col_median)
        
        return distance