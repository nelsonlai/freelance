# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def pruneTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        def hasOne(node):
            if not node:
                return False
            leftHas = hasOne(node.left)
            rightHas = hasOne(node.right)
            if not leftHas:
                node.left = None
            if not rightHas:
                node.right = None
            return node.val == 1 or leftHas or rightHas
        
        return root if hasOne(root) else None
