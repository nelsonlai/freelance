"""
Problem: Count Number of Maximum Bitwise-OR Subsets
Difficulty: Medium
Tags: array, bit manipulation, dp

Approach: Find max OR value, then count subsets with that OR value
Time Complexity: O(n * 2^n) or O(n * max_or) with DP
Space Complexity: O(max_or)
"""

class Solution:
    def countMaxOrSubsets(self, nums: List[int]) -> int:
        # Find maximum OR value
        max_or = 0
        for num in nums:
            max_or |= num
        
        # Count subsets with OR = max_or using DP
        n = len(nums)
        # dp[mask] = number of ways to achieve OR = mask
        dp = {0: 1}
        
        for num in nums:
            new_dp = dp.copy()
            for mask, count in dp.items():
                new_mask = mask | num
                new_dp[new_mask] = new_dp.get(new_mask, 0) + count
            dp = new_dp
        
        return dp.get(max_or, 0)