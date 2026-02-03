"""
Problem: Path With Minimum Effort
Difficulty: Medium
Tags: array, graph, search, queue, heap, dijkstra

Approach: Dijkstra's algorithm - find path with minimum maximum effort
Time Complexity: O(m * n * log(m * n)) where m, n are dimensions
Space Complexity: O(m * n) for heap and visited
"""

import heapq

class Solution:
    def minimumEffortPath(self, heights: List[List[int]]) -> int:
        m, n = len(heights), len(heights[0])
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        
        heap = [(0, 0, 0)]  # (effort, row, col)
        visited = set()
        
        while heap:
            effort, r, c = heapq.heappop(heap)
            
            if (r, c) in visited:
                continue
            visited.add((r, c))
            
            if r == m - 1 and c == n - 1:
                return effort
            
            for dr, dc in directions:
                nr, nc = r + dr, c + dc
                if 0 <= nr < m and 0 <= nc < n and (nr, nc) not in visited:
                    new_effort = max(effort, abs(heights[r][c] - heights[nr][nc]))
                    heapq.heappush(heap, (new_effort, nr, nc))
        
        return 0