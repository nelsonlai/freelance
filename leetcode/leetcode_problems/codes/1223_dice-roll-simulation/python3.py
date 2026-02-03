"""
Problem: Dice Roll Simulation
Difficulty: Hard
Tags: array, dp

Approach: DP - dp[i][j][k] = ways to roll i dice ending with j, k consecutive j's
Time Complexity: O(n * 6 * max(rollMax))
Space Complexity: O(n * 6 * max(rollMax)), can be optimized
"""

class Solution:
    def dieSimulator(self, n: int, rollMax: List[int]) -> int:
        MOD = 10**9 + 7
        # dp[i][j] = number of sequences of length i ending with face j
        dp = [[0] * 6 for _ in range(n + 1)]
        
        for j in range(6):
            dp[1][j] = 1
        
        for i in range(2, n + 1):
            for j in range(6):
                for prev_j in range(6):
                    if prev_j == j:
                        # Can only continue if within rollMax limit
                        if i <= rollMax[j]:
                            dp[i][j] = (dp[i][j] + dp[i-1][j]) % MOD
                    else:
                        # Can switch to different face
                        dp[i][j] = (dp[i][j] + dp[i-1][prev_j]) % MOD
        
        return sum(dp[n]) % MOD