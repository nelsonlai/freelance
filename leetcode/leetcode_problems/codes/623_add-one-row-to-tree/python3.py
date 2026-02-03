"""
Problem: Add One Row to Tree
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
    def addOneRow(self, root: Optional[TreeNode], val: int, depth: int) -> Optional[TreeNode]:
        if depth == 1:
            new_root = TreeNode(val)
            new_root.left = root
            return new_root
        
        def dfs(node, current_depth):
            if not node:
                return
            if current_depth == depth - 1:
                left = TreeNode(val)
                right = TreeNode(val)
                left.left = node.left
                right.right = node.right
                node.left = left
                node.right = right
            else:
                dfs(node.left, current_depth + 1)
                dfs(node.right, current_depth + 1)
        
        dfs(root, 1)
        return root