"""
Problem: Design Circular Deque
Difficulty: Medium
Tags: array, linked_list, queue

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class MyCircularDeque:
    def __init__(self, k: int):
        self.queue = [0] * k
        self.head = 0
        self.count = 0
        self.capacity = k

    def insertFront(self, value: int) -> bool:
        if self.count == self.capacity:
            return False
        self.head = (self.head - 1 + self.capacity) % self.capacity
        self.queue[self.head] = value
        self.count += 1
        return True

    def insertLast(self, value: int) -> bool:
        if self.count == self.capacity:
            return False
        tail = (self.head + self.count) % self.capacity
        self.queue[tail] = value
        self.count += 1
        return True

    def deleteFront(self) -> bool:
        if self.count == 0:
            return False
        self.head = (self.head + 1) % self.capacity
        self.count -= 1
        return True

    def deleteLast(self) -> bool:
        if self.count == 0:
            return False
        self.count -= 1
        return True

    def getFront(self) -> int:
        if self.count == 0:
            return -1
        return self.queue[self.head]

    def getRear(self) -> int:
        if self.count == 0:
            return -1
        tail = (self.head + self.count - 1) % self.capacity
        return self.queue[tail]

    def isEmpty(self) -> bool:
        return self.count == 0

    def isFull(self) -> bool:
        return self.count == self.capacity