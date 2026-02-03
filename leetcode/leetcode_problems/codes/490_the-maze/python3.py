"""
Problem: The Maze
Difficulty: Medium
Tags: array, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

from collections import deque

class Solution:
    def hasPath(self, maze: List[List[int]], start: List[int], destination: List[int]) -> bool:
        m, n = len(maze), len(maze[0])
        directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]
        visited = set()
        queue = deque([tuple(start)])
        visited.add(tuple(start))
        
        while queue:
            x, y = queue.popleft()
            if [x, y] == destination:
                return True
            
            for dx, dy in directions:
                nx, ny = x, y
                while 0 <= nx + dx < m and 0 <= ny + dy < n and maze[nx + dx][ny + dy] == 0:
                    nx += dx
                    ny += dy
                
                if (nx, ny) not in visited:
                    visited.add((nx, ny))
                    queue.append((nx, ny))
        
        return False