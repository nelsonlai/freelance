"""
Problem: Minimum Incompatibility
Difficulty: Hard
Tags: array, dp, bitmask, backtracking

Approach: DP with bitmask - try all subsets of size n/k, minimize incompatibility
Time Complexity: O(3^n * n) where n is length
Space Complexity: O(2^n)
"""

from functools import lru_cache
from collections import Counter

class Solution:
    def minimumIncompatibility(self, nums: List[int], k: int) -> int:
        n = len(nums)
        size = n // k
        
        freq = Counter(nums)
        if max(freq.values()) > k:
            return -1
        
        @lru_cache(maxsize=None)
        def dp(mask):
            if mask == 0:
                return 0
            
            indices = [i for i in range(n) if mask & (1 << i)]
            
            if len(indices) < size:
                return float('inf')
            
            result = float('inf')
            
            # Try all subsets of size 'size'
            from itertools import combinations
            for combo in combinations(indices, size):
                subset = [nums[i] for i in combo]
                if len(set(subset)) < size:
                    continue
                
                incompatibility = max(subset) - min(subset)
                new_mask = mask
                for i in combo:
                    new_mask ^= (1 << i)
                
                result = min(result, incompatibility + dp(new_mask))
            
            return result
        
        result = dp((1 << n) - 1)
        return result if result != float('inf') else -1