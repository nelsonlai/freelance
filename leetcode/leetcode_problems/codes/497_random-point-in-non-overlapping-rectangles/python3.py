"""
Problem: Random Point in Non-overlapping Rectangles
Difficulty: Medium
Tags: array, math, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

import random

class Solution:

    def __init__(self, rects: List[List[int]]):
        self.rects = rects
        self.weights = []
        for rect in rects:
            x1, y1, x2, y2 = rect
            area = (x2 - x1 + 1) * (y2 - y1 + 1)
            self.weights.append(area)
        
        total = sum(self.weights)
        self.weights = [w / total for w in self.weights]

    def pick(self) -> List[int]:
        rect = random.choices(self.rects, weights=self.weights)[0]
        x1, y1, x2, y2 = rect
        x = random.randint(x1, x2)
        y = random.randint(y1, y2)
        return [x, y]