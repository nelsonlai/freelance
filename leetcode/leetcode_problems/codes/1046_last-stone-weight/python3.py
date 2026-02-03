"""
Problem: Last Stone Weight
Difficulty: Easy
Tags: array, queue, heap

Approach: Use max heap to always get two heaviest stones
Time Complexity: O(n log n)
Space Complexity: O(n) for heap
"""

import heapq

class Solution:
    def lastStoneWeight(self, stones: List[int]) -> int:
        heap = [-stone for stone in stones]
        heapq.heapify(heap)
        
        while len(heap) > 1:
            first = -heapq.heappop(heap)
            second = -heapq.heappop(heap)
            
            if first != second:
                heapq.heappush(heap, -(first - second))
        
        return -heap[0] if heap else 0