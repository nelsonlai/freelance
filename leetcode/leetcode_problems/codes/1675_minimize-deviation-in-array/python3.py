"""
Problem: Minimize Deviation in Array
Difficulty: Hard
Tags: array, greedy, queue, heap

Approach: Make all numbers even, use max heap, repeatedly divide max by 2
Time Complexity: O(n log n * log(max))
Space Complexity: O(n)
"""

import heapq

class Solution:
    def minimumDeviation(self, nums: List[int]) -> int:
        heap = []
        min_val = float('inf')
        
        # Make all numbers even and add to heap
        for num in nums:
            if num % 2 == 1:
                num *= 2
            heapq.heappush(heap, -num)
            min_val = min(min_val, num)
        
        result = float('inf')
        
        while True:
            max_val = -heapq.heappop(heap)
            result = min(result, max_val - min_val)
            
            if max_val % 2 == 1:
                break
            
            new_val = max_val // 2
            min_val = min(min_val, new_val)
            heapq.heappush(heap, -new_val)
        
        return result