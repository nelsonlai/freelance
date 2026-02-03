"""
Problem: Lowest Common Ancestor of a Binary Tree IV
Difficulty: Medium
Tags: array, tree, hash, search, dfs

Approach: DFS - count how many target nodes are in subtree, return node where count == len(nodes)
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(h) for recursion stack
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def lowestCommonAncestor(self, root: 'TreeNode', nodes: 'List[TreeNode]') -> 'TreeNode':
        node_set = set(nodes)
        self.lca = None
        
        def dfs(node):
            if not node:
                return 0
            
            count = 0
            if node in node_set:
                count += 1
            
            count += dfs(node.left)
            count += dfs(node.right)
            
            if count == len(nodes) and self.lca is None:
                self.lca = node
            
            return count
        
        dfs(root)
        return self.lca