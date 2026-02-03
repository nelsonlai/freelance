"""
Problem: Remove Stones to Minimize the Total
Difficulty: Medium
Tags: array, greedy, queue, heap

Approach: Use max heap to always remove from largest pile
Time Complexity: O(n log n + k log n) where n is piles
Space Complexity: O(n)
"""

import heapq

class Solution:
    def minStoneSum(self, piles: List[int], k: int) -> int:
        heap = [-p for p in piles]
        heapq.heapify(heap)
        
        for _ in range(k):
            largest = -heapq.heappop(heap)
            remove = largest // 2
            heapq.heappush(heap, -(largest - remove))
        
        return sum(-p for p in heap)