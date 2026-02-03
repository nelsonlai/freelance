"""
Problem: Nim Game
Difficulty: Easy
Tags: math, heap

Approach: Optimized algorithm based on problem constraints
Time Complexity: O(n) to O(n^2) depending on approach
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def canWinNim(self, n: int) -> bool:
        return n % 4 != 0