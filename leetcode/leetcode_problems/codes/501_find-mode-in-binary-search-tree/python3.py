"""
Problem: Find Mode in Binary Search Tree
Difficulty: Easy
Tags: tree, search, stack

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
    def findMode(self, root: Optional[TreeNode]) -> List[int]:
        count = defaultdict(int)
        
        def inorder(node):
            if node:
                inorder(node.left)
                count[node.val] += 1
                inorder(node.right)
        
        inorder(root)
        
        if not count:
            return []
        
        max_count = max(count.values())
        return [val for val, cnt in count.items() if cnt == max_count]