"""
Problem: Construct Binary Search Tree from Preorder Traversal
Difficulty: Medium
Tags: array, tree, search, stack

Approach: Recursive - use upper bound to determine where to split left and right subtrees
Time Complexity: O(n)
Space Complexity: O(h) for recursion stack where h is height
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def bstFromPreorder(self, preorder: List[int]) -> Optional[TreeNode]:
        self.idx = 0
        
        def build(upper_bound):
            if self.idx >= len(preorder) or preorder[self.idx] > upper_bound:
                return None
            
            node = TreeNode(preorder[self.idx])
            self.idx += 1
            
            node.left = build(node.val)
            node.right = build(upper_bound)
            
            return node
        
        return build(float('inf'))