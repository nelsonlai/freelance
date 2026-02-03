"""
Problem: Sort the Matrix Diagonally
Difficulty: Medium
Tags: array, sort

Approach: Group elements by diagonal (i-j), sort each group, place back
Time Complexity: O(m * n * log(min(m, n)))
Space Complexity: O(m * n) for groups
"""

from collections import defaultdict

class Solution:
    def diagonalSort(self, mat: List[List[int]]) -> List[List[int]]:
        m, n = len(mat), len(mat[0])
        diagonals = defaultdict(list)
        
        for i in range(m):
            for j in range(n):
                diagonals[i - j].append(mat[i][j])
        
        for key in diagonals:
            diagonals[key].sort(reverse=True)
        
        result = [[0] * n for _ in range(m)]
        for i in range(m):
            for j in range(n):
                result[i][j] = diagonals[i - j].pop()
        
        return result