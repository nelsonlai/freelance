"""
Problem: Special Positions in a Binary Matrix
Difficulty: Easy
Tags: array

Approach: Count 1s in each row and column, check positions where row and column both have exactly 1
Time Complexity: O(m * n) where m, n are matrix dimensions
Space Complexity: O(m + n) for row and column counts
"""

class Solution:
    def numSpecial(self, mat: List[List[int]]) -> int:
        m, n = len(mat), len(mat[0])
        row_count = [0] * m
        col_count = [0] * n
        
        for i in range(m):
            for j in range(n):
                if mat[i][j] == 1:
                    row_count[i] += 1
                    col_count[j] += 1
        
        result = 0
        for i in range(m):
            for j in range(n):
                if mat[i][j] == 1 and row_count[i] == 1 and col_count[j] == 1:
                    result += 1
        
        return result