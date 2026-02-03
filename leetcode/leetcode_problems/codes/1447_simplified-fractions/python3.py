"""
Problem: Simplified Fractions
Difficulty: Medium
Tags: string, math

Approach: Generate all fractions, only include if GCD(numerator, denominator) == 1
Time Complexity: O(n^2 * log n) for GCD calculations
Space Complexity: O(n^2) for result
"""

import math

class Solution:
    def simplifiedFractions(self, n: int) -> List[str]:
        result = []
        for denominator in range(2, n + 1):
            for numerator in range(1, denominator):
                if math.gcd(numerator, denominator) == 1:
                    result.append(f"{numerator}/{denominator}")
        return result