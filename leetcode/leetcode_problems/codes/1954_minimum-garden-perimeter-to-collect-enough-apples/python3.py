"""
Problem: Minimum Garden Perimeter to Collect Enough Apples
Difficulty: Medium
Tags: tree, math, search, binary search

Approach: Binary search on perimeter, calculate apples in square
Time Complexity: O(log(neededApples))
Space Complexity: O(1)
"""

class Solution:
    def minimumPerimeter(self, neededApples: int) -> int:
        def apples_in_square(radius):
            # Apples in square from -radius to radius (inclusive)
            # Sum formula: 2 * radius * (radius + 1) * (2 * radius + 1) / 3
            return 2 * radius * (radius + 1) * (2 * radius + 1)
        
        left, right = 0, 10**6
        result = 0
        
        while left <= right:
            mid = (left + right) // 2
            if apples_in_square(mid) >= neededApples:
                result = mid
                right = mid - 1
            else:
                left = mid + 1
        
        return 8 * result