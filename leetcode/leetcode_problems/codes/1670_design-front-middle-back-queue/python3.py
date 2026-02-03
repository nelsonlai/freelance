"""
Problem: Design Front Middle Back Queue
Difficulty: Medium
Tags: array, linked_list, queue, deque

Approach: Use deque for O(1) operations, calculate middle index
Time Complexity: O(1) for all operations except pushMiddle/popMiddle which are O(n)
Space Complexity: O(n)
"""

from collections import deque

class FrontMiddleBackQueue:

    def __init__(self):
        self.queue = deque()

    def pushFront(self, val: int) -> None:
        self.queue.appendleft(val)

    def pushMiddle(self, val: int) -> None:
        mid = len(self.queue) // 2
        self.queue.insert(mid, val)

    def pushBack(self, val: int) -> None:
        self.queue.append(val)

    def popFront(self) -> int:
        return self.queue.popleft() if self.queue else -1

    def popMiddle(self) -> int:
        if not self.queue:
            return -1
        mid = (len(self.queue) - 1) // 2
        val = self.queue[mid]
        del self.queue[mid]
        return val

    def popBack(self) -> int:
        return self.queue.pop() if self.queue else -1