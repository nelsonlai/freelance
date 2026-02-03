"""
Problem: Coordinate With Maximum Network Quality
Difficulty: Medium
Tags: array, graph, simulation

Approach: Try all integer coordinates in range, calculate signal quality from all towers
Time Complexity: O(n * range^2) where range is coordinate range
Space Complexity: O(1)
"""

import math

class Solution:
    def bestCoordinate(self, towers: List[List[int]], radius: int) -> List[int]:
        min_x = min(t[0] for t in towers)
        max_x = max(t[0] for t in towers)
        min_y = min(t[1] for t in towers)
        max_y = max(t[1] for t in towers)
        
        max_quality = 0
        result = [0, 0]
        
        for x in range(min_x, max_x + 1):
            for y in range(min_y, max_y + 1):
                quality = 0
                for tx, ty, q in towers:
                    dist = math.sqrt((x - tx)**2 + (y - ty)**2)
                    if dist <= radius:
                        quality += int(q / (1 + dist))
                
                if quality > max_quality or (quality == max_quality and (x < result[0] or (x == result[0] and y < result[1]))):
                    max_quality = quality
                    result = [x, y]
        
        return result