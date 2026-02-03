"""
Problem: Elimination Game
Difficulty: Medium
Tags: math, sort

Approach: Optimized algorithm based on problem constraints
Time Complexity: O(n) to O(n^2) depending on approach
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def lastRemaining(self, n: int) -> int:
        left = True
        remaining = n
        step = 1
        head = 1
        
        while remaining > 1:
            if left or remaining % 2 == 1:
                head += step
            remaining //= 2
            step *= 2
            left = not left
        
        return head