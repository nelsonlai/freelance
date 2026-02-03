"""
Problem: Largest BST Subtree
Difficulty: Medium
Tags: tree, dp, search

Approach: DFS or BFS traversal
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(n) or O(n * m) for DP table
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def largestBSTSubtree(self, root: Optional[TreeNode]) -> int:
        def dfs(node):
            if not node:
                return (0, float('inf'), float('-inf'))
            
            left_size, left_min, left_max = dfs(node.left)
            right_size, right_min, right_max = dfs(node.right)
            
            if left_max < node.val < right_min:
                return (left_size + right_size + 1, min(left_min, node.val), max(right_max, node.val))
            
            return (max(left_size, right_size), float('-inf'), float('inf'))
        
        return dfs(root)[0]