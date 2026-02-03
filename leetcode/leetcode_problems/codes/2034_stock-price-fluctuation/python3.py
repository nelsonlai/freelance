"""
Problem: Stock Price Fluctuation 
Difficulty: Medium
Tags: hash, queue, heap

Approach: Use hash map for prices, heaps for min/max with lazy deletion
Time Complexity: O(log n) for update, O(1) for current, O(log n) for min/max
Space Complexity: O(n)
"""

import heapq
from collections import defaultdict

class StockPrice:

    def __init__(self):
        self.prices = {}
        self.max_heap = []
        self.min_heap = []
        self.latest_timestamp = 0

    def update(self, timestamp: int, price: int) -> None:
        self.prices[timestamp] = price
        self.latest_timestamp = max(self.latest_timestamp, timestamp)
        heapq.heappush(self.max_heap, (-price, timestamp))
        heapq.heappush(self.min_heap, (price, timestamp))

    def current(self) -> int:
        return self.prices[self.latest_timestamp]

    def maximum(self) -> int:
        while self.max_heap and self.prices[self.max_heap[0][1]] != -self.max_heap[0][0]:
            heapq.heappop(self.max_heap)
        return -self.max_heap[0][0]

    def minimum(self) -> int:
        while self.min_heap and self.prices[self.min_heap[0][1]] != self.min_heap[0][0]:
            heapq.heappop(self.min_heap)
        return self.min_heap[0][0]