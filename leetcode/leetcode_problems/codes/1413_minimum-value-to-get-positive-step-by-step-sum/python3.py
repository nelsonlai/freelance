"""
Problem: Minimum Value to Get Positive Step by Step Sum
Difficulty: Easy
Tags: array

Approach: Track minimum prefix sum, return 1 - min_sum (if negative)
Time Complexity: O(n) where n is length of nums
Space Complexity: O(1)
"""

class Solution:
    def minStartValue(self, nums: List[int]) -> int:
        min_sum = 0
        prefix_sum = 0
        
        for num in nums:
            prefix_sum += num
            min_sum = min(min_sum, prefix_sum)
        
        return 1 - min_sum if min_sum < 0 else 1