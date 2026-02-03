"""
Problem: Binary Tree Paths
Difficulty: Easy
Tags: string, tree, search

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
    def binaryTreePaths(self, root: Optional[TreeNode]) -> List[str]:
        result = []
        
        def dfs(node, path):
            if not node:
                return
            
            path.append(str(node.val))
            
            if not node.left and not node.right:
                result.append('->'.join(path))
            else:
                dfs(node.left, path)
                dfs(node.right, path)
            
            path.pop()
        
        dfs(root, [])
        return result