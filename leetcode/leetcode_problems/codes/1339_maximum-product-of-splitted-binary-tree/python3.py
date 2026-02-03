"""
Problem: Maximum Product of Splitted Binary Tree
Difficulty: Medium
Tags: tree, search

Approach: Calculate total sum, DFS to find subtree sums, maximize product
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
    def maxProduct(self, root: Optional[TreeNode]) -> int:
        MOD = 10**9 + 7
        
        def total_sum(node):
            if not node:
                return 0
            return node.val + total_sum(node.left) + total_sum(node.right)
        
        total = total_sum(root)
        max_product = 0
        
        def dfs(node):
            nonlocal max_product
            if not node:
                return 0
            
            subtree_sum = node.val + dfs(node.left) + dfs(node.right)
            product = subtree_sum * (total - subtree_sum)
            max_product = max(max_product, product)
            return subtree_sum
        
        dfs(root)
        return max_product % MOD