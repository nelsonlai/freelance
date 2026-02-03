"""
Problem: Min Cost to Connect All Points
Difficulty: Medium
Tags: array, tree, graph

Approach: Minimum Spanning Tree using Kruskal's algorithm with Union-Find
Time Complexity: O(n^2 log n) where n is number of points
Space Complexity: O(n^2) for edges
"""

class Solution:
    def minCostConnectPoints(self, points: List[List[int]]) -> int:
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
        
        n = len(points)
        edges = []
        
        for i in range(n):
            for j in range(i + 1, n):
                cost = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1])
                edges.append((cost, i, j))
        
        edges.sort()
        
        parent = list(range(n))
        rank = [1] * n
        result = 0
        count = 0
        
        for cost, u, v in edges:
            if union(parent, rank, u, v):
                result += cost
                count += 1
                if count == n - 1:
                    break
        
        return result