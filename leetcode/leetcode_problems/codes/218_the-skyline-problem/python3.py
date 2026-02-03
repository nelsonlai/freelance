"""
Problem: The Skyline Problem
Difficulty: Hard
Tags: array, tree, dp, sort, queue, heap

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

import heapq

class Solution:
    def getSkyline(self, buildings: List[List[int]]) -> List[List[int]]:
        events = []
        for left, right, height in buildings:
            events.append((left, -height, right))
            events.append((right, 0, 0))
        
        events.sort()
        result = []
        heap = [(0, float('inf'))]
        prev_height = 0
        
        for x, neg_height, right in events:
            while heap[0][1] <= x:
                heapq.heappop(heap)
            
            if neg_height:
                heapq.heappush(heap, (neg_height, right))
            
            current_height = -heap[0][0]
            if current_height != prev_height:
                result.append([x, current_height])
                prev_height = current_height
        
        return result