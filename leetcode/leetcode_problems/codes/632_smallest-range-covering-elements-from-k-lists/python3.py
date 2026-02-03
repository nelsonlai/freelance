"""
Problem: Smallest Range Covering Elements from K Lists
Difficulty: Hard
Tags: array, greedy, hash, sort, queue, heap

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

import heapq

class Solution:
    def smallestRange(self, nums: List[List[int]]) -> List[int]:
        heap = []
        max_val = float('-inf')
        
        for i, arr in enumerate(nums):
            heapq.heappush(heap, (arr[0], i, 0))
            max_val = max(max_val, arr[0])
        
        result = [heap[0][0], max_val]
        pointers = [0] * len(nums)
        
        while True:
            val, list_idx, idx = heapq.heappop(heap)
            
            if max_val - val < result[1] - result[0]:
                result = [val, max_val]
            
            if idx + 1 >= len(nums[list_idx]):
                break
            
            next_val = nums[list_idx][idx + 1]
            max_val = max(max_val, next_val)
            heapq.heappush(heap, (next_val, list_idx, idx + 1))
        
        return result