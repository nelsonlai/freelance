"""
Problem: Convert Integer to the Sum of Two No-Zero Integers
Difficulty: Easy
Tags: math

Approach: Try a from 1 to n-1, check if both a and n-a contain no zero
Time Complexity: O(n * log n) in worst case
Space Complexity: O(1)
"""

class Solution:
    def getNoZeroIntegers(self, n: int) -> List[int]:
        def has_no_zero(num):
            while num > 0:
                if num % 10 == 0:
                    return False
                num //= 10
            return True
        
        for a in range(1, n):
            b = n - a
            if has_no_zero(a) and has_no_zero(b):
                return [a, b]
        
        return []