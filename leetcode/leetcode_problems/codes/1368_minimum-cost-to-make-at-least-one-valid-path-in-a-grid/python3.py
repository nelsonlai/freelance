"""
Problem: Minimum Cost to Make at Least One Valid Path in a Grid
Difficulty: Hard
Tags: array, graph, search, queue, heap

Approach: 0-1 BFS - follow direction costs 0, change direction costs 1
Time Complexity: O(m * n) where m, n are grid dimensions
Space Complexity: O(m * n) for deque
"""

from collections import deque

class Solution:
    def minCost(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        directions = {1: (0, 1), 2: (0, -1), 3: (1, 0), 4: (-1, 0)}
        costs = [[float('inf')] * n for _ in range(m)]
        costs[0][0] = 0
        
        dq = deque([(0, 0)])
        
        while dq:
            r, c = dq.popleft()
            
            if r == m - 1 and c == n - 1:
                return costs[r][c]
            
            for dir_num, (dr, dc) in directions.items():
                nr, nc = r + dr, c + dc
                if 0 <= nr < m and 0 <= nc < n:
                    cost = 0 if grid[r][c] == dir_num else 1
                    if costs[nr][nc] > costs[r][c] + cost:
                        costs[nr][nc] = costs[r][c] + cost
                        if cost == 0:
                            dq.appendleft((nr, nc))
                        else:
                            dq.append((nr, nc))
        
        return costs[m-1][n-1]