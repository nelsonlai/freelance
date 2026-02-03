"""
Problem: Number of Submatrices That Sum to Target
Difficulty: Hard
Tags: array, hash

Approach: For each row range, compute column prefix sums and use hash map
Time Complexity: O(m^2 * n) where m and n are dimensions
Space Complexity: O(n) for hash map
"""

from collections import defaultdict

class Solution:
    def numSubmatrixSumTarget(self, matrix: List[List[int]], target: int) -> int:
        m, n = len(matrix), len(matrix[0])
        result = 0
        
        for i in range(m):
            col_sum = [0] * n
            for j in range(i, m):
                for k in range(n):
                    col_sum[k] += matrix[j][k]
                
                prefix_sum = defaultdict(int)
                prefix_sum[0] = 1
                current_sum = 0
                
                for k in range(n):
                    current_sum += col_sum[k]
                    result += prefix_sum[current_sum - target]
                    prefix_sum[current_sum] += 1
        
        return result