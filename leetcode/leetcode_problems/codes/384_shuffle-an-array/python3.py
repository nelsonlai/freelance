"""
Problem: Shuffle an Array
Difficulty: Medium
Tags: array, math

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

import random

class Solution:

    def __init__(self, nums: List[int]):
        self.original = nums[:]
        self.nums = nums[:]

    def reset(self) -> List[int]:
        self.nums = self.original[:]
        return self.nums

    def shuffle(self) -> List[int]:
        for i in range(len(self.nums) - 1, 0, -1):
            j = random.randint(0, i)
            self.nums[i], self.nums[j] = self.nums[j], self.nums[i]
        return self.nums