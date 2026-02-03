"""
Problem: Lucky Numbers in a Matrix
Difficulty: Easy
Tags: array

Approach: Find min in each row, check if it's max in its column
Time Complexity: O(m * n) where m, n are matrix dimensions
Space Complexity: O(m + n) for row mins and col maxs
"""

class Solution:
    def luckyNumbers(self, matrix: List[List[int]]) -> List[int]:
        m, n = len(matrix), len(matrix[0])
        row_mins = [min(row) for row in matrix]
        col_maxs = [max(matrix[i][j] for i in range(m)) for j in range(n)]
        
        result = []
        for i in range(m):
            for j in range(n):
                if matrix[i][j] == row_mins[i] == col_maxs[j]:
                    result.append(matrix[i][j])
        
        return result