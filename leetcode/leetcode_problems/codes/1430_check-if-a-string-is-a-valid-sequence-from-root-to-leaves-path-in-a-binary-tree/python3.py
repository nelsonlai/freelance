"""
Problem: Check If a String Is a Valid Sequence from Root to Leaves Path in a Binary Tree
Difficulty: Medium
Tags: array, string, tree, search

Approach: DFS - check if path matches array and ends at leaf
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
    def isValidSequence(self, root: Optional[TreeNode], arr: List[int]) -> bool:
        def dfs(node, idx):
            if not node or idx >= len(arr) or node.val != arr[idx]:
                return False
            
            if idx == len(arr) - 1:
                return not node.left and not node.right
            
            return dfs(node.left, idx + 1) or dfs(node.right, idx + 1)
        
        return dfs(root, 0)