"""
Problem: Maximum Number of Groups Getting Fresh Donuts
Difficulty: Hard
Tags: array, dp, greedy, state compression

Approach: DP with state compression - track remainder counts
Time Complexity: O(batchSize^batchSize * n)
Space Complexity: O(batchSize^batchSize)
"""

from functools import lru_cache
from collections import Counter

class Solution:
    def maxHappyGroups(self, batchSize: int, groups: List[int]) -> int:
        remainders = [0] * batchSize
        for g in groups:
            remainders[g % batchSize] += 1
        
        # Greedy: pair groups that sum to batchSize
        result = remainders[0]
        for i in range(1, batchSize // 2 + 1):
            if i == batchSize - i:
                pairs = remainders[i] // 2
                result += pairs
                remainders[i] -= pairs * 2
            else:
                pairs = min(remainders[i], remainders[batchSize - i])
                result += pairs
                remainders[i] -= pairs
                remainders[batchSize - i] -= pairs
        
        # DP for remaining groups
        @lru_cache(maxsize=None)
        def dp(state):
            if sum(state) == 0:
                return 0
            
            state_list = list(state)
            result = 0
            
            for i in range(batchSize):
                if state_list[i] > 0:
                    new_state = list(state_list)
                    new_state[i] -= 1
                    new_remainder = (sum(j * new_state[j] for j in range(batchSize)) + i) % batchSize
                    result = max(result, dp(tuple(new_state)) + (1 if new_remainder == 0 else 0))
            
            return result
        
        return result + dp(tuple(remainders[1:]))