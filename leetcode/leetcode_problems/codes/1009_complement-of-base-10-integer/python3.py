"""
Problem: Complement of Base 10 Integer
Difficulty: Easy
Tags: general

Approach: Flip all bits - find mask with all 1s for number of bits in n
Time Complexity: O(log n)
Space Complexity: O(1)
"""

class Solution:
    def bitwiseComplement(self, n: int) -> int:
        if n == 0:
            return 1
        
        mask = 1
        while mask <= n:
            mask <<= 1
        
        return (mask - 1) ^ n