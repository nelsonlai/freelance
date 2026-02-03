"""
Problem: Design Phone Directory
Difficulty: Medium
Tags: array, hash, linked_list, queue

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

class PhoneDirectory:

    def __init__(self, maxNumbers: int):
        self.available = set(range(maxNumbers))
        self.used = set()

    def get(self) -> int:
        if not self.available:
            return -1
        number = self.available.pop()
        self.used.add(number)
        return number

    def check(self, number: int) -> bool:
        return number in self.available

    def release(self, number: int) -> None:
        if number in self.used:
            self.used.remove(number)
            self.available.add(number)