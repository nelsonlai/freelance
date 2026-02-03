"""
Problem: All Elements in Two Binary Search Trees
Difficulty: Medium
Tags: tree, sort, search

Approach: Inorder traversal of both trees, merge two sorted lists
Time Complexity: O(n + m) where n, m are tree sizes
Space Complexity: O(n + m) for lists
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def getAllElements(self, root1: Optional[TreeNode], root2: Optional[TreeNode]) -> List[int]:
        def inorder(node):
            if not node:
                return []
            return inorder(node.left) + [node.val] + inorder(node.right)
        
        list1 = inorder(root1)
        list2 = inorder(root2)
        
        result = []
        i = j = 0
        while i < len(list1) and j < len(list2):
            if list1[i] <= list2[j]:
                result.append(list1[i])
                i += 1
            else:
                result.append(list2[j])
                j += 1
        
        result.extend(list1[i:])
        result.extend(list2[j:])
        return result