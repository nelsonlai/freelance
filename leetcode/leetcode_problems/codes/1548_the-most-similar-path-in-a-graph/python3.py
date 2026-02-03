"""
Problem: The Most Similar Path in a Graph
Difficulty: Hard
Tags: array, string, graph, dp

Approach: DP - dp[i][j] = min edit distance ending at city j at position i
Time Complexity: O(m * n^2) where m is target length, n is cities
Space Complexity: O(m * n) for DP table
"""

from collections import defaultdict

class Solution:
    def mostSimilar(self, n: int, roads: List[List[int]], names: List[str], targetPath: List[str]) -> List[int]:
        graph = defaultdict(list)
        for u, v in roads:
            graph[u].append(v)
            graph[v].append(u)
        
        m = len(targetPath)
        dp = [[float('inf')] * n for _ in range(m)]
        parent = [[-1] * n for _ in range(m)]
        
        for j in range(n):
            dp[0][j] = 0 if names[j] == targetPath[0] else 1
        
        for i in range(1, m):
            for j in range(n):
                for neighbor in graph[j]:
                    cost = 0 if names[j] == targetPath[i] else 1
                    if dp[i-1][neighbor] + cost < dp[i][j]:
                        dp[i][j] = dp[i-1][neighbor] + cost
                        parent[i][j] = neighbor
        
        min_idx = min(range(n), key=lambda x: dp[m-1][x])
        result = [min_idx]
        
        for i in range(m - 1, 0, -1):
            result.append(parent[i][result[-1]])
        
        return result[::-1]