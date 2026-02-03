"""
Problem: Maximum Path Quality of a Graph
Difficulty: Hard
Tags: array, graph, DFS, backtracking

Approach: DFS with backtracking to explore all paths within time limit
Time Complexity: O(4^10) worst case with pruning
Space Complexity: O(n)
"""

from collections import defaultdict

class Solution:
    def maximalPathQuality(self, values: List[int], edges: List[List[int]], maxTime: int) -> int:
        graph = defaultdict(list)
        for u, v, time in edges:
            graph[u].append((v, time))
            graph[v].append((u, time))
        
        n = len(values)
        max_quality = 0
        
        def dfs(node, time_used, quality, visited_nodes):
            nonlocal max_quality
            
            if node == 0:
                max_quality = max(max_quality, quality)
            
            for neighbor, time_cost in graph[node]:
                if time_used + time_cost <= maxTime:
                    is_new_node = neighbor not in visited_nodes
                    if is_new_node:
                        visited_nodes.add(neighbor)
                        quality += values[neighbor]
                    
                    dfs(neighbor, time_used + time_cost, quality, visited_nodes)
                    
                    if is_new_node:
                        visited_nodes.remove(neighbor)
                        quality -= values[neighbor]
        
        visited = {0}
        dfs(0, 0, values[0], visited)
        return max_quality