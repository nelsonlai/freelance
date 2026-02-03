"""
Problem: Remove One Element to Make the Array Strictly Increasing
Difficulty: Easy
Tags: array, greedy

Approach: Check if removing one element makes array strictly increasing
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def canBeIncreasing(self, nums: List[int]) -> bool:
        def isStrictlyIncreasing(arr):
            for i in range(1, len(arr)):
                if arr[i] <= arr[i - 1]:
                    return False
            return True
        
        if isStrictlyIncreasing(nums):
            return True
        
        for i in range(len(nums)):
            new_nums = nums[:i] + nums[i + 1:]
            if isStrictlyIncreasing(new_nums):
                return True
        
        return False