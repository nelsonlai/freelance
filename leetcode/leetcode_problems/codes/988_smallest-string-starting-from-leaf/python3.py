"""
Problem: Smallest String Starting From Leaf
Difficulty: Medium
Tags: string, tree, graph, search

Approach: DFS - collect all root-to-leaf strings, return lexicographically smallest
Time Complexity: O(n * h) where h is height
Space Complexity: O(h) for recursion stack
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def smallestFromLeaf(self, root: Optional[TreeNode]) -> str:
        self.result = None
        
        def dfs(node, path):
            if not node:
                return
            
            path.append(chr(ord('a') + node.val))
            
            if not node.left and not node.right:
                s = ''.join(reversed(path))
                if self.result is None or s < self.result:
                    self.result = s
            else:
                dfs(node.left, path)
                dfs(node.right, path)
            
            path.pop()
        
        dfs(root, [])
        return self.result