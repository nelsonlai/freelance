"""
Problem: Remove Covered Intervals
Difficulty: Medium
Tags: array, sort

Approach: Sort by start (ascending), end (descending), track max end seen
Time Complexity: O(n log n) for sorting
Space Complexity: O(1)
"""

class Solution:
    def removeCoveredIntervals(self, intervals: List[List[int]]) -> int:
        intervals.sort(key=lambda x: (x[0], -x[1]))
        max_end = -1
        count = 0
        
        for start, end in intervals:
            if end > max_end:
                count += 1
                max_end = end
        
        return count