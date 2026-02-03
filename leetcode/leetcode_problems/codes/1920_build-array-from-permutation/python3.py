"""
Problem: Build Array from Permutation
Difficulty: Easy
Tags: array

Approach: Build new array using nums as indices
Time Complexity: O(n) where n is length
Space Complexity: O(n)
"""

class Solution:
    def buildArray(self, nums: List[int]) -> List[int]:
        return [nums[nums[i]] for i in range(len(nums))]