"""
Problem: Stone Game II
Difficulty: Medium
Tags: array, dp, math

Approach: DP with memoization - maximize current player's score
Time Complexity: O(n^3) where n is the length of piles
Space Complexity: O(n^2) for memoization
"""

class Solution:
    def stoneGameII(self, piles: List[int]) -> int:
        n = len(piles)
        suffix_sum = [0] * (n + 1)
        for i in range(n - 1, -1, -1):
            suffix_sum[i] = suffix_sum[i + 1] + piles[i]
        
        memo = {}
        
        def dp(i, m):
            if i >= n:
                return 0
            if (i, m) in memo:
                return memo[(i, m)]
            
            max_stones = 0
            for x in range(1, 2 * m + 1):
                if i + x > n:
                    break
                max_stones = max(max_stones, suffix_sum[i] - dp(i + x, max(m, x)))
            
            memo[(i, m)] = max_stones
            return max_stones
        
        return dp(0, 1)