"""
Problem: Queries on Number of Points Inside a Circle
Difficulty: Medium
Tags: array, math

Approach: For each query, count points within circle using distance formula
Time Complexity: O(q * p) where q is queries, p is points
Space Complexity: O(q)
"""

class Solution:
    def countPoints(self, points: List[List[int]], queries: List[List[int]]) -> List[int]:
        result = []
        
        for x, y, r in queries:
            count = 0
            for px, py in points:
                dx = px - x
                dy = py - y
                if dx * dx + dy * dy <= r * r:
                    count += 1
            result.append(count)
        
        return result