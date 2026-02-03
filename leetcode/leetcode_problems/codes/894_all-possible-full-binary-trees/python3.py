# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def allPossibleFBT(self, n: int) -> List[Optional[TreeNode]]:
        if n % 2 == 0:
            return []
        if n == 1:
            return [TreeNode(0)]
        
        result = []
        for i in range(1, n, 2):
            for left in self.allPossibleFBT(i):
                for right in self.allPossibleFBT(n - 1 - i):
                    root = TreeNode(0)
                    root.left = left
                    root.right = right
                    result.append(root)
        
        return result
