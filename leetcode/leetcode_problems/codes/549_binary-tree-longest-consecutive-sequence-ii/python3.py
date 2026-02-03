"""
Problem: Binary Tree Longest Consecutive Sequence II
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
        
        def dfs(node):
            if not node:
                return 0, 0
            
            inc, dec = 1, 1
            
            if node.left:
                left_inc, left_dec = dfs(node.left)
                if node.val == node.left.val + 1:
                    inc = max(inc, left_inc + 1)
                if node.val == node.left.val - 1:
                    dec = max(dec, left_dec + 1)
            
            if node.right:
                right_inc, right_dec = dfs(node.right)
                if node.val == node.right.val + 1:
                    inc = max(inc, right_inc + 1)
                if node.val == node.right.val - 1:
                    dec = max(dec, right_dec + 1)
            
            self.max_length = max(self.max_length, inc + dec - 1)
            return inc, dec
        
        dfs(root)
        return self.max_length