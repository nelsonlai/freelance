"""
Problem: Graph Valid Tree
Difficulty: Medium
Tags: tree, graph, search

Approach: DFS or BFS traversal
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(h) for recursion stack where h is height
"""

class Solution:
    def validTree(self, n: int, edges: List[List[int]]) -> bool:
        if len(edges) != n - 1:
            return False
        
        graph = [[] for _ in range(n)]
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)
        
        visited = set()
        
        def dfs(node, parent):
            if node in visited:
                return False
            
            visited.add(node)
            for neighbor in graph[node]:
                if neighbor != parent:
                    if not dfs(neighbor, node):
                        return False
            return True
        
        if not dfs(0, -1):
            return False
        
        return len(visited) == n