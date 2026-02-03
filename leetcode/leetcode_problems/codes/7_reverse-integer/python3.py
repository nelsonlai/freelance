"""
Problem: Reverse Integer
Difficulty: Medium
Tags: math

Approach: Optimized algorithm based on problem constraints
Time Complexity: O(n) to O(n^2) depending on approach
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def reverse(self, x: int) -> int:
        INT_MAX = 2**31 - 1
        INT_MIN = -2**31
        
        result = 0
        sign = 1 if x >= 0 else -1
        x = abs(x)
        
        while x != 0:
            digit = x % 10
            x //= 10
            
            if result > (INT_MAX - digit) // 10:
                return 0
            
            result = result * 10 + digit
        
        return sign * result