"""
Problem: Perform String Shifts
Difficulty: Easy
Tags: array, string, math

Approach: Calculate net shift amount, rotate string
Time Complexity: O(n) where n is length of s
Space Complexity: O(n) for result
"""

class Solution:
    def stringShift(self, s: str, shift: List[List[int]]) -> str:
        total_shift = 0
        for direction, amount in shift:
            if direction == 0:
                total_shift -= amount
            else:
                total_shift += amount
        
        total_shift %= len(s)
        return s[-total_shift:] + s[:-total_shift]