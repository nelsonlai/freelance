"""
Problem: Check If It Is a Straight Line
Difficulty: Easy
Tags: array, math

Approach: Check if all points have same slope relative to first point
Time Complexity: O(n) where n is number of points
Space Complexity: O(1)
"""

class Solution:
    def checkStraightLine(self, coordinates: List[List[int]]) -> bool:
        if len(coordinates) <= 2:
            return True
        
        x0, y0 = coordinates[0]
        x1, y1 = coordinates[1]
        dx = x1 - x0
        dy = y1 - y0
        
        for i in range(2, len(coordinates)):
            x, y = coordinates[i]
            # Check cross product: (x-x0, y-y0) x (dx, dy) = 0
            if (x - x0) * dy != (y - y0) * dx:
                return False
        
        return True