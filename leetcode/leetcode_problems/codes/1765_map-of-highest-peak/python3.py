"""
Problem: Map of Highest Peak
Difficulty: Medium
Tags: array, search, bfs

Approach: Multi-source BFS - start from all water cells, assign heights level by level
Time Complexity: O(m * n) where m, n are dimensions
Space Complexity: O(m * n) for queue
"""

from collections import deque

class Solution:
    def highestPeak(self, isWater: List[List[int]]) -> List[List[int]]:
        m, n = len(isWater), len(isWater[0])
        result = [[-1] * n for _ in range(m)]
        queue = deque()
        
        # Initialize water cells
        for i in range(m):
            for j in range(n):
                if isWater[i][j] == 1:
                    result[i][j] = 0
                    queue.append((i, j))
        
        directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]
        
        while queue:
            r, c = queue.popleft()
            
            for dr, dc in directions:
                nr, nc = r + dr, c + dc
                if 0 <= nr < m and 0 <= nc < n and result[nr][nc] == -1:
                    result[nr][nc] = result[r][c] + 1
                    queue.append((nr, nc))
        
        return result