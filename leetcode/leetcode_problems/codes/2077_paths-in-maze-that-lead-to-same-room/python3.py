"""
Problem: Paths in Maze That Lead to Same Room
Difficulty: Medium
Tags: array, graph

Approach: Find cycles of length 3 (triangles) in the graph
Time Complexity: O(n^2) where n is number of nodes
Space Complexity: O(n + m) where m is edges
"""

from collections import defaultdict

class Solution:
    def numberOfPaths(self, n: int, corridors: List[List[int]]) -> int:
        graph = defaultdict(set)
        for u, v in corridors:
            graph[u].add(v)
            graph[v].add(u)
        
        result = 0
        
        # Find all triangles (cycles of length 3)
        for u in range(1, n + 1):
            neighbors = list(graph[u])
            for i in range(len(neighbors)):
                for j in range(i + 1, len(neighbors)):
                    v, w = neighbors[i], neighbors[j]
                    # Check if v and w are connected (forming a triangle)
                    if w in graph[v]:
                        result += 1
        
        # Each triangle is counted 3 times (once for each vertex)
        return result // 3