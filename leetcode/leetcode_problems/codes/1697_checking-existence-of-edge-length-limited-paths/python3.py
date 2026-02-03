"""
Problem: Checking Existence of Edge Length Limited Paths
Difficulty: Hard
Tags: array, graph, sort, union-find

Approach: Sort edges and queries by limit, use Union-Find to connect nodes
Time Complexity: O(n + m log m + q log q) where m is edges, q is queries
Space Complexity: O(n)
"""

class Solution:
    def distanceLimitedPathsExist(self, n: int, edgeList: List[List[int]], queries: List[List[int]]) -> List[bool]:
        parent = list(range(n))
        
        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]
        
        def union(x, y):
            px, py = find(x), find(y)
            if px != py:
                parent[px] = py
        
        # Sort edges by distance
        edgeList.sort(key=lambda x: x[2])
        
        # Sort queries by limit, keep original index
        queries_with_idx = [(i, p, q, limit) for i, (p, q, limit) in enumerate(queries)]
        queries_with_idx.sort(key=lambda x: x[3])
        
        result = [False] * len(queries)
        edge_idx = 0
        
        for orig_idx, p, q, limit in queries_with_idx:
            # Add all edges with distance < limit
            while edge_idx < len(edgeList) and edgeList[edge_idx][2] < limit:
                u, v, _ = edgeList[edge_idx]
                union(u, v)
                edge_idx += 1
            
            result[orig_idx] = (find(p) == find(q))
        
        return result