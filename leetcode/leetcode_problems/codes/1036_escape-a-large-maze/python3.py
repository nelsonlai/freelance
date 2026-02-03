"""
Problem: Escape a Large Maze
Difficulty: Hard
Tags: array, hash, search

Approach: BFS with limited search - if we can explore 20000 cells from source/target, we can escape
Time Complexity: O(B^2) where B is number of blocked cells
Space Complexity: O(B^2) for visited set
"""

from collections import deque

class Solution:
    def isEscapePossible(self, blocked: List[List[int]], source: List[int], target: List[int]) -> bool:
        blocked_set = {(r, c) for r, c in blocked}
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        
        def bfs(start, end):
            queue = deque([start])
            visited = {tuple(start)}
            max_area = 20000
            
            while queue and len(visited) < max_area:
                r, c = queue.popleft()
                if [r, c] == end:
                    return True
                
                for dr, dc in directions:
                    nr, nc = r + dr, c + dc
                    if 0 <= nr < 10**6 and 0 <= nc < 10**6 and (nr, nc) not in blocked_set and (nr, nc) not in visited:
                        visited.add((nr, nc))
                        queue.append([nr, nc])
            
            return len(visited) >= max_area
        
        return bfs(source, target) and bfs(target, source)