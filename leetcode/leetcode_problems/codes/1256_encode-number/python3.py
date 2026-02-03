"""
Problem: Encode Number
Difficulty: Medium
Tags: string, math

Approach: Convert num+1 to binary, remove leading 1
Time Complexity: O(log num)
Space Complexity: O(log num)
"""

class Solution:
    def encode(self, num: int) -> str:
        if num == 0:
            return ""
        return bin(num + 1)[3:]