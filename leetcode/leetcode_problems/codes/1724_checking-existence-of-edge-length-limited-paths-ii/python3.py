"""
Problem: Checking Existence of Edge Length Limited Paths II
Difficulty: Hard
Tags: tree, graph, union-find

Approach: Use Union-Find, add edges incrementally by limit, check connectivity
Time Complexity: O(n + m * α(n) + q) where m is edges, q is queries
Space Complexity: O(n)
"""

class DistanceLimitedPathsExist:

    def __init__(self, n: int, edgeList: List[List[int]]):
        self.n = n
        self.edges = sorted(edgeList, key=lambda x: x[2])
        self.parent = list(range(n))
        
    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]
    
    def union(self, x, y):
        px, py = self.find(x), self.find(y)
        if px != py:
            self.parent[px] = py

    def query(self, p: int, q: int, limit: int) -> bool:
        # Reset parent
        self.parent = list(range(self.n))
        
        # Add all edges with distance < limit
        for u, v, dist in self.edges:
            if dist >= limit:
                break
            self.union(u, v)
        
        return self.find(p) == self.find(q)