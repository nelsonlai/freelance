"""
Problem: The Number of the Smallest Unoccupied Chair
Difficulty: Medium
Tags: array, hash, queue, heap

Approach: Use heap to track available chairs and occupied chairs
Time Complexity: O(n log n) where n is friends
Space Complexity: O(n)
"""

import heapq

class Solution:
    def smallestChair(self, times: List[List[int]], targetFriend: int) -> int:
        n = len(times)
        events = []
        for i, (arrival, leave) in enumerate(times):
            events.append((arrival, 1, i))
            events.append((leave, 0, i))
        
        events.sort()
        available = list(range(n))
        heapq.heapify(available)
        occupied = {}  # friend -> chair
        chair_map = {}  # friend -> chair
        
        for time, event_type, friend in events:
            if event_type == 0:  # leave
                chair = chair_map[friend]
                heapq.heappush(available, chair)
            else:  # arrive
                chair = heapq.heappop(available)
                chair_map[friend] = chair
                if friend == targetFriend:
                    return chair
        
        return -1