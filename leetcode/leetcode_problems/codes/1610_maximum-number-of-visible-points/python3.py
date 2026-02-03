"""
Problem: Maximum Number of Visible Points
Difficulty: Hard
Tags: array, math, sort, sliding window

Approach: Convert points to angles relative to location, use sliding window to find max points in angle range
Time Complexity: O(n log n) for sorting angles
Space Complexity: O(n) for angles
"""

import math

class Solution:
    def visiblePoints(self, points: List[List[int]], angle: int, location: List[int]) -> int:
        x0, y0 = location
        angles = []
        same_point = 0
        
        for x, y in points:
            if x == x0 and y == y0:
                same_point += 1
                continue
            
            angle_rad = math.atan2(y - y0, x - x0)
            angle_deg = math.degrees(angle_rad)
            angles.append(angle_deg)
        
        angles.sort()
        # Duplicate angles to handle wrap-around
        angles += [a + 360 for a in angles]
        
        max_count = 0
        left = 0
        
        for right in range(len(angles)):
            while angles[right] - angles[left] > angle:
                left += 1
            max_count = max(max_count, right - left + 1)
        
        return max_count + same_point