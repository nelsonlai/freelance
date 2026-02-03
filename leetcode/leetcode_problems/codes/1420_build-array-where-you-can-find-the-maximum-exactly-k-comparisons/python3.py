"""
Problem: Build Array Where You Can Find The Maximum Exactly K Comparisons
Difficulty: Hard
Tags: array, dp, search

Approach: DP - dp[i][j][l] = ways to build array of length i, max value j, k comparisons l
Time Complexity: O(n * m * k)
Space Complexity: O(n * m * k)
"""

class Solution:
    def numOfArrays(self, n: int, m: int, k: int) -> int:
        MOD = 10**9 + 7
        
        if k == 0:
            return 0
        
        dp = [[[0] * (k + 1) for _ in range(m + 1)] for _ in range(n + 1)]
        
        for j in range(1, m + 1):
            dp[1][j][1] = 1
        
        for i in range(2, n + 1):
            for j in range(1, m + 1):
                for l in range(1, min(i, k) + 1):
                    dp[i][j][l] = (dp[i][j][l] + dp[i-1][j][l] * j) % MOD
                    for prev_max in range(1, j):
                        dp[i][j][l] = (dp[i][j][l] + dp[i-1][prev_max][l-1]) % MOD
        
        result = 0
        for j in range(1, m + 1):
            result = (result + dp[n][j][k]) % MOD
        
        return result