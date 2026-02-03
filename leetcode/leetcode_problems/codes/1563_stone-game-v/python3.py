"""
Problem: Stone Game V
Difficulty: Hard
Tags: array, dp, math

Approach: DP - dp[i][j] = max score for subarray from i to j, try all splits
Time Complexity: O(n^3) where n is length of stoneValue
Space Complexity: O(n^2) for DP table
"""

from functools import lru_cache

class Solution:
    def stoneGameV(self, stoneValue: List[int]) -> int:
        n = len(stoneValue)
        prefix = [0] * (n + 1)
        for i in range(n):
            prefix[i + 1] = prefix[i] + stoneValue[i]
        
        @lru_cache(None)
        def dp(i, j):
            if i >= j:
                return 0
            
            result = 0
            for k in range(i, j):
                left_sum = prefix[k + 1] - prefix[i]
                right_sum = prefix[j + 1] - prefix[k + 1]
                
                if left_sum < right_sum:
                    result = max(result, left_sum + dp(i, k))
                elif left_sum > right_sum:
                    result = max(result, right_sum + dp(k + 1, j))
                else:
                    result = max(result, left_sum + max(dp(i, k), dp(k + 1, j)))
            
            return result
        
        return dp(0, n - 1)