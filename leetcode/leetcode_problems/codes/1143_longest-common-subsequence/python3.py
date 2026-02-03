"""
Problem: Longest Common Subsequence
Difficulty: Medium
Tags: string, dp

Approach: DP - dp[i][j] = LCS of text1[:i] and text2[:j]
Time Complexity: O(m * n) where m, n are lengths of text1 and text2
Space Complexity: O(m * n) for DP table, can be optimized to O(min(m, n))
"""

class Solution:
    def longestCommonSubsequence(self, text1: str, text2: str) -> int:
        m, n = len(text1), len(text2)
        dp = [[0] * (n + 1) for _ in range(m + 1)]
        
        for i in range(1, m + 1):
            for j in range(1, n + 1):
                if text1[i-1] == text2[j-1]:
                    dp[i][j] = dp[i-1][j-1] + 1
                else:
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1])
        
        return dp[m][n]