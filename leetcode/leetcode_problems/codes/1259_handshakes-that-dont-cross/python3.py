"""
Problem: Handshakes That Don't Cross
Difficulty: Hard
Tags: dp, math

Approach: Catalan numbers - dp[n] = sum of dp[i] * dp[n-1-i] for all valid splits
Time Complexity: O(n^2) where n is numPeople
Space Complexity: O(n) for DP array
"""

class Solution:
    def numberOfWays(self, numPeople: int) -> int:
        MOD = 10**9 + 7
        n = numPeople // 2
        dp = [0] * (n + 1)
        dp[0] = 1
        
        for i in range(1, n + 1):
            for j in range(i):
                dp[i] = (dp[i] + dp[j] * dp[i - 1 - j]) % MOD
        
        return dp[n]