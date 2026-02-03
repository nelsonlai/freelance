"""
Problem: Maximum 69 Number
Difficulty: Easy
Tags: greedy, math

Approach: Convert to string, replace first '6' with '9'
Time Complexity: O(log num)
Space Complexity: O(log num)
"""

class Solution:
    def maximum69Number (self, num: int) -> int:
        s = str(num)
        return int(s.replace('6', '9', 1))