"""
Problem: Check If a Number Is Majority Element in a Sorted Array
Difficulty: Easy
Tags: array, sort, search

Approach: Binary search to find first and last occurrence, check if count > n/2
Time Complexity: O(log n) where n is the length of nums
Space Complexity: O(1)
"""

class Solution:
    def isMajorityElement(self, nums: List[int], target: int) -> bool:
        import bisect
        n = len(nums)
        left = bisect.bisect_left(nums, target)
        right = bisect.bisect_right(nums, target)
        count = right - left
        return count > n // 2