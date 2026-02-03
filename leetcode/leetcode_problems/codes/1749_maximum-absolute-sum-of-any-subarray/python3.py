"""
Problem: Maximum Absolute Sum of Any Subarray
Difficulty: Medium
Tags: array, dp, kadane

Approach: Find max and min subarray sums, return max absolute value
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def maxAbsoluteSum(self, nums: List[int]) -> int:
        max_sum = min_sum = 0
        max_so_far = min_so_far = 0
        
        for num in nums:
            max_so_far = max(num, max_so_far + num)
            min_so_far = min(num, min_so_far + num)
            max_sum = max(max_sum, max_so_far)
            min_sum = min(min_sum, min_so_far)
        
        return max(abs(max_sum), abs(min_sum))