"""
Problem: Maximal Rectangle
Difficulty: Hard
Tags: array, dp, stack

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def maximalRectangle(self, matrix: List[List[str]]) -> int:
        if not matrix or not matrix[0]:
            return 0
        
        rows, cols = len(matrix), len(matrix[0])
        heights = [0] * cols
        max_area = 0
        
        for i in range(rows):
            for j in range(cols):
                heights[j] = heights[j] + 1 if matrix[i][j] == '1' else 0
            
            stack = []
            for j in range(cols + 1):
                while stack and (j == cols or heights[stack[-1]] > heights[j]):
                    height = heights[stack.pop()]
                    width = j if not stack else j - stack[-1] - 1
                    max_area = max(max_area, height * width)
                if j < cols:
                    stack.append(j)
        
        return max_area