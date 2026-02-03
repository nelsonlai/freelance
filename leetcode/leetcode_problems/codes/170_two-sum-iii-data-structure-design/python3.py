"""
Problem: Two Sum III - Data structure design
Difficulty: Easy
Tags: array, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import defaultdict

class TwoSum:

    def __init__(self):
        self.numbers = defaultdict(int)

    def add(self, number: int) -> None:
        self.numbers[number] += 1

    def find(self, value: int) -> bool:
        for num in self.numbers:
            complement = value - num
            if complement in self.numbers:
                if complement != num or self.numbers[num] > 1:
                    return True
        return False