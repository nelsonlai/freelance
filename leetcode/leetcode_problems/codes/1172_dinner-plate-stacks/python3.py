"""
Problem: Dinner Plate Stacks
Difficulty: Hard
Tags: hash, stack, queue, heap

Approach: Use list of stacks, min heap to track non-full stacks for push, track rightmost non-empty for pop
Time Complexity: O(log n) for push/pop where n is number of stacks
Space Complexity: O(n) for stacks and heap
"""

import heapq

class DinnerPlates:

    def __init__(self, capacity: int):
        self.capacity = capacity
        self.stacks = []
        self.available = []  # Min heap of indices of non-full stacks

    def push(self, val: int) -> None:
        # Find first available stack
        while self.available and (self.available[0] >= len(self.stacks) or len(self.stacks[self.available[0]]) >= self.capacity):
            heapq.heappop(self.available)
        
        if not self.available:
            self.stacks.append([])
            heapq.heappush(self.available, len(self.stacks) - 1)
        
        idx = self.available[0]
        self.stacks[idx].append(val)
        
        if len(self.stacks[idx]) >= self.capacity:
            heapq.heappop(self.available)

    def pop(self) -> int:
        # Pop from rightmost non-empty stack
        while self.stacks and not self.stacks[-1]:
            self.stacks.pop()
        
        if not self.stacks:
            return -1
        
        val = self.stacks[-1].pop()
        idx = len(self.stacks) - 1
        
        if len(self.stacks[-1]) < self.capacity:
            heapq.heappush(self.available, idx)
        
        return val

    def popAtStack(self, index: int) -> int:
        if index >= len(self.stacks) or not self.stacks[index]:
            return -1
        
        val = self.stacks[index].pop()
        if len(self.stacks[index]) < self.capacity:
            heapq.heappush(self.available, index)
        
        return val