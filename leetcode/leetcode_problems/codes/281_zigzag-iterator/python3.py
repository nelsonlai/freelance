"""
Problem: Zigzag Iterator
Difficulty: Medium
Tags: array, queue

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

from collections import deque

class ZigzagIterator:
    def __init__(self, v1: List[int], v2: List[int]):
        self.queue = deque()
        if v1:
            self.queue.append((0, v1))
        if v2:
            self.queue.append((0, v2))

    def next(self) -> int:
        list_idx, vec = self.queue.popleft()
        val = vec[list_idx]
        list_idx += 1
        if list_idx < len(vec):
            self.queue.append((list_idx, vec))
        return val

    def hasNext(self) -> bool:
        return len(self.queue) > 0