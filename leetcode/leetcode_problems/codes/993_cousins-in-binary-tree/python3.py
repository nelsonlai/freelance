"""
Problem: Cousins in Binary Tree
Difficulty: Easy
Tags: tree, search

Approach: BFS - find depth and parent of x and y, check if same depth but different parents
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(n) for queue
"""

from collections import deque

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def isCousins(self, root: Optional[TreeNode], x: int, y: int) -> bool:
        x_info = y_info = None
        
        queue = deque([(root, None, 0)])
        
        while queue:
            node, parent, depth = queue.popleft()
            
            if node.val == x:
                x_info = (parent, depth)
            if node.val == y:
                y_info = (parent, depth)
            
            if node.left:
                queue.append((node.left, node, depth + 1))
            if node.right:
                queue.append((node.right, node, depth + 1))
        
        if x_info and y_info:
            return x_info[1] == y_info[1] and x_info[0] != y_info[0]
        
        return False