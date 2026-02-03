"""
Problem: Range Sum of BST
Difficulty: Easy
Tags: tree, search

Approach: DFS traversal, skip subtrees outside range
Time Complexity: O(n) worst case, but can be optimized to O(log n) for balanced tree
Space Complexity: O(h) for recursion stack where h is height
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def rangeSumBST(self, root: Optional[TreeNode], low: int, high: int) -> int:
        if not root:
            return 0
        
        total = 0
        if low <= root.val <= high:
            total += root.val
        
        if root.val > low:
            total += self.rangeSumBST(root.left, low, high)
        if root.val < high:
            total += self.rangeSumBST(root.right, low, high)
        
        return total