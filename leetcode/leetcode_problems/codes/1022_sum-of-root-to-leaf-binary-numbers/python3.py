"""
Problem: Sum of Root To Leaf Binary Numbers
Difficulty: Easy
Tags: tree, search

Approach: DFS - accumulate binary number from root to leaf, sum all leaf values
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
    def sumRootToLeaf(self, root: Optional[TreeNode]) -> int:
        self.total = 0
        
        def dfs(node, current):
            if not node:
                return
            
            current = current * 2 + node.val
            
            if not node.left and not node.right:
                self.total += current
            else:
                dfs(node.left, current)
                dfs(node.right, current)
        
        dfs(root, 0)
        return self.total