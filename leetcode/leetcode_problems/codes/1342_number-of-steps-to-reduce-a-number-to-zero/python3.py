"""
Problem: Number of Steps to Reduce a Number to Zero
Difficulty: Easy
Tags: math

Approach: Simulate - if even divide by 2, if odd subtract 1
Time Complexity: O(log num)
Space Complexity: O(1)
"""

class Solution:
    def numberOfSteps(self, num: int) -> int:
        steps = 0
        while num > 0:
            if num % 2 == 0:
                num //= 2
            else:
                num -= 1
            steps += 1
        return steps