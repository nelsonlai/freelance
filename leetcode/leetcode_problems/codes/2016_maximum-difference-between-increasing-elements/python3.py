"""
Problem: Maximum Difference Between Increasing Elements
Difficulty: Easy
Tags: array

Approach: Track minimum value seen so far, calculate max difference
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def maximumDifference(self, nums: List[int]) -> int:
        min_val = nums[0]
        max_diff = -1
        
        for i in range(1, len(nums)):
            if nums[i] > min_val:
                max_diff = max(max_diff, nums[i] - min_val)
            min_val = min(min_val, nums[i])
        
        return max_diff