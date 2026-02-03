"""
Problem: Reducing Dishes
Difficulty: Hard
Tags: array, dp, greedy, sort

Approach: Sort descending, use DP - dp[i][j] = max satisfaction using first i dishes, j cooked
Time Complexity: O(n^2) where n is number of dishes
Space Complexity: O(n) using rolling array
"""

class Solution:
    def maxSatisfaction(self, satisfaction: List[int]) -> int:
        satisfaction.sort(reverse=True)
        n = len(satisfaction)
        dp = [0] * (n + 1)
        
        for i in range(n):
            new_dp = [0] * (n + 1)
            for j in range(1, i + 2):
                new_dp[j] = max(dp[j], dp[j-1] + satisfaction[i] * j)
            dp = new_dp
        
        return max(dp)