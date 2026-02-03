"""
Problem: Range Sum Query 2D - Mutable
Difficulty: Medium
Tags: array, tree

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

class NumMatrix:

    def __init__(self, matrix: List[List[int]]):
        if not matrix or not matrix[0]:
            return
        
        self.m = len(matrix)
        self.n = len(matrix[0])
        self.matrix = matrix
        self.bit = [[0] * (self.n + 1) for _ in range(self.m + 1)]
        
        for i in range(self.m):
            for j in range(self.n):
                self.updateBIT(i, j, matrix[i][j])

    def updateBIT(self, row, col, delta):
        i = row + 1
        while i <= self.m:
            j = col + 1
            while j <= self.n:
                self.bit[i][j] += delta
                j += j & -j
            i += i & -i

    def queryBIT(self, row, col):
        total = 0
        i = row + 1
        while i > 0:
            j = col + 1
            while j > 0:
                total += self.bit[i][j]
                j -= j & -j
            i -= i & -i
        return total

    def update(self, row: int, col: int, val: int) -> None:
        delta = val - self.matrix[row][col]
        self.matrix[row][col] = val
        self.updateBIT(row, col, delta)

    def sumRegion(self, row1: int, col1: int, row2: int, col2: int) -> int:
        return (self.queryBIT(row2, col2) - 
                self.queryBIT(row1 - 1, col2) - 
                self.queryBIT(row2, col1 - 1) + 
                self.queryBIT(row1 - 1, col1 - 1))