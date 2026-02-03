"""
Problem: Change the Root of a Binary Tree
Difficulty: Medium
Tags: tree, search, dfs

Approach: Traverse from leaf to root, flip parent-child relationships
Time Complexity: O(h) where h is height
Space Complexity: O(h) for recursion
"""

"""
# Definition for a Node.
class Node:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None
        self.parent = None
"""

class Solution:
    def flipBinaryTree(self, root: 'Node', leaf: 'Node') -> 'Node':
        def flip(node, prev):
            if not node:
                return
            
            old_parent = node.parent
            
            if old_parent:
                if old_parent.left == node:
                    old_parent.left = None
                else:
                    old_parent.right = None
            
            if prev:
                if node.left == prev:
                    node.left = None
                else:
                    node.right = None
                node.parent = prev
            
            if old_parent:
                if prev:
                    if prev.left is None:
                        prev.left = old_parent
                    else:
                        prev.right = old_parent
                else:
                    node.parent = old_parent
            
            if old_parent and old_parent != root:
                flip(old_parent, node)
        
        flip(leaf, None)
        return leaf