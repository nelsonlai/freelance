"""
Problem: Find Servers That Handled Most Number of Requests
Difficulty: Hard
Tags: array, queue, heap

Approach: Use heap to track available servers, count requests per server
Time Complexity: O(n log k) where n is requests, k is servers
Space Complexity: O(k) for heap
"""

import heapq
from sortedcontainers import SortedList

class Solution:
    def busiestServers(self, k: int, arrival: List[int], load: List[int]) -> List[int]:
        available = SortedList(range(k))
        busy = []  # (end_time, server_id)
        count = [0] * k
        
        for i, (arr, ld) in enumerate(zip(arrival, load)):
            # Free up servers that finished
            while busy and busy[0][0] <= arr:
                _, server = heapq.heappop(busy)
                available.add(server)
            
            if not available:
                continue
            
            # Find server starting from i % k
            idx = available.bisect_left(i % k)
            if idx == len(available):
                idx = 0
            
            server = available[idx]
            available.remove(server)
            heapq.heappush(busy, (arr + ld, server))
            count[server] += 1
        
        max_count = max(count)
        return [i for i in range(k) if count[i] == max_count]