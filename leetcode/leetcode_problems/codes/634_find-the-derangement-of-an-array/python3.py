"""
Problem: Find the Derangement of An Array
Difficulty: Medium
Tags: array, dp, math

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def findDerangement(self, n: int) -> int:
        MOD = 10**9 + 7
        if n <= 1:
            return 0
        if n == 2:
            return 1
        
        dp = [0] * (n + 1)
        dp[1] = 0
        dp[2] = 1
        
        for i in range(3, n + 1):
            dp[i] = ((i - 1) * (dp[i-1] + dp[i-2])) % MOD
        
        return dp[n]