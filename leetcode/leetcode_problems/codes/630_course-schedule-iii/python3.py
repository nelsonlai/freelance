"""
Problem: Course Schedule III
Difficulty: Hard
Tags: array, greedy, sort, queue, heap

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

import heapq

class Solution:
    def scheduleCourse(self, courses: List[List[int]]) -> int:
        courses.sort(key=lambda x: x[1])
        heap = []
        time = 0
        
        for duration, deadline in courses:
            time += duration
            heapq.heappush(heap, -duration)
            
            if time > deadline:
                time += heapq.heappop(heap)
        
        return len(heap)