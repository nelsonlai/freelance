"""
Problem: Maximum Product of Three Numbers
Difficulty: Easy
Tags: array, math, sort

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def maximumProduct(self, nums: List[int]) -> int:
        nums.sort()
        n = len(nums)
        return max(nums[0] * nums[1] * nums[n-1], nums[n-1] * nums[n-2] * nums[n-3])