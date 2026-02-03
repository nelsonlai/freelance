"""
Problem: XOR Operation in an Array
Difficulty: Easy
Tags: array, math

Approach: Generate array [start, start+2, start+4, ...], XOR all elements
Time Complexity: O(n) where n is array length
Space Complexity: O(1)
"""

class Solution:
    def xorOperation(self, n: int, start: int) -> int:
        result = 0
        for i in range(n):
            result ^= start + 2 * i
        return result