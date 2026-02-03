"""
Problem: Moving Stones Until Consecutive II
Difficulty: Medium
Tags: array, dp, math, sort

Approach: Sort stones, use sliding window to find min/max moves
Time Complexity: O(n log n) for sorting
Space Complexity: O(1)
"""

class Solution:
    def numMovesStonesII(self, stones: List[int]) -> List[int]:
        stones.sort()
        n = len(stones)
        
        # Maximum: move stones to fill gaps
        max_moves = max(stones[-1] - stones[1] - n + 2, stones[-2] - stones[0] - n + 2)
        
        # Minimum: sliding window to find window with most stones
        min_moves = n
        j = 0
        for i in range(n):
            while j < n and stones[j] - stones[i] < n:
                j += 1
            if j - i == n - 1 and stones[j - 1] - stones[i] == n - 2:
                min_moves = min(min_moves, 2)
            else:
                min_moves = min(min_moves, n - (j - i))
        
        return [min_moves, max_moves]