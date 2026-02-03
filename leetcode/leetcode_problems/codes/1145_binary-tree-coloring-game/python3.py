"""
Problem: Binary Tree Coloring Game
Difficulty: Medium
Tags: tree, search

Approach: Find node x, calculate sizes of left, right, and parent subtrees
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
    def btreeGameWinningMove(self, root: Optional[TreeNode], n: int, x: int) -> bool:
        left_size = 0
        right_size = 0
        
        def dfs(node):
            if not node:
                return 0
            
            left = dfs(node.left)
            right = dfs(node.right)
            
            if node.val == x:
                nonlocal left_size, right_size
                left_size = left
                right_size = right
            
            return left + right + 1
        
        dfs(root)
        parent_size = n - left_size - right_size - 1
        
        # Player 2 can choose left, right, or parent subtree
        # Need to block more than half of nodes
        return max(left_size, right_size, parent_size) > n // 2