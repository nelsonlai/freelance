"""
Problem: Sum of Digits in the Minimum Number
Difficulty: Easy
Tags: array, math

Approach: Find minimum, sum its digits, return parity
Time Complexity: O(n + log(min(nums)))
Space Complexity: O(1)
"""

class Solution:
    def sumOfDigits(self, nums: List[int]) -> int:
        min_num = min(nums)
        digit_sum = sum(int(d) for d in str(min_num))
        return 1 - (digit_sum % 2)