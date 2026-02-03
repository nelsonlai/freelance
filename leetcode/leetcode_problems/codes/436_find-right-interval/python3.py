"""
Problem: Find Right Interval
Difficulty: Medium
Tags: array, sort, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def findRightInterval(self, intervals: List[List[int]]) -> List[int]:
        n = len(intervals)
        starts = [(intervals[i][0], i) for i in range(n)]
        starts.sort()
        
        result = []
        for interval in intervals:
            end = interval[1]
            left, right = 0, n - 1
            idx = -1
            
            while left <= right:
                mid = (left + right) // 2
                if starts[mid][0] >= end:
                    idx = starts[mid][1]
                    right = mid - 1
                else:
                    left = mid + 1
            
            result.append(idx)
        
        return result