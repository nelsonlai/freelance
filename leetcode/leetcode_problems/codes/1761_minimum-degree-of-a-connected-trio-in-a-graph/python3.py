"""
Problem: Minimum Degree of a Connected Trio in a Graph
Difficulty: Hard
Tags: array, graph

Approach: Find all trios (triangles), calculate degree sum minus 6 (internal edges counted twice)
Time Complexity: O(n^3) where n is nodes
Space Complexity: O(n^2) for adjacency matrix
"""

class Solution:
    def minTrioDegree(self, n: int, edges: List[List[int]]) -> int:
        adj = [[False] * (n + 1) for _ in range(n + 1)]
        degree = [0] * (n + 1)
        
        for u, v in edges:
            adj[u][v] = True
            adj[v][u] = True
            degree[u] += 1
            degree[v] += 1
        
        result = float('inf')
        
        for i in range(1, n + 1):
            for j in range(i + 1, n + 1):
                if not adj[i][j]:
                    continue
                for k in range(j + 1, n + 1):
                    if adj[i][k] and adj[j][k]:
                        # Trio found
                        trio_degree = degree[i] + degree[j] + degree[k] - 6
                        result = min(result, trio_degree)
        
        return result if result != float('inf') else -1