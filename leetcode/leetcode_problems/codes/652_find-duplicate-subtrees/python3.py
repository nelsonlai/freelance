"""
Problem: Find Duplicate Subtrees
Difficulty: Medium
Tags: tree, hash, search

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
from collections import defaultdict

class Solution:
    def findDuplicateSubtrees(self, root: Optional[TreeNode]) -> List[Optional[TreeNode]]:
        count = defaultdict(int)
        result = []
        
        def serialize(node):
            if not node:
                return "#"
            
            serial = f"{node.val},{serialize(node.left)},{serialize(node.right)}"
            count[serial] += 1
            
            if count[serial] == 2:
                result.append(node)
            
            return serial
        
        serialize(root)
        return result