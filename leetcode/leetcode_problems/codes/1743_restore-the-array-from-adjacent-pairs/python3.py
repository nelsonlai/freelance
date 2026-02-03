"""
Problem: Restore the Array From Adjacent Pairs
Difficulty: Medium
Tags: array, hash, graph, dfs

Approach: Build graph from pairs, find endpoint (degree 1), DFS to reconstruct array
Time Complexity: O(n) where n is length
Space Complexity: O(n)
"""

from collections import defaultdict

class Solution:
    def restoreArray(self, adjacentPairs: List[List[int]]) -> List[int]:
        graph = defaultdict(list)
        for u, v in adjacentPairs:
            graph[u].append(v)
            graph[v].append(u)
        
        # Find starting point (node with degree 1)
        start = None
        for node, neighbors in graph.items():
            if len(neighbors) == 1:
                start = node
                break
        
        result = []
        visited = set()
        
        def dfs(node):
            result.append(node)
            visited.add(node)
            for neighbor in graph[node]:
                if neighbor not in visited:
                    dfs(neighbor)
        
        dfs(start)
        return result