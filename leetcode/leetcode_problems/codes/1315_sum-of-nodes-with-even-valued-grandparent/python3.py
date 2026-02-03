"""
Problem: Sum of Nodes with Even-Valued Grandparent
Difficulty: Medium
Tags: tree, dp, search

Approach: DFS - pass parent and grandparent values, sum if grandparent is even
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(h) for recursion stack
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def sumEvenGrandparent(self, root: Optional[TreeNode]) -> int:
        def dfs(node, parent, grandparent):
            if not node:
                return 0
            
            total = 0
            if grandparent and grandparent % 2 == 0:
                total += node.val
            
            total += dfs(node.left, node.val, parent)
            total += dfs(node.right, node.val, parent)
            return total
        
        return dfs(root, None, None)