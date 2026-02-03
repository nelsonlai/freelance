"""
Problem: Least Operators to Express Number
Difficulty: Hard
Tags: dp, math

Approach: Greedy - express target in base x, minimize operations
Time Complexity: O(log_x(target))
Space Complexity: O(log_x(target)) for recursion
"""

from functools import lru_cache

class Solution:
    def leastOpsExpressTarget(self, x: int, target: int) -> int:
        @lru_cache(None)
        def dfs(t):
            if t == 0:
                return 0
            if t < x:
                return min(2 * t - 1, 2 * (x - t))
            
            k = 0
            power = 1
            while power * x <= t:
                power *= x
                k += 1
            
            # Option 1: Use k+1 times (x^(k+1))
            res1 = k + 1 + dfs(t - power)
            
            # Option 2: Use k+1 times but subtract
            if power * x - t < t:
                res2 = k + 1 + dfs(power * x - t)
                return min(res1, res2)
            
            return res1
        
        return dfs(target)