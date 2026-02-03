"""
Problem: Delete Tree Nodes
Difficulty: Medium
Tags: array, tree, search

Approach: Build tree, DFS to calculate subtree sums, count nodes with non-zero sum
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(n) for tree
"""

from collections import defaultdict

class Solution:
    def deleteTreeNodes(self, nodes: int, parent: List[int], value: List[int]) -> int:
        children = defaultdict(list)
        for i in range(nodes):
            if parent[i] != -1:
                children[parent[i]].append(i)
        
        def dfs(node):
            total_sum = value[node]
            count = 1
            
            for child in children[node]:
                child_sum, child_count = dfs(child)
                total_sum += child_sum
                count += child_count
            
            if total_sum == 0:
                return 0, 0
            
            return total_sum, count
        
        _, result = dfs(0)
        return result