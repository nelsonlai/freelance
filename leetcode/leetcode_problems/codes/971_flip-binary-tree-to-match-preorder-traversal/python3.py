"""
Problem: Flip Binary Tree To Match Preorder Traversal
Difficulty: Medium
Tags: tree, search

Approach: DFS - try matching voyage, flip if needed
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
    def flipMatchVoyage(self, root: Optional[TreeNode], voyage: List[int]) -> List[int]:
        self.idx = 0
        self.flips = []
        
        def dfs(node):
            if not node:
                return True
            
            if node.val != voyage[self.idx]:
                return False
            
            self.idx += 1
            
            if node.left and node.left.val != voyage[self.idx]:
                self.flips.append(node.val)
                return dfs(node.right) and dfs(node.left)
            
            return dfs(node.left) and dfs(node.right)
        
        return self.flips if dfs(root) else [-1]