"""
Problem: Maximal Network Rank
Difficulty: Medium
Tags: array, graph

Approach: Count degrees, for each pair of cities, rank = degree[i] + degree[j] - (1 if connected else 0)
Time Complexity: O(n^2) where n is number of cities
Space Complexity: O(n^2) for adjacency set
"""

class Solution:
    def maximalNetworkRank(self, n: int, roads: List[List[int]]) -> int:
        degree = [0] * n
        connected = set()
        
        for u, v in roads:
            degree[u] += 1
            degree[v] += 1
            connected.add((min(u, v), max(u, v)))
        
        max_rank = 0
        for i in range(n):
            for j in range(i + 1, n):
                rank = degree[i] + degree[j]
                if (i, j) in connected:
                    rank -= 1
                max_rank = max(max_rank, rank)
        
        return max_rank