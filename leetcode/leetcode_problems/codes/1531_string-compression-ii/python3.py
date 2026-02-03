"""
Problem: String Compression II
Difficulty: Hard
Tags: string, dp

Approach: DP - dp[i][j] = min length compressing s[:i] with j deletions
Time Complexity: O(n^2 * k) where n is length of s
Space Complexity: O(n * k) for DP table
"""

from functools import lru_cache

class Solution:
    def getLengthOfOptimalCompression(self, s: str, k: int) -> int:
        @lru_cache(None)
        def dp(i, k, prev_char, prev_count):
            if k < 0:
                return float('inf')
            if i == len(s):
                return 0
            
            delete = dp(i + 1, k - 1, prev_char, prev_count)
            
            if s[i] == prev_char:
                keep = dp(i + 1, k, prev_char, prev_count + 1)
                if prev_count == 1 or prev_count == 9 or prev_count == 99:
                    keep += 1
            else:
                keep = 1 + dp(i + 1, k, s[i], 1)
            
            return min(delete, keep)
        
        return dp(0, k, '', 0)