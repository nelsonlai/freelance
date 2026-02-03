"""
Problem: Closest Binary Search Tree Value
Difficulty: Easy
Tags: tree, search

Approach: DFS or BFS traversal
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
    def closestValue(self, root: Optional[TreeNode], target: float) -> int:
        closest = root.val
        
        while root:
            if abs(root.val - target) < abs(closest - target):
                closest = root.val
            
            if target < root.val:
                root = root.left
            else:
                root = root.right
        
        return closest