"""
Problem: Maximum Average Pass Ratio
Difficulty: Medium
Tags: array, greedy, queue, heap

Approach: Use max heap - always add student to class with highest improvement
Time Complexity: O(n log n + k log n) where k is extraStudents
Space Complexity: O(n)
"""

import heapq

class Solution:
    def maxAverageRatio(self, classes: List[List[int]], extraStudents: int) -> float:
        def improvement(passed, total):
            return (passed + 1) / (total + 1) - passed / total
        
        heap = [(-improvement(p, t), p, t) for p, t in classes]
        heapq.heapify(heap)
        
        for _ in range(extraStudents):
            _, p, t = heapq.heappop(heap)
            heapq.heappush(heap, (-improvement(p + 1, t + 1), p + 1, t + 1))
        
        return sum(p / t for _, p, t in heap) / len(classes)