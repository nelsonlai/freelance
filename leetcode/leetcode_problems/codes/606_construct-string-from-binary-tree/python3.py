"""
Problem: Construct String from Binary Tree
Difficulty: Medium
Tags: string, tree, search

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def tree2str(self, root: Optional[TreeNode]) -> str:
        if not root:
            return ""
        
        result = str(root.val)
        
        if root.left or root.right:
            result += "(" + self.tree2str(root.left) + ")"
        
        if root.right:
            result += "(" + self.tree2str(root.right) + ")"
        
        return result