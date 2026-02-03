"""
Problem: Minimum Insertion Steps to Make a String Palindrome
Difficulty: Hard
Tags: string, dp

Approach: Find longest palindromic subsequence, answer is n - LPS
Time Complexity: O(n^2) where n is length of s
Space Complexity: O(n^2) for DP table, can be optimized to O(n)
"""

class Solution:
    def minInsertions(self, s: str) -> int:
        n = len(s)
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
        
        lps = dp[0][n-1]
        return n - lps