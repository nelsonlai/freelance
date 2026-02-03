"""
Problem: Design Circular Queue
Difficulty: Medium
Tags: array, linked_list, queue

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class MyCircularQueue:
    def __init__(self, k: int):
        self.queue = [0] * k
        self.head = 0
        self.count = 0
        self.capacity = k

    def enQueue(self, value: int) -> bool:
        if self.count == self.capacity:
            return False
        self.queue[(self.head + self.count) % self.capacity] = value
        self.count += 1
        return True

    def deQueue(self) -> bool:
        if self.count == 0:
            return False
        self.head = (self.head + 1) % self.capacity
        self.count -= 1
        return True

    def Front(self) -> int:
        if self.count == 0:
            return -1
        return self.queue[self.head]

    def Rear(self) -> int:
        if self.count == 0:
            return -1
        return self.queue[(self.head + self.count - 1) % self.capacity]

    def isEmpty(self) -> bool:
        return self.count == 0

    def isFull(self) -> bool:
        return self.count == self.capacity