"""
Problem: Number of Ways to Rearrange Sticks With K Sticks Visible
Difficulty: Hard
Tags: dp, math

Approach: DP - dp[n][k] = ways to arrange n sticks with k visible
Time Complexity: O(n * k) where n, k are parameters
Space Complexity: O(n * k)
"""

MOD = 10**9 + 7

class Solution:
    def rearrangeSticks(self, n: int, k: int) -> int:
        # dp[i][j] = ways to arrange i sticks with j visible
        dp = [[0] * (k + 1) for _ in range(n + 1)]
        dp[0][0] = 1
        
        for i in range(1, n + 1):
            for j in range(1, min(i, k) + 1):
                # Place tallest stick at end: 1 way, j-1 visible from remaining
                dp[i][j] = dp[i-1][j-1]
                # Place any other stick at end: (i-1) ways, j visible from remaining
                dp[i][j] = (dp[i][j] + (i - 1) * dp[i-1][j]) % MOD
        
        return dp[n][k]