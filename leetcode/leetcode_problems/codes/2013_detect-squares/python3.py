"""
Problem: Detect Squares
Difficulty: Medium
Tags: array, hash

Approach: Store points in hash map, for query check all possible squares
Time Complexity: O(n) for count where n is number of points
Space Complexity: O(n) for hash map
"""

from collections import defaultdict

class DetectSquares:

    def __init__(self):
        self.points = defaultdict(int)

    def add(self, point: List[int]) -> None:
        self.points[tuple(point)] += 1

    def count(self, point: List[int]) -> int:
        x, y = point
        result = 0
        
        for (px, py), count in self.points.items():
            if px == x and py == y:
                continue
            
            # Check if can form square: (x, y), (px, py), (x, py), (px, y)
            if abs(px - x) == abs(py - y) and abs(px - x) > 0:
                # Check if other two corners exist
                corner1 = (x, py)
                corner2 = (px, y)
                
                if corner1 in self.points and corner2 in self.points:
                    result += count * self.points[corner1] * self.points[corner2]
        
        return result