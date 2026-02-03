"""
Problem: Largest Perimeter Triangle
Difficulty: Easy
Tags: array, greedy, math, sort

Approach: Sort and check from largest - triangle inequality: a < b + c
Time Complexity: O(n log n) for sorting
Space Complexity: O(1)
"""

class Solution:
    def largestPerimeter(self, nums: List[int]) -> int:
        nums.sort(reverse=True)
        for i in range(len(nums) - 2):
            if nums[i] < nums[i + 1] + nums[i + 2]:
                return nums[i] + nums[i + 1] + nums[i + 2]
        return 0