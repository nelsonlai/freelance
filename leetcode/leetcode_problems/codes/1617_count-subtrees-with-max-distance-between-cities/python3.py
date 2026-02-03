"""
Problem: Count Subtrees With Max Distance Between Cities
Difficulty: Hard
Tags: array, tree, dp, bitmask

Approach: For each subset of cities, check if it forms a connected subtree and find diameter
Time Complexity: O(2^n * n^2)
Space Complexity: O(2^n)
"""

from collections import deque

class Solution:
    def countSubgraphsForEachDiameter(self, n: int, edges: List[List[int]]) -> List[int]:
        graph = [[] for _ in range(n)]
        for u, v in edges:
            graph[u-1].append(v-1)
            graph[v-1].append(u-1)
        
        result = [0] * (n - 1)
        
        for mask in range(1, 1 << n):
            nodes = [i for i in range(n) if mask & (1 << i)]
            if len(nodes) < 2:
                continue
            
            # Check connectivity
            visited = set()
            queue = deque([nodes[0]])
            visited.add(nodes[0])
            
            while queue:
                node = queue.popleft()
                for neighbor in graph[node]:
                    if neighbor in nodes and neighbor not in visited:
                        visited.add(neighbor)
                        queue.append(neighbor)
            
            if len(visited) != len(nodes):
                continue
            
            # Find diameter using BFS from each node
            max_dist = 0
            for start in nodes:
                dist = {start: 0}
                queue = deque([start])
                
                while queue:
                    node = queue.popleft()
                    for neighbor in graph[node]:
                        if neighbor in nodes and neighbor not in dist:
                            dist[neighbor] = dist[node] + 1
                            queue.append(neighbor)
                            max_dist = max(max_dist, dist[neighbor])
            
            if max_dist > 0:
                result[max_dist - 1] += 1
        
        return result