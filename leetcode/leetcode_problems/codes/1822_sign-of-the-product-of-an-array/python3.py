"""
Problem: Sign of the Product of an Array
Difficulty: Easy
Tags: array, math

Approach: Count negative numbers, return sign
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def arraySign(self, nums: List[int]) -> int:
        negative_count = 0
        for num in nums:
            if num == 0:
                return 0
            if num < 0:
                negative_count += 1
        return 1 if negative_count % 2 == 0 else -1