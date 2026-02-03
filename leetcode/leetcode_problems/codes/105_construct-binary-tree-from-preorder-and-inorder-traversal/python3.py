"""
Problem: Construct Binary Tree from Preorder and Inorder Traversal
Difficulty: Medium
Tags: array, tree, hash

Approach: Use two pointers or sliding window technique
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
    def buildTree(self, preorder: List[int], inorder: List[int]) -> Optional[TreeNode]:
        if not preorder or not inorder:
            return None
        
        root_val = preorder[0]
        root = TreeNode(root_val)
        root_index = inorder.index(root_val)
        
        root.left = self.buildTree(preorder[1:1+root_index], inorder[:root_index])
        root.right = self.buildTree(preorder[1+root_index:], inorder[root_index+1:])
        
        return root