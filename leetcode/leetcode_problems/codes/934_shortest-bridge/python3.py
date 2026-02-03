"""
Problem: Shortest Bridge
Difficulty: Medium
Tags: array, search

Approach: DFS to find first island, then BFS to find shortest path to second island
Time Complexity: O(n * m) where n and m are dimensions
Space Complexity: O(n * m) for queue and visited set
"""

from collections import deque

class Solution:
    def shortestBridge(self, grid: List[List[int]]) -> int:
        n = len(grid)
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        
        # Find first island using DFS
        def dfs(i, j, island):
            if i < 0 or i >= n or j < 0 or j >= n or grid[i][j] != 1:
                return
            grid[i][j] = 2
            island.append((i, j))
            for di, dj in directions:
                dfs(i + di, j + dj, island)
        
        # Find first island
        island = []
        for i in range(n):
            for j in range(n):
                if grid[i][j] == 1:
                    dfs(i, j, island)
                    break
            if island:
                break
        
        # BFS to find shortest path to second island
        queue = deque([(i, j, 0) for i, j in island])
        visited = set(island)
        
        while queue:
            i, j, dist = queue.popleft()
            for di, dj in directions:
                ni, nj = i + di, j + dj
                if 0 <= ni < n and 0 <= nj < n and (ni, nj) not in visited:
                    if grid[ni][nj] == 1:
                        return dist
                    visited.add((ni, nj))
                    queue.append((ni, nj, dist + 1))
        
        return -1