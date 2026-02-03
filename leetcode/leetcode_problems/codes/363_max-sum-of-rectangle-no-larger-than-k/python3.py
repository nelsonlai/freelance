"""
Problem: Max Sum of Rectangle No Larger Than K
Difficulty: Hard
Tags: array, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

import bisect

class Solution:
    def maxSumSubmatrix(self, matrix: List[List[int]], k: int) -> int:
        m, n = len(matrix), len(matrix[0])
        result = float('-inf')
        
        for left in range(n):
            row_sum = [0] * m
            for right in range(left, n):
                for i in range(m):
                    row_sum[i] += matrix[i][right]
                
                prefix_sum = [0]
                curr_sum = 0
                for sum_val in row_sum:
                    curr_sum += sum_val
                    idx = bisect.bisect_left(prefix_sum, curr_sum - k)
                    if idx < len(prefix_sum):
                        result = max(result, curr_sum - prefix_sum[idx])
                    bisect.insort(prefix_sum, curr_sum)
        
        return result