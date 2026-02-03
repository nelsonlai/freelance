"""
Problem: Two Furthest Houses With Different Colors
Difficulty: Easy
Tags: array, greedy

Approach: Find maximum distance by checking first/last house with each color
Time Complexity: O(n) where n is array length
Space Complexity: O(1)
"""

class Solution:
    def maxDistance(self, colors: List[int]) -> int:
        n = len(colors)
        max_dist = 0
        
        # Check distance from first house to last house with different color
        for i in range(n):
            if colors[i] != colors[0]:
                max_dist = max(max_dist, i)
            if colors[i] != colors[-1]:
                max_dist = max(max_dist, n - 1 - i)
        
        return max_dist