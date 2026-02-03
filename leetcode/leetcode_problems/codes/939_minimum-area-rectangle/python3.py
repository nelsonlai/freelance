"""
Problem: Minimum Area Rectangle
Difficulty: Medium
Tags: array, math, hash, sort

Approach: Group points by x-coordinate, for each pair of x-coordinates find common y-coordinates
Time Complexity: O(n^2) in worst case
Space Complexity: O(n) for storing points
"""

class Solution:
    def minAreaRect(self, points: List[List[int]]) -> int:
        from collections import defaultdict
        
        x_to_y = defaultdict(set)
        for x, y in points:
            x_to_y[x].add(y)
        
        min_area = float('inf')
        x_coords = sorted(x_to_y.keys())
        
        for i in range(len(x_coords)):
            for j in range(i + 1, len(x_coords)):
                x1, x2 = x_coords[i], x_coords[j]
                common_y = x_to_y[x1] & x_to_y[x2]
                if len(common_y) >= 2:
                    sorted_y = sorted(common_y)
                    for k in range(len(sorted_y) - 1):
                        height = sorted_y[k + 1] - sorted_y[k]
                        area = abs(x2 - x1) * height
                        min_area = min(min_area, area)
        
        return min_area if min_area != float('inf') else 0