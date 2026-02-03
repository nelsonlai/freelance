"""
Problem: Pseudo-Palindromic Paths in a Binary Tree
Difficulty: Medium
Tags: string, tree, search

Approach: DFS - track digit counts, check if at most one odd count at leaf
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
    def pseudoPalindromicPaths (self, root: Optional[TreeNode]) -> int:
        count = [0] * 10
        
        def dfs(node):
            if not node:
                return 0
            
            count[node.val] += 1
            
            if not node.left and not node.right:
                odd_count = sum(1 for c in count if c % 2 == 1)
                count[node.val] -= 1
                return 1 if odd_count <= 1 else 0
            
            result = dfs(node.left) + dfs(node.right)
            count[node.val] -= 1
            return result
        
        return dfs(root)