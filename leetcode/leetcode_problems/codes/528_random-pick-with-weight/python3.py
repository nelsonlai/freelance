"""
Problem: Random Pick with Weight
Difficulty: Medium
Tags: array, math, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

import random
import bisect

class Solution:

    def __init__(self, w: List[int]):
        self.prefix_sum = []
        total = 0
        for weight in w:
            total += weight
            self.prefix_sum.append(total)
        self.total = total

    def pickIndex(self) -> int:
        target = random.randint(1, self.total)
        return bisect.bisect_left(self.prefix_sum, target)