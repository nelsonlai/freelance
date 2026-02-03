"""
Problem: Single-Threaded CPU
Difficulty: Medium
Tags: array, sort, queue, heap

Approach: Sort by enqueue time, use heap to select shortest task
Time Complexity: O(n log n) where n is tasks
Space Complexity: O(n)
"""

import heapq

class Solution:
    def getOrder(self, tasks: List[List[int]]) -> List[int]:
        tasks_with_idx = [(enqueue, process, i) for i, (enqueue, process) in enumerate(tasks)]
        tasks_with_idx.sort()
        
        heap = []
        result = []
        time = 0
        i = 0
        
        while i < len(tasks_with_idx) or heap:
            # Add all available tasks
            while i < len(tasks_with_idx) and tasks_with_idx[i][0] <= time:
                enqueue, process, idx = tasks_with_idx[i]
                heapq.heappush(heap, (process, idx))
                i += 1
            
            if heap:
                process, idx = heapq.heappop(heap)
                result.append(idx)
                time += process
            else:
                time = tasks_with_idx[i][0]
        
        return result