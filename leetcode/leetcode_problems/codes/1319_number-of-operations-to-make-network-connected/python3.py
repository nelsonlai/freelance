"""
Problem: Number of Operations to Make Network Connected
Difficulty: Medium
Tags: graph, search

Approach: Count connected components, need (components - 1) cables, check if enough cables
Time Complexity: O(n + m) where n is nodes, m is edges
Space Complexity: O(n) for graph and visited
"""

from collections import defaultdict

class Solution:
    def makeConnected(self, n: int, connections: List[List[int]]) -> int:
        if len(connections) < n - 1:
            return -1
        
        graph = defaultdict(list)
        for u, v in connections:
            graph[u].append(v)
            graph[v].append(u)
        
        visited = set()
        components = 0
        
        def dfs(node):
            visited.add(node)
            for neighbor in graph[node]:
                if neighbor not in visited:
                    dfs(neighbor)
        
        for i in range(n):
            if i not in visited:
                components += 1
                dfs(i)
        
        return components - 1