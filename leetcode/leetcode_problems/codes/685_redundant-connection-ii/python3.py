"""
Problem: Redundant Connection II
Difficulty: Hard
Tags: array, tree, graph, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

class Solution:
    def findRedundantDirectedConnection(self, edges: List[List[int]]) -> List[int]:
        n = len(edges)
        parent = list(range(n + 1))
        candidate1 = candidate2 = None
        
        for edge in edges:
            u, v = edge
            if parent[v] != v:
                candidate1 = [parent[v], v]
                candidate2 = edge
            else:
                parent[v] = u
        
        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]
        
        parent = list(range(n + 1))
        for edge in edges:
            if edge == candidate2:
                continue
            u, v = edge
            if find(u) == find(v):
                return candidate1 if candidate1 else edge
            parent[find(u)] = find(v)
        
        return candidate2