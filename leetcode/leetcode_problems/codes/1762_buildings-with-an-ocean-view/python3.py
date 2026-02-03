"""
Problem: Buildings With an Ocean View
Difficulty: Medium
Tags: array, stack, monotonic stack

Approach: Traverse from right, track maximum height seen, add indices with ocean view
Time Complexity: O(n) where n is length
Space Complexity: O(n) for result
"""

class Solution:
    def findBuildings(self, heights: List[int]) -> List[int]:
        result = []
        max_height = 0
        
        for i in range(len(heights) - 1, -1, -1):
            if heights[i] > max_height:
                result.append(i)
                max_height = heights[i]
        
        return result[::-1]