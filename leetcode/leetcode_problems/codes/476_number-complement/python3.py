"""
Problem: Number Complement
Difficulty: Easy
Tags: general

Approach: Optimized algorithm based on problem constraints
Time Complexity: O(n) to O(n^2) depending on approach
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def findComplement(self, num: int) -> int:
        mask = 1
        while mask < num:
            mask = (mask << 1) | 1
        return num ^ mask