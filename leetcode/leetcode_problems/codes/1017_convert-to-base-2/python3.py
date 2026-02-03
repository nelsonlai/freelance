"""
Problem: Convert to Base -2
Difficulty: Medium
Tags: string, math

Approach: Convert to base -2 by repeatedly dividing and handling negative remainders
Time Complexity: O(log n)
Space Complexity: O(log n) for result
"""

class Solution:
    def baseNeg2(self, n: int) -> str:
        if n == 0:
            return "0"
        
        result = []
        while n != 0:
            remainder = n % -2
            n //= -2
            if remainder < 0:
                remainder += 2
                n += 1
            result.append(str(remainder))
        
        return ''.join(reversed(result))