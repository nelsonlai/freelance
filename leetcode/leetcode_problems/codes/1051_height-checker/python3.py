"""
Problem: Height Checker
Difficulty: Easy
Tags: array, sort

Approach: Sort expected heights, count mismatches
Time Complexity: O(n log n) for sorting
Space Complexity: O(n) for sorted array
"""

class Solution:
    def heightChecker(self, heights: List[int]) -> int:
        expected = sorted(heights)
        return sum(1 for i in range(len(heights)) if heights[i] != expected[i])