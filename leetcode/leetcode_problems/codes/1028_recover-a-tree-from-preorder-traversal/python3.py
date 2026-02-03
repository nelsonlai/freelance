"""
Problem: Recover a Tree From Preorder Traversal
Difficulty: Hard
Tags: string, tree, search

Approach: Parse string to extract depth and value, use stack to build tree
Time Complexity: O(n) where n is string length
Space Complexity: O(h) for stack where h is height
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def recoverFromPreorder(self, traversal: str) -> Optional[TreeNode]:
        stack = []
        i = 0
        
        while i < len(traversal):
            depth = 0
            while i < len(traversal) and traversal[i] == '-':
                depth += 1
                i += 1
            
            num_str = []
            while i < len(traversal) and traversal[i].isdigit():
                num_str.append(traversal[i])
                i += 1
            val = int(''.join(num_str))
            
            node = TreeNode(val)
            
            while len(stack) > depth:
                stack.pop()
            
            if stack:
                if stack[-1].left is None:
                    stack[-1].left = node
                else:
                    stack[-1].right = node
            
            stack.append(node)
        
        return stack[0] if stack else None