"""
Problem: Closest Binary Search Tree Value II
Difficulty: Hard
Tags: array, tree, search, stack, queue, heap

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
from collections import deque

class Solution:
    def closestKValues(self, root: Optional[TreeNode], target: float, k: int) -> List[int]:
        def inorder(node):
            if not node:
                return
            inorder(node.left)
            if len(result) < k:
                result.append(node.val)
            else:
                if abs(node.val - target) < abs(result[0] - target):
                    result.popleft()
                    result.append(node.val)
                else:
                    return
            inorder(node.right)
        
        result = deque()
        inorder(root)
        return list(result)