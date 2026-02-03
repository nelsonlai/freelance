"""
Problem: Shortest Distance from All Buildings
Difficulty: Hard
Tags: array, tree, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

from collections import deque

class Solution:
    def shortestDistance(self, grid: List[List[int]]) -> int:
        if not grid or not grid[0]:
            return -1
        
        m, n = len(grid), len(grid[0])
        buildings = sum(1 for i in range(m) for j in range(n) if grid[i][j] == 1)
        distance = [[0] * n for _ in range(m)]
        reach = [[0] * n for _ in range(m)]
        
        def bfs(start_i, start_j):
            visited = [[False] * n for _ in range(m)]
            queue = deque([(start_i, start_j, 0)])
            visited[start_i][start_j] = True
            count = 1
            
            while queue:
                i, j, dist = queue.popleft()
                for di, dj in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
                    ni, nj = i + di, j + dj
                    if 0 <= ni < m and 0 <= nj < n and not visited[ni][nj]:
                        visited[ni][nj] = True
                        if grid[ni][nj] == 0:
                            distance[ni][nj] += dist + 1
                            reach[ni][nj] += 1
                            queue.append((ni, nj, dist + 1))
                        elif grid[ni][nj] == 1:
                            count += 1
            
            return count == buildings
        
        for i in range(m):
            for j in range(n):
                if grid[i][j] == 1:
                    if not bfs(i, j):
                        return -1
        
        min_distance = float('inf')
        for i in range(m):
            for j in range(n):
                if grid[i][j] == 0 and reach[i][j] == buildings:
                    min_distance = min(min_distance, distance[i][j])
        
        return min_distance if min_distance != float('inf') else -1