"""
Problem: Distinct Subsequences II
Difficulty: Hard
Tags: string, dp

Approach: Dynamic programming - track distinct subsequences ending at each position
Time Complexity: O(n) where n is string length
Space Complexity: O(1) using constant space for last occurrence tracking
"""

class Solution:
    def distinctSubseqII(self, s: str) -> int:
        MOD = 10**9 + 7
        dp = [0] * (len(s) + 1)
        last_occurrence = {}
        
        dp[0] = 1  # Empty subsequence
        
        for i in range(1, len(s) + 1):
            dp[i] = (2 * dp[i-1]) % MOD
            if s[i-1] in last_occurrence:
                dp[i] = (dp[i] - dp[last_occurrence[s[i-1]] - 1]) % MOD
            last_occurrence[s[i-1]] = i
        
        return (dp[len(s)] - 1) % MOD  # Subtract empty subsequence