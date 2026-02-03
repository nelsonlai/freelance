"""
Problem: Minimum Number of Days to Disconnect Island
Difficulty: Hard
Tags: array, search

Approach: Check if already disconnected, then try removing 1 or 2 cells
Time Complexity: O(m * n * (m * n)) for checking connectivity
Space Complexity: O(m * n) for DFS
"""

class Solution:
    def minDays(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        
        def count_islands():
            visited = [[False] * n for _ in range(m)]
            count = 0
            
            def dfs(r, c):
                if r < 0 or r >= m or c < 0 or c >= n or visited[r][c] or grid[r][c] == 0:
                    return
                visited[r][c] = True
                for dr, dc in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
                    dfs(r + dr, c + dc)
            
            for i in range(m):
                for j in range(n):
                    if grid[i][j] == 1 and not visited[i][j]:
                        count += 1
                        dfs(i, j)
            
            return count
        
        islands = count_islands()
        if islands != 1:
            return 0
        
        for i in range(m):
            for j in range(n):
                if grid[i][j] == 1:
                    grid[i][j] = 0
                    if count_islands() != 1:
                        return 1
                    grid[i][j] = 1
        
        return 2