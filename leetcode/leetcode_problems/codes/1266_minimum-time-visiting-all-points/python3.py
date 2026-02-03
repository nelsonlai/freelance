"""
Problem: Minimum Time Visiting All Points
Difficulty: Easy
Tags: array, math

Approach: Chebyshev distance - max of horizontal and vertical distance
Time Complexity: O(n) where n is number of points
Space Complexity: O(1)
"""

class Solution:
    def minTimeToVisitAllPoints(self, points: List[List[int]]) -> int:
        time = 0
        for i in range(len(points) - 1):
            dx = abs(points[i+1][0] - points[i][0])
            dy = abs(points[i+1][1] - points[i][1])
            time += max(dx, dy)
        return time