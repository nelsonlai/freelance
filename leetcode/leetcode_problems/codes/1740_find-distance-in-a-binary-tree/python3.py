"""
Problem: Find Distance in a Binary Tree
Difficulty: Medium
Tags: tree, hash, search, lca

Approach: Find LCA, calculate distance from LCA to both nodes
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
    def findDistance(self, root: Optional[TreeNode], p: int, q: int) -> int:
        def find_lca(node):
            if not node or node.val == p or node.val == q:
                return node
            
            left = find_lca(node.left)
            right = find_lca(node.right)
            
            if left and right:
                return node
            return left or right
        
        def distance(node, target, dist):
            if not node:
                return -1
            if node.val == target:
                return dist
            
            left = distance(node.left, target, dist + 1)
            if left != -1:
                return left
            return distance(node.right, target, dist + 1)
        
        lca = find_lca(root)
        return distance(lca, p, 0) + distance(lca, q, 0)