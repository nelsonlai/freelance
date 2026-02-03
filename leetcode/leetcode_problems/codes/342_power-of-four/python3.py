"""
Problem: Power of Four
Difficulty: Easy
Tags: math

Approach: Optimized algorithm based on problem constraints
Time Complexity: O(n) to O(n^2) depending on approach
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def isPowerOfFour(self, n: int) -> bool:
        if n <= 0:
            return False
        return n & (n - 1) == 0 and (n - 1) % 3 == 0