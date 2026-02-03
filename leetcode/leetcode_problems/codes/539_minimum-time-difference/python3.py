"""
Problem: Minimum Time Difference
Difficulty: Medium
Tags: array, string, math, sort

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def findMinDifference(self, timePoints: List[str]) -> int:
        def time_to_minutes(time):
            h, m = map(int, time.split(':'))
            return h * 60 + m
        
        minutes = sorted([time_to_minutes(t) for t in timePoints])
        min_diff = float('inf')
        
        for i in range(len(minutes)):
            diff = minutes[i] - minutes[i-1]
            min_diff = min(min_diff, diff, 1440 - diff)
        
        return min_diff