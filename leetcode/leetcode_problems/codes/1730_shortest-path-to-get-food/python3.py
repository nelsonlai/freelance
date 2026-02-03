"""
Problem: Shortest Path to Get Food
Difficulty: Medium
Tags: array, graph, search, bfs

Approach: BFS from starting position to find shortest path to food
Time Complexity: O(m * n) where m, n are dimensions
Space Complexity: O(m * n) for queue
"""

from collections import deque

class Solution:
    def getFood(self, grid: List[List[str]]) -> int:
        m, n = len(grid), len(grid[0])
        
        # Find starting position
        start = None
        for i in range(m):
            for j in range(n):
                if grid[i][j] == '*':
                    start = (i, j)
                    break
            if start:
                break
        
        queue = deque([(start[0], start[1], 0)])
        visited = {(start[0], start[1])}
        directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]
        
        while queue:
            r, c, steps = queue.popleft()
            
            if grid[r][c] == '#':
                return steps
            
            for dr, dc in directions:
                nr, nc = r + dr, c + dc
                if 0 <= nr < m and 0 <= nc < n and (nr, nc) not in visited and grid[nr][nc] != 'X':
                    visited.add((nr, nc))
                    queue.append((nr, nc, steps + 1))
        
        return -1