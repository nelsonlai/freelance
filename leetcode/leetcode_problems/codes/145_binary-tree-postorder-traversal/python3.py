"""
Problem: Binary Tree Postorder Traversal
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
class Solution:
    def postorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        result = []
        stack = []
        current = root
        last_visited = None
        
        while current or stack:
            while current:
                stack.append(current)
                current = current.left
            
            peek = stack[-1]
            if peek.right and last_visited != peek.right:
                current = peek.right
            else:
                result.append(peek.val)
                last_visited = stack.pop()
        
        return result