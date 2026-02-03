"""
Problem: Find Nearest Point That Has the Same X or Y Coordinate
Difficulty: Easy
Tags: array

Approach: Find valid points (same x or y), calculate Manhattan distance, return index of nearest
Time Complexity: O(n) where n is number of points
Space Complexity: O(1)
"""

class Solution:
    def nearestValidPoint(self, x: int, y: int, points: List[List[int]]) -> int:
        min_dist = float('inf')
        result = -1
        
        for i, (px, py) in enumerate(points):
            if px == x or py == y:
                dist = abs(px - x) + abs(py - y)
                if dist < min_dist:
                    min_dist = dist
                    result = i
        
        return result