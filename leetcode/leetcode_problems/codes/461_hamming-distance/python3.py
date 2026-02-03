"""
Problem: Hamming Distance
Difficulty: Easy
Tags: general

Approach: Optimized algorithm based on problem constraints
Time Complexity: O(n) to O(n^2) depending on approach
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def hammingDistance(self, x: int, y: int) -> int:
        xor = x ^ y
        count = 0
        while xor:
            count += xor & 1
            xor >>= 1
        return count