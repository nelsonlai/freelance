"""
Problem: Kth Smallest Element in a Sorted Matrix
Difficulty: Medium
Tags: array, sort, search, queue, heap

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

import heapq

class Solution:
    def kthSmallest(self, matrix: List[List[int]], k: int) -> int:
        n = len(matrix)
        heap = []
        
        for i in range(min(k, n)):
            heapq.heappush(heap, (matrix[i][0], i, 0))
        
        for _ in range(k - 1):
            val, row, col = heapq.heappop(heap)
            if col + 1 < n:
                heapq.heappush(heap, (matrix[row][col + 1], row, col + 1))
        
        return heap[0][0]