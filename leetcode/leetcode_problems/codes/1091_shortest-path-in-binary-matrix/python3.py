"""
Problem: Shortest Path in Binary Matrix
Difficulty: Medium
Tags: array, search

Approach: BFS to find shortest path from (0,0) to (n-1,n-1)
Time Complexity: O(n^2) where n is grid size
Space Complexity: O(n^2) for queue
"""

from collections import deque

class Solution:
    def shortestPathBinaryMatrix(self, grid: List[List[int]]) -> int:
        n = len(grid)
        if grid[0][0] == 1 or grid[n-1][n-1] == 1:
            return -1
        
        queue = deque([(0, 0, 1)])
        grid[0][0] = 1
        
        directions = [(-1,-1), (-1,0), (-1,1), (0,-1), (0,1), (1,-1), (1,0), (1,1)]
        
        while queue:
            r, c, dist = queue.popleft()
            if r == n - 1 and c == n - 1:
                return dist
            
            for dr, dc in directions:
                nr, nc = r + dr, c + dc
                if 0 <= nr < n and 0 <= nc < n and grid[nr][nc] == 0:
                    grid[nr][nc] = 1
                    queue.append((nr, nc, dist + 1))
        
        return -1