"""
Problem: Maximum Number of Darts Inside of a Circular Dartboard
Difficulty: Hard
Tags: array, math

Approach: For each pair of points, find circles containing them, check all points
Time Complexity: O(n^3) where n is number of darts
Space Complexity: O(1)
"""

import math

class Solution:
    def numPoints(self, darts: List[List[int]], r: int) -> int:
        n = len(darts)
        max_count = 1
        
        for i in range(n):
            for j in range(i + 1, n):
                x1, y1 = darts[i]
                x2, y2 = darts[j]
                dx, dy = x2 - x1, y2 - y1
                dist = math.sqrt(dx*dx + dy*dy)
                
                if dist > 2 * r:
                    continue
                
                mid_x, mid_y = (x1 + x2) / 2, (y1 + y2) / 2
                h = math.sqrt(r*r - (dist/2)**2)
                
                # Two possible circle centers
                for sign in [-1, 1]:
                    center_x = mid_x - sign * h * dy / dist
                    center_y = mid_y + sign * h * dx / dist
                    
                    count = 0
                    for x, y in darts:
                        if (x - center_x)**2 + (y - center_y)**2 <= r*r + 1e-9:
                            count += 1
                    max_count = max(max_count, count)
        
        return max_count