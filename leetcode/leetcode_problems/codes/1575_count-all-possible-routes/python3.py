"""
Problem: Count All Possible Routes
Difficulty: Hard
Tags: array, dp

Approach: DP with memoization - dp[city][fuel] = number of ways to reach finish from city with fuel
Time Complexity: O(n^2 * fuel) where n is number of locations
Space Complexity: O(n * fuel) for memoization
"""

from functools import lru_cache

MOD = 10**9 + 7

class Solution:
    def countRoutes(self, locations: List[int], start: int, finish: int, fuel: int) -> int:
        @lru_cache(None)
        def dp(city, remaining_fuel):
            if remaining_fuel < 0:
                return 0
            
            result = 1 if city == finish else 0
            
            for next_city in range(len(locations)):
                if next_city != city:
                    cost = abs(locations[city] - locations[next_city])
                    if cost <= remaining_fuel:
                        result = (result + dp(next_city, remaining_fuel - cost)) % MOD
            
            return result
        
        return dp(start, fuel)