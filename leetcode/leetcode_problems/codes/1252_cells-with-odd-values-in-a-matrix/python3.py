"""
Problem: Cells with Odd Values in a Matrix
Difficulty: Easy
Tags: array, math

Approach: Track row and column increments, count cells with odd sum
Time Complexity: O(m * n + len(indices))
Space Complexity: O(m + n)
"""

class Solution:
    def oddCells(self, m: int, n: int, indices: List[List[int]]) -> int:
        rows = [0] * m
        cols = [0] * n
        
        for r, c in indices:
            rows[r] += 1
            cols[c] += 1
        
        odd_count = 0
        for i in range(m):
            for j in range(n):
                if (rows[i] + cols[j]) % 2 == 1:
                    odd_count += 1
        
        return odd_count