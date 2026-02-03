"""
Problem: Frog Jump
Difficulty: Hard
Tags: array, dp, sort

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

from functools import lru_cache

class Solution:
    def canCross(self, stones: List[int]) -> bool:
        stone_set = set(stones)
        
        @lru_cache(None)
        def dfs(position, last_jump):
            if position == stones[-1]:
                return True
            
            for jump in [last_jump - 1, last_jump, last_jump + 1]:
                if jump > 0:
                    next_position = position + jump
                    if next_position in stone_set and dfs(next_position, jump):
                        return True
            
            return False
        
        if stones[1] != 1:
            return False
        
        return dfs(1, 1)