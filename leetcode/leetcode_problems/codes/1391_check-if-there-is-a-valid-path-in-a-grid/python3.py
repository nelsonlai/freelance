"""
Problem: Check if There is a Valid Path in a Grid
Difficulty: Medium
Tags: array, tree, graph, search

Approach: BFS/DFS - check street connections, verify valid path from (0,0) to (m-1,n-1)
Time Complexity: O(m * n) where m, n are grid dimensions
Space Complexity: O(m * n) for visited
"""

from collections import deque

class Solution:
    def hasValidPath(self, grid: List[List[int]]) -> bool:
        m, n = len(grid), len(grid[0])
        # Street connections: up, right, down, left
        connections = {
            1: [False, True, False, True],
            2: [True, False, True, False],
            3: [False, False, True, True],
            4: [False, True, True, False],
            5: [True, False, False, True],
            6: [True, True, False, False]
        }
        directions = [(-1, 0), (0, 1), (1, 0), (0, -1)]
        
        queue = deque([(0, 0)])
        visited = {(0, 0)}
        
        while queue:
            r, c = queue.popleft()
            if r == m - 1 and c == n - 1:
                return True
            
            street = grid[r][c]
            for i, (dr, dc) in enumerate(directions):
                if not connections[street][i]:
                    continue
                
                nr, nc = r + dr, c + dc
                if 0 <= nr < m and 0 <= nc < n and (nr, nc) not in visited:
                    next_street = grid[nr][nc]
                    opposite_dir = (i + 2) % 4
                    if connections[next_street][opposite_dir]:
                        visited.add((nr, nc))
                        queue.append((nr, nc))
        
        return False