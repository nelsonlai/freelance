"""
Problem: Rotting Oranges
Difficulty: Medium
Tags: array, search

Approach: BFS - start from all rotten oranges, spread to adjacent fresh oranges
Time Complexity: O(m * n) where m and n are grid dimensions
Space Complexity: O(m * n) for queue
"""

from collections import deque

class Solution:
    def orangesRotting(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        queue = deque()
        fresh_count = 0
        
        for i in range(m):
            for j in range(n):
                if grid[i][j] == 2:
                    queue.append((i, j, 0))
                elif grid[i][j] == 1:
                    fresh_count += 1
        
        if fresh_count == 0:
            return 0
        
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        max_time = 0
        
        while queue:
            i, j, time = queue.popleft()
            
            for di, dj in directions:
                ni, nj = i + di, j + dj
                if 0 <= ni < m and 0 <= nj < n and grid[ni][nj] == 1:
                    grid[ni][nj] = 2
                    fresh_count -= 1
                    max_time = max(max_time, time + 1)
                    queue.append((ni, nj, time + 1))
        
        return max_time if fresh_count == 0 else -1