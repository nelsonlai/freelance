"""
Problem: Find the Winner of the Circular Game
Difficulty: Medium
Tags: array, math, queue, josephus

Approach: Josephus problem - recursive or iterative solution
Time Complexity: O(n) where n is players
Space Complexity: O(1)
"""

class Solution:
    def findTheWinner(self, n: int, k: int) -> int:
        winner = 0
        for i in range(2, n + 1):
            winner = (winner + k) % i
        return winner + 1