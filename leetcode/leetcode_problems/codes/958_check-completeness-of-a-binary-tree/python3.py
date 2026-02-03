"""
Problem: Check Completeness of a Binary Tree
Difficulty: Medium
Tags: tree, search

Approach: BFS - check if all nodes before a null are non-null
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
    def isCompleteTree(self, root: Optional[TreeNode]) -> bool:
        queue = deque([root])
        seen_null = False
        
        while queue:
            node = queue.popleft()
            
            if node is None:
                seen_null = True
            else:
                if seen_null:
                    return False
                queue.append(node.left)
                queue.append(node.right)
        
        return True