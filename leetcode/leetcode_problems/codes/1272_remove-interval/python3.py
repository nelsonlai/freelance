"""
Problem: Remove Interval
Difficulty: Medium
Tags: array, sort

Approach: For each interval, split if it overlaps with toBeRemoved
Time Complexity: O(n) where n is number of intervals
Space Complexity: O(n) for result
"""

class Solution:
    def removeInterval(self, intervals: List[List[int]], toBeRemoved: List[int]) -> List[List[int]]:
        result = []
        remove_start, remove_end = toBeRemoved
        
        for start, end in intervals:
            if end <= remove_start or start >= remove_end:
                # No overlap
                result.append([start, end])
            else:
                # Overlap - split if needed
                if start < remove_start:
                    result.append([start, remove_start])
                if end > remove_end:
                    result.append([remove_end, end])
        
        return result