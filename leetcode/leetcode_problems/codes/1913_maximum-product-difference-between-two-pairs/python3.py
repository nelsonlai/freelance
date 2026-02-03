"""
Problem: Maximum Product Difference Between Two Pairs
Difficulty: Easy
Tags: array, sort

Approach: Find two largest and two smallest numbers
Time Complexity: O(n) - can use partial sort
Space Complexity: O(1)
"""

class Solution:
    def maxProductDifference(self, nums: List[int]) -> int:
        nums.sort()
        return nums[-1] * nums[-2] - nums[0] * nums[1]