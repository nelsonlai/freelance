"""
Problem: The Time When the Network Becomes Idle
Difficulty: Medium
Tags: array, graph, search, BFS

Approach: BFS to find shortest distances, calculate when each server becomes idle
Time Complexity: O(n + m) where n is nodes, m is edges
Space Complexity: O(n + m)
"""

from collections import deque, defaultdict

class Solution:
    def networkBecomesIdle(self, edges: List[List[int]], patience: List[int]) -> int:
        n = len(patience)
        graph = defaultdict(list)
        
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)
        
        # BFS to find shortest distances from node 0
        dist = [-1] * n
        dist[0] = 0
        queue = deque([0])
        
        while queue:
            node = queue.popleft()
            for neighbor in graph[node]:
                if dist[neighbor] == -1:
                    dist[neighbor] = dist[node] + 1
                    queue.append(neighbor)
        
        max_time = 0
        
        for i in range(1, n):
            round_trip = 2 * dist[i]
            # Calculate when last message is sent
            if round_trip <= patience[i]:
                # No resend needed
                idle_time = round_trip + 1
            else:
                # Last resend happens at: patience[i] * floor((round_trip - 1) / patience[i])
                last_send = patience[i] * ((round_trip - 1) // patience[i])
                idle_time = last_send + round_trip + 1
            
            max_time = max(max_time, idle_time)
        
        return max_time