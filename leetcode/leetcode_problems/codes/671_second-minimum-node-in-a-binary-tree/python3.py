"""
Problem: Second Minimum Node In a Binary Tree
Difficulty: Easy
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
    def findSecondMinimumValue(self, root: Optional[TreeNode]) -> int:
        if not root:
            return -1
        
        def dfs(node):
            if not node:
                return float('inf')
            
            if node.val > root.val:
                return node.val
            
            left = dfs(node.left)
            right = dfs(node.right)
            
            return min(left, right)
        
        result = dfs(root)
        return -1 if result == float('inf') else result