"""
Problem: Reshape the Matrix
Difficulty: Easy
Tags: array

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def matrixReshape(self, mat: List[List[int]], r: int, c: int) -> List[List[int]]:
        m, n = len(mat), len(mat[0])
        if m * n != r * c:
            return mat
        
        result = []
        flat = [num for row in mat for num in row]
        
        for i in range(r):
            result.append(flat[i*c:(i+1)*c])
        
        return result