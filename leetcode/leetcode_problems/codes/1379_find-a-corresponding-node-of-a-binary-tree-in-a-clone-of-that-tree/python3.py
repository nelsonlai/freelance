"""
Problem: Find a Corresponding Node of a Binary Tree in a Clone of That Tree
Difficulty: Easy
Tags: tree, search

Approach: DFS - traverse both trees simultaneously, return cloned node when found
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(h) for recursion stack
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def getTargetCopy(self, original: TreeNode, cloned: TreeNode, target: TreeNode) -> TreeNode:
        if not original:
            return None
        
        if original == target:
            return cloned
        
        left = self.getTargetCopy(original.left, cloned.left, target)
        if left:
            return left
        
        return self.getTargetCopy(original.right, cloned.right, target)