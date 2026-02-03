"""
Problem: Remove 9
Difficulty: Hard
Tags: math

Approach: Optimized algorithm based on problem constraints
Time Complexity: O(n) to O(n^2) depending on approach
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def newInteger(self, n: int) -> int:
        result = 0
        base = 1
        
        while n > 0:
            result += (n % 9) * base
            n //= 9
            base *= 10
        
        return result