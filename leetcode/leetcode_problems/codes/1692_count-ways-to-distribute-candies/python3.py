"""
Problem: Count Ways to Distribute Candies
Difficulty: Hard
Tags: dp, combinatorics

Approach: DP - dp[i][j] = ways to distribute i candies to j bags
Time Complexity: O(n * k) where n is candies, k is bags
Space Complexity: O(n * k)
"""

MOD = 10**9 + 7

class Solution:
    def waysToDistribute(self, n: int, k: int) -> int:
        if n < k:
            return 0
        
        dp = [[0] * (k + 1) for _ in range(n + 1)]
        
        for j in range(1, k + 1):
            dp[j][j] = 1
        
        for i in range(1, n + 1):
            for j in range(1, min(i, k) + 1):
                # Put candy in existing bag or new bag
                dp[i][j] = (dp[i - 1][j] * j + dp[i - 1][j - 1]) % MOD
        
        return dp[n][k]