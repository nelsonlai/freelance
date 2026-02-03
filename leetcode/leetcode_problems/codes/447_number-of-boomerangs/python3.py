"""
Problem: Number of Boomerangs
Difficulty: Medium
Tags: array, math, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import defaultdict

class Solution:
    def numberOfBoomerangs(self, points: List[List[int]]) -> int:
        def distance(p1, p2):
            dx = p1[0] - p2[0]
            dy = p1[1] - p2[1]
            return dx * dx + dy * dy
        
        total = 0
        for i in range(len(points)):
            dist_count = defaultdict(int)
            for j in range(len(points)):
                if i != j:
                    dist = distance(points[i], points[j])
                    dist_count[dist] += 1
            
            for count in dist_count.values():
                total += count * (count - 1)
        
        return total