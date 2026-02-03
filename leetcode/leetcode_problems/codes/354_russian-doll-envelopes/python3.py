"""
Problem: Russian Doll Envelopes
Difficulty: Hard
Tags: array, dp, sort, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

import bisect

class Solution:
    def maxEnvelopes(self, envelopes: List[List[int]]) -> int:
        envelopes.sort(key=lambda x: (x[0], -x[1]))
        
        dp = []
        for _, height in envelopes:
            idx = bisect.bisect_left(dp, height)
            if idx == len(dp):
                dp.append(height)
            else:
                dp[idx] = height
        
        return len(dp)