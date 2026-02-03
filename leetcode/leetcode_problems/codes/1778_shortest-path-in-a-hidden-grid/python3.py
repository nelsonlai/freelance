"""
Problem: Shortest Path in a Hidden Grid
Difficulty: Medium
Tags: array, graph, search, dfs, bfs

Approach: First DFS to explore and map grid, then BFS to find shortest path
Time Complexity: O(m * n) where m, n are grid dimensions
Space Complexity: O(m * n)
"""

from collections import deque

class Solution(object):
    def findShortestPath(self, master: 'GridMaster') -> int:
        directions = {'U': (-1, 0), 'D': (1, 0), 'L': (0, -1), 'R': (0, 1)}
        reverse = {'U': 'D', 'D': 'U', 'L': 'R', 'R': 'L'}
        
        grid = {}
        target = None
        
        def dfs(r, c):
            nonlocal target
            if master.isTarget():
                target = (r, c)
            
            for d, (dr, dc) in directions.items():
                nr, nc = r + dr, c + dc
                if (nr, nc) not in grid and master.canMove(d):
                    master.move(d)
                    grid[(nr, nc)] = True
                    dfs(nr, nc)
                    master.move(reverse[d])
        
        grid[(0, 0)] = True
        dfs(0, 0)
        
        if target is None:
            return -1
        
        # BFS to find shortest path
        queue = deque([(0, 0, 0)])
        visited = {(0, 0)}
        
        while queue:
            r, c, steps = queue.popleft()
            
            if (r, c) == target:
                return steps
            
            for dr, dc in directions.values():
                nr, nc = r + dr, c + dc
                if (nr, nc) in grid and (nr, nc) not in visited:
                    visited.add((nr, nc))
                    queue.append((nr, nc, steps + 1))
        
        return -1