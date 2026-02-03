"""
Problem: Squirrel Simulation
Difficulty: Medium
Tags: array, tree, math

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

class Solution:
    def minDistance(self, height: int, width: int, tree: List[int], squirrel: List[int], nuts: List[List[int]]) -> int:
        total = 0
        max_diff = float('-inf')
        
        for nut in nuts:
            dist_to_tree = abs(nut[0] - tree[0]) + abs(nut[1] - tree[1])
            dist_to_squirrel = abs(nut[0] - squirrel[0]) + abs(nut[1] - squirrel[1])
            total += dist_to_tree * 2
            max_diff = max(max_diff, dist_to_tree - dist_to_squirrel)
        
        return total - max_diff