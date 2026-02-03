"""
Problem: Maximize Palindrome Length From Subsequences
Difficulty: Hard
Tags: string, dp

Approach: Find longest palindromic subsequence in combined string, ensure at least one char from each
Time Complexity: O((n+m)^2) where n, m are lengths
Space Complexity: O((n+m)^2)
"""

class Solution:
    def longestPalindrome(self, word1: str, word2: str) -> int:
        s = word1 + word2
        n = len(s)
        m = len(word1)
        
        # DP for longest palindromic subsequence
        dp = [[0] * n for _ in range(n)]
        
        for i in range(n):
            dp[i][i] = 1
        
        for length in range(2, n + 1):
            for i in range(n - length + 1):
                j = i + length - 1
                if s[i] == s[j]:
                    dp[i][j] = 2 + (dp[i+1][j-1] if i+1 <= j-1 else 0)
                else:
                    dp[i][j] = max(dp[i+1][j], dp[i][j-1])
        
        result = 0
        # Check palindromes that use at least one from each word
        for i in range(m):
            for j in range(m, n):
                if s[i] == s[j]:
                    result = max(result, dp[i][j])
        
        return result