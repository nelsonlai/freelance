"""
Problem: Binary Tree Cameras
Difficulty: Hard
Tags: tree, dp, search

Approach: Greedy DFS - place cameras at parent of uncovered leaves
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
    def minCameraCover(self, root: Optional[TreeNode]) -> int:
        self.cameras = 0
        
        # 0: uncovered, 1: covered, 2: has camera
        def dfs(node):
            if not node:
                return 1  # covered
            
            left = dfs(node.left)
            right = dfs(node.right)
            
            if left == 0 or right == 0:
                self.cameras += 1
                return 2  # place camera
            
            if left == 2 or right == 2:
                return 1  # covered by child camera
            
            return 0  # uncovered
        
        if dfs(root) == 0:
            self.cameras += 1
        
        return self.cameras