"""
Problem: Minimum Cost to Reach Destination in Time
Difficulty: Hard
Tags: array, graph, dp, shortest path

Approach: DP with time constraint - dp[city][time] = min cost
Time Complexity: O(maxTime * (n + m)) where n is cities, m is edges
Space Complexity: O(n * maxTime)
"""

class Solution:
    def minCost(self, maxTime: int, edges: List[List[int]], passingFees: List[int]) -> int:
        n = len(passingFees)
        graph = [[] for _ in range(n)]
        
        for u, v, time in edges:
            graph[u].append((v, time))
            graph[v].append((u, time))
        
        dp = [[float('inf')] * (maxTime + 1) for _ in range(n)]
        dp[0][0] = passingFees[0]
        
        for time in range(maxTime + 1):
            for u in range(n):
                if dp[u][time] == float('inf'):
                    continue
                
                for v, edge_time in graph[u]:
                    new_time = time + edge_time
                    if new_time <= maxTime:
                        new_cost = dp[u][time] + passingFees[v]
                        if new_cost < dp[v][new_time]:
                            dp[v][new_time] = new_cost
        
        result = min(dp[n - 1])
        return result if result != float('inf') else -1