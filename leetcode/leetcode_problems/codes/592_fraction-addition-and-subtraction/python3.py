"""
Problem: Fraction Addition and Subtraction
Difficulty: Medium
Tags: string, math

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

import re
from math import gcd

class Solution:
    def fractionAddition(self, expression: str) -> str:
        fractions = re.findall(r'([+-]?\d+)/(\d+)', expression)
        
        numerator = 0
        denominator = 1
        
        for num, den in fractions:
            num = int(num)
            den = int(den)
            numerator = numerator * den + num * denominator
            denominator *= den
        
        if numerator == 0:
            return "0/1"
        
        g = gcd(abs(numerator), denominator)
        numerator //= g
        denominator //= g
        
        return f"{numerator}/{denominator}"