"""
Problem: Largest Subarray Length K
Difficulty: Easy
Tags: array, greedy

Approach: Find starting position with maximum first element, return subarray
Time Complexity: O(n) where n is length
Space Complexity: O(k) for result
"""

class Solution:
    def largestSubarray(self, nums: List[int], k: int) -> List[int]:
        max_start = 0
        for i in range(len(nums) - k + 1):
            if nums[i] > nums[max_start]:
                max_start = i
        
        return nums[max_start:max_start + k]