"""
Problem: Design a Stack With Increment Operation
Difficulty: Medium
Tags: array, stack

Approach: Use lazy increment - store increments in separate array
Time Complexity: O(1) for all operations
Space Complexity: O(n) for stack and increments
"""

class CustomStack:

    def __init__(self, maxSize: int):
        self.stack = []
        self.maxSize = maxSize
        self.increments = []

    def push(self, x: int) -> None:
        if len(self.stack) < self.maxSize:
            self.stack.append(x)
            self.increments.append(0)

    def pop(self) -> int:
        if not self.stack:
            return -1
        
        if len(self.increments) > 1:
            self.increments[-2] += self.increments[-1]
        
        return self.stack.pop() + self.increments.pop()

    def increment(self, k: int, val: int) -> None:
        if self.increments:
            idx = min(k, len(self.increments)) - 1
            if idx >= 0:
                self.increments[idx] += val