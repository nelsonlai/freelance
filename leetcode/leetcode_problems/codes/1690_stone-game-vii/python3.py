"""
Problem: Stone Game VII
Difficulty: Medium
Tags: array, dp, math

Approach: DP - dp[i][j] = max score difference, use prefix sum for range sum
Time Complexity: O(n^2) where n is length
Space Complexity: O(n^2)
"""

from functools import lru_cache

class Solution:
    def stoneGameVII(self, stones: List[int]) -> int:
        n = len(stones)
        prefix = [0]
        for stone in stones:
            prefix.append(prefix[-1] + stone)
        
        @lru_cache(maxsize=None)
        def dp(i, j):
            if i >= j:
                return 0
            
            # Remove left: sum from i+1 to j
            remove_left = (prefix[j + 1] - prefix[i + 1]) - dp(i + 1, j)
            
            # Remove right: sum from i to j-1
            remove_right = (prefix[j] - prefix[i]) - dp(i, j - 1)
            
            return max(remove_left, remove_right)
        
        return dp(0, n - 1)