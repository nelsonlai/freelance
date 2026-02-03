"""
Problem: K Inverse Pairs Array
Difficulty: Hard
Tags: array, dp

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def kInversePairs(self, n: int, k: int) -> int:
        MOD = 10**9 + 7
        dp = [[0] * (k + 1) for _ in range(n + 1)]
        dp[0][0] = 1
        
        for i in range(1, n + 1):
            dp[i][0] = 1
            for j in range(1, k + 1):
                dp[i][j] = (dp[i][j-1] + dp[i-1][j]) % MOD
                if j >= i:
                    dp[i][j] = (dp[i][j] - dp[i-1][j-i] + MOD) % MOD
        
        return dp[n][k]