"""
Problem: Minimum Flips to Make a OR b Equal to c
Difficulty: Medium
Tags: general

Approach: Check each bit - if c bit is 1, need at least one of a or b to be 1
Time Complexity: O(log(max(a,b,c)))
Space Complexity: O(1)
"""

class Solution:
    def minFlips(self, a: int, b: int, c: int) -> int:
        flips = 0
        while a > 0 or b > 0 or c > 0:
            a_bit = a & 1
            b_bit = b & 1
            c_bit = c & 1
            
            if c_bit == 1:
                if a_bit == 0 and b_bit == 0:
                    flips += 1
            else:
                if a_bit == 1:
                    flips += 1
                if b_bit == 1:
                    flips += 1
            
            a >>= 1
            b >>= 1
            c >>= 1
        
        return flips