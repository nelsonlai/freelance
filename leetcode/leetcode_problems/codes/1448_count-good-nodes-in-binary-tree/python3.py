"""
Problem: Count Good Nodes in Binary Tree
Difficulty: Medium
Tags: tree, search

Approach: DFS - track max value from root, count nodes >= max
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
    def goodNodes(self, root: TreeNode) -> int:
        def dfs(node, max_val):
            if not node:
                return 0
            
            count = 1 if node.val >= max_val else 0
            new_max = max(max_val, node.val)
            count += dfs(node.left, new_max)
            count += dfs(node.right, new_max)
            return count
        
        return dfs(root, root.val)