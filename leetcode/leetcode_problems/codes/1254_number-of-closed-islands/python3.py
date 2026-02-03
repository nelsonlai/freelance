"""
Problem: Number of Closed Islands
Difficulty: Medium
Tags: array, graph, search

Approach: DFS - first mark border islands, then count remaining closed islands
Time Complexity: O(m * n) where m, n are grid dimensions
Space Complexity: O(m * n) for recursion stack
"""

class Solution:
    def closedIsland(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        
        def dfs(r, c):
            if r < 0 or r >= m or c < 0 or c >= n:
                return False
            if grid[r][c] != 0:
                return True
            
            grid[r][c] = 1
            is_closed = True
            for dr, dc in directions:
                if not dfs(r + dr, c + dc):
                    is_closed = False
            return is_closed
        
        # Mark border islands
        for i in range(m):
            if grid[i][0] == 0:
                dfs(i, 0)
            if grid[i][n-1] == 0:
                dfs(i, n-1)
        for j in range(n):
            if grid[0][j] == 0:
                dfs(0, j)
            if grid[m-1][j] == 0:
                dfs(m-1, j)
        
        # Count closed islands
        count = 0
        for i in range(1, m - 1):
            for j in range(1, n - 1):
                if grid[i][j] == 0:
                    if dfs(i, j):
                        count += 1
        
        return count