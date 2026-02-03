"""
Problem: Minimum One Bit Operations to Make Integers Zero
Difficulty: Hard
Tags: dp, bit manipulation, math

Approach: Gray code pattern - operations follow Gray code sequence
Time Complexity: O(log n)
Space Complexity: O(1)
"""

class Solution:
    def minimumOneBitOperations(self, n: int) -> int:
        result = 0
        while n:
            result ^= n
            n >>= 1
        return result