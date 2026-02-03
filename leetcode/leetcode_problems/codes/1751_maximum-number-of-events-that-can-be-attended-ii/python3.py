"""
Problem: Maximum Number of Events That Can Be Attended II
Difficulty: Hard
Tags: array, dp, sort, search, binary search

Approach: DP with binary search - sort by end time, dp[i][j] = max value attending j events from first i
Time Complexity: O(n * k * log n) where n is events
Space Complexity: O(n * k)
"""

import bisect
from functools import lru_cache

class Solution:
    def maxValue(self, events: List[List[int]], k: int) -> int:
        events.sort(key=lambda x: x[1])
        n = len(events)
        end_times = [events[i][1] for i in range(n)]
        
        @lru_cache(maxsize=None)
        def dp(i, remaining):
            if i < 0 or remaining == 0:
                return 0
            
            # Don't attend event i
            result = dp(i - 1, remaining)
            
            # Attend event i - find last event that ends before this starts
            start = events[i][0]
            prev_idx = bisect.bisect_left(end_times, start) - 1
            
            # Attend event i
            result = max(result, events[i][2] + dp(prev_idx, remaining - 1))
            
            return result
        
        return dp(n - 1, k)