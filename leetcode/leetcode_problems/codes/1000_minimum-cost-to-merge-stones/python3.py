"""
Problem: Minimum Cost to Merge Stones
Difficulty: Hard
Tags: array, dp

Approach: DP - merge stones in groups of k, minimize cost
Time Complexity: O(n^3) where n is number of stones
Space Complexity: O(n^2) for DP table
"""

from functools import lru_cache
import sys

class Solution:
    def mergeStones(self, stones: List[int], k: int) -> int:
        n = len(stones)
        if (n - 1) % (k - 1) != 0:
            return -1
        
        prefix = [0]
        for stone in stones:
            prefix.append(prefix[-1] + stone)
        
        @lru_cache(None)
        def dp(i, j, piles):
            if i == j and piles == 1:
                return 0
            if (j - i + 1 - piles) % (k - 1) != 0:
                return sys.maxsize
            
            if piles == 1:
                return dp(i, j, k) + prefix[j + 1] - prefix[i]
            
            result = sys.maxsize
            for m in range(i, j, k - 1):
                result = min(result, dp(i, m, 1) + dp(m + 1, j, piles - 1))
            
            return result
        
        result = dp(0, n - 1, 1)
        return result if result < sys.maxsize else -1
