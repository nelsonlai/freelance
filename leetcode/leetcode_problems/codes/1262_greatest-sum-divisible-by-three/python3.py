"""
Problem: Greatest Sum Divisible by Three
Difficulty: Medium
Tags: array, dp, greedy, sort

Approach: DP - track max sum for each remainder (0, 1, 2)
Time Complexity: O(n) where n is length of nums
Space Complexity: O(1) using variables
"""

class Solution:
    def maxSumDivThree(self, nums: List[int]) -> int:
        dp = [0, float('-inf'), float('-inf')]
        
        for num in nums:
            new_dp = dp[:]
            for i in range(3):
                remainder = (i + num) % 3
                new_dp[remainder] = max(new_dp[remainder], dp[i] + num)
            dp = new_dp
        
        return dp[0]