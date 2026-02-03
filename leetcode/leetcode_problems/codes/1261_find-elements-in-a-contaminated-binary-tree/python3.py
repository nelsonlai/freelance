"""
Problem: Find Elements in a Contaminated Binary Tree
Difficulty: Medium
Tags: tree, hash, search

Approach: Recover tree values (left=2*val+1, right=2*val+2), store in set for O(1) lookup
Time Complexity: O(n) for init, O(1) for find
Space Complexity: O(n) for set
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class FindElements:

    def __init__(self, root: Optional[TreeNode]):
        self.values = set()
        
        def recover(node, val):
            if not node:
                return
            node.val = val
            self.values.add(val)
            recover(node.left, 2 * val + 1)
            recover(node.right, 2 * val + 2)
        
        recover(root, 0)

    def find(self, target: int) -> bool:
        return target in self.values