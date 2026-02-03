"""
Problem: Remove Max Number of Edges to Keep Graph Fully Traversable
Difficulty: Hard
Tags: array, graph

Approach: Use Union-Find - first add type 3 edges, then type 1 and 2 separately
Time Complexity: O(e * α(n)) where e is edges, α is inverse Ackermann
Space Complexity: O(n) for Union-Find
"""

class Solution:
    def maxNumEdgesToRemove(self, n: int, edges: List[List[int]]) -> int:
        def find(parent, x):
            if parent[x] != x:
                parent[x] = find(parent, parent[x])
            return parent[x]
        
        def union(parent, rank, x, y):
            px, py = find(parent, x), find(parent, y)
            if px == py:
                return False
            if rank[px] < rank[py]:
                px, py = py, px
            parent[py] = px
            rank[px] += rank[py]
            return True
        
        type3_edges = []
        type1_edges = []
        type2_edges = []
        
        for t, u, v in edges:
            u -= 1
            v -= 1
            if t == 3:
                type3_edges.append((u, v))
            elif t == 1:
                type1_edges.append((u, v))
            else:
                type2_edges.append((u, v))
        
        parent = list(range(n))
        rank = [1] * n
        
        used = 0
        for u, v in type3_edges:
            if union(parent, rank, u, v):
                used += 1
        
        parent1 = parent[:]
        rank1 = rank[:]
        parent2 = parent[:]
        rank2 = rank[:]
        
        for u, v in type1_edges:
            if union(parent1, rank1, u, v):
                used += 1
        
        for u, v in type2_edges:
            if union(parent2, rank2, u, v):
                used += 1
        
        if rank1[find(parent1, 0)] != n or rank2[find(parent2, 0)] != n:
            return -1
        
        return len(edges) - used