"""
Problem: Determine Color of a Chessboard Square
Difficulty: Easy
Tags: string, math

Approach: Check if sum of row and column indices is even
Time Complexity: O(1)
Space Complexity: O(1)
"""

class Solution:
    def squareIsWhite(self, coordinates: str) -> bool:
        col = ord(coordinates[0]) - ord('a')
        row = int(coordinates[1]) - 1
        return (col + row) % 2 == 1