"""
Problem: First Unique Number
Difficulty: Medium
Tags: array, hash, queue

Approach: Use OrderedDict to maintain insertion order, track counts
Time Complexity: O(1) for showFirstUnique, O(1) for add
Space Complexity: O(n) for counts and queue
"""

from collections import OrderedDict

class FirstUnique:

    def __init__(self, nums: List[int]):
        self.count = {}
        self.unique = OrderedDict()
        for num in nums:
            self.add(num)

    def showFirstUnique(self) -> int:
        if self.unique:
            return next(iter(self.unique))
        return -1

    def add(self, value: int) -> None:
        if value not in self.count:
            self.count[value] = 1
            self.unique[value] = None
        else:
            self.count[value] += 1
            if value in self.unique:
                del self.unique[value]