"""
Problem: Minimum Elements to Add to Form a Given Sum
Difficulty: Medium
Tags: array, greedy, math

Approach: Calculate difference, add minimum elements within limit
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

import math

class Solution:
    def minElements(self, nums: List[int], limit: int, goal: int) -> int:
        diff = goal - sum(nums)
        return math.ceil(abs(diff) / limit)