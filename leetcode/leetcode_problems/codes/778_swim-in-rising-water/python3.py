import heapq

class Solution:
    def swimInWater(self, grid: List[List[int]]) -> int:
        n = len(grid)
        heap = [(grid[0][0], 0, 0)]
        visited = {(0, 0)}
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        
        while heap:
            time, r, c = heapq.heappop(heap)
            if r == n - 1 and c == n - 1:
                return time
            
            for dr, dc in directions:
                nr, nc = r + dr, c + dc
                if 0 <= nr < n and 0 <= nc < n and (nr, nc) not in visited:
                    visited.add((nr, nc))
                    heapq.heappush(heap, (max(time, grid[nr][nc]), nr, nc))
        
        return -1
