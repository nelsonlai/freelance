"""
Problem: Sparse Matrix Multiplication
Difficulty: Medium
Tags: array, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import defaultdict

class Solution:
    def multiply(self, mat1: List[List[int]], mat2: List[List[int]]) -> List[List[int]]:
        m, k, n = len(mat1), len(mat1[0]), len(mat2[0])
        
        sparse1 = defaultdict(dict)
        for i in range(m):
            for j in range(k):
                if mat1[i][j] != 0:
                    sparse1[i][j] = mat1[i][j]
        
        sparse2 = defaultdict(dict)
        for i in range(k):
            for j in range(n):
                if mat2[i][j] != 0:
                    sparse2[i][j] = mat2[i][j]
        
        result = [[0] * n for _ in range(m)]
        
        for i in sparse1:
            for j in sparse1[i]:
                if j in sparse2:
                    for k in sparse2[j]:
                        result[i][k] += sparse1[i][j] * sparse2[j][k]
        
        return result