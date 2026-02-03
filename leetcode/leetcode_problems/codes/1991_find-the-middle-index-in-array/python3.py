"""
Problem: Find the Middle Index in Array
Difficulty: Easy
Tags: array, prefix sum

Approach: Find index where left sum equals right sum
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def findMiddleIndex(self, nums: List[int]) -> int:
        total = sum(nums)
        left_sum = 0
        
        for i, num in enumerate(nums):
            if left_sum == total - left_sum - num:
                return i
            left_sum += num
        
        return -1