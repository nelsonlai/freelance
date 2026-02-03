"""
Problem: Moving Stones Until Consecutive
Difficulty: Medium
Tags: array, dp, math

Approach: Sort stones, calculate min and max moves
Time Complexity: O(1)
Space Complexity: O(1)
"""

class Solution:
    def numMovesStones(self, a: int, b: int, c: int) -> List[int]:
        stones = sorted([a, b, c])
        x, y, z = stones
        
        max_moves = (z - x - 2)
        
        if z - x == 2:
            min_moves = 0
        elif y - x <= 2 or z - y <= 2:
            min_moves = 1
        else:
            min_moves = 2
        
        return [min_moves, max_moves]