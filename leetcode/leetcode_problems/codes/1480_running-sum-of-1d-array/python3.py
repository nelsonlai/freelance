"""
Problem: Running Sum of 1d Array
Difficulty: Easy
Tags: array

Approach: Calculate prefix sum
Time Complexity: O(n) where n is length of nums
Space Complexity: O(n) for result
"""

class Solution:
    def runningSum(self, nums: List[int]) -> List[int]:
        result = []
        prefix = 0
        for num in nums:
            prefix += num
            result.append(prefix)
        return result