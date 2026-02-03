"""
Problem: Nearest Exit from Entrance in Maze
Difficulty: Medium
Tags: array, graph, search, BFS

Approach: BFS from entrance, find nearest border cell
Time Complexity: O(m * n) where m, n are dimensions
Space Complexity: O(m * n)
"""

from collections import deque

class Solution:
    def nearestExit(self, maze: List[List[str]], entrance: List[int]) -> int:
        m, n = len(maze), len(maze[0])
        queue = deque([(entrance[0], entrance[1], 0)])
        visited = {(entrance[0], entrance[1])}
        
        directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]
        
        while queue:
            i, j, steps = queue.popleft()
            
            if (i == 0 or i == m - 1 or j == 0 or j == n - 1) and [i, j] != entrance:
                return steps
            
            for di, dj in directions:
                ni, nj = i + di, j + dj
                if 0 <= ni < m and 0 <= nj < n and maze[ni][nj] == '.' and (ni, nj) not in visited:
                    visited.add((ni, nj))
                    queue.append((ni, nj, steps + 1))
        
        return -1