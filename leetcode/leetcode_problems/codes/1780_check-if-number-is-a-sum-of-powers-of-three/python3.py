"""
Problem: Check if Number is a Sum of Powers of Three
Difficulty: Medium
Tags: math, base conversion

Approach: Convert to base 3, check if all digits are 0 or 1 (no digit 2)
Time Complexity: O(log n) where n is the number
Space Complexity: O(1)
"""

class Solution:
    def checkPowersOfThree(self, n: int) -> bool:
        while n > 0:
            if n % 3 == 2:
                return False
            n //= 3
        return True