"""
Problem: Tree Diameter
Difficulty: Medium
Tags: array, tree, graph, sort, search

Approach: Two DFS - first find farthest node, then find diameter from that node
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(n) for graph
"""

from collections import defaultdict

class Solution:
    def treeDiameter(self, edges: List[List[int]]) -> int:
        if not edges:
            return 0
        
        graph = defaultdict(list)
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)
        
        def dfs(node, parent):
            max_depth = 0
            farthest_node = node
            
            for neighbor in graph[node]:
                if neighbor != parent:
                    depth, far_node = dfs(neighbor, node)
                    if depth + 1 > max_depth:
                        max_depth = depth + 1
                        farthest_node = far_node
            
            return max_depth, farthest_node
        
        # First DFS to find one end of diameter
        _, end1 = dfs(0, -1)
        # Second DFS to find diameter length
        diameter, _ = dfs(end1, -1)
        
        return diameter