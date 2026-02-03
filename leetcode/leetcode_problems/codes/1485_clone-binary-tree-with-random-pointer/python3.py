"""
Problem: Clone Binary Tree With Random Pointer
Difficulty: Medium
Tags: array, tree, hash, search

Approach: DFS - create mapping, clone nodes, set random pointers
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(n) for mapping
"""

# Definition for Node.
# class Node:
#     def __init__(self, val=0, left=None, right=None, random=None):
#         self.val = val
#         self.left = left
#         self.right = right
#         self.random = random

class Solution:
    def copyRandomBinaryTree(self, root: 'Optional[Node]') -> 'Optional[NodeCopy]':
        if not root:
            return None
        
        mapping = {}
        
        def clone(node):
            if not node:
                return None
            
            if node in mapping:
                return mapping[node]
            
            new_node = NodeCopy(node.val)
            mapping[node] = new_node
            new_node.left = clone(node.left)
            new_node.right = clone(node.right)
            new_node.random = clone(node.random)
            
            return new_node
        
        return clone(root)