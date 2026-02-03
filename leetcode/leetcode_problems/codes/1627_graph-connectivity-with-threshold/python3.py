"""
Problem: Graph Connectivity With Threshold
Difficulty: Hard
Tags: array, graph, math, union-find

Approach: Union-Find - connect nodes with GCD > threshold
Time Complexity: O(n * log n + q) where q is queries
Space Complexity: O(n) for Union-Find
"""

class Solution:
    def areConnected(self, n: int, threshold: int, queries: List[List[int]]) -> List[bool]:
        parent = list(range(n + 1))
        
        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]
        
        def union(x, y):
            px, py = find(x), find(y)
            if px != py:
                parent[px] = py
        
        # Connect nodes with GCD > threshold
        for i in range(threshold + 1, n + 1):
            for j in range(i * 2, n + 1, i):
                union(i, j)
        
        return [find(u) == find(v) for u, v in queries]