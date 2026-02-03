"""
Problem: Random Flip Matrix
Difficulty: Medium
Tags: math, hash

Approach: Use hash map for O(1) lookups
Time Complexity: O(n) to O(n^2) depending on approach
Space Complexity: O(n) for hash map
"""

import random

class Solution:

    def __init__(self, m: int, n: int):
        self.m = m
        self.n = n
        self.total = m * n
        self.flipped = set()

    def flip(self) -> List[int]:
        while True:
            idx = random.randint(0, self.total - 1)
            if idx not in self.flipped:
                self.flipped.add(idx)
                return [idx // self.n, idx % self.n]
    
    def reset(self) -> None:
        self.flipped.clear()