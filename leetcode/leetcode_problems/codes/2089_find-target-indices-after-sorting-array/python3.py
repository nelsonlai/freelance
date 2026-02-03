"""
Problem: Find Target Indices After Sorting Array
Difficulty: Easy
Tags: array, sort

Approach: Sort array and find all indices where target appears
Time Complexity: O(n log n) where n is array length
Space Complexity: O(1)
"""

class Solution:
    def targetIndices(self, nums: List[int], target: int) -> List[int]:
        nums.sort()
        result = []
        for i, num in enumerate(nums):
            if num == target:
                result.append(i)
        return result