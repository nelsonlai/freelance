"""
Problem: Lowest Common Ancestor of a Binary Tree II
Difficulty: Medium
Tags: tree, search, dfs

Approach: DFS - count how many of p and q are found in subtree, return node where count == 2
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(h) for recursion stack where h is height
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        self.lca = None
        
        def dfs(node):
            if not node:
                return 0
            
            count = 0
            if node == p or node == q:
                count += 1
            
            count += dfs(node.left)
            count += dfs(node.right)
            
            if count == 2 and self.lca is None:
                self.lca = node
            
            return count
        
        dfs(root)
        return self.lca