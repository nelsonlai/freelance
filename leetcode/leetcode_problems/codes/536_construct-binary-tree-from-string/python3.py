"""
Problem: Construct Binary Tree from String
Difficulty: Medium
Tags: string, tree, search, stack

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def str2tree(self, s: str) -> Optional[TreeNode]:
        if not s:
            return None
        
        i = 0
        while i < len(s) and (s[i].isdigit() or s[i] == '-'):
            i += 1
        
        val = int(s[:i])
        root = TreeNode(val)
        
        if i < len(s) and s[i] == '(':
            i += 1
            start = i
            count = 1
            while i < len(s) and count > 0:
                if s[i] == '(':
                    count += 1
                elif s[i] == ')':
                    count -= 1
                i += 1
            root.left = self.str2tree(s[start:i-1])
        
        if i < len(s) and s[i] == '(':
            i += 1
            start = i
            count = 1
            while i < len(s) and count > 0:
                if s[i] == '(':
                    count += 1
                elif s[i] == ')':
                    count -= 1
                i += 1
            root.right = self.str2tree(s[start:i-1])
        
        return root