"""
Problem: Binary Tree Tilt
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
    def findTilt(self, root: Optional[TreeNode]) -> int:
        self.total_tilt = 0
        
        def sum_tree(node):
            if not node:
                return 0
            
            left_sum = sum_tree(node.left)
            right_sum = sum_tree(node.right)
            self.total_tilt += abs(left_sum - right_sum)
            
            return node.val + left_sum + right_sum
        
        sum_tree(root)
        return self.total_tilt