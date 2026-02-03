"""
Problem: Two Sum BSTs
Difficulty: Medium
Tags: array, tree, search, stack

Approach: Store values from one BST in set, search for complement in other BST
Time Complexity: O(n + m) where n, m are sizes of trees
Space Complexity: O(n) for set
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def twoSumBSTs(self, root1: Optional[TreeNode], root2: Optional[TreeNode], target: int) -> bool:
        def collect_values(node, values):
            if not node:
                return
            values.add(node.val)
            collect_values(node.left, values)
            collect_values(node.right, values)
        
        def search_complement(node, complement_set):
            if not node:
                return False
            if target - node.val in complement_set:
                return True
            return search_complement(node.left, complement_set) or search_complement(node.right, complement_set)
        
        values1 = set()
        collect_values(root1, values1)
        return search_complement(root2, values1)