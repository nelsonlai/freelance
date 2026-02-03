"""
Problem: Design Bounded Blocking Queue
Difficulty: Medium
Tags: queue

Approach: Use threading locks and condition variables for thread-safe queue
Time Complexity: O(1) per operation
Space Complexity: O(capacity) for queue
"""

import threading
from collections import deque

class BoundedBlockingQueue(object):

    def __init__(self, capacity: int):
        self.capacity = capacity
        self.queue = deque()
        self.lock = threading.Lock()
        self.not_full = threading.Condition(self.lock)
        self.not_empty = threading.Condition(self.lock)

    def enqueue(self, element: int) -> None:
        with self.not_full:
            while len(self.queue) >= self.capacity:
                self.not_full.wait()
            self.queue.append(element)
            self.not_empty.notify()

    def dequeue(self) -> int:
        with self.not_empty:
            while len(self.queue) == 0:
                self.not_empty.wait()
            element = self.queue.popleft()
            self.not_full.notify()
            return element

    def size(self) -> int:
        with self.lock:
            return len(self.queue)