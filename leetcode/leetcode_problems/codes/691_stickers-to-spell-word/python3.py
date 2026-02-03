"""
Problem: Stickers to Spell Word
Difficulty: Hard
Tags: array, string, dp, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

from collections import Counter
from functools import lru_cache

class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:
        sticker_counts = [Counter(sticker) for sticker in stickers]
        
        @lru_cache(None)
        def dp(target_str):
            if not target_str:
                return 0
            
            target_count = Counter(target_str)
            result = float('inf')
            
            for sticker_count in sticker_counts:
                if target_str[0] not in sticker_count:
                    continue
                
                new_target = []
                for char in target_count:
                    if target_count[char] > sticker_count[char]:
                        new_target.extend([char] * (target_count[char] - sticker_count[char]))
                
                new_target_str = ''.join(sorted(new_target))
                result = min(result, 1 + dp(new_target_str))
            
            return result if result != float('inf') else -1
        
        result = dp(''.join(sorted(target)))
        return result if result != -1 else -1