"""
Problem: The Maze II
Difficulty: Medium
Tags: array, graph, search, queue, heap

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

import heapq

class Solution:
    def shortestDistance(self, maze: List[List[int]], start: List[int], destination: List[int]) -> int:
        m, n = len(maze), len(maze[0])
        directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]
        heap = [(0, start[0], start[1])]
        distances = {(start[0], start[1]): 0}
        
        while heap:
            dist, x, y = heapq.heappop(heap)
            
            if [x, y] == destination:
                return dist
            
            if distances.get((x, y), float('inf')) < dist:
                continue
            
            for dx, dy in directions:
                nx, ny = x, y
                steps = 0
                while 0 <= nx + dx < m and 0 <= ny + dy < n and maze[nx + dx][ny + dy] == 0:
                    nx += dx
                    ny += dy
                    steps += 1
                
                if (nx, ny) not in distances or distances[(nx, ny)] > dist + steps:
                    distances[(nx, ny)] = dist + steps
                    heapq.heappush(heap, (dist + steps, nx, ny))
        
        return -1