"""
Problem: Concatenation of Consecutive Binary Numbers
Difficulty: Medium
Tags: string, math, bit manipulation

Approach: For each number, shift result left by number of bits, then add number
Time Complexity: O(n) where n is input
Space Complexity: O(1)
"""

MOD = 10**9 + 7

class Solution:
    def concatenatedBinary(self, n: int) -> int:
        result = 0
        
        for i in range(1, n + 1):
            bits = i.bit_length()
            result = ((result << bits) | i) % MOD
        
        return result