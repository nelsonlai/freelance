"""
Problem: Boundary of Binary Tree
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
    def boundaryOfBinaryTree(self, root: Optional[TreeNode]) -> List[int]:
        if not root:
            return []
        
        if not root.left and not root.right:
            return [root.val]
        
        result = [root.val]
        
        def left_boundary(node):
            if not node or (not node.left and not node.right):
                return
            result.append(node.val)
            if node.left:
                left_boundary(node.left)
            else:
                left_boundary(node.right)
        
        def leaves(node):
            if not node:
                return
            if not node.left and not node.right:
                result.append(node.val)
                return
            leaves(node.left)
            leaves(node.right)
        
        def right_boundary(node):
            if not node or (not node.left and not node.right):
                return
            if node.right:
                right_boundary(node.right)
            else:
                right_boundary(node.left)
            result.append(node.val)
        
        if root.left:
            left_boundary(root.left)
        leaves(root)
        if root.right:
            right_boundary(root.right)
        
        return result