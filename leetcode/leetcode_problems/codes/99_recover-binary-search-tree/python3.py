"""
Problem: Recover Binary Search Tree
Difficulty: Medium
Tags: tree, search

Approach: DFS or BFS traversal
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(h) for recursion stack where h is height
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def recoverTree(self, root: Optional[TreeNode]) -> None:
        first = None
        second = None
        prev = None
        
        def inorder(node):
            nonlocal first, second, prev
            if not node:
                return
            
            inorder(node.left)
            
            if prev and prev.val > node.val:
                if not first:
                    first = prev
                second = node
            
            prev = node
            inorder(node.right)
        
        inorder(root)
        first.val, second.val = second.val, first.val