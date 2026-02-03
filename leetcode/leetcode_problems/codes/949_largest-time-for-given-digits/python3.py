"""
Problem: Largest Time for Given Digits
Difficulty: Medium
Tags: array, string

Approach: Try all permutations and find valid time with maximum value
Time Complexity: O(4!) = O(24)
Space Complexity: O(1)
"""

from itertools import permutations

class Solution:
    def largestTimeFromDigits(self, arr: List[int]) -> str:
        max_time = -1
        
        for perm in permutations(arr):
            hours = perm[0] * 10 + perm[1]
            minutes = perm[2] * 10 + perm[3]
            
            if 0 <= hours < 24 and 0 <= minutes < 60:
                time_value = hours * 60 + minutes
                max_time = max(max_time, time_value)
        
        if max_time == -1:
            return ""
        
        hours = max_time // 60
        minutes = max_time % 60
        return f"{hours:02d}:{minutes:02d}"