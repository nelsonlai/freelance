"""
Problem: Number of Dice Rolls With Target Sum
Difficulty: Medium
Tags: dp

Approach: DP - dp[i][j] = ways to get sum j using i dice
Time Complexity: O(n * target * k) where n is number of dice, k is faces
Space Complexity: O(n * target), can be optimized to O(target)
"""

class Solution:
    def numRollsToTarget(self, n: int, k: int, target: int) -> int:
        MOD = 10**9 + 7
        dp = [[0] * (target + 1) for _ in range(n + 1)]
        dp[0][0] = 1
        
        for i in range(1, n + 1):
            for j in range(1, target + 1):
                for face in range(1, min(k, j) + 1):
                    dp[i][j] = (dp[i][j] + dp[i-1][j-face]) % MOD
        
        return dp[n][target]