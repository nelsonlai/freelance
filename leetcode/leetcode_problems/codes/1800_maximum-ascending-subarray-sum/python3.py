"""
Problem: Maximum Ascending Subarray Sum
Difficulty: Easy
Tags: array

Approach: Traverse array, track ascending subarrays and their sums
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def maxAscendingSum(self, nums: List[int]) -> int:
        result = current_sum = nums[0]
        
        for i in range(1, len(nums)):
            if nums[i] > nums[i-1]:
                current_sum += nums[i]
            else:
                current_sum = nums[i]
            result = max(result, current_sum)
        
        return result