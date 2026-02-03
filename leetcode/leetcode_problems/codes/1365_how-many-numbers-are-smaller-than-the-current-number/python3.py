"""
Problem: How Many Numbers Are Smaller Than the Current Number
Difficulty: Easy
Tags: array, hash, sort

Approach: Sort array, use hash map to store count of smaller numbers
Time Complexity: O(n log n) for sorting
Space Complexity: O(n) for sorted array and map
"""

class Solution:
    def smallerNumbersThanCurrent(self, nums: List[int]) -> List[int]:
        sorted_nums = sorted(nums)
        count_map = {}
        for i, num in enumerate(sorted_nums):
            if num not in count_map:
                count_map[num] = i
        return [count_map[num] for num in nums]