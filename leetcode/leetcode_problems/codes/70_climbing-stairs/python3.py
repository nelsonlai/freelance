"""
Problem: Climbing Stairs
Difficulty: Easy
Tags: dp, math

Approach: Dynamic programming with memoization or tabulation
Time Complexity: O(n * m) where n and m are problem dimensions
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def climbStairs(self, n: int) -> int:
        if n < 3:
            return n
        
        first, second = 1, 2
        for i in range(3, n + 1):
            first, second = second, first + second
        
        return second