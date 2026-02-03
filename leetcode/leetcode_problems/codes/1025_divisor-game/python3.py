"""
Problem: Divisor Game
Difficulty: Easy
Tags: dp, math

Approach: Alice wins if n is even (can always subtract 1)
Time Complexity: O(1)
Space Complexity: O(1)
"""

class Solution:
    def divisorGame(self, n: int) -> bool:
        return n % 2 == 0