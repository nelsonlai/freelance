"""
Problem: Armstrong Number
Difficulty: Easy
Tags: math

Approach: Calculate sum of digits raised to power of number of digits
Time Complexity: O(d) where d is the number of digits
Space Complexity: O(1)
"""

class Solution:
    def isArmstrong(self, n: int) -> bool:
        digits = str(n)
        k = len(digits)
        total = sum(int(d) ** k for d in digits)
        return total == n