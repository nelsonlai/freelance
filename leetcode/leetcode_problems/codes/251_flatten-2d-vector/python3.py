"""
Problem: Flatten 2D Vector
Difficulty: Medium
Tags: array

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Vector2D:

    def __init__(self, vec: List[List[int]]):
        self.vec = vec
        self.row = 0
        self.col = 0
        self._advance()

    def _advance(self):
        while self.row < len(self.vec) and self.col >= len(self.vec[self.row]):
            self.row += 1
            self.col = 0

    def next(self) -> int:
        result = self.vec[self.row][self.col]
        self.col += 1
        self._advance()
        return result

    def hasNext(self) -> bool:
        return self.row < len(self.vec)