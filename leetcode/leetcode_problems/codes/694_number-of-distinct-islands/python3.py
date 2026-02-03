"""
Problem: Number of Distinct Islands
Difficulty: Medium
Tags: graph, hash, search

Approach: Use hash map for O(1) lookups
Time Complexity: O(n) to O(n^2) depending on approach
Space Complexity: O(n) for hash map
"""

class Solution:
    def numDistinctIslands(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        seen = set()
        
        def dfs(i, j, shape, start_i, start_j):
            if 0 <= i < m and 0 <= j < n and grid[i][j] == 1:
                grid[i][j] = 0
                shape.append((i - start_i, j - start_j))
                dfs(i + 1, j, shape, start_i, start_j)
                dfs(i - 1, j, shape, start_i, start_j)
                dfs(i, j + 1, shape, start_i, start_j)
                dfs(i, j - 1, shape, start_i, start_j)
        
        for i in range(m):
            for j in range(n):
                if grid[i][j] == 1:
                    shape = []
                    dfs(i, j, shape, i, j)
                    seen.add(tuple(shape))
        
        return len(seen)