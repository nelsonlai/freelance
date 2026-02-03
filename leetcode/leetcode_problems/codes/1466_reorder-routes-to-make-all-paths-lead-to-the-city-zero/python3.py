"""
Problem: Reorder Routes to Make All Paths Lead to the City Zero
Difficulty: Medium
Tags: tree, graph, search

Approach: Build bidirectional graph, DFS from 0, count edges pointing away
Time Complexity: O(n) where n is number of cities
Space Complexity: O(n) for graph
"""

from collections import defaultdict

class Solution:
    def minReorder(self, n: int, connections: List[List[int]]) -> int:
        graph = defaultdict(list)
        for u, v in connections:
            graph[u].append((v, True))
            graph[v].append((u, False))
        
        def dfs(node, parent):
            count = 0
            for neighbor, is_original in graph[node]:
                if neighbor != parent:
                    if is_original:
                        count += 1
                    count += dfs(neighbor, node)
            return count
        
        return dfs(0, -1)