"""
Problem: Distant Barcodes
Difficulty: Medium
Tags: array, greedy, hash, sort, queue, heap

Approach: Use max heap to alternate most frequent with second most frequent
Time Complexity: O(n log n)
Space Complexity: O(n) for heap
"""

import heapq
from collections import Counter

class Solution:
    def rearrangeBarcodes(self, barcodes: List[int]) -> List[int]:
        count = Counter(barcodes)
        heap = [(-freq, num) for num, freq in count.items()]
        heapq.heapify(heap)
        
        result = []
        prev = None
        
        while heap:
            freq1, num1 = heapq.heappop(heap)
            result.append(num1)
            freq1 += 1
            
            if prev:
                heapq.heappush(heap, prev)
                prev = None
            
            if freq1 < 0:
                prev = (freq1, num1)
        
        return result