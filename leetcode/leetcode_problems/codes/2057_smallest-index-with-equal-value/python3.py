"""
Problem: Smallest Index With Equal Value
Difficulty: Easy
Tags: array

Approach: Check if nums[i] == i % 10 for each index
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def smallestEqual(self, nums: List[int]) -> int:
        for i, num in enumerate(nums):
            if i % 10 == num:
                return i
        return -1