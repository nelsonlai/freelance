"""
Problem: Maximum Area of a Piece of Cake After Horizontal and Vertical Cuts
Difficulty: Medium
Tags: array, greedy, sort

Approach: Find max horizontal and vertical gaps, multiply them
Time Complexity: O(n log n) for sorting
Space Complexity: O(1)
"""

class Solution:
    def maxArea(self, h: int, w: int, horizontalCuts: List[int], verticalCuts: List[int]) -> int:
        MOD = 10**9 + 7
        horizontalCuts.sort()
        verticalCuts.sort()
        
        max_h = max(horizontalCuts[0], h - horizontalCuts[-1])
        for i in range(1, len(horizontalCuts)):
            max_h = max(max_h, horizontalCuts[i] - horizontalCuts[i-1])
        
        max_w = max(verticalCuts[0], w - verticalCuts[-1])
        for i in range(1, len(verticalCuts)):
            max_w = max(max_w, verticalCuts[i] - verticalCuts[i-1])
        
        return (max_h * max_w) % MOD