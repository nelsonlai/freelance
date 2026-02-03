"""
Problem: Convert 1D Array Into 2D Array
Difficulty: Easy
Tags: array

Approach: Check if size matches, then reshape array
Time Complexity: O(m * n) where m, n are dimensions
Space Complexity: O(m * n)
"""

class Solution:
    def construct2DArray(self, original: List[int], m: int, n: int) -> List[List[int]]:
        if len(original) != m * n:
            return []
        
        result = []
        for i in range(m):
            result.append(original[i * n:(i + 1) * n])
        
        return result