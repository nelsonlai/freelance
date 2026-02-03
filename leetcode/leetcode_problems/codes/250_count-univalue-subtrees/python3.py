"""
Problem: Count Univalue Subtrees
Difficulty: Medium
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
    def countUnivalSubtrees(self, root: Optional[TreeNode]) -> int:
        self.count = 0
        
        def isUnival(node):
            if not node:
                return True
            
            left = isUnival(node.left)
            right = isUnival(node.right)
            
            if not left or not right:
                return False
            
            if node.left and node.left.val != node.val:
                return False
            if node.right and node.right.val != node.val:
                return False
            
            self.count += 1
            return True
        
        isUnival(root)
        return self.count