"""
Problem: Seat Reservation Manager
Difficulty: Medium
Tags: queue, heap, design

Approach: Use min heap to track available seats
Time Complexity: O(log n) per operation
Space Complexity: O(n)
"""

import heapq

class SeatManager:

    def __init__(self, n: int):
        self.available = list(range(1, n + 1))
        heapq.heapify(self.available)

    def reserve(self) -> int:
        return heapq.heappop(self.available)

    def unreserve(self, seatNumber: int) -> None:
        heapq.heappush(self.available, seatNumber)