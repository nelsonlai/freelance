"""
Problem: Longest Line of Consecutive One in Matrix
Difficulty: Medium
Tags: array, dp

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def longestLine(self, mat: List[List[int]]) -> int:
        if not mat or not mat[0]:
            return 0
        
        m, n = len(mat), len(mat[0])
        directions = [(0, 1), (1, 0), (1, 1), (1, -1)]
        max_length = 0
        
        for i in range(m):
            for j in range(n):
                if mat[i][j] == 1:
                    for dx, dy in directions:
                        length = 0
                        x, y = i, j
                        while 0 <= x < m and 0 <= y < n and mat[x][y] == 1:
                            length += 1
                            x += dx
                            y += dy
                        max_length = max(max_length, length)
        
        return max_length