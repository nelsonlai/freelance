"""
Problem: Greatest Common Divisor of Strings
Difficulty: Easy
Tags: string, math

Approach: Check if strings are divisible, then find GCD of lengths
Time Complexity: O(n + m) where n and m are string lengths
Space Complexity: O(1)
"""

import math

class Solution:
    def gcdOfStrings(self, str1: str, str2: str) -> str:
        if str1 + str2 != str2 + str1:
            return ""
        
        gcd_len = math.gcd(len(str1), len(str2))
        return str1[:gcd_len]