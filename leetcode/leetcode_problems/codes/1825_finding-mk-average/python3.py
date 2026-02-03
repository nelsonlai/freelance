"""
Problem: Finding MK Average
Difficulty: Hard
Tags: queue, heap, design

Approach: Use deque to maintain window, sorted list for k smallest/largest
Time Complexity: O(log m) per addElement, O(1) per calculateMKAverage
Space Complexity: O(m)
"""

from collections import deque
import bisect

class MKAverage:

    def __init__(self, m: int, k: int):
        self.m = m
        self.k = k
        self.queue = deque()
        self.sorted_list = []

    def addElement(self, num: int) -> None:
        self.queue.append(num)
        bisect.insort(self.sorted_list, num)
        
        if len(self.queue) > self.m:
            removed = self.queue.popleft()
            self.sorted_list.pop(bisect.bisect_left(self.sorted_list, removed))

    def calculateMKAverage(self) -> int:
        if len(self.queue) < self.m:
            return -1
        
        middle_sum = sum(self.sorted_list[self.k:-self.k])
        return middle_sum // (self.m - 2 * self.k)