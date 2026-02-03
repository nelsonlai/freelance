"""
Problem: Unique Paths III
Difficulty: Hard
Tags: array, tree

Approach: DFS with backtracking - visit all empty cells exactly once
Time Complexity: O(3^(m*n)) in worst case
Space Complexity: O(m*n) for recursion stack
"""

class Solution:
    def uniquePathsIII(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        start = None
        empty_count = 0
        
        for i in range(m):
            for j in range(n):
                if grid[i][j] == 1:
                    start = (i, j)
                elif grid[i][j] == 0:
                    empty_count += 1
        
        self.paths = 0
        
        def dfs(i, j, remaining):
            if grid[i][j] == 2:
                if remaining == 0:
                    self.paths += 1
                return
            
            grid[i][j] = -1
            for di, dj in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
                ni, nj = i + di, j + dj
                if 0 <= ni < m and 0 <= nj < n and grid[ni][nj] != -1:
                    dfs(ni, nj, remaining - (1 if grid[ni][nj] == 0 else 0))
            grid[i][j] = 0
        
        dfs(start[0], start[1], empty_count)
        return self.paths