"""
Problem: Largest Submatrix With Rearrangements
Difficulty: Medium
Tags: array, greedy, sort

Approach: Calculate consecutive ones per column, sort each row, find max area
Time Complexity: O(m * n log n) where m is rows, n is columns
Space Complexity: O(n)
"""

class Solution:
    def largestSubmatrix(self, matrix: List[List[int]]) -> int:
        m, n = len(matrix), len(matrix[0])
        
        # Calculate consecutive ones from top
        for i in range(1, m):
            for j in range(n):
                if matrix[i][j] == 1:
                    matrix[i][j] += matrix[i-1][j]
        
        result = 0
        
        # For each row, sort and calculate max area
        for i in range(m):
            row = sorted(matrix[i], reverse=True)
            for j in range(n):
                result = max(result, row[j] * (j + 1))
        
        return result