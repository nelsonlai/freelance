"""
Problem: Fraction to Recurring Decimal
Difficulty: Medium
Tags: string, math, hash

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

class Solution:
    def fractionToDecimal(self, numerator: int, denominator: int) -> str:
        if numerator == 0:
            return "0"
        
        result = []
        if (numerator < 0) ^ (denominator < 0):
            result.append("-")
        
        num = abs(numerator)
        den = abs(denominator)
        
        result.append(str(num // den))
        remainder = num % den
        
        if remainder == 0:
            return "".join(result)
        
        result.append(".")
        remainder_map = {}
        
        while remainder != 0:
            if remainder in remainder_map:
                result.insert(remainder_map[remainder], "(")
                result.append(")")
                break
            
            remainder_map[remainder] = len(result)
            remainder *= 10
            result.append(str(remainder // den))
            remainder %= den
        
        return "".join(result)