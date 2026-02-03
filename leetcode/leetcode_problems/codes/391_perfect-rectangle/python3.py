"""
Problem: Perfect Rectangle
Difficulty: Hard
Tags: array, math, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import defaultdict

class Solution:
    def isRectangleCover(self, rectangles: List[List[int]]) -> bool:
        corners = defaultdict(int)
        area = 0
        min_x = min_y = float('inf')
        max_x = max_y = float('-inf')
        
        for x1, y1, x2, y2 in rectangles:
            min_x = min(min_x, x1)
            min_y = min(min_y, y1)
            max_x = max(max_x, x2)
            max_y = max(max_y, y2)
            
            area += (x2 - x1) * (y2 - y1)
            
            corners[(x1, y1)] += 1
            corners[(x1, y2)] += 1
            corners[(x2, y1)] += 1
            corners[(x2, y2)] += 1
        
        expected_area = (max_x - min_x) * (max_y - min_y)
        if area != expected_area:
            return False
        
        corner_points = {(min_x, min_y), (min_x, max_y), (max_x, min_y), (max_x, max_y)}
        
        for point in corners:
            count = corners[point]
            if point in corner_points:
                if count != 1:
                    return False
            else:
                if count % 2 != 0:
                    return False
        
        return True