"""
Problem: The Maze III
Difficulty: Hard
Tags: array, string, graph, search, queue, heap

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

import heapq

class Solution:
    def findShortestWay(self, maze: List[List[int]], ball: List[int], hole: List[int]) -> str:
        m, n = len(maze), len(maze[0])
        directions = [('u', -1, 0), ('d', 1, 0), ('l', 0, -1), ('r', 0, 1)]
        heap = [(0, '', ball[0], ball[1])]
        visited = {}
        
        while heap:
            dist, path, x, y = heapq.heappop(heap)
            if [x, y] == hole:
                return path
            
            if (x, y) in visited and visited[(x, y)] <= dist:
                continue
            visited[(x, y)] = dist
            
            for direction, dx, dy in directions:
                nx, ny = x, y
                steps = 0
                while 0 <= nx + dx < m and 0 <= ny + dy < n and maze[nx + dx][ny + dy] == 0:
                    nx += dx
                    ny += dy
                    steps += 1
                    if [nx, ny] == hole:
                        break
                
                if (nx, ny) not in visited or visited[(nx, ny)] > dist + steps:
                    heapq.heappush(heap, (dist + steps, path + direction, nx, ny))
        
        return "impossible"