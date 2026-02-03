"""
Problem: Two Sum IV - Input is a BST
Difficulty: Easy
Tags: array, tree, hash, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def findTarget(self, root: Optional[TreeNode], k: int) -> bool:
        seen = set()
        
        def dfs(node):
            if not node:
                return False
            
            if k - node.val in seen:
                return True
            
            seen.add(node.val)
            return dfs(node.left) or dfs(node.right)
        
        return dfs(root)