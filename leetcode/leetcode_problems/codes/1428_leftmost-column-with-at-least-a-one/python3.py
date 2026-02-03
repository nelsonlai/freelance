"""
Problem: Leftmost Column with at Least a One
Difficulty: Medium
Tags: array, sort, search

Approach: Start from top-right, move left if 1, down if 0
Time Complexity: O(rows + cols)
Space Complexity: O(1)
"""

# """
# This is BinaryMatrix's API interface.
# You should not implement it, or speculate about its implementation
# """
#class BinaryMatrix(object):
#    def get(self, row: int, col: int) -> int:
#    def dimensions(self) -> list[]:

class Solution:
    def leftMostColumnWithOne(self, binaryMatrix: 'BinaryMatrix') -> int:
        rows, cols = binaryMatrix.dimensions()
        row, col = 0, cols - 1
        result = -1
        
        while row < rows and col >= 0:
            if binaryMatrix.get(row, col) == 1:
                result = col
                col -= 1
            else:
                row += 1
        
        return result