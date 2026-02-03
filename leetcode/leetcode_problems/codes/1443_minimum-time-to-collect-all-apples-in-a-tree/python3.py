"""
Problem: Minimum Time to Collect All Apples in a Tree
Difficulty: Medium
Tags: array, tree, hash, search

Approach: DFS - return time needed for subtree, add 2 for each edge to visit
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(n) for tree
"""

from collections import defaultdict

class Solution:
    def minTime(self, n: int, edges: List[List[int]], hasApple: List[bool]) -> int:
        tree = defaultdict(list)
        for u, v in edges:
            tree[u].append(v)
            tree[v].append(u)
        
        def dfs(node, parent):
            total_time = 0
            for child in tree[node]:
                if child == parent:
                    continue
                child_time = dfs(child, node)
                if child_time > 0 or hasApple[child]:
                    total_time += child_time + 2
            return total_time
        
        return dfs(0, -1)