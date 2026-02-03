"""
Problem: Minimum Number of Arrows to Burst Balloons
Difficulty: Medium
Tags: array, greedy, sort

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def findMinArrowShots(self, points: List[List[int]]) -> int:
        if not points:
            return 0
        
        points.sort(key=lambda x: x[1])
        arrows = 1
        end = points[0][1]
        
        for i in range(1, len(points)):
            if points[i][0] > end:
                arrows += 1
                end = points[i][1]
        
        return arrows