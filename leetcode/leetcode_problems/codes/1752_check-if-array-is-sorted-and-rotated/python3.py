"""
Problem: Check if Array Is Sorted and Rotated
Difficulty: Easy
Tags: array, sort

Approach: Count inversions - should have at most one place where nums[i] > nums[i+1]
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def check(self, nums: List[int]) -> bool:
        inversions = 0
        n = len(nums)
        
        for i in range(n):
            if nums[i] > nums[(i + 1) % n]:
                inversions += 1
        
        return inversions <= 1