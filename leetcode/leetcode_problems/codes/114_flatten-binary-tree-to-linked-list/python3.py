"""
Problem: Flatten Binary Tree to Linked List
Difficulty: Medium
Tags: tree, search, linked_list, stack

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
    def flatten(self, root: Optional[TreeNode]) -> None:
        if not root:
            return
        
        self.flatten(root.left)
        self.flatten(root.right)
        
        if root.left:
            right = root.right
            root.right = root.left
            root.left = None
            
            while root.right:
                root = root.right
            root.right = right