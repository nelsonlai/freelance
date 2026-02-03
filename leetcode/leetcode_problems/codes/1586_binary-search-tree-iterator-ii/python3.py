"""
Problem: Binary Search Tree Iterator II
Difficulty: Medium
Tags: tree, search, stack

Approach: Store all nodes in list via inorder traversal, track current index
Time Complexity: O(n) for init, O(1) for operations
Space Complexity: O(n) for node list
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class BSTIterator:

    def __init__(self, root: Optional[TreeNode]):
        self.nodes = []
        self.idx = -1
        
        def inorder(node):
            if node:
                inorder(node.left)
                self.nodes.append(node.val)
                inorder(node.right)
        
        inorder(root)

    def hasNext(self) -> bool:
        return self.idx < len(self.nodes) - 1

    def next(self) -> int:
        self.idx += 1
        return self.nodes[self.idx]

    def hasPrev(self) -> bool:
        return self.idx > 0

    def prev(self) -> int:
        self.idx -= 1
        return self.nodes[self.idx]