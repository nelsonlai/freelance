"""
Problem: Minimum Area Rectangle II
Difficulty: Medium
Tags: array, math, hash

Approach: For each pair of points, find diagonal pairs that form rectangles
Time Complexity: O(n^2) in worst case
Space Complexity: O(n) for point set
"""

class Solution:
    def minAreaFreeRect(self, points: List[List[int]]) -> float:
        from collections import defaultdict
        
        point_set = {(x, y) for x, y in points}
        min_area = float('inf')
        
        for i in range(len(points)):
            for j in range(i + 1, len(points)):
                x1, y1 = points[i]
                x2, y2 = points[j]
                
                # Check if this pair can be a diagonal
                for k in range(len(points)):
                    if k == i or k == j:
                        continue
                    x3, y3 = points[k]
                    
                    # Vector from point i to point j
                    dx1, dy1 = x2 - x1, y2 - y1
                    # Vector from point i to point k
                    dx2, dy2 = x3 - x1, y3 - y1
                    
                    # Check if they form a right angle (dot product = 0)
                    if dx1 * dx2 + dy1 * dy2 == 0:
                        # Calculate fourth point
                        x4, y4 = x1 + dx1 + dx2, y1 + dy1 + dy2
                        if (x4, y4) in point_set:
                            # Calculate area
                            area = abs(dx1 * dy2 - dx2 * dy1)
                            min_area = min(min_area, area)
        
        return min_area if min_area != float('inf') else 0.0