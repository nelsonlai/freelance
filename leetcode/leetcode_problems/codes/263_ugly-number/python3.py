"""
Problem: Ugly Number
Difficulty: Easy
Tags: math

Approach: Optimized algorithm based on problem constraints
Time Complexity: O(n) to O(n^2) depending on approach
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def isUgly(self, n: int) -> bool:
        if n <= 0:
            return False
        
        for factor in [2, 3, 5]:
            while n % factor == 0:
                n //= factor
        
        return n == 1