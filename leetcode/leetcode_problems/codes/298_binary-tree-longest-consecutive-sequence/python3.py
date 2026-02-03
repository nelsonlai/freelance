"""
Problem: Binary Tree Longest Consecutive Sequence
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
    def longestConsecutive(self, root: Optional[TreeNode]) -> int:
        self.max_length = 0
        
        def dfs(node, parent_val, length):
            if not node:
                return
            
            if parent_val is not None and node.val == parent_val + 1:
                length += 1
            else:
                length = 1
            
            self.max_length = max(self.max_length, length)
            
            dfs(node.left, node.val, length)
            dfs(node.right, node.val, length)
        
        dfs(root, None, 0)
        return self.max_length