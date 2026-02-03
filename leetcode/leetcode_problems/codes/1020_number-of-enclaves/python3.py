"""
Problem: Number of Enclaves
Difficulty: Medium
Tags: array, graph, search

Approach: DFS from boundary cells to mark reachable, count remaining 1s
Time Complexity: O(m * n) where m and n are grid dimensions
Space Complexity: O(m * n) for recursion stack
"""

class Solution:
    def numEnclaves(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        
        def dfs(i, j):
            if i < 0 or i >= m or j < 0 or j >= n or grid[i][j] == 0:
                return
            grid[i][j] = 0
            for di, dj in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
                dfs(i + di, j + dj)
        
        # Mark boundary-connected cells
        for i in range(m):
            dfs(i, 0)
            dfs(i, n - 1)
        for j in range(n):
            dfs(0, j)
            dfs(m - 1, j)
        
        # Count remaining 1s
        return sum(sum(row) for row in grid)