"""
Problem: Minimum Path Cost in a Hidden Grid
Difficulty: Medium
Tags: array, graph, search, dfs, dijkstra

Approach: First DFS to explore grid, then Dijkstra to find shortest path
Time Complexity: O(m * n * log(m*n)) where m, n are dimensions
Space Complexity: O(m * n)
"""

import heapq
from collections import defaultdict

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
                    cost = master.move(d)
                    grid[(nr, nc)] = cost
                    dfs(nr, nc)
                    master.move(reverse[d])
        
        grid[(0, 0)] = 0
        dfs(0, 0)
        
        if target is None:
            return -1
        
        # Dijkstra
        dist = defaultdict(lambda: float('inf'))
        dist[(0, 0)] = 0
        heap = [(0, 0, 0)]
        
        while heap:
            cost, r, c = heapq.heappop(heap)
            if (r, c) == target:
                return cost
            
            if cost > dist[(r, c)]:
                continue
            
            for dr, dc in directions.values():
                nr, nc = r + dr, c + dc
                if (nr, nc) in grid:
                    new_cost = cost + grid[(nr, nc)]
                    if new_cost < dist[(nr, nc)]:
                        dist[(nr, nc)] = new_cost
                        heapq.heappush(heap, (new_cost, nr, nc))
        
        return -1