"""
Problem: Campus Bikes II
Difficulty: Medium
Tags: array, dp

Approach: DP with bitmask - assign bikes to workers with minimum total distance
Time Complexity: O(m * 2^n) where m is workers, n is bikes
Space Complexity: O(2^n) for DP
"""

from functools import lru_cache

class Solution:
    def assignBikes(self, workers: List[List[int]], bikes: List[List[int]]) -> int:
        def manhattan(p1, p2):
            return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1])
        
        @lru_cache(None)
        def dp(worker_idx, mask):
            if worker_idx == len(workers):
                return 0
            
            result = float('inf')
            for bike_idx in range(len(bikes)):
                if mask & (1 << bike_idx) == 0:
                    dist = manhattan(workers[worker_idx], bikes[bike_idx])
                    result = min(result, dist + dp(worker_idx + 1, mask | (1 << bike_idx)))
            
            return result
        
        return dp(0, 0)