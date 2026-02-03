"""
Problem: Design Most Recently Used Queue
Difficulty: Medium
Tags: array, linked_list, queue, design

Approach: Use list, move element to end when fetched
Time Complexity: O(n) for fetch
Space Complexity: O(n)
"""

class MRUQueue:

    def __init__(self, n: int):
        self.queue = list(range(1, n + 1))

    def fetch(self, k: int) -> int:
        val = self.queue.pop(k - 1)
        self.queue.append(val)
        return val