"""
Problem: Palindrome Partitioning III
Difficulty: Hard
Tags: string, tree, dp

Approach: DP - dp[i][j] = min changes to partition s[0:i] into j palindromes
Time Complexity: O(n^2 * k) where n is length of s
Space Complexity: O(n * k) for DP table
"""

class Solution:
    def palindromePartition(self, s: str, k: int) -> int:
        n = len(s)
        
        # Precompute changes needed to make substring palindrome
        def changes_needed(start, end):
            count = 0
            while start < end:
                if s[start] != s[end]:
                    count += 1
                start += 1
                end -= 1
            return count
        
        # dp[i][j] = min changes to partition s[0:i] into j palindromes
        dp = [[float('inf')] * (k + 1) for _ in range(n + 1)]
        dp[0][0] = 0
        
        for i in range(1, n + 1):
            for j in range(1, min(i, k) + 1):
                for prev in range(j - 1, i):
                    dp[i][j] = min(dp[i][j], dp[prev][j-1] + changes_needed(prev, i - 1))
        
        return dp[n][k]