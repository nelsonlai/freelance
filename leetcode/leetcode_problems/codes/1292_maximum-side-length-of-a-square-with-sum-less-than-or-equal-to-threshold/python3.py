"""
Problem: Maximum Side Length of a Square with Sum Less than or Equal to Threshold
Difficulty: Medium
Tags: array, search

Approach: Prefix sum + binary search on side length
Time Complexity: O(m * n * log(min(m, n)))
Space Complexity: O(m * n) for prefix sum
"""

class Solution:
    def maxSideLength(self, mat: List[List[int]], threshold: int) -> int:
        m, n = len(mat), len(mat[0])
        prefix = [[0] * (n + 1) for _ in range(m + 1)]
        
        for i in range(1, m + 1):
            for j in range(1, n + 1):
                prefix[i][j] = (prefix[i-1][j] + prefix[i][j-1] - 
                               prefix[i-1][j-1] + mat[i-1][j-1])
        
        def square_sum(r, c, size):
            return (prefix[r][c] - prefix[r-size][c] - 
                   prefix[r][c-size] + prefix[r-size][c-size])
        
        max_side = 0
        for i in range(1, m + 1):
            for j in range(1, n + 1):
                for size in range(max_side + 1, min(i, j) + 1):
                    if square_sum(i, j, size) <= threshold:
                        max_side = size
                    else:
                        break
        
        return max_side