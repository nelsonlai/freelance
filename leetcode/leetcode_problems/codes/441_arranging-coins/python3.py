"""
Problem: Arranging Coins
Difficulty: Easy
Tags: math, search

Approach: Optimized algorithm based on problem constraints
Time Complexity: O(n) to O(n^2) depending on approach
Space Complexity: O(1) to O(n) depending on approach
"""

import math

class Solution:
    def arrangeCoins(self, n: int) -> int:
        return int((math.sqrt(8 * n + 1) - 1) // 2)