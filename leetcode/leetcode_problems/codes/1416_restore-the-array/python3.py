"""
Problem: Restore The Array
Difficulty: Hard
Tags: array, string, dp

Approach: DP - dp[i] = number of ways to split s[i:], try all valid numbers starting at i
Time Complexity: O(n * log10(k)) where n is length of s
Space Complexity: O(n) for DP table
"""

class Solution:
    def numberOfArrays(self, s: str, k: int) -> int:
        MOD = 10**9 + 7
        n = len(s)
        dp = [0] * (n + 1)
        dp[n] = 1
        
        for i in range(n - 1, -1, -1):
            if s[i] == '0':
                continue
            
            num = 0
            for j in range(i, n):
                num = num * 10 + int(s[j])
                if num > k:
                    break
                dp[i] = (dp[i] + dp[j + 1]) % MOD
        
        return dp[0]