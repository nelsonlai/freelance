"""
Problem: Critical Connections in a Network
Difficulty: Hard
Tags: graph, search

Approach: Tarjan's algorithm to find bridges (critical connections)
Time Complexity: O(V + E) where V is vertices, E is edges
Space Complexity: O(V + E) for graph and arrays
"""

class Solution:
    def criticalConnections(self, n: int, connections: List[List[int]]) -> List[List[int]]:
        from collections import defaultdict
        
        graph = defaultdict(list)
        for u, v in connections:
            graph[u].append(v)
            graph[v].append(u)
        
        disc = [-1] * n
        low = [-1] * n
        time = [0]
        result = []
        
        def dfs(u, parent):
            disc[u] = low[u] = time[0]
            time[0] += 1
            
            for v in graph[u]:
                if v == parent:
                    continue
                if disc[v] == -1:
                    dfs(v, u)
                    low[u] = min(low[u], low[v])
                    if low[v] > disc[u]:
                        result.append([u, v])
                else:
                    low[u] = min(low[u], disc[v])
        
        for i in range(n):
            if disc[i] == -1:
                dfs(i, -1)
        
        return result