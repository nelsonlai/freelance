"""
Problem: Find the City With the Smallest Number of Neighbors at a Threshold Distance
Difficulty: Medium
Tags: array, graph, dp

Approach: Floyd-Warshall to find all-pairs shortest paths, count neighbors within threshold
Time Complexity: O(n^3) where n is number of cities
Space Complexity: O(n^2) for distance matrix
"""

class Solution:
    def findTheCity(self, n: int, edges: List[List[int]], distanceThreshold: int) -> int:
        dist = [[float('inf')] * n for _ in range(n)]
        
        for i in range(n):
            dist[i][i] = 0
        
        for u, v, w in edges:
            dist[u][v] = w
            dist[v][u] = w
        
        for k in range(n):
            for i in range(n):
                for j in range(n):
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
        
        min_count = float('inf')
        result = -1
        
        for i in range(n):
            count = sum(1 for j in range(n) if i != j and dist[i][j] <= distanceThreshold)
            if count <= min_count:
                min_count = count
                result = i
        
        return result