"""
Problem: Connecting Cities With Minimum Cost
Difficulty: Medium
Tags: array, tree, graph, queue, heap

Approach: Kruskal's algorithm with Union-Find to find Minimum Spanning Tree
Time Complexity: O(E log E) where E is number of edges
Space Complexity: O(n) for Union-Find
"""

class Solution:
    def minimumCost(self, n: int, connections: List[List[int]]) -> int:
        parent = list(range(n + 1))
        
        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]
        
        def union(x, y):
            px, py = find(x), find(y)
            if px == py:
                return False
            parent[px] = py
            return True
        
        connections.sort(key=lambda x: x[2])
        total_cost = 0
        edges_used = 0
        
        for u, v, cost in connections:
            if union(u, v):
                total_cost += cost
                edges_used += 1
                if edges_used == n - 1:
                    return total_cost
        
        return -1