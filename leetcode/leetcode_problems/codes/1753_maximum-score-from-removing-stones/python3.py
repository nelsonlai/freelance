"""
Problem: Maximum Score From Removing Stones
Difficulty: Medium
Tags: greedy, math, queue, heap

Approach: Always remove from two largest piles
Time Complexity: O(n) where n is total stones
Space Complexity: O(1)
"""

import heapq

class Solution:
    def maximumScore(self, a: int, b: int, c: int) -> int:
        heap = [-a, -b, -c]
        heapq.heapify(heap)
        score = 0
        
        while len(heap) >= 2:
            first = -heapq.heappop(heap)
            second = -heapq.heappop(heap)
            
            if first > 0 and second > 0:
                score += 1
                first -= 1
                second -= 1
                
                if first > 0:
                    heapq.heappush(heap, -first)
                if second > 0:
                    heapq.heappush(heap, -second)
        
        return score