"""
Problem: Distribute Coins in Binary Tree
Difficulty: Medium
Tags: tree, search

Approach: DFS - return excess coins from subtree, moves = sum of absolute excess
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
    def distributeCoins(self, root: Optional[TreeNode]) -> int:
        self.moves = 0
        
        def dfs(node):
            if not node:
                return 0
            
            left_excess = dfs(node.left)
            right_excess = dfs(node.right)
            
            self.moves += abs(left_excess) + abs(right_excess)
            
            return node.val + left_excess + right_excess - 1
        
        dfs(root)
        return self.moves