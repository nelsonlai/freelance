"""
Problem: Coloring A Border
Difficulty: Medium
Tags: array, search

Approach: DFS to find connected component, mark border cells
Time Complexity: O(m * n) where m and n are grid dimensions
Space Complexity: O(m * n) for recursion stack
"""

class Solution:
    def colorBorder(self, grid: List[List[int]], row: int, col: int, color: int) -> List[List[int]]:
        m, n = len(grid), len(grid[0])
        original_color = grid[row][col]
        visited = set()
        border = []
        
        def dfs(i, j):
            if (i, j) in visited:
                return
            visited.add((i, j))
            
            is_border = False
            for di, dj in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
                ni, nj = i + di, j + dj
                if ni < 0 or ni >= m or nj < 0 or nj >= n or grid[ni][nj] != original_color:
                    is_border = True
                elif (ni, nj) not in visited:
                    dfs(ni, nj)
            
            if is_border:
                border.append((i, j))
        
        dfs(row, col)
        for i, j in border:
            grid[i][j] = color
        
        return grid