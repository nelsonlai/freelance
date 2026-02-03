"""
Problem: Lowest Common Ancestor of a Binary Tree III
Difficulty: Medium
Tags: array, tree, hash, two pointers

Approach: Find path from p and q to root, find first common node
Time Complexity: O(h) where h is height
Space Complexity: O(h) for paths
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
    def lowestCommonAncestor(self, p: 'Node', q: 'Node') -> 'Node':
        path_p = set()
        node = p
        while node:
            path_p.add(node)
            node = node.parent
        
        node = q
        while node:
            if node in path_p:
                return node
            node = node.parent
        
        return None