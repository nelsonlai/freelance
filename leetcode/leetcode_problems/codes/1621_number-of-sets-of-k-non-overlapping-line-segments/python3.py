"""
Problem: Number of Sets of K Non-Overlapping Line Segments
Difficulty: Medium
Tags: dp, math, combinatorics

Approach: DP - dp[i][j] = number of ways to place j segments using first i points
Time Complexity: O(n * k)
Space Complexity: O(n * k)
"""

MOD = 10**9 + 7

class Solution:
    def numberOfSets(self, n: int, k: int) -> int:
        # dp[i][j] = ways to place j segments using points 0 to i
        dp = [[0] * (k + 1) for _ in range(n)]
        
        for i in range(n):
            dp[i][0] = 1
        
        for j in range(1, k + 1):
            prefix = 0
            for i in range(1, n):
                prefix = (prefix + dp[i-1][j-1]) % MOD
                dp[i][j] = (dp[i-1][j] + prefix) % MOD
        
        return dp[n-1][k]