"""
Problem: Process Tasks Using Servers
Difficulty: Medium
Tags: array, queue, heap

Approach: Use two heaps - available servers and busy servers
Time Complexity: O(m log n) where m is tasks, n is servers
Space Complexity: O(n)
"""

import heapq

class Solution:
    def assignTasks(self, servers: List[int], tasks: List[int]) -> List[int]:
        # (weight, index)
        available = [(servers[i], i) for i in range(len(servers))]
        heapq.heapify(available)
        
        # (finish_time, weight, index)
        busy = []
        result = []
        time = 0
        
        for i, task_time in enumerate(tasks):
            time = max(time, i)
            
            # Free up finished servers
            while busy and busy[0][0] <= time:
                finish_time, weight, idx = heapq.heappop(busy)
                heapq.heappush(available, (weight, idx))
            
            # Assign task to available server
            if available:
                weight, idx = heapq.heappop(available)
                result.append(idx)
                heapq.heappush(busy, (time + task_time, weight, idx))
            else:
                # Wait for next server to be free
                finish_time, weight, idx = heapq.heappop(busy)
                time = finish_time
                result.append(idx)
                heapq.heappush(busy, (time + task_time, weight, idx))
        
        return result