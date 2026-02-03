"""
Problem: Construct Target Array With Multiple Sums
Difficulty: Hard
Tags: array, queue, heap

Approach: Reverse process - work backwards from target, use max heap
Time Complexity: O(n log(max(target))) in worst case
Space Complexity: O(n) for heap
"""

import heapq

class Solution:
    def isPossible(self, target: List[int]) -> bool:
        if len(target) == 1:
            return target[0] == 1
        
        total = sum(target)
        heap = [-x for x in target]
        heapq.heapify(heap)
        
        while -heap[0] > 1:
            largest = -heapq.heappop(heap)
            rest = total - largest
            
            if rest == 0 or largest <= rest:
                return False
            
            prev = largest % rest
            if prev == 0:
                prev = rest
            
            total = total - largest + prev
            heapq.heappush(heap, -prev)
        
        return True