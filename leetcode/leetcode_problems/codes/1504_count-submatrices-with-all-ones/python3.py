"""
Problem: Count Submatrices With All Ones
Difficulty: Medium
Tags: array, dp, stack

Approach: For each row, calculate consecutive 1s, use histogram approach to count rectangles
Time Complexity: O(m * n^2) where m, n are matrix dimensions
Space Complexity: O(n) for heights
"""

class Solution:
    def numSubmat(self, mat: List[List[int]]) -> int:
        m, n = len(mat), len(mat[0])
        result = 0
        
        for i in range(m):
            heights = [0] * n
            for j in range(i, m):
                for k in range(n):
                    if mat[j][k] == 1:
                        heights[k] += 1
                    else:
                        heights[k] = 0
                
                # Count rectangles ending at each column
                stack = []
                for k in range(n):
                    while stack and heights[stack[-1]] >= heights[k]:
                        stack.pop()
                    
                    if stack:
                        prev = stack[-1]
                        result += heights[k] * (k - prev)
                    else:
                        result += heights[k] * (k + 1)
                    
                    stack.append(k)
        
        return result