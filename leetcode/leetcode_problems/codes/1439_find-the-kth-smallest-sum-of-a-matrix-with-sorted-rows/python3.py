"""
Problem: Find the Kth Smallest Sum of a Matrix With Sorted Rows
Difficulty: Hard
Tags: array, sort, search, queue, heap

Approach: Use heap to merge sorted rows, keep k smallest sums
Time Complexity: O(m * k * log(k)) where m is rows
Space Complexity: O(k) for heap
"""

import heapq

class Solution:
    def kthSmallest(self, mat: List[List[int]], k: int) -> int:
        heap = [0]
        
        for row in mat:
            new_heap = []
            for sum_val in heap:
                for num in row:
                    heapq.heappush(new_heap, sum_val + num)
                    if len(new_heap) > k:
                        heapq.heappop(new_heap)
            heap = new_heap
        
        return heap[0]