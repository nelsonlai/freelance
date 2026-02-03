"""
Problem: Second Minimum Time to Reach Destination
Difficulty: Hard
Tags: array, graph, search, BFS, Dijkstra

Approach: Modified BFS/Dijkstra to find second shortest path considering traffic lights
Time Complexity: O(n + m) where n is nodes, m is edges
Space Complexity: O(n + m)
"""

from collections import deque, defaultdict

class Solution:
    def secondMinimum(self, n: int, edges: List[List[int]], time: int, change: int) -> int:
        graph = defaultdict(list)
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)
        
        # dist[i][0] = shortest time to node i
        # dist[i][1] = second shortest time to node i
        dist = [[float('inf')] * 2 for _ in range(n + 1)]
        dist[1][0] = 0
        
        queue = deque([(1, 0)])
        
        while queue:
            node, current_time = queue.popleft()
            
            # Calculate wait time due to traffic light
            # Light changes every 2*change seconds
            if (current_time // change) % 2 == 1:
                # Red light - wait until next green
                current_time = ((current_time // change) + 1) * change
            
            next_time = current_time + time
            
            for neighbor in graph[node]:
                if next_time < dist[neighbor][0]:
                    # New shortest path
                    dist[neighbor][1] = dist[neighbor][0]
                    dist[neighbor][0] = next_time
                    queue.append((neighbor, next_time))
                elif next_time > dist[neighbor][0] and next_time < dist[neighbor][1]:
                    # New second shortest path
                    dist[neighbor][1] = next_time
                    queue.append((neighbor, next_time))
        
        return dist[n][1]