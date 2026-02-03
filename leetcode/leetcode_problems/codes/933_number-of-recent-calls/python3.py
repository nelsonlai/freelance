"""
Problem: Number of Recent Calls
Difficulty: Easy
Tags: queue

Approach: Use deque to maintain calls within [t-3000, t] range
Time Complexity: O(1) amortized per ping
Space Complexity: O(n) for storing calls
"""

from collections import deque

class RecentCounter:

    def __init__(self):
        self.queue = deque()

    def ping(self, t: int) -> int:
        self.queue.append(t)
        # Remove calls outside the 3000ms window
        while self.queue[0] < t - 3000:
            self.queue.popleft()
        return len(self.queue)