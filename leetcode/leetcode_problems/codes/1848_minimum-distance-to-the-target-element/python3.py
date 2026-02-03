"""
Problem: Minimum Distance to the Target Element
Difficulty: Easy
Tags: array

Approach: Find all target indices, return minimum distance from start
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def getMinDistance(self, nums: List[int], target: int, start: int) -> int:
        result = float('inf')
        for i, num in enumerate(nums):
            if num == target:
                result = min(result, abs(i - start))
        return result