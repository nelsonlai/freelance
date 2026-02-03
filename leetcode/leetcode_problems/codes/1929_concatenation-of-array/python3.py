"""
Problem: Concatenation of Array
Difficulty: Easy
Tags: array

Approach: Concatenate array with itself
Time Complexity: O(n) where n is length
Space Complexity: O(n)
"""

class Solution:
    def getConcatenation(self, nums: List[int]) -> List[int]:
        return nums + nums