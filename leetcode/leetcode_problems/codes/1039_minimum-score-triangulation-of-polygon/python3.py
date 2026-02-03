"""
Problem: Minimum Score Triangulation of Polygon
Difficulty: Medium
Tags: array, dp

Approach: DP - for each edge (i,j), try all possible triangles with vertex k
Time Complexity: O(n^3)
Space Complexity: O(n^2) for DP table
"""

from functools import lru_cache

class Solution:
    def minScoreTriangulation(self, values: List[int]) -> int:
        @lru_cache(None)
        def dp(i, j):
            if j - i < 2:
                return 0
            
            result = float('inf')
            for k in range(i + 1, j):
                result = min(result, values[i] * values[j] * values[k] + dp(i, k) + dp(k, j))
            
            return result
        
        return dp(0, len(values) - 1)