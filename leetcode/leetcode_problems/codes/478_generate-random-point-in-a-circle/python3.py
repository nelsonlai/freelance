"""
Problem: Generate Random Point in a Circle
Difficulty: Medium
Tags: array, dp, math

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

import random
import math

class Solution:

    def __init__(self, radius: float, x_center: float, y_center: float):
        self.radius = radius
        self.x_center = x_center
        self.y_center = y_center

    def randPoint(self) -> List[float]:
        angle = random.uniform(0, 2 * math.pi)
        r = self.radius * math.sqrt(random.uniform(0, 1))
        x = self.x_center + r * math.cos(angle)
        y = self.y_center + r * math.sin(angle)
        return [x, y]