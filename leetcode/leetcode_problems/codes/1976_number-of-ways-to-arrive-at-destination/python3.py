"""
Problem: Number of Ways to Arrive at Destination
Difficulty: Medium
Tags: array, graph, dp, sort, Dijkstra

Approach: Dijkstra to find shortest paths, count ways using DP
Time Complexity: O((n + m) log n) where n is nodes, m is edges
Space Complexity: O(n + m)
"""

import heapq
from collections import defaultdict

class Solution:
    def countPaths(self, n: int, roads: List[List[int]]) -> int:
        MOD = 10**9 + 7
        graph = defaultdict(list)
        
        for u, v, time in roads:
            graph[u].append((v, time))
            graph[v].append((u, time))
        
        dist = [float('inf')] * n
        ways = [0] * n
        dist[0] = 0
        ways[0] = 1
        
        heap = [(0, 0)]
        
        while heap:
            d, u = heapq.heappop(heap)
            if d > dist[u]:
                continue
            
            for v, time in graph[u]:
                if dist[u] + time < dist[v]:
                    dist[v] = dist[u] + time
                    ways[v] = ways[u]
                    heapq.heappush(heap, (dist[v], v))
                elif dist[u] + time == dist[v]:
                    ways[v] = (ways[v] + ways[u]) % MOD
        
        return ways[n-1]