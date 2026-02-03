"""
Problem: Trapping Rain Water II
Difficulty: Hard
Tags: array, search, queue, heap

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

import heapq

class Solution:
    def trapRainWater(self, heightMap: List[List[int]]) -> int:
        if not heightMap or not heightMap[0]:
            return 0
        
        m, n = len(heightMap), len(heightMap[0])
        visited = [[False] * n for _ in range(m)]
        heap = []
        
        for i in range(m):
            heapq.heappush(heap, (heightMap[i][0], i, 0))
            heapq.heappush(heap, (heightMap[i][n-1], i, n-1))
            visited[i][0] = True
            visited[i][n-1] = True
        
        for j in range(n):
            heapq.heappush(heap, (heightMap[0][j], 0, j))
            heapq.heappush(heap, (heightMap[m-1][j], m-1, j))
            visited[0][j] = True
            visited[m-1][j] = True
        
        directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]
        water = 0
        
        while heap:
            height, i, j = heapq.heappop(heap)
            for di, dj in directions:
                ni, nj = i + di, j + dj
                if 0 <= ni < m and 0 <= nj < n and not visited[ni][nj]:
                    visited[ni][nj] = True
                    water += max(0, height - heightMap[ni][nj])
                    heapq.heappush(heap, (max(height, heightMap[ni][nj]), ni, nj))
        
        return water