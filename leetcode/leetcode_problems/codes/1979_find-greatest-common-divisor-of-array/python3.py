"""
Problem: Find Greatest Common Divisor of Array
Difficulty: Easy
Tags: array, math

Approach: Find GCD of min and max elements
Time Complexity: O(n + log(min, max)) where n is length
Space Complexity: O(1)
"""

import math

class Solution:
    def findGCD(self, nums: List[int]) -> int:
        return math.gcd(min(nums), max(nums))