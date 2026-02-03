"""
Problem: Toss Strange Coins
Difficulty: Medium
Tags: array, dp, math

Approach: DP - dp[i][j] = probability of j heads in first i coins
Time Complexity: O(n * target) where n is number of coins
Space Complexity: O(target) using rolling array
"""

class Solution:
    def probabilityOfHeads(self, prob: List[float], target: int) -> float:
        n = len(prob)
        dp = [0.0] * (target + 1)
        dp[0] = 1.0
        
        for i in range(n):
            new_dp = [0.0] * (target + 1)
            for j in range(min(i + 1, target + 1)):
                if j < target:
                    new_dp[j + 1] += dp[j] * prob[i]
                new_dp[j] += dp[j] * (1 - prob[i])
            dp = new_dp
        
        return dp[target]