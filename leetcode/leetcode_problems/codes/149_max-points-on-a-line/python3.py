"""
Problem: Max Points on a Line
Difficulty: Hard
Tags: array, math, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import defaultdict
from math import gcd

class Solution:
    def maxPoints(self, points: List[List[int]]) -> int:
        if len(points) <= 2:
            return len(points)
        
        max_points = 0
        
        for i in range(len(points)):
            slope_count = defaultdict(int)
            same_point = 1
            
            for j in range(i + 1, len(points)):
                x1, y1 = points[i]
                x2, y2 = points[j]
                
                if x1 == x2 and y1 == y2:
                    same_point += 1
                else:
                    dx = x2 - x1
                    dy = y2 - y1
                    g = gcd(dx, dy)
                    slope = (dx // g, dy // g)
                    slope_count[slope] += 1
            
            current_max = same_point
            if slope_count:
                current_max += max(slope_count.values())
            max_points = max(max_points, current_max)
        
        return max_points