"""
Problem: Line Reflection
Difficulty: Medium
Tags: array, math, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

class Solution:
    def isReflected(self, points: List[List[int]]) -> bool:
        if not points:
            return True
        
        point_set = set((x, y) for x, y in points)
        min_x = min(x for x, y in points)
        max_x = max(x for x, y in points)
        mid_x = (min_x + max_x) / 2
        
        for x, y in points:
            reflected_x = 2 * mid_x - x
            if (reflected_x, y) not in point_set:
                return False
        
        return True