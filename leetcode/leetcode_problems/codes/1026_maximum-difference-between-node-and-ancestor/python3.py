"""
Problem: Maximum Difference Between Node and Ancestor
Difficulty: Medium
Tags: tree, search

Approach: DFS - track min and max values in path, update max difference
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
    def maxAncestorDiff(self, root: Optional[TreeNode]) -> int:
        self.max_diff = 0
        
        def dfs(node, min_val, max_val):
            if not node:
                return
            
            min_val = min(min_val, node.val)
            max_val = max(max_val, node.val)
            self.max_diff = max(self.max_diff, max_val - min_val)
            
            dfs(node.left, min_val, max_val)
            dfs(node.right, min_val, max_val)
        
        dfs(root, root.val, root.val)
        return self.max_diff