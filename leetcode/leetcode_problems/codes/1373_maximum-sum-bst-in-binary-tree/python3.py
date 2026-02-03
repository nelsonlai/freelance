"""
Problem: Maximum Sum BST in Binary Tree
Difficulty: Hard
Tags: tree, dp, search

Approach: DFS - return (isBST, min, max, sum) for each subtree
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
    def maxSumBST(self, root: Optional[TreeNode]) -> int:
        max_sum = 0
        
        def dfs(node):
            nonlocal max_sum
            if not node:
                return (True, float('inf'), float('-inf'), 0)
            
            left_valid, left_min, left_max, left_sum = dfs(node.left)
            right_valid, right_min, right_max, right_sum = dfs(node.right)
            
            if left_valid and right_valid and left_max < node.val < right_min:
                total_sum = left_sum + right_sum + node.val
                max_sum = max(max_sum, total_sum)
                return (True, min(left_min, node.val), max(right_max, node.val), total_sum)
            
            return (False, 0, 0, 0)
        
        dfs(root)
        return max_sum