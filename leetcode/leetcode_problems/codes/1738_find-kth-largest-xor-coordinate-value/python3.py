"""
Problem: Find Kth Largest XOR Coordinate Value
Difficulty: Medium
Tags: array, sort, queue, heap, prefix xor

Approach: Calculate 2D prefix XOR, use heap to find kth largest
Time Complexity: O(m * n * log(k)) where m, n are dimensions
Space Complexity: O(m * n)
"""

import heapq

class Solution:
    def kthLargestValue(self, matrix: List[List[int]], k: int) -> int:
        m, n = len(matrix), len(matrix[0])
        heap = []
        
        # Calculate prefix XOR
        for i in range(m):
            for j in range(n):
                if i > 0:
                    matrix[i][j] ^= matrix[i-1][j]
                if j > 0:
                    matrix[i][j] ^= matrix[i][j-1]
                if i > 0 and j > 0:
                    matrix[i][j] ^= matrix[i-1][j-1]
                
                heapq.heappush(heap, matrix[i][j])
                if len(heap) > k:
                    heapq.heappop(heap)
        
        return heap[0]