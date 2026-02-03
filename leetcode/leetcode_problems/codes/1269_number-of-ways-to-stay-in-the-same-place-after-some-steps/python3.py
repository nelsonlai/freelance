"""
Problem: Number of Ways to Stay in the Same Place After Some Steps
Difficulty: Hard
Tags: array, dp

Approach: DP - dp[step][pos] = ways to be at pos after step steps
Time Complexity: O(steps * min(steps, arrLen))
Space Complexity: O(min(steps, arrLen)) using rolling array
"""

class Solution:
    def numWays(self, steps: int, arrLen: int) -> int:
        MOD = 10**9 + 7
        max_pos = min(steps, arrLen)
        dp = [0] * max_pos
        dp[0] = 1
        
        for step in range(1, steps + 1):
            new_dp = [0] * max_pos
            for pos in range(max_pos):
                new_dp[pos] = dp[pos]  # Stay
                if pos > 0:
                    new_dp[pos] = (new_dp[pos] + dp[pos - 1]) % MOD  # Left
                if pos < max_pos - 1:
                    new_dp[pos] = (new_dp[pos] + dp[pos + 1]) % MOD  # Right
            dp = new_dp
        
        return dp[0]