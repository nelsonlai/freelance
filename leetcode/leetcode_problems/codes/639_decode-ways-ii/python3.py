"""
Problem: Decode Ways II
Difficulty: Hard
Tags: string, dp

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def numDecodings(self, s: str) -> int:
        MOD = 10**9 + 7
        n = len(s)
        dp = [0] * (n + 1)
        dp[0] = 1
        
        if s[0] == '*':
            dp[1] = 9
        elif s[0] != '0':
            dp[1] = 1
        
        for i in range(2, n + 1):
            if s[i-1] == '*':
                dp[i] = (dp[i] + 9 * dp[i-1]) % MOD
            elif s[i-1] != '0':
                dp[i] = (dp[i] + dp[i-1]) % MOD
            
            if s[i-2] == '*':
                if s[i-1] == '*':
                    dp[i] = (dp[i] + 15 * dp[i-2]) % MOD
                elif s[i-1] <= '6':
                    dp[i] = (dp[i] + 2 * dp[i-2]) % MOD
                else:
                    dp[i] = (dp[i] + dp[i-2]) % MOD
            elif s[i-2] == '1':
                if s[i-1] == '*':
                    dp[i] = (dp[i] + 9 * dp[i-2]) % MOD
                else:
                    dp[i] = (dp[i] + dp[i-2]) % MOD
            elif s[i-2] == '2':
                if s[i-1] == '*':
                    dp[i] = (dp[i] + 6 * dp[i-2]) % MOD
                elif s[i-1] <= '6':
                    dp[i] = (dp[i] + dp[i-2]) % MOD
        
        return dp[n]