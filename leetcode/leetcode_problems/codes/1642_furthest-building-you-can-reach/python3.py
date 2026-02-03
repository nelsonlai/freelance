"""
Problem: Furthest Building You Can Reach
Difficulty: Medium
Tags: array, greedy, queue, heap

Approach: Use ladders for largest gaps, bricks for smaller ones. Use min heap to track ladder usage.
Time Complexity: O(n log l) where n is buildings, l is ladders
Space Complexity: O(l) for heap
"""

import heapq

class Solution:
    def furthestBuilding(self, heights: List[int], bricks: int, ladders: int) -> int:
        heap = []
        
        for i in range(len(heights) - 1):
            diff = heights[i + 1] - heights[i]
            if diff <= 0:
                continue
            
            if ladders > 0:
                heapq.heappush(heap, diff)
                ladders -= 1
            else:
                if heap and diff > heap[0]:
                    smallest = heapq.heappop(heap)
                    if bricks < smallest:
                        return i
                    bricks -= smallest
                    heapq.heappush(heap, diff)
                else:
                    if bricks < diff:
                        return i
                    bricks -= diff
        
        return len(heights) - 1