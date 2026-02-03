"""
Problem: Find Valid Matrix Given Row and Column Sums
Difficulty: Medium
Tags: array, greedy

Approach: Greedy - for each cell, assign min(rowSum[i], colSum[j]), update both
Time Complexity: O(m * n) where m, n are dimensions
Space Complexity: O(m * n) for result matrix
"""

class Solution:
    def restoreMatrix(self, rowSum: List[int], colSum: List[int]) -> List[List[int]]:
        m, n = len(rowSum), len(colSum)
        matrix = [[0] * n for _ in range(m)]
        
        for i in range(m):
            for j in range(n):
                val = min(rowSum[i], colSum[j])
                matrix[i][j] = val
                rowSum[i] -= val
                colSum[j] -= val
        
        return matrix