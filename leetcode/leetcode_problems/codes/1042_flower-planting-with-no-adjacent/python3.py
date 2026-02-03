"""
Problem: Flower Planting With No Adjacent
Difficulty: Medium
Tags: array, graph, search

Approach: Greedy coloring - assign first available color to each garden
Time Complexity: O(n + m) where m is number of paths
Space Complexity: O(n) for graph and result
"""

from collections import defaultdict

class Solution:
    def gardenNoAdj(self, n: int, paths: List[List[int]]) -> List[int]:
        graph = defaultdict(list)
        for x, y in paths:
            graph[x].append(y)
            graph[y].append(x)
        
        result = [0] * (n + 1)
        
        for i in range(1, n + 1):
            used = {result[neighbor] for neighbor in graph[i]}
            for color in range(1, 5):
                if color not in used:
                    result[i] = color
                    break
        
        return result[1:]