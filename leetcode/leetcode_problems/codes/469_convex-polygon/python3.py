"""
Problem: Convex Polygon
Difficulty: Medium
Tags: array, math

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def isConvex(self, points: List[List[int]]) -> bool:
        def cross_product(o, a, b):
            return (a[0] - o[0]) * (b[1] - o[1]) - (a[1] - o[1]) * (b[0] - o[0])
        
        n = len(points)
        if n < 3:
            return False
        
        prev = 0
        for i in range(n):
            curr = cross_product(points[i], points[(i+1)%n], points[(i+2)%n])
            if curr != 0:
                if prev * curr < 0:
                    return False
                prev = curr
        
        return True