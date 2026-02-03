"""
Problem: Minimum Falling Path Sum
Difficulty: Medium
Tags: array, dp

Approach: Dynamic programming - for each cell, take minimum from three possible paths above
Time Complexity: O(n * m) where n and m are dimensions
Space Complexity: O(1) by modifying input matrix, or O(m) with separate array
"""

class Solution:
    def minFallingPathSum(self, matrix: List[List[int]]) -> int:
        n = len(matrix)
        m = len(matrix[0])
        
        for i in range(1, n):
            for j in range(m):
                min_prev = matrix[i-1][j]
                if j > 0:
                    min_prev = min(min_prev, matrix[i-1][j-1])
                if j < m - 1:
                    min_prev = min(min_prev, matrix[i-1][j+1])
                matrix[i][j] += min_prev
        
        return min(matrix[n-1])