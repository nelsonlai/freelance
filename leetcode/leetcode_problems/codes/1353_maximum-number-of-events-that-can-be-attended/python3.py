"""
Problem: Maximum Number of Events That Can Be Attended
Difficulty: Medium
Tags: array, greedy, sort, queue, heap

Approach: Greedy - sort by end time, use heap to track available events each day
Time Complexity: O(n log n) where n is number of events
Space Complexity: O(n) for heap
"""

import heapq

class Solution:
    def maxEvents(self, events: List[List[int]]) -> int:
        events.sort(key=lambda x: x[0])
        heap = []
        i = 0
        count = 0
        max_day = max(end for _, end in events)
        
        for day in range(1, max_day + 1):
            # Add events that start today
            while i < len(events) and events[i][0] == day:
                heapq.heappush(heap, events[i][1])
                i += 1
            
            # Remove events that have ended
            while heap and heap[0] < day:
                heapq.heappop(heap)
            
            # Attend one event today
            if heap:
                heapq.heappop(heap)
                count += 1
        
        return count