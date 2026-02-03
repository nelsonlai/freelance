"""
Problem: Path With Maximum Minimum Value
Difficulty: Medium
Tags: array, graph, search, queue, heap

Approach: Binary search on answer + BFS/DFS to check if path exists
Time Complexity: O(m * n * log(max_val))
Space Complexity: O(m * n) for visited
"""

import heapq

class Solution:
    def maximumMinimumPath(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        
        # Use max-heap (negate values) to always explore highest value paths
        heap = [(-grid[0][0], 0, 0)]
        visited = set()
        min_val = grid[0][0]
        
        while heap:
            val, r, c = heapq.heappop(heap)
            val = -val
            min_val = min(min_val, val)
            
            if (r, c) == (m - 1, n - 1):
                return min_val
            
            if (r, c) in visited:
                continue
            visited.add((r, c))
            
            for dr, dc in directions:
                nr, nc = r + dr, c + dc
                if 0 <= nr < m and 0 <= nc < n and (nr, nc) not in visited:
                    heapq.heappush(heap, (-grid[nr][nc], nr, nc))
        
        return min_val