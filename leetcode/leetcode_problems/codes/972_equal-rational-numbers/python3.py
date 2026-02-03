"""
Problem: Equal Rational Numbers
Difficulty: Hard
Tags: string, math

Approach: Convert both to float with high precision, handle repeating decimals
Time Complexity: O(1)
Space Complexity: O(1)
"""

from fractions import Fraction

class Solution:
    def isRationalEqual(self, s: str, t: str) -> bool:
        def to_float(rational):
            if '.' not in rational:
                return float(rational)
            
            int_part, dec_part = rational.split('.')
            if '(' not in dec_part:
                return float(rational)
            
            non_repeating, repeating = dec_part.split('(')
            repeating = repeating.rstrip(')')
            
            # Convert to fraction
            if repeating:
                non_rep = int(non_repeating) if non_repeating else 0
                rep = int(repeating)
                denom = 10 ** len(non_repeating) * (10 ** len(repeating) - 1)
                num = int(int_part) * denom + non_rep * (10 ** len(repeating) - 1) + rep
                return Fraction(num, denom)
            else:
                return float(rational)
        
        return abs(to_float(s) - to_float(t)) < 1e-9