"""
Problem: Last Day Where You Can Still Cross
Difficulty: Hard
Tags: array, graph, search, binary search, BFS/DFS

Approach: Binary search on day, check if path exists using BFS
Time Complexity: O(row * col * log(len(cells)))
Space Complexity: O(row * col)
"""

from collections import deque

class Solution:
    def latestDayToCross(self, row: int, col: int, cells: List[List[int]]) -> int:
        def can_cross(day):
            grid = [[0] * col for _ in range(row)]
            for i in range(day):
                r, c = cells[i]
                grid[r-1][c-1] = 1
            
            queue = deque()
            for c in range(col):
                if grid[0][c] == 0:
                    queue.append((0, c))
                    grid[0][c] = 1
            
            directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]
            while queue:
                r, c = queue.popleft()
                if r == row - 1:
                    return True
                
                for dr, dc in directions:
                    nr, nc = r + dr, c + dc
                    if 0 <= nr < row and 0 <= nc < col and grid[nr][nc] == 0:
                        grid[nr][nc] = 1
                        queue.append((nr, nc))
            
            return False
        
        left, right = 0, len(cells)
        result = 0
        
        while left <= right:
            mid = (left + right) // 2
            if can_cross(mid):
                result = mid
                left = mid + 1
            else:
                right = mid - 1
        
        return result