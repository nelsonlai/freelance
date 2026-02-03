"""
Problem: Target Sum
Difficulty: Medium
Tags: array, dp

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

from collections import defaultdict

class Solution:
    def findTargetSumWays(self, nums: List[int], target: int) -> int:
        dp = defaultdict(int)
        dp[0] = 1
        
        for num in nums:
            new_dp = defaultdict(int)
            for sum_val, count in dp.items():
                new_dp[sum_val + num] += count
                new_dp[sum_val - num] += count
            dp = new_dp
        
        return dp[target]