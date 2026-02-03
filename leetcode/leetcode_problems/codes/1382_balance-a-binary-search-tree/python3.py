"""
Problem: Balance a Binary Search Tree
Difficulty: Medium
Tags: tree, greedy, search

Approach: Inorder traversal to get sorted list, build balanced BST from middle
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(n) for sorted list
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def balanceBST(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        def inorder(node):
            if not node:
                return []
            return inorder(node.left) + [node.val] + inorder(node.right)
        
        def buildBST(vals):
            if not vals:
                return None
            mid = len(vals) // 2
            node = TreeNode(vals[mid])
            node.left = buildBST(vals[:mid])
            node.right = buildBST(vals[mid+1:])
            return node
        
        sorted_vals = inorder(root)
        return buildBST(sorted_vals)