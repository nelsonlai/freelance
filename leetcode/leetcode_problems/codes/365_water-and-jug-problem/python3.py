"""
Problem: Water and Jug Problem
Difficulty: Medium
Tags: math, search

Approach: Optimized algorithm based on problem constraints
Time Complexity: O(n) to O(n^2) depending on approach
Space Complexity: O(1) to O(n) depending on approach
"""

import math

class Solution:
    def canMeasureWater(self, x: int, y: int, target: int) -> bool:
        if x + y < target:
            return False
        if x == target or y == target or x + y == target:
            return True
        return target % math.gcd(x, y) == 0