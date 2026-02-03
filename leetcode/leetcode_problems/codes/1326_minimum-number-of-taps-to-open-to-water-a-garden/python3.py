"""
Problem: Minimum Number of Taps to Open to Water a Garden
Difficulty: Hard
Tags: array, dp, greedy

Approach: Greedy - convert to intervals, find minimum intervals to cover [0, n]
Time Complexity: O(n log n) for sorting
Space Complexity: O(n) for intervals
"""

class Solution:
    def minTaps(self, n: int, ranges: List[int]) -> int:
        intervals = []
        for i, r in enumerate(ranges):
            intervals.append((max(0, i - r), min(n, i + r)))
        
        intervals.sort()
        
        taps = 0
        covered = 0
        i = 0
        
        while covered < n:
            max_end = covered
            while i < len(intervals) and intervals[i][0] <= covered:
                max_end = max(max_end, intervals[i][1])
                i += 1
            
            if max_end == covered:
                return -1
            
            covered = max_end
            taps += 1
        
        return taps