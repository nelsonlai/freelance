"""
Problem: All Paths from Source Lead to Destination
Difficulty: Medium
Tags: graph, sort

Approach: DFS with cycle detection - check all paths from source lead to destination
Time Complexity: O(V + E)
Space Complexity: O(V + E) for graph
"""

from collections import defaultdict

class Solution:
    def leadsToDestination(self, n: int, edges: List[List[int]], source: int, destination: int) -> bool:
        graph = defaultdict(list)
        for u, v in edges:
            graph[u].append(v)
        
        visited = {}
        
        def dfs(node):
            if node in visited:
                return visited[node]
            
            if node == destination:
                visited[node] = True
                return True
            
            if node not in graph:
                visited[node] = False
                return False
            
            visited[node] = False  # Mark as visiting
            for neighbor in graph[node]:
                if not dfs(neighbor):
                    return False
            
            visited[node] = True
            return True
        
        return dfs(source)