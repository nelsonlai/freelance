"""
Problem: Erect the Fence II
Difficulty: Hard
Tags: array, math, geometry, smallest enclosing circle

Approach: Find smallest circle enclosing all points (Welzl's algorithm)
Time Complexity: O(n) expected
Space Complexity: O(n)
"""

import math

class Solution:
    def outerTrees(self, trees: List[List[int]]) -> List[float]:
        def dist(p1, p2):
            return math.sqrt((p1[0] - p2[0])**2 + (p1[1] - p2[1])**2)
        
        def circle_from_2_points(p1, p2):
            cx = (p1[0] + p2[0]) / 2
            cy = (p1[1] + p2[1]) / 2
            r = dist(p1, p2) / 2
            return (cx, cy, r)
        
        def circle_from_3_points(p1, p2, p3):
            ax, ay = p1[0], p1[1]
            bx, by = p2[0], p2[1]
            cx, cy = p3[0], p3[1]
            
            d = 2 * (ax * (by - cy) + bx * (cy - ay) + cx * (ay - by))
            if abs(d) < 1e-9:
                return None
            
            ux = ((ax**2 + ay**2) * (by - cy) + (bx**2 + by**2) * (cy - ay) + (cx**2 + cy**2) * (ay - by)) / d
            uy = ((ax**2 + ay**2) * (cx - bx) + (bx**2 + by**2) * (ax - cx) + (cx**2 + cy**2) * (bx - ax)) / d
            
            r = dist((ux, uy), p1)
            return (ux, uy, r)
        
        def is_inside(circle, p):
            if circle is None:
                return False
            cx, cy, r = circle
            return dist((cx, cy), p) <= r + 1e-9
        
        def welzl(points, R):
            if len(points) == 0 or len(R) == 3:
                if len(R) == 0:
                    return None
                elif len(R) == 1:
                    return (R[0][0], R[0][1], 0)
                elif len(R) == 2:
                    return circle_from_2_points(R[0], R[1])
                else:
                    return circle_from_3_points(R[0], R[1], R[2])
            
            p = points[0]
            circle = welzl(points[1:], R)
            
            if circle is None or not is_inside(circle, p):
                circle = welzl(points[1:], R + [p])
            
            return circle
        
        if len(trees) == 1:
            return [float(trees[0][0]), float(trees[0][1]), 0.0]
        
        circle = welzl(trees, [])
        return [round(circle[0], 5), round(circle[1], 5), round(circle[2], 5)]