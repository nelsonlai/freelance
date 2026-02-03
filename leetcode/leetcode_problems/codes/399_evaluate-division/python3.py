"""
Problem: Evaluate Division
Difficulty: Medium
Tags: array, string, graph, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

from collections import defaultdict

class Solution:
    def calcEquation(self, equations: List[List[str]], values: List[float], queries: List[List[str]]) -> List[float]:
        graph = defaultdict(dict)
        
        for (a, b), value in zip(equations, values):
            graph[a][b] = value
            graph[b][a] = 1.0 / value
        
        def dfs(start, end, visited):
            if start not in graph or end not in graph:
                return -1.0
            
            if end in graph[start]:
                return graph[start][end]
            
            visited.add(start)
            for neighbor, value in graph[start].items():
                if neighbor not in visited:
                    result = dfs(neighbor, end, visited)
                    if result != -1.0:
                        return value * result
            visited.remove(start)
            return -1.0
        
        results = []
        for a, b in queries:
            results.append(dfs(a, b, set()))
        
        return results