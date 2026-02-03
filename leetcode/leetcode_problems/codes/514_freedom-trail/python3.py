"""
Problem: Freedom Trail
Difficulty: Hard
Tags: string, dp, search

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

from collections import defaultdict
from functools import lru_cache

class Solution:
    def findRotateSteps(self, ring: str, key: str) -> int:
        char_positions = defaultdict(list)
        for i, char in enumerate(ring):
            char_positions[char].append(i)
        
        @lru_cache(None)
        def dp(ring_pos, key_pos):
            if key_pos == len(key):
                return 0
            
            min_steps = float('inf')
            target_char = key[key_pos]
            
            for pos in char_positions[target_char]:
                steps = min(abs(pos - ring_pos), len(ring) - abs(pos - ring_pos))
                min_steps = min(min_steps, steps + 1 + dp(pos, key_pos + 1))
            
            return min_steps
        
        return dp(0, 0)