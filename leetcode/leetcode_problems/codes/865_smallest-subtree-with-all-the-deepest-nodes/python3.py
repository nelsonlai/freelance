# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def subtreeWithAllDeepest(self, root: TreeNode) -> TreeNode:
        def dfs(node):
            if not node:
                return (None, 0)
            left, ldepth = dfs(node.left)
            right, rdepth = dfs(node.right)
            if ldepth > rdepth:
                return (left, ldepth + 1)
            if rdepth > ldepth:
                return (right, rdepth + 1)
            return (node, ldepth + 1)
        
        return dfs(root)[0]
