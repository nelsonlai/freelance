"""
Problem: Subrectangle Queries
Difficulty: Medium
Tags: array

Approach: Store rectangle, update values in range for updateSubrectangle
Time Complexity: O(rows * cols) for update, O(1) for getValue
Space Complexity: O(rows * cols) for rectangle
"""

class SubrectangleQueries:

    def __init__(self, rectangle: List[List[int]]):
        self.rect = rectangle

    def updateSubrectangle(self, row1: int, col1: int, row2: int, col2: int, newValue: int) -> None:
        for i in range(row1, row2 + 1):
            for j in range(col1, col2 + 1):
                self.rect[i][j] = newValue

    def getValue(self, row: int, col: int) -> int:
        return self.rect[row][col]