"""
Problem: Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree
Difficulty: Hard
Tags: array, tree, graph, sort

Approach: Find MST weight, check if edge is critical (MST weight increases without it) or pseudo-critical (MST weight same with it forced)
Time Complexity: O(E^2 * α(n)) where E is edges, using Union-Find
Space Complexity: O(n) for Union-Find
"""

class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n
    
    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]
    
    def union(self, x, y):
        px, py = self.find(x), self.find(y)
        if px == py:
            return False
        if self.rank[px] < self.rank[py]:
            px, py = py, px
        self.parent[py] = px
        if self.rank[px] == self.rank[py]:
            self.rank[px] += 1
        return True

class Solution:
    def findCriticalAndPseudoCriticalEdges(self, n: int, edges: List[List[int]]) -> List[List[int]]:
        m = len(edges)
        edges_with_index = [(edges[i][0], edges[i][1], edges[i][2], i) for i in range(m)]
        edges_with_index.sort(key=lambda x: x[2])
        
        def mst_weight(exclude=-1, include=-1):
            uf = UnionFind(n)
            weight = 0
            count = 0
            
            if include != -1:
                u, v, w, _ = edges_with_index[include]
                if uf.union(u, v):
                    weight += w
                    count += 1
            
            for i, (u, v, w, idx) in enumerate(edges_with_index):
                if i == exclude or i == include:
                    continue
                if uf.union(u, v):
                    weight += w
                    count += 1
                    if count == n - 1:
                        break
            
            return weight if count == n - 1 else float('inf')
        
        base_weight = mst_weight()
        critical = []
        pseudo_critical = []
        
        for i in range(m):
            weight_without = mst_weight(exclude=i)
            if weight_without > base_weight:
                critical.append(edges_with_index[i][3])
            else:
                weight_with = mst_weight(include=i)
                if weight_with == base_weight:
                    pseudo_critical.append(edges_with_index[i][3])
        
        return [critical, pseudo_critical]