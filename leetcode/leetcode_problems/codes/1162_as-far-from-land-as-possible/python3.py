"""
Problem: As Far from Land as Possible
Difficulty: Medium
Tags: array, dp, search

Approach: Multi-source BFS from all land cells, find maximum distance to water
Time Complexity: O(m * n) where m, n are grid dimensions
Space Complexity: O(m * n) for queue
"""

class Solution:
    def maxDistance(self, grid: List[List[int]]) -> int:
        from collections import deque
        
        m, n = len(grid), len(grid[0])
        queue = deque()
        
        # Add all land cells to queue
        for i in range(m):
            for j in range(n):
                if grid[i][j] == 1:
                    queue.append((i, j, 0))
        
        if not queue or len(queue) == m * n:
            return -1
        
        max_dist = 0
        directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]
        visited = set()
        
        while queue:
            i, j, dist = queue.popleft()
            
            if (i, j) in visited:
                continue
            visited.add((i, j))
            
            if grid[i][j] == 0:
                max_dist = max(max_dist, dist)
            
            for di, dj in directions:
                ni, nj = i + di, j + dj
                if 0 <= ni < m and 0 <= nj < n and (ni, nj) not in visited:
                    queue.append((ni, nj, dist + 1))
        
        return max_dist if max_dist > 0 else -1