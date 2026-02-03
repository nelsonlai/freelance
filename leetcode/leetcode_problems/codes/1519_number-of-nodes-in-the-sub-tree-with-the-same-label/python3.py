"""
Problem: Number of Nodes in the Sub-Tree With the Same Label
Difficulty: Medium
Tags: array, string, tree, graph, hash, search

Approach: DFS - return count of each label in subtree, count current node's label
Time Complexity: O(n * 26) where n is number of nodes
Space Complexity: O(n) for tree
"""

from collections import defaultdict, Counter

class Solution:
    def countSubTrees(self, n: int, edges: List[List[int]], labels: str) -> List[int]:
        tree = defaultdict(list)
        for u, v in edges:
            tree[u].append(v)
            tree[v].append(u)
        
        result = [0] * n
        
        def dfs(node, parent):
            count = Counter()
            count[labels[node]] = 1
            
            for child in tree[node]:
                if child != parent:
                    child_count = dfs(child, node)
                    count += child_count
            
            result[node] = count[labels[node]]
            return count
        
        dfs(0, -1)
        return result