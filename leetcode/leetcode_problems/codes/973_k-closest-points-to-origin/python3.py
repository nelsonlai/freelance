"""
Problem: K Closest Points to Origin
Difficulty: Medium
Tags: array, math, sort, queue, heap

Approach: Sort points by distance squared, return first k
Time Complexity: O(n log n) for sorting
Space Complexity: O(1) excluding output
"""

class Solution:
    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
        points.sort(key=lambda p: p[0]**2 + p[1]**2)
        return points[:k]