"""
Problem: Optimize Water Distribution in a Village
Difficulty: Hard
Tags: array, tree, graph, queue, heap

Approach: Treat wells as edges from virtual node 0, use Kruskal's algorithm
Time Complexity: O(E log E) where E is number of edges
Space Complexity: O(n) for Union-Find
"""

class Solution:
    def minCostToSupplyWater(self, n: int, wells: List[int], pipes: List[List[int]]) -> int:
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
        
        # Add virtual edges from node 0 (well) to each house
        edges = []
        for i, cost in enumerate(wells, 1):
            edges.append((cost, 0, i))
        
        # Add pipe edges
        for house1, house2, cost in pipes:
            edges.append((cost, house1, house2))
        
        edges.sort()
        total_cost = 0
        edges_used = 0
        
        for cost, u, v in edges:
            if union(u, v):
                total_cost += cost
                edges_used += 1
                if edges_used == n:
                    return total_cost
        
        return total_cost