"""
Problem: Maximum Matrix Sum
Difficulty: Medium
Tags: array, greedy

Approach: Can flip pairs of negatives, maximize sum by minimizing negatives
Time Complexity: O(n * m) where n, m are dimensions
Space Complexity: O(1)
"""

class Solution:
    def maxMatrixSum(self, matrix: List[List[int]]) -> int:
        total = 0
        min_abs = float('inf')
        negative_count = 0
        
        for row in matrix:
            for num in row:
                total += abs(num)
                min_abs = min(min_abs, abs(num))
                if num < 0:
                    negative_count += 1
        
        if negative_count % 2 == 1:
            total -= 2 * min_abs
        
        return total