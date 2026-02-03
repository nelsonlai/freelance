"""
Problem: Number of Steps to Reduce a Number in Binary Representation to One
Difficulty: Medium
Tags: string

Approach: Simulate - if even divide by 2, if odd add 1, count steps
Time Complexity: O(n) where n is length of s
Space Complexity: O(1)
"""

class Solution:
    def numSteps(self, s: str) -> int:
        steps = 0
        carry = 0
        
        for i in range(len(s) - 1, 0, -1):
            digit = int(s[i]) + carry
            if digit % 2 == 1:
                steps += 2
                carry = 1
            else:
                steps += 1
                carry = 0
        
        return steps + carry