"""
Problem: Longest Increasing Subsequence
Difficulty: Medium
Tags: array, dp, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

import bisect

class Solution:
    def lengthOfLIS(self, nums: List[int]) -> int:
        tails = []
        
        for num in nums:
            pos = bisect.bisect_left(tails, num)
            if pos == len(tails):
                tails.append(num)
            else:
                tails[pos] = num
        
        return len(tails)