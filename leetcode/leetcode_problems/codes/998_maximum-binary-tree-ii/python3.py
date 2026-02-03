"""
Problem: Maximum Binary Tree II
Difficulty: Medium
Tags: tree

Approach: Insert val at rightmost path where it's greater than parent
Time Complexity: O(h) where h is height
Space Complexity: O(h) for recursion stack
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def insertIntoMaxTree(self, root: Optional[TreeNode], val: int) -> Optional[TreeNode]:
        if not root or val > root.val:
            new_node = TreeNode(val)
            new_node.left = root
            return new_node
        
        root.right = self.insertIntoMaxTree(root.right, val)
        return root