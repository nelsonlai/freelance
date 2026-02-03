"""
Problem: Shortest Distance to Target Color
Difficulty: Medium
Tags: array, dp, search

Approach: Precompute left and right distances for each color at each position
Time Complexity: O(n * c + q) where n is length, c is colors, q is queries
Space Complexity: O(n * c) for distance arrays
"""

class Solution:
    def shortestDistanceColor(self, colors: List[int], queries: List[List[int]]) -> List[int]:
        n = len(colors)
        # Precompute distances for each color
        color_positions = {1: [], 2: [], 3: []}
        for i, color in enumerate(colors):
            color_positions[color].append(i)
        
        result = []
        for index, color in queries:
            if color not in color_positions or not color_positions[color]:
                result.append(-1)
                continue
            
            positions = color_positions[color]
            # Binary search for closest position
            import bisect
            pos = bisect.bisect_left(positions, index)
            
            min_dist = float('inf')
            if pos < len(positions):
                min_dist = min(min_dist, abs(positions[pos] - index))
            if pos > 0:
                min_dist = min(min_dist, abs(positions[pos-1] - index))
            
            result.append(min_dist if min_dist != float('inf') else -1)
        
        return result