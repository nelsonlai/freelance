"""
Problem: Widest Vertical Area Between Two Points Containing No Points
Difficulty: Easy
Tags: array, sort

Approach: Sort by x-coordinate, find max difference between consecutive x-coordinates
Time Complexity: O(n log n) for sorting
Space Complexity: O(1)
"""

class Solution:
    def maxWidthOfVerticalArea(self, points: List[List[int]]) -> int:
        x_coords = sorted([p[0] for p in points])
        max_width = 0
        
        for i in range(1, len(x_coords)):
            max_width = max(max_width, x_coords[i] - x_coords[i-1])
        
        return max_width