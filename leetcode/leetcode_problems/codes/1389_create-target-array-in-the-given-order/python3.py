"""
Problem: Create Target Array in the Given Order
Difficulty: Easy
Tags: array

Approach: Insert nums[i] at index[i] in target array
Time Complexity: O(n^2) due to insertions
Space Complexity: O(n) for result
"""

class Solution:
    def createTargetArray(self, nums: List[int], index: List[int]) -> List[int]:
        result = []
        for i in range(len(nums)):
            result.insert(index[i], nums[i])
        return result