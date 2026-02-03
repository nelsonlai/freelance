"""
Problem: Number of Restricted Paths From First to Last Node
Difficulty: Medium
Tags: array, graph, dp, dijkstra

Approach: Dijkstra from n to compute distances, then DP with memoization
Time Complexity: O((V + E) log V) for Dijkstra + O(V + E) for DP
Space Complexity: O(V + E)
"""

import heapq
from functools import lru_cache

class Solution:
    def countRestrictedPaths(self, n: int, edges: List[List[int]]) -> int:
        graph = [[] for _ in range(n + 1)]
        for u, v, w in edges:
            graph[u].append((v, w))
            graph[v].append((u, w))
        
        # Dijkstra from n
        dist = [float('inf')] * (n + 1)
        dist[n] = 0
        heap = [(0, n)]
        
        while heap:
            d, u = heapq.heappop(heap)
            if d > dist[u]:
                continue
            for v, w in graph[u]:
                if dist[u] + w < dist[v]:
                    dist[v] = dist[u] + w
                    heapq.heappush(heap, (dist[v], v))
        
        # DP with memoization
        MOD = 10**9 + 7
        
        @lru_cache(maxsize=None)
        def dp(u):
            if u == n:
                return 1
            result = 0
            for v, _ in graph[u]:
                if dist[v] < dist[u]:
                    result = (result + dp(v)) % MOD
            return result
        
        return dp(1)