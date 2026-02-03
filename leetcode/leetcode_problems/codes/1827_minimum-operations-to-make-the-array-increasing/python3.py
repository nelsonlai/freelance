"""
Problem: Minimum Operations to Make the Array Increasing
Difficulty: Easy
Tags: array, greedy

Approach: Greedy - ensure each element is greater than previous
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def minOperations(self, nums: List[int]) -> int:
        operations = 0
        for i in range(1, len(nums)):
            if nums[i] <= nums[i-1]:
                operations += nums[i-1] + 1 - nums[i]
                nums[i] = nums[i-1] + 1
        return operations