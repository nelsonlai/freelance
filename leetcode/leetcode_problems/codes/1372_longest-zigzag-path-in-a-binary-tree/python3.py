"""
Problem: Longest ZigZag Path in a Binary Tree
Difficulty: Medium
Tags: tree, dp, search

Approach: DFS - track longest path going left and right from each node
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(h) for recursion stack
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def longestZigZag(self, root: Optional[TreeNode]) -> int:
        max_path = 0
        
        def dfs(node, go_left, length):
            nonlocal max_path
            if not node:
                return
            
            max_path = max(max_path, length)
            
            if go_left:
                dfs(node.left, False, length + 1)
                dfs(node.right, True, 1)
            else:
                dfs(node.right, True, length + 1)
                dfs(node.left, False, 1)
        
        dfs(root, True, 0)
        dfs(root, False, 0)
        return max_path