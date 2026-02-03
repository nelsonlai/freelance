"""
Problem: Find if Path Exists in Graph
Difficulty: Easy
Tags: array, graph, search, BFS/DFS

Approach: BFS or DFS to check if path exists from source to destination
Time Complexity: O(n + m) where n is nodes, m is edges
Space Complexity: O(n)
"""

from collections import defaultdict, deque

class Solution:
    def validPath(self, n: int, edges: List[List[int]], source: int, destination: int) -> bool:
        if source == destination:
            return True
        
        graph = defaultdict(list)
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)
        
        queue = deque([source])
        visited = {source}
        
        while queue:
            node = queue.popleft()
            if node == destination:
                return True
            
            for neighbor in graph[node]:
                if neighbor not in visited:
                    visited.add(neighbor)
                    queue.append(neighbor)
        
        return False