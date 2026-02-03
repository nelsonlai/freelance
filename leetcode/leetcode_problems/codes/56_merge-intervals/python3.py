"""
Problem: Merge Intervals
Difficulty: Medium
Tags: array, sort

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        if not intervals:
            return []
        
        intervals.sort(key=lambda x: x[0])
        result = [intervals[0]]
        
        for current in intervals[1:]:
            if current[0] <= result[-1][1]:
                result[-1][1] = max(result[-1][1], current[1])
            else:
                result.append(current)
        
        return result