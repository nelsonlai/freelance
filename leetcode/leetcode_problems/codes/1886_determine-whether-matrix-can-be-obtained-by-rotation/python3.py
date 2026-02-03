"""
Problem: Determine Whether Matrix Can Be Obtained By Rotation
Difficulty: Easy
Tags: array

Approach: Try all 4 rotations (0, 90, 180, 270 degrees)
Time Complexity: O(n^2) where n is dimension
Space Complexity: O(1)
"""

class Solution:
    def findRotation(self, mat: List[List[int]], target: List[List[int]]) -> bool:
        n = len(mat)
        
        for _ in range(4):
            if mat == target:
                return True
            # Rotate 90 degrees clockwise
            mat = [[mat[n-1-j][i] for j in range(n)] for i in range(n)]
        
        return False