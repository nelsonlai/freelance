"""
Problem: Game of Nim
Difficulty: Medium
Tags: array, dp, math, game theory

Approach: Nim game - XOR of all piles, if non-zero first player wins
Time Complexity: O(n) where n is piles
Space Complexity: O(1)
"""

class Solution:
    def nimGame(self, piles: List[int]) -> bool:
        xor = 0
        for pile in piles:
            xor ^= pile
        return xor != 0