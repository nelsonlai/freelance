"""
Problem: Number Of Ways To Reconstruct A Tree
Difficulty: Hard
Tags: array, tree, graph

Approach: Build adjacency from pairs, check if valid tree can be constructed
Time Complexity: O(n^2) where n is nodes
Space Complexity: O(n^2)
"""

from collections import defaultdict

class Solution:
    def checkWays(self, pairs: List[List[int]]) -> int:
        adj = defaultdict(set)
        for u, v in pairs:
            adj[u].add(v)
            adj[v].add(u)
        
        nodes = sorted(adj.keys(), key=lambda x: len(adj[x]), reverse=True)
        
        if len(adj[nodes[0]]) != len(nodes) - 1:
            return 0
        
        parent = {}
        for i in range(1, len(nodes)):
            node = nodes[i]
            found_parent = False
            
            for j in range(i):
                candidate = nodes[j]
                if node in adj[candidate]:
                    # Check if candidate's neighbors contain all of node's neighbors
                    if adj[node].issubset(adj[candidate]):
                        parent[node] = candidate
                        found_parent = True
                        break
            
            if not found_parent:
                return 0
        
        # Check if multiple roots possible
        root_count = sum(1 for node in nodes if len(adj[node]) == len(nodes) - 1)
        return 2 if root_count > 1 else 1