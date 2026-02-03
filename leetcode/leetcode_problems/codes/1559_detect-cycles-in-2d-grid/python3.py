"""
Problem: Detect Cycles in 2D Grid
Difficulty: Medium
Tags: array, graph, search

Approach: DFS - check for cycles of length >= 4, track parent to avoid immediate back edge
Time Complexity: O(m * n) where m, n are grid dimensions
Space Complexity: O(m * n) for visited
"""

class Solution:
    def containsCycle(self, grid: List[List[str]]) -> bool:
        m, n = len(grid), len(grid[0])
        visited = [[False] * n for _ in range(m)]
        
        def dfs(r, c, pr, pc, char):
            if r < 0 or r >= m or c < 0 or c >= n or grid[r][c] != char:
                return False
            
            if visited[r][c]:
                return True
            
            visited[r][c] = True
            
            directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
            for dr, dc in directions:
                nr, nc = r + dr, c + dc
                if (nr, nc) != (pr, pc):
                    if dfs(nr, nc, r, c, char):
                        return True
            
            return False
        
        for i in range(m):
            for j in range(n):
                if not visited[i][j]:
                    if dfs(i, j, -1, -1, grid[i][j]):
                        return True
        
        return False