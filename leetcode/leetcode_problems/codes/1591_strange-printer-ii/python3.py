"""
Problem: Strange Printer II
Difficulty: Hard
Tags: array, graph, sort

Approach: Find bounds for each color, check dependencies, topological sort
Time Complexity: O(c^2 * m * n) where c is colors, m, n are grid dimensions
Space Complexity: O(c^2) for graph
"""

from collections import defaultdict, deque

class Solution:
    def isPrintable(self, targetGrid: List[List[int]]) -> bool:
        m, n = len(targetGrid), len(targetGrid[0])
        colors = set()
        for row in targetGrid:
            colors.update(row)
        
        bounds = {}
        for color in colors:
            min_r = min_c = float('inf')
            max_r = max_c = -1
            for i in range(m):
                for j in range(n):
                    if targetGrid[i][j] == color:
                        min_r = min(min_r, i)
                        max_r = max(max_r, i)
                        min_c = min(min_c, j)
                        max_c = max(max_c, j)
            bounds[color] = (min_r, max_r, min_c, max_c)
        
        graph = defaultdict(set)
        for color in colors:
            min_r, max_r, min_c, max_c = bounds[color]
            for i in range(min_r, max_r + 1):
                for j in range(min_c, max_c + 1):
                    other = targetGrid[i][j]
                    if other != color:
                        graph[other].add(color)
        
        in_degree = {color: 0 for color in colors}
        for color in colors:
            for neighbor in graph[color]:
                in_degree[neighbor] += 1
        
        queue = deque([color for color in colors if in_degree[color] == 0])
        processed = 0
        
        while queue:
            color = queue.popleft()
            processed += 1
            
            for neighbor in graph[color]:
                in_degree[neighbor] -= 1
                if in_degree[neighbor] == 0:
                    queue.append(neighbor)
        
        return processed == len(colors)