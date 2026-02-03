"""
Problem: Longest Palindromic Subsequence II
Difficulty: Medium
Tags: string, dp

Approach: DP - find longest palindromic subsequence with even length and alternating characters
Time Complexity: O(n^2) where n is length
Space Complexity: O(n^2)
"""

from functools import lru_cache

class Solution:
    def longestPalindromeSubseq(self, s: str) -> int:
        @lru_cache(maxsize=None)
        def dp(i, j, prev_char):
            if i >= j:
                return 0
            
            if s[i] == s[j] and s[i] != prev_char:
                return 2 + dp(i + 1, j - 1, s[i])
            
            return max(dp(i + 1, j, prev_char), dp(i, j - 1, prev_char))
        
        result = dp(0, len(s) - 1, '')
        return result if result > 0 else 0