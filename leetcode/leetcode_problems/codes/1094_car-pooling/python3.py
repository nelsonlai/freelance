"""
Problem: Car Pooling
Difficulty: Medium
Tags: array, sort, queue, heap

Approach: Track passenger changes at each location, check capacity
Time Complexity: O(n log n) for sorting
Space Complexity: O(n) for events
"""

class Solution:
    def carPooling(self, trips: List[List[int]], capacity: int) -> bool:
        events = []
        for num, start, end in trips:
            events.append((start, num))
            events.append((end, -num))
        
        events.sort()
        current = 0
        
        for location, change in events:
            current += change
            if current > capacity:
                return False
        
        return True