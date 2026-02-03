"""
Problem: Step-By-Step Directions From a Binary Tree Node to Another
Difficulty: Medium
Tags: string, tree, DFS, LCA

Approach: Find paths to both nodes, find LCA, construct path
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(h) where h is height
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def getDirections(self, root: Optional[TreeNode], startValue: int, destValue: int) -> str:
        def findPath(node, target, path):
            if not node:
                return False
            if node.val == target:
                return True
            
            path.append('L')
            if findPath(node.left, target, path):
                return True
            path.pop()
            
            path.append('R')
            if findPath(node.right, target, path):
                return True
            path.pop()
            
            return False
        
        start_path = []
        dest_path = []
        findPath(root, startValue, start_path)
        findPath(root, destValue, dest_path)
        
        # Find common prefix
        i = 0
        while i < len(start_path) and i < len(dest_path) and start_path[i] == dest_path[i]:
            i += 1
        
        # Go up from start to LCA, then down to dest
        result = 'U' * (len(start_path) - i) + ''.join(dest_path[i:])
        return result