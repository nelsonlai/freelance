"""
Problem: Matrix Diagonal Sum
Difficulty: Easy
Tags: array

Approach: Sum main diagonal and anti-diagonal, subtract center if odd-sized matrix
Time Complexity: O(n) where n is matrix size
Space Complexity: O(1)
"""

class Solution:
    def diagonalSum(self, mat: List[List[int]]) -> int:
        n = len(mat)
        result = 0
        
        for i in range(n):
            result += mat[i][i]
            result += mat[i][n - 1 - i]
        
        if n % 2 == 1:
            result -= mat[n // 2][n // 2]
        
        return result