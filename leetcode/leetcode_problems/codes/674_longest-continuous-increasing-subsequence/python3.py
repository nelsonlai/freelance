"""
Problem: Longest Continuous Increasing Subsequence
Difficulty: Easy
Tags: array, sort

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def findLengthOfLCIS(self, nums: List[int]) -> int:
        if not nums:
            return 0
        
        max_length = 1
        current_length = 1
        
        for i in range(1, len(nums)):
            if nums[i] > nums[i-1]:
                current_length += 1
                max_length = max(max_length, current_length)
            else:
                current_length = 1
        
        return max_length