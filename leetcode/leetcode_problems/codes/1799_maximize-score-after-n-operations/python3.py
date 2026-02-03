"""
Problem: Maximize Score After N Operations
Difficulty: Hard
Tags: array, dp, math, bitmask

Approach: DP with bitmask - track pairs used, compute GCD for all pairs
Time Complexity: O(2^n * n^2) where n is length
Space Complexity: O(2^n)
"""

import math
from functools import lru_cache

class Solution:
    def maxScore(self, nums: List[int]) -> int:
        n = len(nums)
        
        @lru_cache(maxsize=None)
        def dp(mask, op):
            if mask == (1 << n) - 1:
                return 0
            
            result = 0
            for i in range(n):
                if mask & (1 << i):
                    continue
                for j in range(i + 1, n):
                    if mask & (1 << j):
                        continue
                    new_mask = mask | (1 << i) | (1 << j)
                    gcd_val = math.gcd(nums[i], nums[j])
                    result = max(result, op * gcd_val + dp(new_mask, op + 1))
            
            return result
        
        return dp(0, 1)