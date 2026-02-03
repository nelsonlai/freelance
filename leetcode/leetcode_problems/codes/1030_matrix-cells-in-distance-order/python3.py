"""
Problem: Matrix Cells in Distance Order
Difficulty: Easy
Tags: array, math, sort

Approach: Generate all cells, sort by Manhattan distance from center
Time Complexity: O(rows * cols * log(rows * cols))
Space Complexity: O(rows * cols)
"""

class Solution:
    def allCellsDistOrder(self, rows: int, cols: int, rCenter: int, cCenter: int) -> List[List[int]]:
        cells = []
        for i in range(rows):
            for j in range(cols):
                cells.append([i, j])
        
        cells.sort(key=lambda x: abs(x[0] - rCenter) + abs(x[1] - cCenter))
        return cells