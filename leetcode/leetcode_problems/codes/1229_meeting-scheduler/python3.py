"""
Problem: Meeting Scheduler
Difficulty: Medium
Tags: array, sort

Approach: Sort slots, use two pointers to find overlapping interval >= duration
Time Complexity: O(n log n) for sorting
Space Complexity: O(1)
"""

class Solution:
    def minAvailableDuration(self, slots1: List[List[int]], slots2: List[List[int]], duration: int) -> List[int]:
        slots1.sort()
        slots2.sort()
        
        i = j = 0
        while i < len(slots1) and j < len(slots2):
            start = max(slots1[i][0], slots2[j][0])
            end = min(slots1[i][1], slots2[j][1])
            
            if end - start >= duration:
                return [start, start + duration]
            
            if slots1[i][1] < slots2[j][1]:
                i += 1
            else:
                j += 1
        
        return []