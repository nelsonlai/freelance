"""
Problem: Pacific Atlantic Water Flow
Difficulty: Medium
Tags: array, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def pacificAtlantic(self, heights: List[List[int]]) -> List[List[int]]:
        if not heights or not heights[0]:
            return []
        
        m, n = len(heights), len(heights[0])
        pacific = [[False] * n for _ in range(m)]
        atlantic = [[False] * n for _ in range(m)]
        
        def dfs(i, j, visited, prev_height):
            if i < 0 or i >= m or j < 0 or j >= n or visited[i][j] or heights[i][j] < prev_height:
                return
            visited[i][j] = True
            for di, dj in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
                dfs(i + di, j + dj, visited, heights[i][j])
        
        for i in range(m):
            dfs(i, 0, pacific, float('-inf'))
            dfs(i, n - 1, atlantic, float('-inf'))
        
        for j in range(n):
            dfs(0, j, pacific, float('-inf'))
            dfs(m - 1, j, atlantic, float('-inf'))
        
        result = []
        for i in range(m):
            for j in range(n):
                if pacific[i][j] and atlantic[i][j]:
                    result.append([i, j])
        
        return result