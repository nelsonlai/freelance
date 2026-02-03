"""
Problem: Shortest Path in a Grid with Obstacles Elimination
Difficulty: Hard
Tags: array, tree, graph, search

Approach: BFS with state (r, c, remaining_k), track visited states
Time Complexity: O(m * n * k) where m, n are grid dimensions
Space Complexity: O(m * n * k) for visited states
"""

from collections import deque

class Solution:
    def shortestPath(self, grid: List[List[int]], k: int) -> int:
        m, n = len(grid), len(grid[0])
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        
        queue = deque([(0, 0, k, 0)])
        visited = {(0, 0, k)}
        
        while queue:
            r, c, remaining, steps = queue.popleft()
            
            if r == m - 1 and c == n - 1:
                return steps
            
            for dr, dc in directions:
                nr, nc = r + dr, c + dc
                if 0 <= nr < m and 0 <= nc < n:
                    new_remaining = remaining - grid[nr][nc]
                    state = (nr, nc, new_remaining)
                    if new_remaining >= 0 and state not in visited:
                        visited.add(state)
                        queue.append((nr, nc, new_remaining, steps + 1))
        
        return -1