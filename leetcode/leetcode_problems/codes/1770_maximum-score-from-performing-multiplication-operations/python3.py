"""
Problem: Maximum Score from Performing Multiplication Operations
Difficulty: Hard
Tags: array, dp

Approach: DP - dp[i][j] = max score using first i multipliers, j from left
Time Complexity: O(m^2) where m is multipliers length
Space Complexity: O(m^2)
"""

from functools import lru_cache

class Solution:
    def maximumScore(self, nums: List[int], multipliers: List[int]) -> int:
        n, m = len(nums), len(multipliers)
        
        @lru_cache(maxsize=None)
        def dp(i, left):
            if i == m:
                return 0
            
            right = n - 1 - (i - left)
            multiplier = multipliers[i]
            
            # Take from left
            take_left = nums[left] * multiplier + dp(i + 1, left + 1)
            # Take from right
            take_right = nums[right] * multiplier + dp(i + 1, left)
            
            return max(take_left, take_right)
        
        return dp(0, 0)