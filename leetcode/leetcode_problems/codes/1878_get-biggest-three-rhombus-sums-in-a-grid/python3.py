"""
Problem: Get Biggest Three Rhombus Sums in a Grid
Difficulty: Medium
Tags: array, math, heap

Approach: For each center, try all possible rhombus sizes, use heap to track top 3
Time Complexity: O(m * n * min(m,n)) where m, n are dimensions
Space Complexity: O(1) excluding output
"""

import heapq

class Solution:
    def getBiggestThree(self, grid: List[List[int]]) -> List[int]:
        m, n = len(grid), len(grid[0])
        sums = set()
        
        for i in range(m):
            for j in range(n):
                # Try all possible rhombus sizes
                for size in range(min(i + 1, m - i, j + 1, n - j)):
                    total = 0
                    # Top
                    if size == 0:
                        total = grid[i][j]
                    else:
                        # Top vertex
                        total += grid[i - size][j]
                        # Bottom vertex
                        total += grid[i + size][j]
                        # Left vertex
                        total += grid[i][j - size]
                        # Right vertex
                        total += grid[i][j + size]
                        
                        # Edges
                        for k in range(1, size):
                            total += grid[i - size + k][j - k]
                            total += grid[i - size + k][j + k]
                            total += grid[i + size - k][j - k]
                            total += grid[i + size - k][j + k]
                    
                    sums.add(total)
        
        # Get top 3
        heap = []
        for s in sums:
            heapq.heappush(heap, s)
            if len(heap) > 3:
                heapq.heappop(heap)
        
        result = sorted(heap, reverse=True)
        return result